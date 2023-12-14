#include <algorithm>
#include <array>
#include <map>

#include "cache.h"
#include "prefetch.h"

#define nPRINT_TRACE

void CACHE::l2c_prefetcher_initialize() 
{
    std::cout << NAME << " Stride L2Cache prefetcher" << std::endl; 
}

void CACHE::prefetcher_cycle_operate()
{

}

uint64_t CACHE::l2c_prefetcher_operate(uint64_t addr, uint64_t ip, uint8_t cache_hit, uint8_t type, uint64_t metadata_in)
{
    if(type==PREFETCH){
        PREF_TYPE pref_type = decode_pref_type(metadata_in);
        int32_t stride = decode_stride(metadata_in);

        if(pref_type == PREF_STRIDE){
            uint64_t pf_address = addr + (stride << L2_STRIDE_SHIFT);
            prefetch_line(pf_address, true, metadata_in);

            #ifdef PRINT_TRACE
                cout  << "\t[Stride L2C      ] cycles: " << current_cycle << hex 
                      << ", base_addr: " << addr
                      << ", pf_addr: " << pf_address 
                      << ", type: " << +type
                      << ", metadata_in: " << metadata_in 
                      << dec << endl;
            #endif
        }
    }

    return metadata_in;
}


uint64_t CACHE::l2c_prefetcher_cache_fill(uint64_t addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t evicted_addr, uint64_t metadata_in, int64_t ret_val)
{
  return metadata_in;
}


void CACHE::l2c_prefetcher_final_stats() {}