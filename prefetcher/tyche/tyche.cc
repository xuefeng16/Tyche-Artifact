#include <algorithm>
#include <array>
#include <map>
#include <unordered_map>

#include "cache.h"
#include "prefetch.h"
#include "memory_data.h"

#define DEBUG
#define PRINT_INSTR_PC 0xffffffffffffffff
#define PRINT_OPERATE_TRACE XF_DEBUG
#define PRINT_CYCLE_OPERATE XF_DEBUG
#define PRINT_CACHE_FILL_TRACE XF_DEBUG
#define nCOLLECT_LOAD_INFO
#define COLLECT_LOAD_PC 0xffffffffffffffff

#define AMEND_OFF

extern bool start_print;

#ifdef PREF_NUM
    std::map<uint64_t, uint64_t> pref_num;
#endif

extern uint8_t trace_type;
extern IPT_L1 ipt[NUM_CPUS][IPT_NUM];

extern DCT dct[NUM_CPUS]; // instruction chain table
extern AGQ agq[NUM_CPUS];
extern uint64_t total_exc_num;

extern uint64_t isq_search_num;

extern MEMORY_DATA mem_data[NUM_CPUS];

bool only_stride = false;

typedef struct load_miss_info {
  uint64_t total_count;
  uint64_t miss_count;
} load_miss_info_t;
unordered_map<uint64_t, load_miss_info_t> load_info;
unordered_map<uint64_t, uint64_t> load_addr_info;

#ifdef IC_LENGTH_INFO
extern unordered_map<uint64_t, uint64_t> ic_length_info;
extern unordered_map<IDM_OP, uint64_t> ict_op_info;
#endif

void CACHE::l1d_prefetcher_initialize() { 
    std::cout << NAME << " Tyche DCache prefetcher" << "cpu: " << cpu << std::endl; 
    for(uint32_t i = 0; i < IPT_NUM; i++){
        ipt[cpu][i].conf = 0;
        ipt[cpu][i].rplc_bits = i;
    }

    agq[cpu].cpu = cpu;
    agq[cpu].SIZE = AGQ_SIZE;
    agq[cpu].pop_when_full = false;
#ifdef PREFETCH_DEBUG
    agq[cpu].name = "l1_agq";
#endif

    dct[cpu].cpu = cpu;
    cout << "Stride ISQ Size: " << AGQ_SIZE << endl;

    cout << "L1 Stride distance: " << L1_STRIDE_DISTANCE << endl;

#ifdef IC_LENGTH_INFO
    for(uint64_t i = IDM_INVALID; i < IDM_LD_D; i++){
        ict_op_info.insert(pair<IDM_OP, uint64_t>((IDM_OP)i, 0));
    }
#endif
}

void CACHE::prefetcher_cycle_operate()
{
#ifdef PREFETCH_DEBUG
    agq[cpu].check_state();
    dct[cpu].check_state();
#endif

    auto agq_item = agq[cpu].first_ready_item();
    if(agq_item != agq[cpu].buffer.end()){
        uint64_t dct_ptr = agq_item->dct_ptr;
        auto dct_item = dct[cpu].buffer.begin() + dct_ptr;

        isq_search_num++;

        #if PRINT_CYCLE_OPERATE == 1
        //if(start_print)
            cout << "[cycle_operate    ] ";
            agq_item->print();
        #endif
        if(idm_op_is_load(dct_item->op)){
            bool has_successor = dct[cpu].has_successor(dct_ptr);
            uint64_t pf_metadata = encode_metadata(dct_ptr, has_successor? PREF_IMD : PREF_IMD_END);
            uint64_t pf_address = dct_item->src + agq_item->ret_value;
            if(pf_address & 0xffffff0000000000 || pf_address == 0){
                agq[cpu].AGQ_BEYOND_NUM++;
                agq[cpu].buffer.erase(agq_item);
            } else {
                int succ = prefetch_line(pf_address, true, pf_metadata);

            #ifdef PREF_NUM
                auto hit_item = pref_num.find(dct_item->ip);
                if(hit_item != pref_num.end()){
                    hit_item->second++;
                }else{
                    pref_num.insert(std::pair<uint64_t,uint64_t>(dct_item->ip, 1));
                }
            #endif

                if(succ == 1){
                    agq_item->issued = true;
                    agq_item->ret_value = pf_address;
                    if(!has_successor){
                        agq[cpu].buffer.erase(agq_item);
                    }
                }
                total_exc_num++;
            }
        } else {
            uint64_t alu_ret_val = dct_item->execute_alu(agq_item->ret_value);
            if(idm_op_is_mul(dct_item->op)){
                agq_item->issued = true;
                agq_item->alu_res = alu_ret_val;
                agq_item->alu_cycle = 3;
            } else{
                agq_item->issued = true;
                agq_item->alu_res = alu_ret_val;
                agq_item->alu_cycle = 2;
            }
            total_exc_num++;
        }
    }

    for(auto it = agq[cpu].buffer.begin(); it != agq[cpu].buffer.end(); it++) {
        auto dct_item = dct[cpu].buffer.begin() + it->dct_ptr;
        if(!idm_op_is_load(dct_item->op) && it->issued && it->alu_cycle > 0){
            it->alu_cycle--;
        }
    }

    for(auto it = agq[cpu].buffer.begin(); it != agq[cpu].buffer.end(); it++) {
        auto dct_item = dct[cpu].buffer.begin() + it->dct_ptr;

        if(!idm_op_is_load(dct_item->op) && it->issued && it->alu_cycle == 0){
            bool has_successor = agq[cpu].update_src(it, it->alu_res);
            if(!has_successor){
                agq[cpu].buffer.erase(it);
                agq[cpu].AGQ_ALU_ALONE++;
            }
            break;
        }
    }
} 

uint8_t update_conf(int64_t stride, int64_t last_stride, uint8_t conf){
    uint8_t conf_ret;
    if (stride == 0){
        conf_ret = conf;
    } else if(conf == 1){
        conf_ret = conf + 1;
    } else if(stride == last_stride){
        conf_ret = (conf < SP_CONF_MAX)? (conf+1) : conf;
    } else{
        conf_ret = (conf > 0          )? (conf-1) : 0;
    }

    return conf_ret;
}

void search_ima(uint32_t cpu, uint64_t ip, uint64_t pf_address, uint64_t current_cycle, uint64_t origin_addr, int64_t delta) {
    int64_t dct_ptr = dct[cpu].search_pc(ip);

    if(dct_ptr != -1 && dct[cpu].has_successor(dct_ptr) && dct[cpu].buffer[dct_ptr].head){
        AGQ_ITEM new_agq_item;
        new_agq_item.valid = true;
        new_agq_item.issued = true;
        new_agq_item.ret_value = pf_address;
        new_agq_item.dct_ptr = dct_ptr;
        new_agq_item.is_load = true;
    #ifdef PREFETCH_DEBUG
        new_agq_item.cycle = current_cycle;
    #endif
        agq[cpu].insert(new_agq_item);
    }

#ifdef IC_LENGTH_INFO
    if(dct_ptr != -1 && dct[cpu].has_successor(dct_ptr, true) && dct[cpu].buffer[dct_ptr].head){
        vector<uint64_t> idx_vec = {(uint64_t) dct_ptr};

        int cnt = 0;
        while(!idx_vec.empty()) {
            uint64_t index = *idx_vec.begin();
            idx_vec.erase(idx_vec.begin());

            for (auto it = dct[cpu].buffer.begin(); it != dct[cpu].buffer.end(); it++) {
                if(it->valid && !it->head && it->last_dct_ptr==index && it->need_handle()){
                    idx_vec.push_back(distance(dct[cpu].buffer.begin(), it));
                    ict_op_info[it->op]++;
                }
            }
            cnt++;

            if(cnt > 10000){
                cout << "dct_ptr: " << dct_ptr << endl;
                dct[cpu].print_buffer();
                exit(1);
            }
        }

        std::unordered_map<uint64_t, uint64_t>::iterator hit_item;
        hit_item = ic_length_info.find(cnt);
        if(hit_item != ic_length_info.end()){
            ic_length_info[cnt]++;
        } else{
            ic_length_info.insert(pair<uint64_t, uint64_t>(cnt, 1));
        }
    }

#endif
}


uint64_t CACHE::l1d_prefetcher_operate(uint64_t addr, uint64_t ip, uint8_t cache_hit, uint8_t type, uint64_t metadata_in)
{
    uint64_t trace_ip = (trace_type == TRACE_TYPE_LOONGARCH)? (ip >> 2) : ip;
    uint32_t hit_idx = IPT_NUM;

    #ifdef PREFETCH_DEBUG
        bool dbg_hit = false;
    #endif

    //// Find hit item
    for(uint32_t i = 0; i < IPT_NUM; i++){
        if(ipt[cpu][i].conf != 0 && ipt[cpu][i].ip == trace_ip){
            hit_idx = i;

        #ifdef PREFETCH_DEBUG
            if(dbg_hit){
                cout << "Multi Way Hit!!!" << endl;
                exit(1);
            }
            dbg_hit = true;
        #endif
        }
    }

    //// Stride Hit
    if(hit_idx != IPT_NUM){
        IPT_L1 ipt_hit_item = ipt[cpu][hit_idx];


        int64_t new_stride = addr - ipt_hit_item.last_addr;

        bool ignore = new_stride==0 /*&& !younger*/;

        bool conf_trigger = ipt_hit_item.conf > 1 && ipt_hit_item.stride != 0 &&
                            ((ipt_hit_item.stride == new_stride    ) ||
                             (ipt_hit_item.conf>=3 && new_stride!=0)   );
        bool trigger_prefetch = conf_trigger ;//|| change_to_use_line;

        if(trigger_prefetch){
            int64_t stride = ipt_hit_item.stride;
            uint64_t distance = L1_STRIDE_DISTANCE; // 32
            int64_t delta = stride * distance;

            uint64_t pf_address = addr + delta; 
            uint64_t pf_metadata = encode_metadata((int)(stride * distance), PREF_STRIDE);
            int succ = prefetch_line(pf_address, true, pf_metadata);

            #ifdef PREF_NUM
                auto hit_item = pref_num.find(ip);
                if(hit_item != pref_num.end()){
                    hit_item->second++;
                }else{
                    pref_num.insert(std::pair<uint64_t,uint64_t>(ip, 1));
                }
            #endif

            // Insert into AGQ
            if(!only_stride && succ != 0) {
                search_ima(cpu, trace_ip, pf_address, current_cycle, addr, delta);
            }
        }

        if(!ignore){
            ipt[cpu][hit_idx].last_addr = addr;
            ipt[cpu][hit_idx].conf = update_conf(new_stride, ipt_hit_item.stride, ipt_hit_item.conf);

            if(ipt_hit_item.conf==1){
                ipt[cpu][hit_idx].stride = new_stride;
            }
        }

        for(uint32_t j = 0; j < IPT_NUM; j++){
            if(ipt[cpu][j].rplc_bits > ipt_hit_item.rplc_bits){
                ipt[cpu][j].rplc_bits --;
            }
        }
        ipt[cpu][hit_idx].rplc_bits = IPT_NUM-1;

        return metadata_in;
    } else {
        // Stride Miss
        uint8_t ip_idx = IPT_NUM;
        uint8_t rplc0_idx = IPT_NUM;
        uint8_t conf0_idx  = IPT_NUM;
        uint8_t conf0_rplc = IPT_NUM;

        #ifdef PREFETCH_DEBUG
            bool dbg_hit = false;
        #endif
        for(uint32_t i = 0; i < IPT_NUM; i++){
            if(ipt[cpu][i].conf < 2 && ipt[cpu][i].rplc_bits < conf0_rplc){
                conf0_idx = i;
                conf0_rplc = ipt[cpu][i].rplc_bits;
            }

            if(ipt[cpu][i].ip == trace_ip){
                ip_idx = i;
            }

            if(ipt[cpu][i].rplc_bits == 0){
                rplc0_idx = i;

            #ifdef PREFETCH_DEBUG
                if(dbg_hit){
                    cout << "Find Multiple Entries rplc_bits==0!" << endl;
                    exit(1);
                }
                dbg_hit = true;
            #endif
            }
        }

        uint8_t rplc_idx = (ip_idx < IPT_NUM)? ip_idx : (conf0_idx < IPT_NUM)? conf0_idx : rplc0_idx;

        ipt[cpu][rplc_idx].ip        = trace_ip;
        ipt[cpu][rplc_idx].last_addr = addr;
        ipt[cpu][rplc_idx].conf      = 1;

        for(uint32_t j = 0; j < IPT_NUM; j++){
            if(ipt[cpu][j].rplc_bits > ipt[cpu][rplc_idx].rplc_bits){
                ipt[cpu][j].rplc_bits --;
            }
        }
        ipt[cpu][rplc_idx].rplc_bits = IPT_NUM-1;
        //ipt[cpu][rplc_idx].pref_filter.clear();

        #ifdef PREFETCH_DEBUG
            assert(rplc_idx < IPT_NUM);
        #endif
    }

    return metadata_in;
}


uint64_t CACHE::l1d_prefetcher_cache_fill(uint64_t addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t evicted_addr, uint64_t metadata_in, int64_t ret_val)
{
    #if PRINT_CACHE_FILL_TRACE == 1
        cout << "\t[l1d_prefetcher_cache_fill]" 
             << " cycle: " << current_cycle << hex
             << ", addr: " << addr
             << ", ret_val: " << ret_val << dec
             << endl;
    #endif

    idm_load_return(cpu, addr);

    return metadata_in;
}


void CACHE::l1d_prefetcher_final_stats() {
    cout << "DCT_FULL: " << dct[cpu].IDM_ISSSUEQ_FULL << endl;
    cout << "AGQ_FULL: " << agq[cpu].AGQ_FULL << endl;

#ifdef PREF_NUM
	for (map<uint64_t, uint64_t>::iterator it = pref_num.begin(); it != pref_num.end(); it++){
		cout << "ip = " << hex << it->first << dec << ",  num = " << it->second << endl;
	}
#endif

#ifdef COLLECT_LOAD_INFO
    std::vector<uint64_t> load_pc;
    for(auto &[key, value]: load_info)
        load_pc.emplace_back(key);

    sort(load_pc.begin(), load_pc.end(), [&](const uint64_t&a, const uint64_t&b)->bool{
        return load_info[a].total_count==load_info[b].total_count? a<b : load_info[a].total_count>load_info[b].total_count;
    });

    uint32_t num = 50;
    uint32_t icount = 0;
    for(auto i = load_pc.begin(); i != load_pc.end(); i++){
        uint64_t pc = *i;
        load_miss_info_t info_item =  load_info[*i];
        double miss_ratio = 1.0*info_item.miss_count/info_item.total_count;
        printf("[%02d]: PC: %#lx, load num: %8ld, miss num: %8ld, miss ratio: %6.2f%%\n", icount, pc, info_item.total_count, info_item.miss_count, miss_ratio*100);
    
        //icount++;
        if(++icount == num)
            break;
    }
#endif

#if COLLECT_LOAD_PC != 0xffffffffffffffff
    cout << "The Address Range of PC: " << hex << COLLECT_LOAD_PC << dec;
    cout << " is " << load_addr_info.size() << " * size of the load." << endl;

    std::vector<uint64_t> load_addr;
    for(auto &[key, value]: load_addr_info)
        load_addr.emplace_back(key);

    sort(load_addr.begin(), load_addr.end(), [&](const uint64_t&a, const uint64_t&b)->bool{
        return load_addr_info[a]==load_addr_info[b]? a<b : load_addr_info[a]>load_addr_info[b];
    });

    uint32_t addr_num = 10;
    uint32_t addr_icount = 0;
    for(auto i = load_addr.begin(); i != load_addr.end(); i++){
        printf("[%02d]: num: %8ld\n", addr_icount, load_addr_info[*i]);

        //icount++;
        if(++addr_icount == addr_num)
            break;
    }
#endif
}
