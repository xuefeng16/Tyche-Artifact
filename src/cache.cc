/*
 *    Copyright 2023 The ChampSim Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "cache.h"

#include <algorithm>
#include <iterator>

#include "champsim.h"
#include "champsim_constants.h"
#include "util.h"
#include "vmem.h"
#include "memory_data.h"
#include "prefetch.h"

#ifndef SANITY_CHECK
#define NDEBUG
#endif

#define PRINT_INSTR_ID  0xffffffffffffffff
#define PRINT_INSTR_PC  0xffffffffffffffff
#define nPRINT_HANDLE_READ_TRACE
#define nPRINT_READ_MISS_TRACE
#define nPRINT_HANDLE_PREF_TRACE
#define nPRINT_HANDLE_FILL_TRACE
#define PRINT_PREF_LINE_TRACE XF_DEBUG
#define nPRINT_VA_TRANS_TRACE
#define nPRINT_ADD_RQ_TRACE
#define nPRINT_ADD_PQ_TRACE
#define nPRINT_TRACE
#define nCHECK_MEM_WRITE

bool start_print = true;
extern uint8_t trace_type;

extern VirtualMemory vmem;
extern uint8_t warmup_complete[NUM_CPUS];

extern uint64_t ima_pref_num;
extern uint64_t ima_pref_miss_num;

#ifdef MISS_COLLECT_INFO
    extern uint64_t miss_load_num;
    extern uint64_t miss_stride_num;
    extern uint64_t miss_ima_num;
    //extern uint64_t miss_ima_single_num;
    //extern uint64_t miss_ima_double_num;
    extern uint64_t miss_ima_complex_num;
    void collect_miss_info(PACKET& handle_pkt, bool miss);
#endif


void CACHE::handle_fill()
{
  while (writes_available_this_cycle > 0) {
    auto fill_mshr = MSHR.begin();
    if (fill_mshr == std::end(MSHR) || fill_mshr->event_cycle > current_cycle)
      return;

#ifdef PRINT_HANDLE_FILL_TRACE
    cout << "\t[handle_fill     ] " << NAME 
         << ", instr: " << fill_mshr->instr_id 
         << ", cycles: " << current_cycle << hex
         << ", pc: 0x" << fill_mshr->ip
         << ", vaddr: " << fill_mshr->v_address 
         << ", paddr: " << fill_mshr->address << dec
         << ", type: " << +fill_mshr->type << hex
         << ", metadata: " << fill_mshr->pf_metadata << dec
         << dec << endl;
#endif

    // find victim
    uint32_t set = get_set(fill_mshr->address);

    auto set_begin = std::next(std::begin(block), set * NUM_WAY);
    auto set_end = std::next(set_begin, NUM_WAY);
    auto first_inv = std::find_if_not(set_begin, set_end, is_valid<BLOCK>());
    uint32_t way = std::distance(set_begin, first_inv);
    if (way == NUM_WAY)
      way = impl_replacement_find_victim(fill_mshr->cpu, fill_mshr->instr_id, set, &block.data()[set * NUM_WAY], fill_mshr->ip, fill_mshr->address,
                                         fill_mshr->type);

    bool success = filllike_miss(set, way, *fill_mshr);
    if (!success)
      return;
    if (way != NUM_WAY) {
      // update processed packets
      fill_mshr->data = block[set * NUM_WAY + way].data;

      for (auto ret : fill_mshr->to_return)
        ret->return_data(&(*fill_mshr));
    }


    if(fill_mshr->instr_id  == PRINT_INSTR_ID){
        cout << "\t[handle_fill] " << NAME
             << " instr: " << fill_mshr->instr_id 
             << ", cycles: " << current_cycle << hex
             << ", vaddr: " << fill_mshr->v_address 
             << ", paddr: " << fill_mshr->address
             << ", pc: 0x" << fill_mshr->ip 
             << ", type: " << +fill_mshr->type
             << dec << endl;
    }

    MSHR.erase(fill_mshr);
    writes_available_this_cycle--;
  }
}

void CACHE::handle_writeback()
{
  while (writes_available_this_cycle > 0) {
    if (!WQ.has_ready())
      return;

    // handle the oldest entry
    PACKET& handle_pkt = WQ.front();

    // access cache
    uint32_t set = get_set(handle_pkt.address);
    uint32_t way = get_way(handle_pkt.address, set);

    BLOCK& fill_block = block[set * NUM_WAY + way];

    if (way < NUM_WAY) // HIT
    {
      impl_replacement_update_state(handle_pkt.cpu, set, way, fill_block.address, handle_pkt.ip, 0, handle_pkt.type, 1);

      // COLLECT STATS
      sim_hit[handle_pkt.cpu][handle_pkt.type]++;
      sim_access[handle_pkt.cpu][handle_pkt.type]++;

      // mark dirty
      fill_block.dirty = 1;
    } else // MISS
    {
      bool success;
      if (handle_pkt.type == RFO && handle_pkt.to_return.empty()) {
        success = readlike_miss(handle_pkt);
      } else {
        // find victim
        auto set_begin = std::next(std::begin(block), set * NUM_WAY);
        auto set_end = std::next(set_begin, NUM_WAY);
        auto first_inv = std::find_if_not(set_begin, set_end, is_valid<BLOCK>());
        way = std::distance(set_begin, first_inv);
        if (way == NUM_WAY)
          way = impl_replacement_find_victim(handle_pkt.cpu, handle_pkt.instr_id, set, &block.data()[set * NUM_WAY], handle_pkt.ip, handle_pkt.address,
                                             handle_pkt.type);

        success = filllike_miss(set, way, handle_pkt);
      }

      if (!success)
        return;
    }

    // remove this entry from WQ
    writes_available_this_cycle--;
    WQ.pop_front();
  }
}

#define TRACK_LOAD_ORDER
std::map<uint64_t, uint64_t> ip_record;
uint64_t anti_order_num = 0;

void CACHE::handle_read()
{
  while (reads_available_this_cycle > 0) {

    if (!RQ.has_ready())
      return;

    // handle the oldest entry
    PACKET& handle_pkt = RQ.front();

#ifdef PRINT_HANDLE_READ_TRACE
if(NAME=="cpu0_L1D")
    cout << "\t[handle_read     ] " << NAME
         << ", instr: " << handle_pkt.instr_id 
         << ", cycles: " << current_cycle << hex
         << ", vaddr: " << handle_pkt.v_address 
         << ", paddr: " << handle_pkt.address
         << ", pc: 0x" << handle_pkt.ip 
         << ", type: " << +handle_pkt.type
         << dec << endl;
#endif

#ifdef TRACK_LOAD_ORDER
    if(NAME=="cpu0_L1D" && handle_pkt.type==LOAD && warmup_complete[cpu]){
        if(ip_record.count(handle_pkt.ip)){
            if(handle_pkt.instr_id < ip_record[handle_pkt.ip]){
                anti_order_num++;
            } else {
                ip_record[handle_pkt.ip] = handle_pkt.instr_id;
            }
        } else {
            ip_record[handle_pkt.ip] = handle_pkt.instr_id;
        }
    }
#endif


    // A (hopefully temporary) hack to know whether to send the evicted paddr or
    // vaddr to the prefetcher
    ever_seen_data |= (handle_pkt.v_address != handle_pkt.ip);

    uint32_t set = get_set(handle_pkt.address);
    uint32_t way = get_way(handle_pkt.address, set);


if(handle_pkt.instr_id == PRINT_INSTR_ID || handle_pkt.ip  == PRINT_INSTR_PC){
    if(NAME=="cpu0_L1D")
        cout << "\t[handle_read] " << NAME 
             << " instr: " << handle_pkt.instr_id 
             << ", pc: 0x" << handle_pkt.ip 
             << ", cycles: " << current_cycle << hex
             << ", vaddr: " << handle_pkt.v_address 
             << ", paddr: " << handle_pkt.address
             << ", hit: " << +(way < NUM_WAY)
             << ", type: " << +handle_pkt.type
             << dec << endl;
}

    sim_read_access[handle_pkt.cpu][handle_pkt.type]++;
    if (way < NUM_WAY) // HIT
    {
      sim_read_hit[handle_pkt.cpu][handle_pkt.type]++;
      readlike_hit(set, way, handle_pkt);
    } else {
      sim_read_miss[handle_pkt.cpu][handle_pkt.type]++;
      bool success = readlike_miss(handle_pkt);
      if (!success)
        return;
    }

    #ifdef MISS_COLLECT_INFO
      if(NAME.rfind("L1D") != std::string::npos && handle_pkt.type == LOAD){
          collect_miss_info(handle_pkt, !(way < NUM_WAY));
      }
    #endif

    // remove this entry from RQ
    RQ.pop_front();
    reads_available_this_cycle--;
  }
}

void CACHE::handle_prefetch()
{
  uint32_t pref_available_this_cycle = 1;
   if(NAME.rfind("L1D") == std::string::npos){
     pref_available_this_cycle = reads_available_this_cycle;
  }

  while (pref_available_this_cycle > 0) {
    if (!PQ.has_ready())
      return;

    // handle the oldest entry
    PACKET& handle_pkt = PQ.front();

    uint32_t set = get_set(handle_pkt.address);
    uint32_t way = get_way(handle_pkt.address, set);

#ifdef PRINT_HANDLE_PREF_TRACE
    cout << "\t[handle_prefetch ] " << NAME
         << ", instr: " << handle_pkt.instr_id 
         << ", cycles: " << current_cycle << hex 
         << ", vaddr: " << handle_pkt.v_address 
         << ", paddr: " << handle_pkt.address << dec
         << ", hit : " << +(way < NUM_WAY)
         << ", pf_origin_level: " << +handle_pkt.pf_origin_level 
         << ", occupancy: " << PQ.occupancy()
         << endl;
#endif

    if (way < NUM_WAY) // HIT
    {
      readlike_hit(set, way, handle_pkt);
      if(NAME.rfind("L1D") != std::string::npos){
        idm_load_return(handle_pkt.cpu, handle_pkt.v_address);
      }
    } else {
      bool success = readlike_miss(handle_pkt);
      if (!success)
        return;
    }

#ifdef PRINT_TRACE
    if(NAME=="cpu0_L1D"){
        cout << "[L1D PQ.pop_front] paddr: " << hex << PQ.front().address << dec << endl;
    }
    if(NAME=="cpu0_L2C"){
        cout << "[L2C PQ.pop_front] paddr: " << hex << PQ.front().address << dec << endl;
    }
#endif

    if(NAME.rfind("L1D") != std::string::npos){
        PREF_TYPE pref_type = decode_pref_type(handle_pkt.pf_metadata);
        if(pref_type == PREF_IMD || pref_type == PREF_IMD_END){
            ima_pref_num++;
        }
    }

    // remove this entry from PQ
    PQ.pop_front();
    pref_available_this_cycle--;
  }
}

void CACHE::readlike_hit(std::size_t set, std::size_t way, PACKET& handle_pkt)
{
  DP(if (warmup_complete[handle_pkt.cpu]) {
    std::cout << "[" << NAME << "] " << __func__ << " hit";
    std::cout << " instr_id: " << handle_pkt.instr_id << " address: " << std::hex << (handle_pkt.address >> OFFSET_BITS);
    std::cout << " full_addr: " << handle_pkt.address;
    std::cout << " full_v_addr: " << handle_pkt.v_address << std::dec;
    std::cout << " type: " << +handle_pkt.type;
    std::cout << " cycle: " << current_cycle << std::endl;
  });

  BLOCK& hit_block = block[set * NUM_WAY + way];

  handle_pkt.data = hit_block.data;

  // update prefetcher on load instruction
  if (should_activate_prefetcher(handle_pkt.type) && handle_pkt.pf_origin_level < fill_level) {
    cpu = handle_pkt.cpu;
    uint64_t pf_base_addr = (virtual_prefetch ? handle_pkt.v_address : handle_pkt.address); //& ~bitmask(match_offset_bits ? 0 : OFFSET_BITS);
    handle_pkt.pf_metadata = impl_prefetcher_cache_operate(pf_base_addr, handle_pkt.ip, 1, handle_pkt.type, handle_pkt.pf_metadata);
  }

  // update replacement policy
  impl_replacement_update_state(handle_pkt.cpu, set, way, hit_block.address, handle_pkt.ip, 0, handle_pkt.type, 1);

  // COLLECT STATS
  sim_hit[handle_pkt.cpu][handle_pkt.type]++;
  sim_access[handle_pkt.cpu][handle_pkt.type]++;

  for (auto ret : handle_pkt.to_return)
    ret->return_data(&handle_pkt);

  // update prefetch stats and reset prefetch bit
  if (hit_block.prefetch) {
    pf_useful++;
    hit_block.prefetch = 0;
  }
}

bool CACHE::readlike_miss(PACKET& handle_pkt)
{
  DP(if (warmup_complete[handle_pkt.cpu]) {
    std::cout << "[" << NAME << "] " << __func__ << " miss";
    std::cout << " instr_id: " << handle_pkt.instr_id << " address: " << std::hex << (handle_pkt.address >> OFFSET_BITS);
    std::cout << " full_addr: " << handle_pkt.address;
    std::cout << " full_v_addr: " << handle_pkt.v_address << std::dec;
    std::cout << " type: " << +handle_pkt.type;
    std::cout << " cycle: " << current_cycle << std::endl;
  });

  // check mshr
  auto mshr_entry = std::find_if(MSHR.begin(), MSHR.end(), eq_addr<PACKET>(handle_pkt.address, OFFSET_BITS));
  bool mshr_full = (MSHR.size() == MSHR_SIZE);

  if (mshr_entry != MSHR.end()) // miss already inflight
  {
#ifdef PRINT_READ_MISS_TRACE
    //if((handle_pkt.address >> 6) == (0x401a4f4980 >> 6))
        cout << "[readlike_miss] Merge " << NAME
             << ", instr: " << handle_pkt.instr_id 
             << ", cycles: " << current_cycle << hex 
             << ", vaddr: " << handle_pkt.v_address 
             << ", paddr: " << handle_pkt.address
             << ", pc: 0x" << handle_pkt.ip << dec
             << ", type: " << +handle_pkt.type
             << ", pf_origin_level: " << +handle_pkt.pf_origin_level 
             << ", size: " << +handle_pkt.size << hex
             << ", metadata: " << handle_pkt.pf_metadata << dec
             << endl;
#endif
    // update fill location
    mshr_entry->fill_level = std::min(mshr_entry->fill_level, handle_pkt.fill_level);

    packet_dep_merge(mshr_entry->lq_index_depend_on_me, handle_pkt.lq_index_depend_on_me);
    packet_dep_merge(mshr_entry->sq_index_depend_on_me, handle_pkt.sq_index_depend_on_me);
    packet_dep_merge(mshr_entry->instr_depend_on_me, handle_pkt.instr_depend_on_me);
    packet_dep_merge(mshr_entry->to_return, handle_pkt.to_return);

    if (mshr_entry->type == PREFETCH && handle_pkt.type != PREFETCH) {
      // Mark the prefetch as useful
      if (mshr_entry->pf_origin_level == fill_level)
        pf_useful++;

      uint64_t prior_event_cycle = mshr_entry->event_cycle;
      auto prior_to_return = std::move(mshr_entry->to_return);
      *mshr_entry = handle_pkt;

      // in case request is already returned, we should keep event_cycle
      mshr_entry->event_cycle = prior_event_cycle;
      mshr_entry->to_return = std::move(prior_to_return);
    }
  } else {
    if (mshr_full){  // not enough MSHR resource
        MSHR_FULL++;
        return false;
    }

    bool is_read = prefetch_as_load || (handle_pkt.type != PREFETCH);

    // check to make sure the lower level queue has room for this read miss
    int queue_type = (is_read) ? 1 : 3;
    if (lower_level->get_occupancy(queue_type, handle_pkt.address) == lower_level->get_size(queue_type, handle_pkt.address))
      return false;

    // Allocate an MSHR
    if (handle_pkt.fill_level <= fill_level) {
      auto it = MSHR.insert(std::end(MSHR), handle_pkt);
      it->cycle_enqueued = current_cycle;
      it->event_cycle = std::numeric_limits<uint64_t>::max();
    }

    if (handle_pkt.fill_level <= fill_level)
      handle_pkt.to_return = {this};
    else
      handle_pkt.to_return.clear();
#ifdef PRINT_READ_MISS_TRACE
    //if((handle_pkt.address >> 6) == (0x401a4f4980 >> 6))
        cout << "[readlike_miss] New MSHR " << NAME
             << ", instr: " << handle_pkt.instr_id 
             << ", cycles: " << current_cycle << hex 
             << ", vaddr: " << handle_pkt.v_address 
             << ", paddr: " << handle_pkt.address
             << ", pc: 0x" << handle_pkt.ip << dec
             << ", type: " << +handle_pkt.type
             << ", pf_origin_level: " << +handle_pkt.pf_origin_level 
             << ", size: " << +handle_pkt.size
             << ", decode_size: " << +decode_size(handle_pkt.pf_metadata) << hex
             << ", metadata: " << handle_pkt.pf_metadata << dec
             << endl;
#endif
    if (!is_read)
      lower_level->add_pq(&handle_pkt);
    else
      lower_level->add_rq(&handle_pkt);
    
    if(handle_pkt.type == PREFETCH && handle_pkt.fill_level == fill_level)
      pf_miss_issued++;      

    if(NAME.rfind("L1D") != std::string::npos){
        PREF_TYPE pref_type = decode_pref_type(handle_pkt.pf_metadata);
        if(pref_type == PREF_IMD || pref_type == PREF_IMD_END){
            ima_pref_miss_num++;
        }
    }

  }

  // update prefetcher on load instructions and prefetches from upper levels
  if (should_activate_prefetcher(handle_pkt.type) && handle_pkt.pf_origin_level < fill_level) {
    cpu = handle_pkt.cpu;
    uint64_t pf_base_addr = (virtual_prefetch ? handle_pkt.v_address : handle_pkt.address); //& ~bitmask(match_offset_bits ? 0 : OFFSET_BITS);
    handle_pkt.pf_metadata = impl_prefetcher_cache_operate(pf_base_addr, handle_pkt.ip, 0, handle_pkt.type, handle_pkt.pf_metadata);
  }

  return true;
}

bool CACHE::filllike_miss(std::size_t set, std::size_t way, PACKET& handle_pkt)
{
  DP(if (warmup_complete[handle_pkt.cpu]) {
    std::cout << "[" << NAME << "] " << __func__ << " miss";
    std::cout << " instr_id: " << handle_pkt.instr_id << " address: " << std::hex << (handle_pkt.address >> OFFSET_BITS);
    std::cout << " full_addr: " << handle_pkt.address;
    std::cout << " full_v_addr: " << handle_pkt.v_address << std::dec;
    std::cout << " type: " << +handle_pkt.type;
    std::cout << " cycle: " << current_cycle << std::endl;
  });

  bool bypass = (way == NUM_WAY);
#ifndef LLC_BYPASS
  assert(!bypass);
#endif
  assert(handle_pkt.type != WRITEBACK || !bypass);

  BLOCK& fill_block = block[set * NUM_WAY + way];
  bool evicting_dirty = !bypass && (lower_level != NULL) && fill_block.dirty;
  uint64_t evicting_address = 0;

  if (!bypass) {
    if (evicting_dirty) {
      PACKET writeback_packet;

      writeback_packet.fill_level = lower_level->fill_level;
      writeback_packet.cpu = handle_pkt.cpu;
      writeback_packet.address = fill_block.address;
      writeback_packet.data = fill_block.data;
      writeback_packet.instr_id = handle_pkt.instr_id;
      writeback_packet.ip = 0;
      writeback_packet.type = WRITEBACK;

      auto result = lower_level->add_wq(&writeback_packet);
      if (result == -2)
        return false;
    }

    if (ever_seen_data)
      evicting_address = fill_block.address & ~bitmask(match_offset_bits ? 0 : OFFSET_BITS);
    else
      evicting_address = fill_block.v_address & ~bitmask(match_offset_bits ? 0 : OFFSET_BITS);

    if (fill_block.prefetch)
      pf_useless++;

    if (handle_pkt.type == PREFETCH)
      pf_fill++;

    fill_block.valid = true;
    fill_block.prefetch = (handle_pkt.type == PREFETCH && handle_pkt.pf_origin_level == fill_level);
    fill_block.dirty = (handle_pkt.type == WRITEBACK || (handle_pkt.type == RFO && handle_pkt.to_return.empty()));
    fill_block.address = handle_pkt.address;
    fill_block.v_address = handle_pkt.v_address;
    fill_block.data = handle_pkt.data;
    fill_block.ip = handle_pkt.ip;
    fill_block.cpu = handle_pkt.cpu;
    fill_block.instr_id = handle_pkt.instr_id;
  }

  if (warmup_complete[handle_pkt.cpu] && (handle_pkt.cycle_enqueued != 0))
    total_miss_latency += current_cycle - handle_pkt.cycle_enqueued;

  // update prefetcher
  cpu = handle_pkt.cpu;
  uint64_t addr = (virtual_prefetch ? handle_pkt.v_address : handle_pkt.address) /*& ~bitmask(match_offset_bits ? 0 : OFFSET_BITS)*/;

  handle_pkt.pf_metadata =
      impl_prefetcher_cache_fill(addr, set, way,
                                 handle_pkt.type == PREFETCH, evicting_address, handle_pkt.pf_metadata, handle_pkt.ip);

  // update replacement policy
  impl_replacement_update_state(handle_pkt.cpu, set, way, handle_pkt.address, handle_pkt.ip, 0, handle_pkt.type, 0);

  // COLLECT STATS
  sim_miss[handle_pkt.cpu][handle_pkt.type]++;
  sim_access[handle_pkt.cpu][handle_pkt.type]++;

  return true;
}

void CACHE::operate()
{
  operate_writes();
  operate_reads();

  impl_prefetcher_cycle_operate();
}

void CACHE::operate_writes()
{
  // perform all writes
  writes_available_this_cycle = MAX_WRITE;
  handle_fill();
  handle_writeback();

  WQ.operate();
}

void CACHE::operate_reads()
{
  // perform all reads
  reads_available_this_cycle = MAX_READ;
  handle_read();
  va_translate_prefetches();
  handle_prefetch();

  RQ.operate();
  PQ.operate();
  VAPQ.operate();
}

uint32_t CACHE::get_set(uint64_t address) { return ((address >> OFFSET_BITS) & bitmask(lg2(NUM_SET))); }

uint32_t CACHE::get_way(uint64_t address, uint32_t set)
{
  auto begin = std::next(block.begin(), set * NUM_WAY);
  auto end = std::next(begin, NUM_WAY);
  return std::distance(begin, std::find_if(begin, end, eq_addr<BLOCK>(address, OFFSET_BITS)));
}

int CACHE::invalidate_entry(uint64_t inval_addr)
{
  uint32_t set = get_set(inval_addr);
  uint32_t way = get_way(inval_addr, set);

  if (way < NUM_WAY)
    block[set * NUM_WAY + way].valid = 0;

  return way;
}

int CACHE::add_rq(PACKET* packet)
{
  assert(packet->address != 0);
  RQ_ACCESS++;

  DP(if (warmup_complete[packet->cpu]) {
    std::cout << "[" << NAME << "_RQ] " << __func__ << " instr_id: " << packet->instr_id << " address: " << std::hex << (packet->address >> OFFSET_BITS);
    std::cout << " full_addr: " << packet->address << " v_address: " << packet->v_address << std::dec << " type: " << +packet->type
              << " occupancy: " << RQ.occupancy();
  })

  #ifdef PRINT_ADD_RQ_TRACE
    if(NAME=="cpu0_L1D"){
      cout << "\t[L1D.add_rq] cycles: " << current_cycle 
           << ", instr: " << packet->instr_id << hex
           << ", vaddr: " << packet->v_address 
           << ", type: " << +packet->type
           << dec << endl;
    }
  #endif
  if(packet->instr_id == PRINT_INSTR_ID){
    cout << "\t[add_rq     ] " << NAME 
         << " instr: " << packet->instr_id 
         << ", cycles: " << current_cycle  << hex
         << ", vaddr: " << packet->v_address 
         << ", type: " << +packet->type
         << dec << endl;
  }


  // check for the latest writebacks in the write queue
  champsim::delay_queue<PACKET>::iterator found_wq = std::find_if(WQ.begin(), WQ.end(), eq_addr<PACKET>(packet->address, match_offset_bits ? 0 : OFFSET_BITS));

  if (found_wq != WQ.end()) {

    DP(if (warmup_complete[packet->cpu]) std::cout << " MERGED_WQ" << std::endl;)

    packet->data = found_wq->data;
    for (auto ret : packet->to_return)
      ret->return_data(packet);

    WQ_FORWARD++;
    return -1;
  }

  // check for duplicates in the read queue
  auto found_rq = std::find_if(RQ.begin(), RQ.end(), eq_addr<PACKET>(packet->address, OFFSET_BITS));
  if (found_rq != RQ.end() && packet_can_merge) {

    DP(if (warmup_complete[packet->cpu]) std::cout << " MERGED_RQ" << std::endl;)

    packet_dep_merge(found_rq->lq_index_depend_on_me, packet->lq_index_depend_on_me);
    packet_dep_merge(found_rq->sq_index_depend_on_me, packet->sq_index_depend_on_me);
    packet_dep_merge(found_rq->instr_depend_on_me, packet->instr_depend_on_me);
    packet_dep_merge(found_rq->to_return, packet->to_return);

    RQ_MERGED++;

    return 0; // merged index
  }

  // check occupancy
  if (RQ.full()) {
    RQ_FULL++;

    DP(if (warmup_complete[packet->cpu]) std::cout << " FULL" << std::endl;)

    return -2; // cannot handle this request
  }

  // if there is no duplicate, add it to RQ
  if (warmup_complete[cpu])
    RQ.push_back(*packet);
  else
    RQ.push_back_ready(*packet);

  DP(if (warmup_complete[packet->cpu]) std::cout << " ADDED" << std::endl;)

  RQ_TO_CACHE++;
  return RQ.occupancy();
}

int CACHE::add_wq(PACKET* packet)
{
  WQ_ACCESS++;

  DP(if (warmup_complete[packet->cpu]) {
    std::cout << "[" << NAME << "_WQ] " << __func__ << " instr_id: " << packet->instr_id << " address: " << std::hex << (packet->address >> OFFSET_BITS);
    std::cout << " full_addr: " << packet->address << " v_address: " << packet->v_address << std::dec << " type: " << +packet->type
              << " occupancy: " << RQ.occupancy();
  })

  // check for duplicates in the write queue
  champsim::delay_queue<PACKET>::iterator found_wq = std::find_if(WQ.begin(), WQ.end(), eq_addr<PACKET>(packet->address, match_offset_bits ? 0 : OFFSET_BITS));

  if (found_wq != WQ.end()) {

    DP(if (warmup_complete[packet->cpu]) std::cout << " MERGED" << std::endl;)

    WQ_MERGED++;
    return 0; // merged index
  }

  // Check for room in the queue
  if (WQ.full()) {
    DP(if (warmup_complete[packet->cpu]) std::cout << " FULL" << std::endl;)

    ++WQ_FULL;
    return -2;
  }

  // if there is no duplicate, add it to the write queue
  if (warmup_complete[cpu])
    WQ.push_back(*packet);
  else
    WQ.push_back_ready(*packet);

  DP(if (warmup_complete[packet->cpu]) std::cout << " ADDED" << std::endl;)

  WQ_TO_CACHE++;
  WQ_ACCESS++;

  return WQ.occupancy();
}

int CACHE::prefetch_line(uint64_t pf_addr, bool fill_this_level, uint64_t prefetch_metadata)
{
  pf_requested++;

  #if PRINT_PREF_LINE_TRACE == 1
      cout << "\t[L1 Prefetch Line] " << NAME
           << " cycle: " << current_cycle << hex 
           << ", type: " << +decode_pref_type(prefetch_metadata)
           << ", addr: " << pf_addr 
           << ", prefetch_metadata: 0x" << prefetch_metadata << dec 
           << endl;
  #endif

  PACKET pf_packet;
  pf_packet.type = PREFETCH;
  pf_packet.fill_level = (fill_this_level ? fill_level : lower_level->fill_level);
  pf_packet.pf_origin_level = fill_level;
  pf_packet.pf_metadata = prefetch_metadata;
  pf_packet.cpu = cpu;
  pf_packet.address = pf_addr;
  pf_packet.v_address = virtual_prefetch ? pf_addr : 0;

  if (virtual_prefetch) {
    if (!VAPQ.full()) {
      VAPQ.push_back(pf_packet);
      return 1;
    }else {
      VAPQ_FULL++;
    }
  } else {
    int result = add_pq(&pf_packet);
    if (result != -2) {
      if (result > 0)
        pf_issued++;
      return 1;
    }
  }

  return 0;
}


int CACHE::prefetch_line(uint64_t pf_addr, bool fill_this_level, uint64_t prefetch_metadata, uint64_t ip)
{
  pf_requested++;

  #if PRINT_PREF_LINE_TRACE == 1
      cout << "\t[L1 Prefetch Line] " << NAME
           << " cycle: " << current_cycle << hex 
           << ", type: " << +decode_pref_type(prefetch_metadata)
           << ", addr: " << pf_addr 
           << ", prefetch_metadata: 0x" << prefetch_metadata << dec 
           << endl;
  #endif

  PACKET pf_packet;
  pf_packet.type = PREFETCH;
  pf_packet.fill_level = (fill_this_level ? fill_level : lower_level->fill_level);
  pf_packet.pf_origin_level = fill_level;
  pf_packet.pf_metadata = prefetch_metadata;
  pf_packet.cpu = cpu;
  pf_packet.address = pf_addr;
  pf_packet.v_address = virtual_prefetch ? pf_addr : 0;
  pf_packet.ip = ip;

  if (virtual_prefetch) {
    if (!VAPQ.full()) {
      VAPQ.push_back(pf_packet);
      return 1;
    }else {
      VAPQ_FULL++;
    }
  } else {
    int result = add_pq(&pf_packet);
    if (result != -2) {
      if (result > 0)
        pf_issued++;
      return 1;
    }
  }

  return 0;
}

int CACHE::prefetch_line(uint64_t ip, uint64_t base_addr, uint64_t pf_addr, bool fill_this_level, uint64_t prefetch_metadata)
{
  static bool deprecate_printed = false;
  if (!deprecate_printed) {
    std::cout << "WARNING: The extended signature CACHE::prefetch_line(ip, "
                 "base_addr, pf_addr, fill_this_level, prefetch_metadata) is "
                 "deprecated."
              << std::endl;
    std::cout << "WARNING: Use CACHE::prefetch_line(pf_addr, fill_this_level, "
                 "prefetch_metadata) instead."
              << std::endl;
    deprecate_printed = true;
  }
  return prefetch_line(pf_addr, fill_this_level, prefetch_metadata);
}

void CACHE::va_translate_prefetches()
{
  // TEMPORARY SOLUTION: mark prefetches as translated after a fixed latency
  if (VAPQ.has_ready()) {
    VAPQ.front().address = vmem.va_to_pa(cpu, VAPQ.front().v_address).first;

#ifdef PRINT_VA_TRANS_TRACE
    if(NAME=="cpu0_L1D"){
        cout << "\t[va_trans_pref   ] instr: " << VAPQ.front().instr_id 
             << ", cycles: " << current_cycle
             << ", vaddr: " << hex << VAPQ.front().v_address 
             << ", paddr: " << hex << VAPQ.front().address
             << ", pc: 0x" << VAPQ.front().ip 
             << ", type: " << +VAPQ.front().type 
             << ", pf_origin_level: " << +VAPQ.front().pf_origin_level 
             << ", occupancy: " << VAPQ.occupancy()
             << dec << endl;
    }
#endif

    // move the translated prefetch over to the regular PQ
    int result = add_pq(&VAPQ.front());

    // remove the prefetch from the VAPQ
    if (result != -2)
      VAPQ.pop_front();

    if (result > 0)
      pf_issued++;
  }
}

int CACHE::add_pq(PACKET* packet)
{
  assert(packet->address != 0);
  PQ_ACCESS++;

  DP(if (warmup_complete[packet->cpu]) {
    std::cout << "[" << NAME << "_WQ] " << __func__ << " instr_id: " << packet->instr_id << " address: " << std::hex << (packet->address >> OFFSET_BITS);
    std::cout << " full_addr: " << packet->address << " v_address: " << packet->v_address << std::dec << " type: " << +packet->type
              << " occupancy: " << RQ.occupancy();
  })

  // check for the latest wirtebacks in the write queue
  champsim::delay_queue<PACKET>::iterator found_wq = std::find_if(WQ.begin(), WQ.end(), eq_addr<PACKET>(packet->address, match_offset_bits ? 0 : OFFSET_BITS));

  if (found_wq != WQ.end()) {

    DP(if (warmup_complete[packet->cpu]) std::cout << " MERGED_WQ" << std::endl;)

    packet->data = found_wq->data;
    for (auto ret : packet->to_return)
      ret->return_data(packet);

    WQ_FORWARD++;
    return -1;
  }

  // check for duplicates in the PQ
  auto found = std::find_if(PQ.begin(), PQ.end(), eq_addr<PACKET>(packet->address, OFFSET_BITS));
  if (found != PQ.end()) {
    DP(if (warmup_complete[packet->cpu]) std::cout << " MERGED_PQ" << std::endl;)

    found->fill_level = std::min(found->fill_level, packet->fill_level);
    packet_dep_merge(found->to_return, packet->to_return);

    PQ_MERGED++;
    return 0;
  }

  // check occupancy
  if (PQ.full()) {

    DP(if (warmup_complete[packet->cpu]) std::cout << " FULL" << std::endl;)

    PQ_FULL++;
    return -2; // cannot handle this request
  }

  #ifdef PRINT_ADD_PQ_TRACE
    cout << "\t[add_pq ] " << NAME
         << ", instr: " << packet->instr_id 
         << ", cycles: " << current_cycle
         << ", vaddr: " << hex << packet->v_address 
         << ", paddr: " << hex << packet->address
         << ", pc: 0x" << packet->ip 
         << ", type: " << +packet->type 
         << ", pf_origin_level: " << +packet->pf_origin_level 
         << ", occupancy: " << PQ.occupancy()
         << dec << endl;
  #endif

  // if there is no duplicate, add it to PQ
  if (warmup_complete[cpu])
    PQ.push_back(*packet);
  else
    PQ.push_back_ready(*packet);

  DP(if (warmup_complete[packet->cpu]) std::cout << " ADDED" << std::endl;)

  PQ_TO_CACHE++;
  return PQ.occupancy();
}

//int CACHE::add_pq_assign_lat(PACKET* packet, long long int latency)
//{
//  assert(packet->address != 0);
//  PQ_ACCESS++;
//
//  DP(if (warmup_complete[packet->cpu]) {
//    std::cout << "[" << NAME << "_WQ] " << __func__ << " instr_id: " << packet->instr_id << " address: " << std::hex << (packet->address >> OFFSET_BITS);
//    std::cout << " full_addr: " << packet->address << " v_address: " << packet->v_address << std::dec << " type: " << +packet->type
//              << " occupancy: " << RQ.occupancy();
//  })
//
//  // check for the latest wirtebacks in the write queue
//  champsim::delay_queue<PACKET>::iterator found_wq = std::find_if(WQ.begin(), WQ.end(), eq_addr<PACKET>(packet->address, match_offset_bits ? 0 : OFFSET_BITS));
//
//  if (found_wq != WQ.end()) {
//
//    DP(if (warmup_complete[packet->cpu]) std::cout << " MERGED_WQ" << std::endl;)
//
//    packet->data = found_wq->data;
//    for (auto ret : packet->to_return)
//      ret->return_data(packet);
//
//    WQ_FORWARD++;
//    return -1;
//  }
//
//  // check for duplicates in the PQ
//  auto found = std::find_if(PQ.begin(), PQ.end(), eq_addr<PACKET>(packet->address, OFFSET_BITS));
//  if (found != PQ.end()) {
//    DP(if (warmup_complete[packet->cpu]) std::cout << " MERGED_PQ" << std::endl;)
//
//    found->fill_level = std::min(found->fill_level, packet->fill_level);
//    packet_dep_merge(found->to_return, packet->to_return);
//
//    PQ_MERGED++;
//    return 0;
//  }
//
//  // check occupancy
//  if (PQ.full()) {
//
//    DP(if (warmup_complete[packet->cpu]) std::cout << " FULL" << std::endl;)
//
//    PQ_FULL++;
//    return -2; // cannot handle this request
//  }
//
//  // if there is no duplicate, add it to PQ
//  if (warmup_complete[cpu])
//    PQ.push_back(*packet, latency);
//  else
//    PQ.push_back_ready(*packet);
//
//  DP(if (warmup_complete[packet->cpu]) std::cout << " ADDED" << std::endl;)
//
//  PQ_TO_CACHE++;
//  return PQ.occupancy();
//}

void CACHE::return_data(PACKET* packet)
{
  // check MSHR information
  auto mshr_entry = std::find_if(MSHR.begin(), MSHR.end(), eq_addr<PACKET>(packet->address, OFFSET_BITS));
  auto first_unreturned = std::find_if(MSHR.begin(), MSHR.end(), [](auto x) { return x.event_cycle == std::numeric_limits<uint64_t>::max(); });

  // sanity check
  if (mshr_entry == MSHR.end()) {
    std::cerr << "[" << NAME << "_MSHR] " << __func__ << " instr_id: " << packet->instr_id << " cannot find a matching entry!";
    std::cerr << " address: " << std::hex << packet->address;
    std::cerr << " v_address: " << packet->v_address;
    std::cerr << " address: " << (packet->address >> OFFSET_BITS) << std::dec;
    std::cerr << " event: " << packet->event_cycle << " current: " << current_cycle << std::endl;
    assert(0);
  }

  // MSHR holds the most updated information about this request
  mshr_entry->data = packet->data;
  mshr_entry->pf_metadata = packet->pf_metadata;
  mshr_entry->event_cycle = current_cycle + (warmup_complete[cpu] ? FILL_LATENCY : 0);

  DP(if (warmup_complete[packet->cpu]) {
    std::cout << "[" << NAME << "_MSHR] " << __func__ << " instr_id: " << mshr_entry->instr_id;
    std::cout << " address: " << std::hex << (mshr_entry->address >> OFFSET_BITS) << " full_addr: " << mshr_entry->address;
    std::cout << " data: " << mshr_entry->data << std::dec;
    std::cout << " index: " << std::distance(MSHR.begin(), mshr_entry) << " occupancy: " << get_occupancy(0, 0);
    std::cout << " event: " << mshr_entry->event_cycle << " current: " << current_cycle << std::endl;
  });

  // Order this entry after previously-returned entries, but before non-returned
  // entries
  std::iter_swap(mshr_entry, first_unreturned);
}

uint32_t CACHE::get_occupancy(uint8_t queue_type, uint64_t address)
{
  if (queue_type == 0)
    return std::count_if(MSHR.begin(), MSHR.end(), is_valid<PACKET>());
  else if (queue_type == 1)
    return RQ.occupancy();
  else if (queue_type == 2)
    return WQ.occupancy();
  else if (queue_type == 3)
    return PQ.occupancy();

  return 0;
}

uint32_t CACHE::get_size(uint8_t queue_type, uint64_t address)
{
  if (queue_type == 0)
    return MSHR_SIZE;
  else if (queue_type == 1)
    return RQ.size();
  else if (queue_type == 2)
    return WQ.size();
  else if (queue_type == 3)
    return PQ.size();

  return 0;
}

bool CACHE::should_activate_prefetcher(int type) { return (1 << static_cast<int>(type)) & pref_activate_mask; }

void CACHE::print_deadlock()
{
  if (!std::empty(MSHR)) {
    std::cout << NAME << " MSHR Entry" << std::endl;
    std::size_t j = 0;
    for (PACKET entry : MSHR) {
      std::cout << "[" << NAME << " MSHR] entry: " << j++ << " instr_id: " << entry.instr_id;
      std::cout << " address: " << std::hex << (entry.address >> LOG2_BLOCK_SIZE) << " full_addr: " << entry.address << std::dec << " type: " << +entry.type;
      std::cout << " fill_level: " << +entry.fill_level << " event_cycle: " << entry.event_cycle;
      cout << " to_return_size: " << entry.to_return.size()
      << std::endl;
    }
  } else {
    std::cout << NAME << " MSHR empty" << std::endl;
  }
}

#ifdef MISS_COLLECT_INFO
void collect_miss_info(PACKET& handle_pkt, bool miss){
    uint8_t dest_register = handle_pkt.lq_index_depend_on_me[0]->rob_index->destination_registers[0];
    if(dest_register != 0){
        uint8_t load_type = handle_pkt.lq_index_depend_on_me[0]->rob_index->load_type;
        if(miss){
            miss_load_num += 1;
            if(load_type == LOAD_STRIDE){
               miss_stride_num += 1;
            } else if(load_type == LOAD_INFECT || load_type == LOAD_COMPLEX){
                miss_ima_num += 1;
                if(load_type == LOAD_COMPLEX){
                   miss_ima_complex_num += 1;
                }
            }
        }
    }
}
#endif