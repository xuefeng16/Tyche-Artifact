#ifndef OOO_PREFETCH_H
#define OOO_PREFETCH_H

#include <cstdint>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip>

#include <stdio.h>
#include <ir2.h>
#include <ins.h>

#define DEBUG

#define XF_DEBUG 0

#define IPT_NUM 32

#define SP_CONF_MAX 3

#define IDM_BIT 8
#define IDM_NUM (1 << IDM_BIT)

#define IPTAG_BIT   47

#define PREFETCH_DEBUG

#define L2_STRIDE_SHIFT 0

#define LOAD_NONE    0
#define LOAD_STRIDE  1
#define LOAD_INFECT  2
#define LOAD_COMPLEX 3

using namespace std;

typedef enum {
    PREF_NONE,
    PREF_STRIDE,
    PREF_PTC,
    PREF_IMD,
    PREF_IMD_END
} PREF_TYPE;


typedef struct pt_format {
    uint8_t type;
    uint64_t dct_ptr;
} pt_format_t;

class IPT_L1 {
    public:
        uint64_t ip = 0;
        uint64_t last_addr = 0;
        int64_t stride = 0;
        uint8_t conf = 0;

        uint8_t rplc_bits; // 3 means most recently used, 0 means least recently used

        vector<uint64_t> pref_filter;
};

typedef enum {
    IDM_INVALID,
    IDM_ADD_W,
    IDM_ADD_D,
    IDM_SUB_W,
    IDM_SUB_D,
    IDM_ALSL0_W,
    IDM_ALSL1_W,
    IDM_ALSL2_W,
    IDM_ALSL3_W,
    IDM_ALSL0_WU,
    IDM_ALSL1_WU,
    IDM_ALSL2_WU,
    IDM_ALSL3_WU,
    IDM_ALSL0_D,
    IDM_ALSL1_D,
    IDM_ALSL2_D,
    IDM_ALSL3_D,
    IDM_AND,
    IDM_OR, // MOVE
    IDM_XOR,
    IDM_MUL_W,
    IDM_MUL_D,
    IDM_SRL_W,
    IDM_SRL_D,
    IDM_SLLI_W,
    IDM_SLLI_D,

    //IDM_SLT,
    //IDM_MASKEQZ,

    IDM_SRA_W,
    IDM_SRA_D,
    IDM_BSTRPICK_W,
    IDM_BSTRPICK_D,

    // Branch
    IDM_BEQ,
    IDM_BNE,
    IDM_BLT,
    IDM_BLTU,
    IDM_BGE,
    IDM_BGEU,
    IDM_BEQZ,
    IDM_BNEZ,

    IDM_LD_B,
    IDM_LD_BU,
    IDM_LD_H,
    IDM_LD_HU,
    IDM_LD_W,
    IDM_LD_WU,
    IDM_LD_D,

    //IDM_NOR,
    //IDM_ANDN,
    //IDM_ORN,
} IDM_OP;

class AGQ_ITEM{
public:
    bool valid = true;
    bool issued = false;
    uint64_t ret_value;
    uint64_t dct_ptr;

    #ifdef PREFETCH_DEBUG
        uint64_t cycle;
    #endif

    // is_load is added just for we can use it in search_addr function. But we can actually get 
    // this info from dct.
    bool is_load;

    // These two fields are used to update mul result.
    uint8_t alu_cycle;
    uint64_t alu_res;

    void print();
};

#define AGQ_SIZE  16

class AGQ {
public:
    vector<AGQ_ITEM> buffer;
    uint32_t SIZE;
    bool pop_when_full = false;
    uint32_t cpu;

    uint64_t AGQ_FULL = 0;
    uint64_t AGQ_CLEAR = 0;
    uint64_t AGQ_ALU_ALONE = 0;
    uint64_t AGQ_BEYOND_NUM = 0;

    uint64_t insert(AGQ_ITEM& item);
    vector<AGQ_ITEM>::iterator search_addr(uint64_t addr);
    vector<AGQ_ITEM>::iterator first_ready_item();
    bool update_src(vector<AGQ_ITEM>::iterator ret_item, uint64_t ret_val);
    void clear_agq();
#ifdef PREFETCH_DEBUG
    string name;
    uint64_t full_cycles = 0;
    void check_state();
    void print_buffer();
#endif
};

class DCT_ITEM {
public:
    bool valid = false;
    bool head = false;
    bool formed;
    bool dense = true;
    uint8_t conf = 0;
    uint64_t pc;
    IDM_OP op = IDM_INVALID;
    bool const_idx;
    uint64_t src;
    uint64_t last_dct_ptr;
    uint8_t cnt = 1;

    #ifdef PREFETCH_DEBUG
        uint64_t ip;
        uint64_t cycle;
    #endif

    uint64_t execute_alu(uint64_t dynamic_src);
    inline bool need_handle(){
        return formed && (conf == 3) && dense;
    }
    void print();

    DCT_ITEM(bool valid, bool head, bool formed, uint8_t conf, uint64_t pc, IDM_OP op,
             bool const_idx, uint64_t src, uint64_t last_dct_ptr, uint64_t ip, uint64_t cycle)
           : valid(valid), head(head), formed(formed), conf(conf), pc(pc), op(op),
             const_idx(const_idx), src(src), last_dct_ptr(last_dct_ptr)
       #ifdef PREFETCH_DEBUG
             , ip(ip), cycle(cycle)
       #endif
    {
    }

};

class DCT { // instruction chain table
    public:
        vector<DCT_ITEM> buffer;
        const uint32_t SIZE;
        uint32_t cpu;

        /**
         * Actually we need not head & tail. DCT is not a real fifo. When we insert a new item
         * into the buffer and the buffer is full, we will clear all items in DCT.
         */
        uint64_t head = 0;
        uint64_t tail = 0;
        uint64_t IDM_ISSSUEQ_FULL = 0;

    bool is_valid_item(vector<DCT_ITEM>::const_iterator item);
    bool is_full();
    uint64_t insert(DCT_ITEM& item);
    void clear_dct();
    bool has_successor(uint64_t index);
    uint64_t search_pc(uint64_t pc);
    //void remove_back();
    //void remove_head_chain();
#ifdef DEBUG
    void check_state();
    void print_buffer();
    void print_item(size_t index);
#endif

    DCT(): SIZE(24){
        for (uint i = 0; i < SIZE; i++) {
            DCT_ITEM item(false, false, false, 0, 0, IDM_INVALID, true, 0, 0
        #ifdef PREFETCH_DEBUG
            , 0, 0);
        #endif
            buffer.push_back(item);
        }
    }
};


#ifdef __cplusplus
extern "C" {
#endif
uint64_t l1_encode_metadata(uint8_t dest_reg, uint8_t size, bool unsign_ext);
uint8_t l1_decode_dest_reg(uint64_t metadata);
uint8_t l1_decode_size(uint64_t metadata);
bool l1_decode_unsign_ext(uint64_t metadata);

uint64_t encode_metadata(int stride, PREF_TYPE pref_type);
int32_t decode_stride(uint64_t metadata);
PREF_TYPE decode_pref_type(uint64_t metadata);

IDM_OP encode_imd_op_ld(uint8_t size, bool unsign_ext);
IDM_OP decode_imd_op(uint16_t inst_op,/* uint64_t src0,*/ uint64_t src1, uint64_t src2);
bool idm_op_is_load(IDM_OP op);
bool idm_op_is_mul(IDM_OP op);
bool idm_op_is_complex(IDM_OP op);
uint8_t idm_op_get_size(IDM_OP op);
bool idm_op_is_unsign_ext(IDM_OP op);
void idm_load_return(uint32_t cpu, uint64_t addr);

#ifdef __cplusplus
}
#endif

#endif

#define L1_STRIDE_DISTANCE 32