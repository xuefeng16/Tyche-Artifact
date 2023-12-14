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

#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <getopt.h>
#include <iomanip>
#include <signal.h>
#include <string.h>
#include <vector>
#include <unordered_map>

#include "cache.h"
#include "champsim.h"
#include "champsim_constants.h"
#include "dram_controller.h"
#include "ooo_cpu.h"
#include "operable.h"
#include "tracereader.h"
#include "vmem.h"
#include "memory_data.h"
#include "regfile.h"
#include "prefetch.h"
#include "instruction.h"

uint64_t total_inst_num = 0;
uint64_t total_load_num = 0;
uint64_t decode_inst_num = 0;
uint64_t decode_load_num = 0;
uint64_t miss_load_num = 0;
uint64_t miss_stride_num = 0;
uint64_t miss_ima_num = 0;
uint64_t miss_ima_complex_num = 0;
uint64_t dct_hit_needbyload_num = 0;
uint64_t dct_hit_same_src_num = 0;
uint64_t dct_hit_num = 0;
uint64_t dct_hit_useless_num = 0;
// uint64_t dct_hit_no_depend_num = 0;
// uint64_t miss_ima_single_num = 0;
// uint64_t miss_ima_double_num = 0;
uint64_t dma_consumer_num = 0;
uint64_t dma_caught_num = 0;
uint64_t dma_consumer_inst_num = 0;
uint64_t dma_caught_inst_num = 0;

uint64_t dct_search_num = 0;
uint64_t dct_write_num = 0;

uint64_t isq_search_num = 0;
uint64_t isq_write_num = 0;

std::unordered_map<uint64_t, load_info_t> pc_info;
std::unordered_map<uint64_t, decode_load_info_t> decode_pc_info;
std::unordered_map<uint64_t, uint64_t> ic_length_info;
std::unordered_map<IDM_OP, uint64_t> ict_op_info;
map<uint64_t, uint64_t> consumer_map;
uint64_t total_exc_num = 0;

uint64_t ima_pref_num = 0;
uint64_t ima_pref_miss_num = 0;

uint8_t regfile_load_type[64] = {};
uint8_t regfile_op[64] = {};
MEMORY_DATA mem_data[NUM_CPUS];
REGFILE regfile[NUM_CPUS];
extern AGQ agq[NUM_CPUS];
extern DCT dct[NUM_CPUS];

uint8_t warmup_complete[NUM_CPUS] = {}, simulation_complete[NUM_CPUS] = {}, all_warmup_complete = 0, all_simulation_complete = 0,
        MAX_INSTR_SOURCES=NUM_INSTR_SOURCES, MAX_INSTR_DESTINATIONS = NUM_INSTR_DESTINATIONS, trace_type = TRACE_TYPE_INVALID, knob_low_bandwidth = 0;
bool compressed_memory = false;

uint64_t warmup_instructions = 1000000, simulation_instructions = 10000000;

auto start_time = time(NULL);

// For backwards compatibility with older module source.
champsim::deprecated_clock_cycle current_core_cycle;

extern MEMORY_CONTROLLER DRAM;
extern VirtualMemory vmem;
extern std::array<O3_CPU*, NUM_CPUS> ooo_cpu;
extern std::array<CACHE*, NUM_CACHES> caches;
extern std::array<champsim::operable*, NUM_OPERABLES> operables;

std::vector<tracereader*> traces;

uint64_t champsim::deprecated_clock_cycle::operator[](std::size_t cpu_idx)
{
  static bool deprecate_printed = false;
  if (!deprecate_printed) {
    std::cout << "WARNING: The use of 'current_core_cycle[cpu]' is deprecated." << std::endl;
    std::cout << "WARNING: Use 'this->current_cycle' instead." << std::endl;
    deprecate_printed = true;
  }
  return ooo_cpu[cpu_idx]->current_cycle;
}

void record_roi_stats(uint32_t cpu, CACHE* cache)
{
  for (uint32_t i = 0; i < NUM_TYPES; i++) {
    cache->roi_access[cpu][i] = cache->sim_access[cpu][i];
    cache->roi_hit[cpu][i] = cache->sim_hit[cpu][i];
    cache->roi_miss[cpu][i] = cache->sim_miss[cpu][i];

    cache->roi_read_access[cpu][i] = cache->sim_read_access[cpu][i];
    cache->roi_read_hit[cpu][i] = cache->sim_read_hit[cpu][i];
    cache->roi_read_miss[cpu][i] = cache->sim_read_miss[cpu][i];
  }
}

void print_roi_stats(uint32_t cpu, CACHE* cache)
{
  uint64_t TOTAL_ACCESS = 0, TOTAL_HIT = 0, TOTAL_MISS = 0;

  for (uint32_t i = 0; i < NUM_TYPES; i++) {
    TOTAL_ACCESS += cache->roi_access[cpu][i];
    TOTAL_HIT += cache->roi_hit[cpu][i];
    TOTAL_MISS += cache->roi_miss[cpu][i];
  }

  if (TOTAL_ACCESS > 0) {
    cout << cache->NAME;
    cout << " TOTAL     ACCESS: " << setw(10) << TOTAL_ACCESS << "  HIT: " << setw(10) << TOTAL_HIT << "  MISS: " << setw(10) << TOTAL_MISS << endl;

    cout << cache->NAME;
    cout << " LOAD      ACCESS: " << setw(10) << cache->roi_access[cpu][0] << "  HIT: " << setw(10) << cache->roi_hit[cpu][0] << "  MISS: " << setw(10)
         << cache->roi_miss[cpu][0] << endl;

    cout << cache->NAME;
    cout << " RFO       ACCESS: " << setw(10) << cache->roi_access[cpu][1] << "  HIT: " << setw(10) << cache->roi_hit[cpu][1] << "  MISS: " << setw(10)
         << cache->roi_miss[cpu][1] << endl;

    cout << cache->NAME;
    cout << " PREFETCH  ACCESS: " << setw(10) << cache->roi_access[cpu][2] << "  HIT: " << setw(10) << cache->roi_hit[cpu][2] << "  MISS: " << setw(10)
         << cache->roi_miss[cpu][2] << endl;

    cout << cache->NAME;
    cout << " WRITEBACK ACCESS: " << setw(10) << cache->roi_access[cpu][3] << "  HIT: " << setw(10) << cache->roi_hit[cpu][3] << "  MISS: " << setw(10)
         << cache->roi_miss[cpu][3] << endl;

    cout << cache->NAME;
    cout << " TRANSLATION ACCESS: " << setw(10) << cache->roi_access[cpu][4] << "  HIT: " << setw(10) << cache->roi_hit[cpu][4] << "  MISS: " << setw(10)
         << cache->roi_miss[cpu][4] << endl;

    cout << cache->NAME;
    cout << " PREFETCH  REQUESTED: " << setw(10) << cache->pf_requested 
         << "  ISSUED: " << setw(10) << cache->pf_issued
         << "  MISS ISSUED: " << setw(10) << cache->pf_miss_issued;
    cout << "  USEFUL: " << setw(10) << cache->pf_useful << "  USELESS: " << setw(10) << cache->pf_useless << endl;

    cout << cache->NAME;
    cout << " AVERAGE MISS LATENCY: " << (1.0 * (cache->total_miss_latency)) / TOTAL_MISS << " cycles" << endl;
    // cout << " AVERAGE MISS LATENCY: " <<
    // (cache->total_miss_latency)/TOTAL_MISS << " cycles " <<
    // cache->total_miss_latency << "/" << TOTAL_MISS<< endl;
  }
}

void print_queue_stats(uint32_t cpu){
    cout << "ROB FULL: " << ooo_cpu[cpu]->ROB_FULL << endl;
    cout << "DECODE_BUFFER FULL: " << ooo_cpu[cpu]->DECODE_BUFFER_FULL << endl;
    cout << "DISPATCH_BUFFER FULL: " << ooo_cpu[cpu]->DISPATCH_BUFFER_FULL << endl;
    cout << "LOADQ FULL: " << ooo_cpu[cpu]->LOADQ_FULL << endl;
    cout << "STOREQ FULL: " << ooo_cpu[cpu]->STOREQ_FULL << endl;
    cout << "ROB_FULL_CYCLE: " << ooo_cpu[cpu]->ROB_FULL_CYCLE << endl;
    cout << "RETIRE_STALL_CYCLE: " << ooo_cpu[cpu]->RETIRE_STALL_CYCLE << endl;
    cout << "DCT FULL: " << dct[cpu].IDM_ISSSUEQ_FULL << endl;
    cout << "AGQ FULL: " << agq[cpu].AGQ_FULL << endl;
    cout << "AGQ CLEAR: " << agq[cpu].AGQ_CLEAR << endl;
    cout << "AGQ ALU_ALONE: " << agq[cpu].AGQ_ALU_ALONE << endl;
    cout << endl;
}

void print_roi_read_stats(uint32_t cpu, CACHE* cache)
{
  uint64_t TOTAL_ACCESS = 0, TOTAL_HIT = 0, TOTAL_MISS = 0;

  for (uint32_t i = 0; i < NUM_TYPES; i++) {
    TOTAL_ACCESS += cache->roi_read_access[cpu][i];
    TOTAL_HIT += cache->roi_read_hit[cpu][i];
    TOTAL_MISS += cache->roi_read_miss[cpu][i];
  }

  if (TOTAL_ACCESS > 0) {
    cout << cache->NAME << " read ";
    cout << " TOTAL     ACCESS: " << setw(10) << TOTAL_ACCESS 
         << "  HIT: "             << setw(10) << TOTAL_HIT 
         << "  MISS: "            << setw(10) << TOTAL_MISS << endl;

    cout << cache->NAME << " read ";
    cout << " LOAD      ACCESS: " << setw(10) << cache->roi_read_access[cpu][LOAD] 
         << "  HIT: "             << setw(10) << cache->roi_read_hit[cpu][LOAD] 
         << "  MISS: "            << setw(10) << cache->roi_read_miss[cpu][LOAD] << endl;

    cout << cache->NAME << " read ";
    cout << " PREFETCH  ACCESS: " << setw(10) << cache->roi_read_access[cpu][PREFETCH] 
         << "  HIT: "             << setw(10) << cache->roi_read_hit[cpu][PREFETCH] 
         << "  MISS: "            << setw(10) << cache->roi_read_miss[cpu][PREFETCH] << endl;

    cout << cache->NAME << " read ";
    cout << " PREFETCH  REQUESTED: " << setw(10) << cache->pf_requested 
         << "  ISSUED: " << setw(10) << cache->pf_issued
         << "  MISS ISSUED: " << setw(10) << cache->pf_miss_issued;
    cout << "  USEFUL: " << setw(10) << cache->pf_useful << "  USELESS: " << setw(10) << cache->pf_useless << endl;

    cout << cache->NAME << " read ";
    cout << " MSHR FULL: " << setw(10) << cache->MSHR_FULL 
         << " VAPQ FULL: " << setw(10) << cache->VAPQ_FULL 
         << " PQ FULL: "   << setw(10) << cache->PQ_FULL 
         << " PQ MERGED: "   << setw(10) << cache->PQ_MERGED << endl;

    cout << endl;
  }
}

void print_stride_ptchain_stats(){
#ifdef COLLECT_INFO
    cout << "Collect Load Info at TraceReader: " << endl;
    cout << "total_inst_num: " << total_inst_num << endl;
    cout << "total_load_num: " << total_load_num << endl;

    std::vector<uint64_t> load_pc;
    for(auto &[key, value]: pc_info){
        load_pc.emplace_back(key);
    }

    sort(load_pc.begin(), load_pc.end(), [&](const uint64_t&a, const uint64_t&b)->bool{
        return pc_info[a].total_count==pc_info[b].total_count? a<b : pc_info[a].total_count>pc_info[b].total_count;
    });

    uint32_t num = 50;
    cout << "Top "<< num << " PC's Info : " << endl;
    uint32_t icount = 0;

    uint64_t instr_stride_count = 0;
    uint64_t instr_ima_count = 0;
    for(auto i = load_pc.begin(); i != load_pc.end(); i++){
        uint64_t pc = *i;
        load_info_t info_item =  pc_info[*i];
        if(++icount < num){
            double load_ratio = 1.0*info_item.total_count/total_load_num;
            double stride_ratio = 1.0*info_item.stride_count/info_item.total_count;
            double pt_ratio = 1.0*info_item.pt_count/info_item.total_count;
            double dma_ratio = 1.0*info_item.dma_count/info_item.total_count;
            printf("[%02d]: PC: %#lx, load num: %8ld, ratio: %6.2f%%, ", icount, pc, info_item.total_count, load_ratio*100);
            printf("stride num: %8ld, ratio: %6.2f%%, ", info_item.stride_count, stride_ratio*100);
            printf("pt chain num: %8ld, ratio: %6.2f%%, ", info_item.pt_count, pt_ratio*100);
            printf("dma num: %8ld, ratio: %6.2f%%\n", info_item.dma_count, dma_ratio*100);
            if(dma_ratio >= 0.8){
              dma_consumer_num++;
              dma_consumer_inst_num += info_item.dma_count;
              auto i = consumer_map.find(pc);
              if(i != consumer_map.end()){
                if((double)i->second / (double)info_item.dma_count >= 0.3){
                  dma_caught_num += 1;
                }
                if(i->second > info_item.dma_count){
                    dma_caught_inst_num += info_item.dma_count;
                } else{
                    dma_caught_inst_num += i->second;
                }
              }
            }
        }

        instr_stride_count += info_item.stride_count;
        instr_ima_count += info_item.dma_count;
    }

    cout << "pc_info size: " << pc_info.size() << endl;
    cout << "load_pc size: " << load_pc.size() << endl;
    cout << "instr_stride_count: " << instr_stride_count << endl;
    cout << "instr_ima_count: " << instr_ima_count << endl;
    cout << "dma consumer num: " << dma_consumer_num << endl;
    cout << "dma caught num: " << dma_caught_num << endl;
    cout << "dma consumer inst num: " << dma_consumer_inst_num << endl;
    cout << "dma caught inst num: " << dma_caught_inst_num << endl;
#endif

#ifdef DECODE_COLLECT_INFO
    cout << "\nCollect Load Info at Decode Stage: " << endl;
    cout << "decode_inst_num: " << decode_inst_num << endl;

    std::vector<uint64_t> decode_load_pc;
    for(auto &[key, value]: decode_pc_info)
        decode_load_pc.emplace_back(key);

    sort(decode_load_pc.begin(), decode_load_pc.end(), [&](const uint64_t&a, const uint64_t&b)->bool{
        return (decode_pc_info[a].total_count==decode_pc_info[b].total_count)? a<b : (decode_pc_info[a].total_count>decode_pc_info[b].total_count);
    });

    uint32_t decode_num = 50;
    cout << "Top "<< decode_num << " PC's Info : " << endl;
    uint32_t decode_icount = 0;

    uint64_t dbg_load_num = 0;
    uint64_t decode_stride_count = 0;
    uint64_t decode_ima_single_count = 0;
    uint64_t decode_ima_double_count = 0;
    uint64_t decode_ima_complex_count = 0;
    for(auto i = decode_load_pc.begin(); i != decode_load_pc.end(); i++){
        uint64_t pc = *i;
        decode_load_info_t info_item =  decode_pc_info[*i];
        if(++decode_icount < decode_num){
            double load_ratio = 1.0*info_item.total_count/decode_inst_num;
            double stride_ratio = 1.0*info_item.stride_count/info_item.total_count;
            double ima_single_ratio = 1.0*info_item.ima_single_count/info_item.total_count;
            double ima_double_ratio = 1.0*info_item.ima_double_count/info_item.total_count;
            double complex_ratio = 1.0*info_item.ima_complex_count/info_item.total_count;
            printf("[%02d]: PC: %#lx, load num: %8ld, ratio: %6.2f%%, ", decode_icount, pc, info_item.total_count, load_ratio*100);
            printf("stride num: %8ld, ratio: %6.2f%%, ", info_item.stride_count, stride_ratio*100);
            printf("ima single num: %8ld, ratio: %6.2f%%, ", info_item.ima_single_count, ima_single_ratio*100);
            printf("ima double num: %8ld, ratio: %6.2f%%, ", info_item.ima_double_count, ima_double_ratio*100);
            printf("ima complex num: %8ld, ratio: %6.2f%%\n", info_item.ima_complex_count, complex_ratio*100);
        }

        dbg_load_num += info_item.total_count;
        decode_stride_count += info_item.stride_count;
        decode_ima_single_count += info_item.ima_single_count;
        decode_ima_double_count += info_item.ima_double_count;
        decode_ima_complex_count += info_item.ima_complex_count;
    }
    if((decode_load_num - dbg_load_num) > 512){
        cout << "decode_load_num is not equal to dbg_load_num!\n" << endl;
    }

    cout << "decode_load_num: " << dbg_load_num << endl;
    cout << "decode_pc_info size: " << decode_pc_info.size() << endl;
    cout << "decode_load_pc size: " << decode_load_pc.size() << endl;
    cout << "decode_stride_count: "      << decode_stride_count      << endl;
    cout << "decode_ima_single_count: "  << decode_ima_single_count  << endl;
    cout << "decode_ima_double_count: "  << decode_ima_double_count  << endl;
    cout << "decode_ima_complex_count: " << decode_ima_complex_count << endl;
#endif

#ifdef MISS_COLLECT_INFO
    cout << endl;
    cout << "miss_load_num: " << miss_load_num << endl;
    cout << "miss_stride_num: " << miss_stride_num << endl;
    cout << "miss_ima_num: " << miss_ima_num  << endl;
    cout << "miss_ima_complex_num: " << miss_ima_complex_num  << endl;
    // cout << "miss_ima_single_num: " << miss_ima_single_num << endl;
    // cout << "miss_ima_double_num: " << miss_ima_double_num << endl;
#endif

#ifdef COLLECT_SAME_SRC
    cout << endl;
    cout << "dct_hit_num: " << dct_hit_needbyload_num << endl;
    cout << "dct_hit_same_src_num: " << dct_hit_same_src_num << endl;
    // cout << "dct_hit_no_depend_num: " << dct_hit_no_depend_num  << endl;
#endif

#ifdef COLLECT_USELESS
    cout << endl;
    cout << "dct_hit_num: " << dct_hit_num << endl;
    cout << "dct_hit_useless_num: " << dct_hit_useless_num << endl;
#endif

#ifdef IC_LENGTH_INFO
    // Instruction Chain Length
    cout << "\nInstruction Chain Length: " << endl;

    std::vector<uint64_t> ic_len;
    for(auto &[key, value]: ic_length_info){
        ic_len.emplace_back(key);
    }

    sort(ic_len.begin(), ic_len.end(), [&](const uint64_t&a, const uint64_t&b)->bool{
        return ic_length_info[a]==ic_length_info[b]? a<b : ic_length_info[a]>ic_length_info[b];
    });

    uint32_t num = 20;
    cout << "Top "<< num << " Length Info : " << endl;
    uint32_t icount = 0;

    uint64_t sum = 0;
    uint64_t sum_cnt = 0;
    for(auto i = ic_len.begin(); i != ic_len.end(); i++){
        uint64_t len = *i;

        if(++icount < num){
            printf("IC Length: %8ld, count: %8ld\n", len, ic_length_info[len]);
        }
        sum += (len * ic_length_info[len]);
        sum_cnt += ic_length_info[len];
    }
    printf("Average IC Length: %f\n", ((double) sum)/sum_cnt);

    //// DCT OP Info
    cout << "\nICT OP Info: " << endl;
    std::vector<IDM_OP> ict_op;
    for(auto &[key, value]: ict_op_info){
        ict_op.emplace_back(key);
    }

    sort(ict_op.begin(), ict_op.end(), [&](const IDM_OP&a, const IDM_OP&b)->bool{
        return ict_op_info[a]==ict_op_info[b]? a<b : ict_op_info[a]>ict_op_info[b];
    });

    uint64_t ict_op_sum = 0;
    cout << " Length Info : " << endl;

    for(uint64_t i = IDM_INVALID; i <= IDM_LD_D; i++){
        printf("IDM OP: %4ld   count: %8ld\n", i, ict_op_info[(IDM_OP)i]);
        ict_op_sum += ict_op_info[(IDM_OP)i];
    }
#endif
}

void print_idm_info(){
    for (uint32_t i = 0; i < NUM_CPUS; i++) {
        printf("[cpu%d] idm_double_stride = %ld\n", i, ooo_cpu[i]->idm_double_stride);
    }
}

void print_sim_stats(uint32_t cpu, CACHE* cache)
{
  uint64_t TOTAL_ACCESS = 0, TOTAL_HIT = 0, TOTAL_MISS = 0;

  for (uint32_t i = 0; i < NUM_TYPES; i++) {
    TOTAL_ACCESS += cache->sim_access[cpu][i];
    TOTAL_HIT += cache->sim_hit[cpu][i];
    TOTAL_MISS += cache->sim_miss[cpu][i];
  }

  if (TOTAL_ACCESS > 0) {
    cout << cache->NAME;
    cout << " TOTAL     ACCESS: " << setw(10) << TOTAL_ACCESS << "  HIT: " << setw(10) << TOTAL_HIT << "  MISS: " << setw(10) << TOTAL_MISS << endl;

    cout << cache->NAME;
    cout << " LOAD      ACCESS: " << setw(10) << cache->sim_access[cpu][0] << "  HIT: " << setw(10) << cache->sim_hit[cpu][0] << "  MISS: " << setw(10)
         << cache->sim_miss[cpu][0] << endl;

    cout << cache->NAME;
    cout << " RFO       ACCESS: " << setw(10) << cache->sim_access[cpu][1] << "  HIT: " << setw(10) << cache->sim_hit[cpu][1] << "  MISS: " << setw(10)
         << cache->sim_miss[cpu][1] << endl;

    cout << cache->NAME;
    cout << " PREFETCH  ACCESS: " << setw(10) << cache->sim_access[cpu][2] << "  HIT: " << setw(10) << cache->sim_hit[cpu][2] << "  MISS: " << setw(10)
         << cache->sim_miss[cpu][2] << endl;

    cout << cache->NAME;
    cout << " WRITEBACK ACCESS: " << setw(10) << cache->sim_access[cpu][3] << "  HIT: " << setw(10) << cache->sim_hit[cpu][3] << "  MISS: " << setw(10)
         << cache->sim_miss[cpu][3] << endl;
  }
}

void print_branch_stats()
{
  for (uint32_t i = 0; i < NUM_CPUS; i++) {
    cout << endl << "CPU " << i << " Branch Prediction Accuracy: ";
    cout << (100.0 * (ooo_cpu[i]->num_branch - ooo_cpu[i]->branch_mispredictions)) / ooo_cpu[i]->num_branch;
    cout << "% MPKI: " << (1000.0 * ooo_cpu[i]->branch_mispredictions) / (ooo_cpu[i]->num_retired - warmup_instructions);
    cout << " Average ROB Occupancy at Mispredict: " << (1.0 * ooo_cpu[i]->total_rob_occupancy_at_branch_mispredict) / ooo_cpu[i]->branch_mispredictions
         << endl;

    /*
    cout << "Branch types" << endl;
    cout << "NOT_BRANCH: " << ooo_cpu[i]->total_branch_types[0] << " " <<
    (100.0*ooo_cpu[i]->total_branch_types[0])/(ooo_cpu[i]->num_retired -
    ooo_cpu[i]->begin_sim_instr) << "%" << endl; cout << "BRANCH_DIRECT_JUMP: "
    << ooo_cpu[i]->total_branch_types[1] << " " <<
    (100.0*ooo_cpu[i]->total_branch_types[1])/(ooo_cpu[i]->num_retired -
    ooo_cpu[i]->begin_sim_instr) << "%" << endl; cout << "BRANCH_INDIRECT: " <<
    ooo_cpu[i]->total_branch_types[2] << " " <<
    (100.0*ooo_cpu[i]->total_branch_types[2])/(ooo_cpu[i]->num_retired -
    ooo_cpu[i]->begin_sim_instr) << "%" << endl; cout << "BRANCH_CONDITIONAL: "
    << ooo_cpu[i]->total_branch_types[3] << " " <<
    (100.0*ooo_cpu[i]->total_branch_types[3])/(ooo_cpu[i]->num_retired -
    ooo_cpu[i]->begin_sim_instr) << "%" << endl; cout << "BRANCH_DIRECT_CALL: "
    << ooo_cpu[i]->total_branch_types[4] << " " <<
    (100.0*ooo_cpu[i]->total_branch_types[4])/(ooo_cpu[i]->num_retired -
    ooo_cpu[i]->begin_sim_instr) << "%" << endl; cout << "BRANCH_INDIRECT_CALL:
    " << ooo_cpu[i]->total_branch_types[5] << " " <<
    (100.0*ooo_cpu[i]->total_branch_types[5])/(ooo_cpu[i]->num_retired -
    ooo_cpu[i]->begin_sim_instr) << "%" << endl; cout << "BRANCH_RETURN: " <<
    ooo_cpu[i]->total_branch_types[6] << " " <<
    (100.0*ooo_cpu[i]->total_branch_types[6])/(ooo_cpu[i]->num_retired -
    ooo_cpu[i]->begin_sim_instr) << "%" << endl; cout << "BRANCH_OTHER: " <<
    ooo_cpu[i]->total_branch_types[7] << " " <<
    (100.0*ooo_cpu[i]->total_branch_types[7])/(ooo_cpu[i]->num_retired -
    ooo_cpu[i]->begin_sim_instr) << "%" << endl << endl;
    */

    cout << "Branch type MPKI" << endl;
    cout << "BRANCH_DIRECT_JUMP: " << (1000.0 * ooo_cpu[i]->branch_type_misses[1] / (ooo_cpu[i]->num_retired - ooo_cpu[i]->begin_sim_instr)) << endl;
    cout << "BRANCH_INDIRECT: " << (1000.0 * ooo_cpu[i]->branch_type_misses[2] / (ooo_cpu[i]->num_retired - ooo_cpu[i]->begin_sim_instr)) << endl;
    cout << "BRANCH_CONDITIONAL: " << (1000.0 * ooo_cpu[i]->branch_type_misses[3] / (ooo_cpu[i]->num_retired - ooo_cpu[i]->begin_sim_instr)) << endl;
    cout << "BRANCH_DIRECT_CALL: " << (1000.0 * ooo_cpu[i]->branch_type_misses[4] / (ooo_cpu[i]->num_retired - ooo_cpu[i]->begin_sim_instr)) << endl;
    cout << "BRANCH_INDIRECT_CALL: " << (1000.0 * ooo_cpu[i]->branch_type_misses[5] / (ooo_cpu[i]->num_retired - ooo_cpu[i]->begin_sim_instr)) << endl;
    cout << "BRANCH_RETURN: " << (1000.0 * ooo_cpu[i]->branch_type_misses[6] / (ooo_cpu[i]->num_retired - ooo_cpu[i]->begin_sim_instr)) << endl << endl;
  }
}

void print_dram_stats()
{
  uint64_t total_congested_cycle = 0;
  uint64_t total_congested_count = 0;

  std::cout << std::endl;
  std::cout << "DRAM Statistics" << std::endl;
  for (uint32_t i = 0; i < DRAM_CHANNELS; i++) {
    std::cout << " CHANNEL " << i << std::endl;

    auto& channel = DRAM.channels[i];
    std::cout << " RQ ROW_BUFFER_HIT: " << std::setw(10) << channel.RQ_ROW_BUFFER_HIT << " ";
    std::cout << " ROW_BUFFER_MISS: " << std::setw(10) << channel.RQ_ROW_BUFFER_MISS;
    std::cout << std::endl;

    std::cout << " DBUS AVG_CONGESTED_CYCLE: ";
    if (channel.dbus_count_congested)
      std::cout << std::setw(10) << ((double)channel.dbus_cycle_congested / channel.dbus_count_congested);
    else
      std::cout << "-";
    std::cout << std::endl;

    std::cout << " WQ ROW_BUFFER_HIT: " << std::setw(10) << channel.WQ_ROW_BUFFER_HIT << " ";
    std::cout << " ROW_BUFFER_MISS: " << std::setw(10) << channel.WQ_ROW_BUFFER_MISS << " ";
    std::cout << " FULL: " << std::setw(10) << channel.WQ_FULL;
    std::cout << std::endl;

    std::cout << std::endl;

    total_congested_cycle += channel.dbus_cycle_congested;
    total_congested_count += channel.dbus_count_congested;
  }

  if (DRAM_CHANNELS > 1) {
    std::cout << " DBUS AVG_CONGESTED_CYCLE: ";
    if (total_congested_count)
      std::cout << std::setw(10) << ((double)total_congested_cycle / total_congested_count);
    else
      std::cout << "-";

    std::cout << std::endl;
  }
}

void reset_cache_stats(uint32_t cpu, CACHE* cache)
{
  for (uint32_t i = 0; i < NUM_TYPES; i++) {
    cache->sim_access[cpu][i] = 0;
    cache->sim_hit[cpu][i] = 0;
    cache->sim_miss[cpu][i] = 0;

    cache->sim_read_access[cpu][i] = 0;
    cache->sim_read_hit[cpu][i] = 0;
    cache->sim_read_miss[cpu][i] = 0;
  }

  cache->pf_requested = 0;
  cache->pf_issued = 0;
  cache->pf_useful = 0;
  cache->pf_useless = 0;
  cache->pf_fill = 0;

  cache->total_miss_latency = 0;

  cache->RQ_ACCESS = 0;
  cache->RQ_MERGED = 0;
  cache->RQ_TO_CACHE = 0;

  cache->WQ_ACCESS = 0;
  cache->WQ_MERGED = 0;
  cache->WQ_TO_CACHE = 0;
  cache->WQ_FORWARD = 0;
  cache->WQ_FULL = 0;
}

void finish_warmup()
{
  uint64_t elapsed_second = (uint64_t)(time(NULL) - start_time), elapsed_minute = elapsed_second / 60, elapsed_hour = elapsed_minute / 60;
  elapsed_minute -= elapsed_hour * 60;
  elapsed_second -= (elapsed_hour * 3600 + elapsed_minute * 60);

  // reset core latency
  // note: since re-ordering he function calls in the main simulation loop, it's
  // no longer necessary to add
  //       extra latency for scheduling and execution, unless you want these
  //       steps to take longer than 1 cycle.
  // PAGE_TABLE_LATENCY = 100;
  // SWAP_LATENCY = 100000;

  cout << endl;
  for (uint32_t i = 0; i < NUM_CPUS; i++) {
    cout << "Warmup complete CPU " << i << " instructions: " << ooo_cpu[i]->num_retired << " cycles: " << ooo_cpu[i]->current_cycle;
    cout << " (Simulation time: " << elapsed_hour << " hr " << elapsed_minute << " min " << elapsed_second << " sec) " << endl;

    ooo_cpu[i]->begin_sim_cycle = ooo_cpu[i]->current_cycle;
    ooo_cpu[i]->begin_sim_instr = ooo_cpu[i]->num_retired;

    // reset branch stats
    ooo_cpu[i]->num_branch = 0;
    ooo_cpu[i]->branch_mispredictions = 0;
    ooo_cpu[i]->total_rob_occupancy_at_branch_mispredict = 0;

    for (uint32_t j = 0; j < 8; j++) {
      ooo_cpu[i]->total_branch_types[j] = 0;
      ooo_cpu[i]->branch_type_misses[j] = 0;
    }

    for (auto it = caches.rbegin(); it != caches.rend(); ++it)
      reset_cache_stats(i, *it);
  }
  cout << endl;

  // reset DRAM stats
  for (uint32_t i = 0; i < DRAM_CHANNELS; i++) {
    DRAM.channels[i].WQ_ROW_BUFFER_HIT = 0;
    DRAM.channels[i].WQ_ROW_BUFFER_MISS = 0;
    DRAM.channels[i].RQ_ROW_BUFFER_HIT = 0;
    DRAM.channels[i].RQ_ROW_BUFFER_MISS = 0;
  }
}

void signal_handler(int signal)
{
  cout << "Caught signal: " << signal << endl;
  exit(1);
}

int main(int argc, char** argv)
{
  // interrupt signal hanlder
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = signal_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  cout << endl << "*** ChampSim Multicore Out-of-Order Simulator ***" << endl << endl;

  // initialize knobs
  uint8_t show_heartbeat = 1;

  // check to see if knobs changed using getopt_long()
  int traces_encountered = 0;
  static struct option long_options[] = {{"warmup_instructions", required_argument, 0, 'w'},
                                         {"simulation_instructions", required_argument, 0, 'i'},
                                         {"hide_heartbeat", no_argument, 0, 'h'},
                                         {"x86", no_argument, 0, 'x'},
                                         {"cloudsuite", no_argument, 0, 'c'},
                                         {"loongarch", no_argument, 0, 'l'},
                                         {"compressed_mem", no_argument, 0, 'p'},
                                         {"traces", no_argument, &traces_encountered, 1},
                                         {0, 0, 0, 0}};

  int c;
  while ((c = getopt_long_only(argc, argv, "w:i:hc", long_options, NULL)) != -1 && !traces_encountered) {
    switch (c) {
    case 'w':
      warmup_instructions = atol(optarg);
      break;
    case 'i':
      simulation_instructions = atol(optarg);
      break;
    case 'h':
      show_heartbeat = 0;
      break;
    case 'x':
      trace_type = TRACE_TYPE_X86;
      break;
    case 'c':
      trace_type = TRACE_TYPE_CLOUDSUITE;
      MAX_INSTR_DESTINATIONS = NUM_INSTR_DESTINATIONS_SPARC;
      break;
    case 'l':
      trace_type = TRACE_TYPE_LOONGARCH;
      MAX_INSTR_DESTINATIONS = NUM_INSTR_DESTINATIONS_LOONGARCH;
      MAX_INSTR_SOURCES = NUM_INSTR_SOURCES_LOONGARCH;
      break;
    case 'p':
      compressed_memory = true;
      break;
    case 0:
      break;
    default:
      abort();
    }
  }

  cout << "Warmup Instructions: " << warmup_instructions << endl;
  cout << "Simulation Instructions: " << simulation_instructions << endl;
  cout << "Number of CPUs: " << NUM_CPUS << endl;

  long long int dram_size = DRAM_CHANNELS * DRAM_RANKS * DRAM_BANKS * DRAM_ROWS * DRAM_COLUMNS * BLOCK_SIZE / 1024 / 1024; // in MiB
  std::cout << "Off-chip DRAM Size: ";
  if (dram_size > 1024)
    std::cout << dram_size / 1024 << " GiB";
  else
    std::cout << dram_size << " MiB";
  std::cout << " Channels: " << DRAM_CHANNELS << " Width: " << 8 * DRAM_CHANNEL_WIDTH << "-bit Data Rate: " << DRAM_IO_FREQ << " MT/s" << std::endl;

  std::cout << std::endl;
  std::cout << "VirtualMemory physical capacity: " << std::size(vmem.ppage_free_list) * vmem.page_size;
  std::cout << " num_ppages: " << std::size(vmem.ppage_free_list) << std::endl;
  std::cout << "VirtualMemory page size: " << PAGE_SIZE << " log2_page_size: " << LOG2_PAGE_SIZE << std::endl;

  std::cout << "LLC size: " << (caches[0]->NUM_SET * caches[0]->NUM_WAY * 64.0 / 1024 / 1024) << " MB" << std::endl;
  std::cout << "LLC Latency: " << (caches[0]->HIT_LATENCY) << " cycles" << std::endl;

  std::cout << std::endl;
  for (int i = optind; i < argc; i++) {
    std::cout << "CPU " << traces.size() << " runs " << argv[i] << std::endl;

    traces.push_back(get_tracereader(argv[i], traces.size(), trace_type));

    if (traces.size() > NUM_CPUS) {
      printf("\n*** Too many traces for the configured number of cores ***\n\n");
      assert(0);
    }
  }

  if (traces.size() != NUM_CPUS) {
    printf("\n*** Not enough traces for the configured number of cores ***\n\n");
    assert(0);
  }
  // end trace file setup

  // SHARED CACHE
  for (O3_CPU* cpu : ooo_cpu) {
    cpu->initialize_core();
  }

  // Regfile & Memory initializaiton
  if(trace_type==TRACE_TYPE_LOONGARCH){
    for (uint64_t i = 0; i < NUM_CPUS; i++) {
      // Regfile
      std::string trace_name = argv[optind+i];
      int pos = trace_name.find(".champsim.xz");
      if(pos == -1){
        pos = trace_name.find(".champsim.trace.xz");
      }
      if(pos == -1){
        std::cout << "Trace Name Error!" << std::endl;
      }
      string prefix_name = trace_name.substr(0, pos);

      regfile[i].set_init_fname(prefix_name + ".regfile.txt");
      regfile[i].init();

      // Memory
      trace_name = argv[optind+i];
      mem_data[i].set_init_fname(prefix_name + ".memory.bin", compressed_memory);
      mem_data[i].init();
    }
  }

  for (auto it = caches.rbegin(); it != caches.rend(); ++it) {
    (*it)->impl_prefetcher_initialize();
    (*it)->impl_replacement_initialize();
  }

  // simulation entry point
  while (std::any_of(std::begin(simulation_complete), std::end(simulation_complete), std::logical_not<uint8_t>())) {

    uint64_t elapsed_second = (uint64_t)(time(NULL) - start_time), elapsed_minute = elapsed_second / 60, elapsed_hour = elapsed_minute / 60;
    elapsed_minute -= elapsed_hour * 60;
    elapsed_second -= (elapsed_hour * 3600 + elapsed_minute * 60);

    for (auto op : operables) {
      try {
        op->_operate();
      } catch (champsim::deadlock& dl) {
        // ooo_cpu[dl.which]->print_deadlock();
        // std::cout << std::endl;
        // for (auto c : caches)
        for (auto c : operables) {
          c->print_deadlock();
          std::cout << std::endl;
        }
        cout << "Print Finish!" << endl;
        abort();
      }
    }
    std::sort(std::begin(operables), std::end(operables), champsim::by_next_operate());

    for (std::size_t i = 0; i < ooo_cpu.size(); ++i) {
      // read from trace
      while (ooo_cpu[i]->fetch_stall == 0 && ooo_cpu[i]->instrs_to_read_this_cycle > 0) {
        ooo_cpu[i]->init_instruction(traces[i]->get());
      }

      // heartbeat information
      if (show_heartbeat && (ooo_cpu[i]->num_retired >= ooo_cpu[i]->next_print_instruction)) {
        float cumulative_ipc;
        if (warmup_complete[i])
          cumulative_ipc = (1.0 * (ooo_cpu[i]->num_retired - ooo_cpu[i]->begin_sim_instr)) / (ooo_cpu[i]->current_cycle - ooo_cpu[i]->begin_sim_cycle);
        else
          cumulative_ipc = (1.0 * ooo_cpu[i]->num_retired) / ooo_cpu[i]->current_cycle;
        float heartbeat_ipc = (1.0 * ooo_cpu[i]->num_retired - ooo_cpu[i]->last_sim_instr) / (ooo_cpu[i]->current_cycle - ooo_cpu[i]->last_sim_cycle);

        cout << "Heartbeat CPU " << i << " instructions: " << ooo_cpu[i]->num_retired << " cycles: " << ooo_cpu[i]->current_cycle;
        cout << " heartbeat IPC: " << heartbeat_ipc << " cumulative IPC: " << cumulative_ipc;
        cout << " (Simulation time: " << elapsed_hour << " hr " << elapsed_minute << " min " << elapsed_second << " sec) " << endl;
        ooo_cpu[i]->next_print_instruction += STAT_PRINTING_PERIOD;

        ooo_cpu[i]->last_sim_instr = ooo_cpu[i]->num_retired;
        ooo_cpu[i]->last_sim_cycle = ooo_cpu[i]->current_cycle;
      }

      // check for warmup
      // warmup complete
      if ((warmup_complete[i] == 0) && (ooo_cpu[i]->num_retired > warmup_instructions)) {
        warmup_complete[i] = 1;
        all_warmup_complete++;
      }
      if (all_warmup_complete == NUM_CPUS) { // this part is called only once
                                             // when all cores are warmed up
        all_warmup_complete++;
        finish_warmup();
      }

      // simulation complete
      if ((all_warmup_complete > NUM_CPUS) && (simulation_complete[i] == 0)
          && (ooo_cpu[i]->num_retired >= (ooo_cpu[i]->begin_sim_instr + simulation_instructions))) {
        simulation_complete[i] = 1;
        ooo_cpu[i]->finish_sim_instr = ooo_cpu[i]->num_retired - ooo_cpu[i]->begin_sim_instr;
        ooo_cpu[i]->finish_sim_cycle = ooo_cpu[i]->current_cycle - ooo_cpu[i]->begin_sim_cycle;

        cout << "Finished CPU " << i << " instructions: " << ooo_cpu[i]->finish_sim_instr << " cycles: " << ooo_cpu[i]->finish_sim_cycle;
        cout << " cumulative IPC: " << ((float)ooo_cpu[i]->finish_sim_instr / ooo_cpu[i]->finish_sim_cycle);
        cout << " (Simulation time: " << elapsed_hour << " hr " << elapsed_minute << " min " << elapsed_second << " sec) " << endl;

        for (auto it = caches.rbegin(); it != caches.rend(); ++it)
          record_roi_stats(i, *it);
      }
    }
  }

  uint64_t elapsed_second = (uint64_t)(time(NULL) - start_time), elapsed_minute = elapsed_second / 60, elapsed_hour = elapsed_minute / 60;
  elapsed_minute -= elapsed_hour * 60;
  elapsed_second -= (elapsed_hour * 3600 + elapsed_minute * 60);

  cout << endl << "ChampSim completed all CPUs" << endl;
  if (NUM_CPUS > 1) {
    cout << endl << "Total Simulation Statistics (not including warmup)" << endl;
    for (uint32_t i = 0; i < NUM_CPUS; i++) {
      cout << endl
           << "CPU " << i
           << " cumulative IPC: " << (float)(ooo_cpu[i]->num_retired - ooo_cpu[i]->begin_sim_instr) / (ooo_cpu[i]->current_cycle - ooo_cpu[i]->begin_sim_cycle);
      cout << " instructions: " << ooo_cpu[i]->num_retired - ooo_cpu[i]->begin_sim_instr
           << " cycles: " << ooo_cpu[i]->current_cycle - ooo_cpu[i]->begin_sim_cycle << endl;
      for (auto it = caches.rbegin(); it != caches.rend(); ++it)
        print_sim_stats(i, *it);
    }
  }

  cout << endl << "Region of Interest Statistics" << endl;
  for (uint32_t i = 0; i < NUM_CPUS; i++) {
    cout << endl << "CPU " << i << " cumulative IPC: " << ((float)ooo_cpu[i]->finish_sim_instr / ooo_cpu[i]->finish_sim_cycle);
    cout << " instructions: " << ooo_cpu[i]->finish_sim_instr << " cycles: " << ooo_cpu[i]->finish_sim_cycle << endl;
    for (auto it = caches.rbegin(); it != caches.rend(); ++it)
      print_roi_stats(i, *it);
  }

  for (auto it = caches.rbegin(); it != caches.rend(); ++it)
    (*it)->impl_prefetcher_final_stats();

  for (auto it = caches.rbegin(); it != caches.rend(); ++it)
    (*it)->impl_replacement_final_stats();

#ifndef CRC2_COMPILE
  print_dram_stats();
  print_branch_stats();
#endif

  cout << "QUEUE Stats: " << endl;
  for (uint32_t i = 0; i < NUM_CPUS; i++) {
    print_queue_stats(i);
  }

  cout << "Read Stats: " << endl;
  for (uint32_t i = 0; i < NUM_CPUS; i++) {
    for (auto it = caches.rbegin(); it != caches.rend(); ++it)
      if((*it)->NAME.find("L1D") != string::npos ||
         (*it)->NAME.find("L2C") != string::npos ||
         (*it)->NAME.find("LLC") != string::npos ){
        print_roi_read_stats(i, *it);
      }
  }

  print_stride_ptchain_stats();

extern uint64_t anti_order_num;
  cout << "L1D anti_order_num: " << anti_order_num << endl;

  print_idm_info();

  cout << "[Tyche]: total execute instruction number: " << total_exc_num << endl;

extern uint64_t successor_num[25];
  //for (size_t i = 0; i < 25; i++) {
  //  cout << "successor_num[" << i << "]" << successor_num[i] << endl;
  //}

  cout << "dct_search_num: " << dct_search_num << endl;
  cout << "dct_write_num: " << dct_write_num << endl;

  cout << "isq_search_num: " << isq_search_num << endl;
  cout << "isq_write_num: " << isq_write_num << endl;


    cout << "ima_pref_num: " << ima_pref_num << endl;
    cout << "ima_pref_miss_num: " << ima_pref_miss_num << endl;

  return 0;
}
