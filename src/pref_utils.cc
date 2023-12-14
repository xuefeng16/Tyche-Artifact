#include "prefetch.h"
#include "cache.h"

#include "champsim_constants.h"
#include "memory_data.h"
#include "instruction.h"

#define PRINT_CYCLE 32696

#define ISQ_WRITE_PORT 4

#define nPRINT_ICT_INSERT
#define PRINT_STRIDE_INSERT XF_DEBUG
#define PRINT_STRIDE_UPDATE XF_DEBUG
#define nCHECK_MEM_READ

#define nPRINT_OPERATE_TRACE
#define nPRINT_PERF_TRACE
#define nPRINT_MEM_TRACE

extern map<uint64_t, uint64_t> consumer_map;
extern uint64_t isq_write_num;

using namespace std;

extern bool start_print;
extern DCT dct[NUM_CPUS];
extern AGQ agq[NUM_CPUS];
extern pt_format_t pt[NUM_CPUS][64];
extern MEMORY_DATA mem_data[NUM_CPUS];

extern uint8_t warmup_complete[NUM_CPUS];

uint64_t l1_encode_metadata(uint8_t dest_reg, uint8_t size, bool unsign_ext){
	uint64_t metadata = 0;
    metadata = dest_reg;
    metadata = metadata | (size << 8);
    metadata = metadata | (unsign_ext << 16);
    return metadata;
}

uint64_t successor_num[25] = {};

uint8_t l1_decode_size(uint64_t metadata){
    uint8_t size = (metadata >> 8) & 0xff;
    return size;
}

bool l1_decode_unsign_ext(uint64_t metadata){
    bool unsign_ext = (metadata >> 16) & 0b1;
    return unsign_ext;
}

uint8_t l1_decode_dest_reg(uint64_t metadata){
    uint8_t dest_reg = metadata & 0xff;
    return dest_reg;
}

uint64_t encode_metadata(int stride, PREF_TYPE pref_type){
	uint64_t metadata = 0;

	if(stride > 0)
    	metadata = stride & 0x7fffffff;
	else
    	metadata = (((-1*stride) & 0x7fffffff) | 0x80000000);

	// encode the type of IP in the next 4 bits 			 
	metadata = metadata | ((uint64_t)pref_type << 32);
	return metadata;
}

int32_t decode_stride(uint64_t metadata){
    int32_t stride=0;
    if(metadata & 0x80000000)
        stride = -1*(metadata & 0x7fffffff);
    else
        stride = metadata & 0x7fffffff;

    return stride;
}

PREF_TYPE decode_pref_type(uint64_t metadata){
    PREF_TYPE pref_type = PREF_TYPE ((metadata >> 32) & 0x7);
    return pref_type;
}

IDM_OP encode_imd_op_ld(uint8_t size, bool unsign_ext){
    if(size == SIZE_DWORD){
        return IDM_LD_D;
    } else if(size == SIZE_WORD){
        return unsign_ext? IDM_LD_WU : IDM_LD_W;
    } else if(size == SIZE_HWORD){
        return unsign_ext? IDM_LD_HU : IDM_LD_H;
    } else if(size == SIZE_BYTE){
        return unsign_ext? IDM_LD_BU : IDM_LD_B;
    } else {
        printf("unsupported size\n");
        exit(1);
    }
}

IDM_OP decode_imd_op(uint16_t inst_op,/* uint64_t src0,*/ uint64_t src1, uint64_t src2){
    switch (inst_op) {
        case LISA_ADD_W:
        case LISA_ADDI_W:
            return IDM_ADD_W;
        case LISA_ADD_D:
        case LISA_ADDI_D:
            return IDM_ADD_D;
        case LISA_SUB_W:
            return IDM_SUB_W;
        case LISA_SUB_D:
            return IDM_SUB_D;
        case LISA_ALSL_W:
            switch (src2) {
                case 0:
                    return IDM_ALSL0_W;
                case 1:
                    return IDM_ALSL1_W;
                case 2:
                    return IDM_ALSL2_W;
                case 3:
                    return IDM_ALSL3_W;
                default:
                    printf("Error ALSL Imm!\n");
                    exit(1);
            }
        case LISA_ALSL_WU:
            switch (src2) {
                case 0:
                    return IDM_ALSL0_WU;
                case 1:
                    return IDM_ALSL1_WU;
                case 2:
                    return IDM_ALSL2_WU;
                case 3:
                    return IDM_ALSL3_WU;
                default:
                    printf("Error ALSL Imm!\n");
                    exit(1);
            }
        case LISA_ALSL_D:
            switch (src2) {
                case 0:
                    return IDM_ALSL0_D;
                case 1:
                    return IDM_ALSL1_D;
                case 2:
                    return IDM_ALSL2_D;
                case 3:
                    return IDM_ALSL3_D;
                default:
                    printf("Error ALSL Imm!\n");
                    exit(1);
            }
        //case LISA_SLT:
        //    return IDM_SLT;
        //case LISA_MASKEQZ:
        //    return IDM_MASKEQZ;
        case LISA_AND:
        case LISA_ANDI:
            return IDM_AND;
        case LISA_OR:
            return IDM_OR;
        case LISA_XOR:
        case LISA_XORI:
            return IDM_XOR;
        case LISA_MUL_W:
            return IDM_MUL_W;
        case LISA_MUL_D:
            return IDM_MUL_D;
        case LISA_SRL_W:
        case LISA_SRLI_W:
            return IDM_SRL_W;
        case LISA_SRL_D:
        case LISA_SRLI_D:
            return IDM_SRL_D;
        case LISA_SLLI_W:
           return IDM_SLLI_W;
        case LISA_SLLI_D:
            return IDM_SLLI_D;
        case LISA_SRA_W:
        case LISA_SRAI_W:
            return IDM_SRA_W;
        case LISA_SRA_D:
        case LISA_SRAI_D:
            return IDM_SRA_D;
        case LISA_BSTRPICK_W:
            return IDM_BSTRPICK_W;
        case LISA_BSTRPICK_D:
            return IDM_BSTRPICK_D;
        case LISA_BEQ:
            return IDM_BEQ;
        case LISA_BNE:
            return IDM_BNE;
        case LISA_BLT:
            return IDM_BLT;
        case LISA_BLTU:
            return IDM_BLTU;
        case LISA_BGE:
            return IDM_BGE;
        case LISA_BGEU:
            return IDM_BGEU;
        case LISA_BEQZ:
            return IDM_BEQZ;
        case LISA_BNEZ:
            return IDM_BNEZ;
        case LISA_LD_B:
        case LISA_LDX_B:
            return IDM_LD_B;
        case LISA_LD_BU:
        case LISA_LDX_BU:
            return IDM_LD_BU;
        case LISA_LD_H:
        case LISA_LDX_H:
            return IDM_LD_H;
        case LISA_LD_HU:
        case LISA_LDX_HU:
            return IDM_LD_HU;
        case LISA_LD_W:
        case LISA_LL_W:
        case LISA_LDX_W:
        case LISA_LDPTR_W:
            return IDM_LD_W;
        case LISA_LD_WU:
        case LISA_LDX_WU:
        case LISA_FLD_S:
        case LISA_FLDX_S:
            return IDM_LD_WU;
        case LISA_LD_D:
        case LISA_LL_D:
        case LISA_LDX_D:
        case LISA_LDPTR_D:
        case LISA_FLD_D:
        case LISA_FLDX_D:
            return IDM_LD_D;
        default:
            return IDM_INVALID;
    }
}

bool idm_op_is_complex(IDM_OP op){
    switch (op) {
    case IDM_AND:
    case IDM_OR:
    case IDM_XOR:
    // case IDM_BSTRPICK_W:
    // case IDM_BSTRPICK_D:
    //case IDM_SLT:
    //case IDM_MASKEQZ:
        return true;
    default:
        return false;
    }
}

bool idm_op_is_load(IDM_OP op){
    switch (op) {
        case IDM_LD_B:
        case IDM_LD_BU:
        case IDM_LD_H:
        case IDM_LD_HU:
        case IDM_LD_W:
        case IDM_LD_WU:
        case IDM_LD_D:
            return true;
        default:
            return false;
    }
}

bool idm_op_is_branch(IDM_OP op){
    switch (op) {
        case IDM_BEQ:
        case IDM_BNE:
        case IDM_BLT:
        case IDM_BLTU:
        case IDM_BGE:
        case IDM_BGEU:
        case IDM_BEQZ:
        case IDM_BNEZ:
            return true;
        default:
            return false;
    }
}

bool idm_op_is_mul(IDM_OP op){
    switch (op) {
        case IDM_MUL_W:
        case IDM_MUL_D:
            return true;
        default:
            return false;
    }
}

uint8_t idm_op_get_size(IDM_OP op){
    switch (op) {
        case IDM_LD_B:
        case IDM_LD_BU:
            return SIZE_BYTE;
        case IDM_LD_H:
        case IDM_LD_HU:
            return SIZE_HWORD;
        case IDM_LD_W:
        case IDM_LD_WU:
            return SIZE_WORD;
        case IDM_LD_D:
            return SIZE_DWORD;
        default:
            return SIZE_NONE;
    }
}

bool idm_op_is_unsign_ext(IDM_OP op){
    switch (op) {
        case IDM_LD_BU:
        case IDM_LD_HU:
        case IDM_LD_WU:
            return true;
        default:
            return false;
    }
}

void AGQ_ITEM::print(){
    cout << "valid: " << +valid
         << ", issued: " << +issued
         << ", dct_ptr: " << +dct_ptr << hex 
         << ", ret_value: " << ret_value << dec
         << ", alu_cycle: " << +alu_cycle << dec
    #ifdef PREFETCH_DEBUG
         << ", cycle: " << cycle
    #endif
         << endl;
}

uint64_t AGQ::insert(AGQ_ITEM& item){
#if PRINT_STRIDE_INSERT == 1
    cout << "\t[stride insert] " << name << ", size: " << buffer.size() << ", ";
    item.print();
#endif
    if(buffer.size() == SIZE){
        AGQ_FULL++;
        if(pop_when_full){
            buffer.erase(buffer.begin());
        } else{
            return -1;
        }
    }

    buffer.push_back(item);
    return 0;
}

vector<AGQ_ITEM>::iterator AGQ::search_addr(uint64_t addr){
    for(auto it = buffer.begin(); it != buffer.end(); it++){
        if(it->valid && it->issued && (addr >> 6) == (it->ret_value >> 6) && it->is_load){
            return it;
        }
    }
    return buffer.end();
}

vector<AGQ_ITEM>::iterator AGQ::first_ready_item(){
    for(auto i=buffer.begin(); i!=buffer.end(); i++){
        if(i->valid && !i->issued){
            return i;
        }
    }

    return buffer.end();
}

bool AGQ::update_src(vector<AGQ_ITEM>::iterator ret_item, uint64_t ret_val){
#if PRINT_STRIDE_UPDATE == 1
    if(PRINT_CYCLE == 0xffffffffffffffff || PRINT_CYCLE == ret_item->cycle){
        cout << "\t[stride_isq update] pos: " << distance(buffer.begin(), ret_item) << ", ret_val: " << ret_val << ", ";
        ret_item->print();
    }
#endif
    uint64_t dct_ptr = ret_item->dct_ptr;
    bool has_found = false;
    uint64_t found_num = 0;

    for(auto it = dct[cpu].buffer.begin(); it != dct[cpu].buffer.end() && found_num < ISQ_WRITE_PORT; it++){
        bool need_handle = it->need_handle();

        if(it->valid && !it->head && it->last_dct_ptr == dct_ptr && need_handle){
            if(!has_found){ // first item
                ret_item->ret_value = ret_val;
                ret_item->issued = false;
                ret_item->dct_ptr = distance(dct[cpu].buffer.begin(), it);
                ret_item->is_load = idm_op_is_load(it->op);
            } else { 
                AGQ_ITEM new_agq_item;
                new_agq_item.valid = true;
                new_agq_item.issued = false;
                new_agq_item.ret_value = ret_val;
                new_agq_item.dct_ptr = distance(dct[cpu].buffer.begin(), it);
                new_agq_item.is_load = idm_op_is_load(it->op);
            #ifdef PREFETCH_DEBUG
                new_agq_item.cycle = ret_item->cycle;
            #endif
                insert(new_agq_item);
            }
            has_found = true;
            found_num++;
            isq_write_num++;
        }
    }

    //successor_num[found_num]++;
    return has_found;
}

void AGQ::clear_agq() {
    AGQ_CLEAR++;
    buffer.clear();
}

bool DCT::is_full(){
    return buffer[tail].valid;
}

uint64_t DCT::insert(DCT_ITEM& item){
    if(is_full()){
        //remove_head_chain();
        clear_dct();
        IDM_ISSSUEQ_FULL++;
        return -1;
    }

#ifdef PRINT_ICT_INSERT
    cout << "\t[dct insert  ] tail: " << tail << ", ";
    item.print();
#endif
    uint64_t insert_pos = tail;
    buffer[insert_pos] = item;
    tail = (insert_pos+1)%SIZE;

    return insert_pos;
}

void DCT::clear_dct(){
    for(auto it = buffer.begin(); it != buffer.end(); it++){
        it->valid = false;
    }
    head = 0;
    tail = 0;
    agq[cpu].clear_agq();
    for(int i = 0; i < 64; i++){
        pt[cpu][i].type = NONE;
    }
}

bool DCT::has_successor(uint64_t index){
    for (auto it = buffer.begin(); it != buffer.end(); it++) {
        bool need_handle = it->need_handle();
        if(it->valid && !it->head && it->last_dct_ptr==index && need_handle){
            return true;
        }
    }

    return false;
}

uint64_t DCT::search_pc(uint64_t ip){
    int64_t hit_cnt = 0;
    uint64_t hit_idx = -1;
    for (auto it = buffer.begin(); it != buffer.end(); it++){
        if(it->valid && (it->pc == ip)){
            hit_cnt++;
            hit_idx = distance(buffer.begin(), it);
        }
    }
    if(hit_cnt > 1){
        printf("Multi Hit in DCT\n");
        exit(1);
    }

    return hit_idx;
}

//void DCT::remove_back(){
//    buffer[--tail].valid = false;
//}

//void DCT::remove_head_chain(){
//    auto it = buffer.begin()+head;
//    while (it->valid && !it->head){
//        it->valid = false;
//        head++;
//        it++;
//        if(it == buffer.end()){
//            it = buffer.begin();
//        }
//    }
//#ifdef PRINT_IDM_ISQ_REMOVE_HIT
//    cout << "[remove_cache_hit ]" << hex
//         << " addr : " << addr << dec
//         << ", after size : " << buffer.size()
//         << endl;
//#endif
//}

#ifdef DEBUG
void AGQ::print_buffer(){
    cout << "AGQ Info: " << name << endl;
    for(auto it = buffer.begin(); it != buffer.end(); it++){
        cout << "stride_isq[" << setw(2) << distance(buffer.begin(), it) << "]: ";
        it->print();
    }
}

void AGQ::check_state(){
    bool error = false;
    if(buffer.size() > SIZE){
        error = true; printf("AGQ SIZE Error!\n");
    }
    for(auto it = buffer.begin(); it != buffer.end(); it++){
        if(!dct[cpu].buffer[it->dct_ptr].valid){
            error = true; printf("AGQ point to invalid idm_issueq!\n");
        }
    }

    if(buffer.size() == SIZE){
        full_cycles++;
    } else {
        full_cycles = 0;
    }
    //if(full_cycles > 100000000){
    //    error = true; printf("AGQ Full For A Long Time!\n");
    //}

    if(error){
        print_buffer();
        exit(1);
    }
}


void DCT::print_buffer(){
    printf("DCT Info:\n");
    printf("head = %ld, tail = %ld\n", head, tail);
    for(auto it = buffer.begin(); it != buffer.end(); it++){
        print_item(distance(buffer.begin(), it));
    }
}

void DCT::print_item(size_t index){
    cout << "dct["  << setw(2) << index << "]";
    buffer[index].print();
}

void DCT::check_state(){
    bool error = false;
    if(head >= SIZE){
        error = true; printf("DCT head Error!\n");
    }
    if(tail >= SIZE){
        error = true; printf("DCT tail Error!\n");
    }
    if(buffer.size() != SIZE){
        error = true; printf("DCT SIZE Error!\n");
    }
    uint32_t occupacy = 0;
    for(auto it = buffer.begin(); it != buffer.end(); it++){
        occupacy += it->valid;
    }

    if(is_full() != (occupacy == SIZE)){
        error = true; printf("Error in is_full!\n");
    }

    uint32_t head_tail_occupacy = (head <= tail)? (tail - head) : (SIZE-tail+head);
    if(!is_full() && occupacy != head_tail_occupacy){
        error = true; printf("DCT occupacy Error!\n");
    }

    // When stride fluctuates, head may be reserted.
    //if(buffer[head].valid && !buffer[head].head){
    //    error = true; printf("DCT head of buffer[head] is not True!\n");
    //}

    for(auto it = buffer.begin(); it != buffer.end(); it++){
        if(it->valid && !buffer[it->last_dct_ptr].valid){
            error = true; printf("DCT[%ld] point to invalid entry!\n", distance(buffer.begin(), it));
        }
    }

    if(error){
        print_buffer();
        exit(1);
    }
}
#endif


uint64_t alsl_w(uint64_t src0, uint64_t src1, uint32_t shift){
    int32_t shifted = (src0 << shift) & 0xffffffff;
    int64_t ret = (int64_t) (((int32_t) shifted) + ((int32_t) src1 & 0xffffffff));
    return (uint64_t) ret;
}

uint64_t alsl_wu(uint64_t src0, uint64_t src1, uint32_t shift){
    int32_t shifted = (src0 << shift) & 0xffffffff;
    int32_t ret = ((int32_t) shifted) + ((int32_t) src1 & 0xffffffff);
    return (uint64_t) (ret & 0xffffffff);
}

uint64_t alsl_d(uint64_t src0, uint64_t src1, uint32_t shift){
    int64_t shifted = (int64_t) (src0 << shift);
    int64_t ret = shifted + ((int64_t) src1);
    return (uint64_t) ret;
}

uint64_t srl(uint64_t src0, uint64_t src1, bool is_word){
    if(is_word){
        int32_t ret = int32_t (((uint32_t) (src0 & 0xffffffff)) >> (src1 & 0x1f));
        return uint64_t ((int64_t) ret);
    } else {
        uint64_t ret = src0 >> (src1 & 0x3f);
        return ret;
    }
}

uint64_t DCT_ITEM::execute_alu(uint64_t dynamic_src){
    uint32_t shift = 0;
    uint64_t alu_src[2];
    alu_src[0] =  const_idx? dynamic_src : src;
    alu_src[1] = !const_idx? dynamic_src : src;
    switch (op) {
        case IDM_ADD_W:
        {
            int64_t ret = (int64_t) (((int32_t) (alu_src[0] & 0xffffffff)) + ((int32_t) alu_src[1] & 0xffffffff));
            return (uint64_t) ret;
        } 
        case IDM_ADD_D:
        {
            int64_t ret = ((int64_t) alu_src[0]) + ((int64_t) alu_src[1]);
            return (uint64_t) ret;
        }
        case IDM_SUB_W: 
        {
            int64_t ret = (int64_t) (((int32_t) (alu_src[0] & 0xffffffff)) - ((int32_t) alu_src[1] & 0xffffffff));
            return (uint64_t) ret;
        } 
        case IDM_SUB_D: 
        {
            int64_t ret = ((int64_t) alu_src[0]) - ((int64_t) alu_src[1]);
            return (uint64_t) ret;
        } 
        case IDM_ALSL0_W:
            shift = 1;
            return alsl_w(alu_src[0], alu_src[1], shift);
        case IDM_ALSL1_W:
            shift = 2;
            return alsl_w(alu_src[0], alu_src[1], shift);
        case IDM_ALSL2_W:
            shift = 3;
            return alsl_w(alu_src[0], alu_src[1], shift);
        case IDM_ALSL3_W:
            shift = 4;
            return alsl_w(alu_src[0], alu_src[1], shift);
        case IDM_ALSL0_WU:
            shift = 1;
            return alsl_wu(alu_src[0], alu_src[1], shift);
        case IDM_ALSL1_WU:
            shift = 2;
            return alsl_wu(alu_src[0], alu_src[1], shift);
        case IDM_ALSL2_WU:
            shift = 3;
            return alsl_wu(alu_src[0], alu_src[1], shift);
        case IDM_ALSL3_WU:
            shift = 4;
            return alsl_wu(alu_src[0], alu_src[1], shift);
        case IDM_ALSL0_D:
            shift = 1;
            return alsl_d(alu_src[0], alu_src[1], shift);
        case IDM_ALSL1_D:
            shift = 2;
            return alsl_d(alu_src[0], alu_src[1], shift);
        case IDM_ALSL2_D:
            shift = 3;
            return alsl_d(alu_src[0], alu_src[1], shift);
        case IDM_ALSL3_D:
            shift = 4;
            return alsl_d(alu_src[0], alu_src[1], shift);
        //case IDM_SLT:
        //    return (((int64_t) alu_src[0]) < ((int64_t) alu_src[1]))? 1 : 0;
        //case IDM_MASKEQZ:
        //    return (alu_src[1]==0)? 0 : alu_src[1];
        case IDM_AND:
            return (alu_src[0] & alu_src[1]);
        case IDM_OR:
            return (alu_src[0] | alu_src[1]);
        case IDM_XOR:
            return (alu_src[0] ^ alu_src[1]);
        case IDM_MUL_W:
        {
            int64_t ret = (int64_t) ((int32_t) (alu_src[0] & 0xffffffff)) * ((int32_t) (alu_src[1] & 0xffffffff));
            return (uint64_t) ret;
        }
        case IDM_MUL_D:
        {
            int64_t ret = ((int64_t) alu_src[0]) * ((int64_t) alu_src[1]);
            return (uint64_t) ret;
        }
        case IDM_SRL_W:
            return srl(alu_src[0], alu_src[1], true);
        case IDM_SRL_D:
            return srl(alu_src[0], alu_src[1], false);
        case IDM_SLLI_W:
        {
            int32_t ret = int32_t (((uint32_t) (alu_src[0] & 0xffffffff)) << (alu_src[1] & 0x1f));
            return uint64_t ((int64_t) ret);
        }
        case IDM_SLLI_D:
            return (alu_src[0] << alu_src[1]);
        case IDM_SRA_W:
        {
            shift = alu_src[1] & 0x1f;
            int64_t ret = (int64_t) (((int32_t) (alu_src[0] & 0xffffffff)) >> shift);
            return (uint64_t) ret;
        }
        case IDM_SRA_D:
        {
            shift = alu_src[1] & 0x3f;
            int64_t ret = (((int64_t) alu_src[0]) >> shift);
            return (uint64_t) ret;
        }
        case IDM_BSTRPICK_W:
        {
            uint8_t msbw = (alu_src[1] >> 8) & 0xff;
            uint8_t lsbw = alu_src[1] & 0xff;
            uint32_t mask = (0xffffffff >> (31 - msbw));
            uint32_t ret_tmp = (alu_src[0] & mask) >> lsbw;
            int64_t ret = (int32_t) ret_tmp;
            return (uint64_t) ret;
        }
        case IDM_BSTRPICK_D:
        {
            uint8_t msbd = (alu_src[1] >> 8) & 0xff;
            uint8_t lsbd = alu_src[1] & 0xff;
            uint64_t mask = (0xffffffffffffffff >> (63 - msbd));
            uint64_t ret = (alu_src[0] & mask) >> lsbd;
            return ret;
        }
        case IDM_BEQ:
            return (alu_src[0] == alu_src[1])? 1 : 0;
        case IDM_BNE:
            return (alu_src[0] != alu_src[1])? 1 : 0;
        case IDM_BLT:
            return (((int64_t) alu_src[0]) < ((int64_t) alu_src[1]))? 1 : 0;
        case IDM_BLTU:
            return (alu_src[0] < alu_src[1])? 1 : 0;
        case IDM_BGE:
            return (((int64_t) alu_src[0]) >= ((int64_t) alu_src[1]))? 1 : 0;
        case IDM_BGEU:
            return (alu_src[0] >= alu_src[1])? 1 : 0;
        case IDM_BEQZ:
            return (alu_src[0] == 0)? 1 : 0;
        case IDM_BNEZ:
            return (alu_src[0] != 0)? 1 : 0;
        default:
            cout << "Unknown op in execute_alu!" << endl;
            print();
            exit(1);
    }
}

void DCT_ITEM::print(){
    cout << std::left
         << " valid: " << +valid
         << ", head: " << +head
         << ", op: " << setw(2) << +op 
         << ", formed: " << +formed
         << ", dense: " << +dense
         << ", conf: " << +conf
         << ", const_idx: " << +const_idx
         << ", last_dct_ptr: " << setw(2) << last_dct_ptr << hex
         << ", src: "  << setw(16) << src << dec
     #ifdef PREFETCH_DEBUG
         << hex 
         << ", ip: " << ip << dec
         << ", cycle: " << cycle
     #endif
         << std::right << endl;
}

void idm_load_return (uint32_t cpu, uint64_t addr){
    auto it = agq[cpu].search_addr(addr);
    while (it != agq[cpu].buffer.end()) {
        auto idm_issue_item = dct[cpu].buffer.begin() + it->dct_ptr;
        uint64_t vaddr = (addr & 0xffffffffffffffc0) | (it->ret_value & 0x3f);
        uint8_t size = idm_op_get_size(idm_issue_item->op);
        uint8_t unsign_ext = idm_op_is_unsign_ext(idm_issue_item->op);
        uint64_t ret_val = mem_data[cpu].read(vaddr, size, !unsign_ext);

        bool has_successor = agq[cpu].update_src(it, ret_val);
        if(!has_successor){
            agq[cpu].buffer.erase(it);
        }
    #ifdef CHECK_MEM_READ
        if(vaddr == 0){
            cout << "vaddr: " << hex << vaddr << dec  << ", size: " << +size
                 << ", ret_val: " << hex << ret_val << dec << endl;
        }
    #endif

        it = agq[cpu].search_addr(addr);
    }
}
