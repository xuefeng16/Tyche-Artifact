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

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <array>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
#include <map>
#include <unordered_map>

#include "champsim_constants.h"
#include "circular_buffer.hpp"
#include "trace_instruction.h"
#include "regfile.h"
#include "la_print.h"
#include "disasm.h"
#include "error.h"
#include "ir2.h"
#include "prefetch.h"

#define PRINT_TRACE_IP 0xffffffffffffffff
#define nPRINT_TRACE_INFO
#define nCOLLECT_INFO
#define nCOLLECT_PATTERN
#define nDECODE_COLLECT_INFO
#define nMISS_COLLECT_INFO
#define nIC_LENGTH_INFO
#define nCOLLECT_SAME_SRC
#define nCOLLECT_USELESS

#define NONE              0
#define ORIGINAL_STRIDE   1
#define ORIGINAL_PT_CHAIN 2
#define INFECTED_STRIDE   3
#define INFECTED_PT_CHAIN 4

extern uint64_t total_inst_num;
extern uint64_t total_load_num;
extern uint8_t regfile_load_type[64];
extern uint8_t regfile_op[64];

extern bool start_print;

typedef struct load_info {
  uint64_t total_count;
  uint64_t last_vaddr;

  int64_t  stride;
  uint8_t  stride_conf;
  uint64_t stride_count;

  uint8_t  pt_conf;
  int64_t  pt_offset;
  uint64_t last_res;
  uint64_t pt_count;

  uint64_t dma_count;
} load_info_t;

typedef struct decode_load_info {
  uint64_t total_count;

  uint64_t stride_count;
  uint64_t ima_single_count;
  uint64_t ima_double_count;
  uint64_t ima_complex_count;
} decode_load_info_t;

extern std::unordered_map<uint64_t, load_info_t> pc_info;

// special registers that help us identify branches
#define REG_STACK_POINTER 6
#define REG_FLAGS 25
#define REG_INSTRUCTION_POINTER 26

#define REG_LOONGARCH_RA 1

// branch types
#define NOT_BRANCH 0
#define BRANCH_DIRECT_JUMP 1
#define BRANCH_INDIRECT 2
#define BRANCH_CONDITIONAL 3
#define BRANCH_DIRECT_CALL 4
#define BRANCH_INDIRECT_CALL 5
#define BRANCH_RETURN 6
#define BRANCH_OTHER 7

extern REGFILE regfile[NUM_CPUS];

struct ooo_model_instr {
  uint64_t instr_id = 0, ip = 0, event_cycle = 0;

  bool is_branch = 0, is_memory = 0, branch_taken = 0, branch_mispredicted = 0, source_added[NUM_INSTR_SOURCES] = {},
       destination_added[NUM_INSTR_DESTINATIONS_SPARC] = {};

  uint8_t asid[2] = {std::numeric_limits<uint8_t>::max(), std::numeric_limits<uint8_t>::max()};

  uint8_t branch_type = NOT_BRANCH;
  uint64_t branch_target = 0;

  uint8_t translated = 0, fetched = 0, decoded = 0, scheduled = 0, executed = 0;
  int num_reg_ops = 0, num_mem_ops = 0, num_reg_dependent = 0;

  uint8_t destination_registers[NUM_INSTR_DESTINATIONS_SPARC] = {}; // output registers

  uint8_t source_registers[NUM_INSTR_SOURCES] = {}; // input registers

  // For LoongArch
  uint32_t inst = 0;
  uint16_t op = 0;
  uint64_t source_reg_val[NUM_INSTR_SOURCES] = {};
  uint64_t ret_val = 0; // if destination_registers isn't 0, the register will be updated to ret_val.
  uint8_t ls_size = 0;
  bool unsign_ext = false;
  bool wait_rob_empty = false;
  #ifdef MISS_COLLECT_INFO
    uint8_t load_type = IDM_INVALID;
  #endif

  // these are indices of instructions in the ROB that depend on me
  std::vector<champsim::circular_buffer<ooo_model_instr>::iterator> registers_instrs_depend_on_me, memory_instrs_depend_on_me;

  // memory addresses that may cause dependencies between instructions
  uint64_t instruction_pa = 0;
  uint64_t destination_memory[NUM_INSTR_DESTINATIONS_SPARC] = {}; // output memory
  uint64_t source_memory[NUM_INSTR_SOURCES] = {};                 // input memory

  std::array<std::vector<LSQ_ENTRY>::iterator, NUM_INSTR_SOURCES> lq_index = {};
  std::array<std::vector<LSQ_ENTRY>::iterator, NUM_INSTR_DESTINATIONS_SPARC> sq_index = {};

  void prinf_info(){

    char msg[32];
    sprint_op_champsim(this->op, msg);
    printf("pc: %#lx, inst: %s, 0x%08x\n", this->ip, msg, this->inst);

    //register
    printf("source_registers     : %02d", this->source_registers[0]);
    for(uint64_t i = 1; i < NUM_INSTR_SOURCES; i++){
      printf(", %02d", this->source_registers[i]);
    }
    printf("\ndestination_registers: %02d", this->destination_registers[0]);
    for(uint64_t i = 1; i < NUM_INSTR_DESTINATIONS_SPARC; i++){
      printf(", %02d", this->destination_registers[i]);
    }

    // memory
    printf("\nsource_memory     : %#lx", this->source_memory[0]);
    for(uint64_t i = 1; i < NUM_INSTR_SOURCES; i++){
      printf(", %#lx", this->source_memory[i]);
    }
    printf("\ndestination_memory: %#lx", this->destination_memory[0]);
    for(uint64_t i = 1; i < NUM_INSTR_DESTINATIONS_SPARC; i++){
      printf(", %#lx", this->destination_memory[i]);
    }

    // source register value
    printf("\nsource_reg_val: %#lx", this->source_reg_val[0]);
    for(uint64_t i = 1; i < NUM_INSTR_SOURCES; i++){
      printf(", %#lx", this->source_reg_val[i]);
    }

    //printf("imm[0]: %d, imm[1]: %d\n", this->imm[0], this->imm[1]);
    printf("\nret_val: 0x%016lx\n", this->ret_val);
    printf("is_branch: %d, branch_taken: %d\n\n", this->is_branch, this->branch_taken); 
  }

  ooo_model_instr() = default;

  ooo_model_instr(uint8_t cpu, input_instr instr)
  {
    std::copy(std::begin(instr.destination_registers), std::end(instr.destination_registers), std::begin(this->destination_registers));
    std::copy(std::begin(instr.destination_memory), std::end(instr.destination_memory), std::begin(this->destination_memory));
    std::copy(std::begin(instr.source_registers), std::end(instr.source_registers), std::begin(this->source_registers));
    std::copy(std::begin(instr.source_memory), std::end(instr.source_memory), std::begin(this->source_memory));

    this->ip = instr.ip;
    this->is_branch = instr.is_branch;
    this->branch_taken = instr.branch_taken;

    asid[0] = cpu;
    asid[1] = cpu;
  }

  ooo_model_instr(uint8_t cpu, cloudsuite_instr instr)
  {
    std::copy(std::begin(instr.destination_registers), std::end(instr.destination_registers), std::begin(this->destination_registers));
    std::copy(std::begin(instr.destination_memory), std::end(instr.destination_memory), std::begin(this->destination_memory));
    std::copy(std::begin(instr.source_registers), std::end(instr.source_registers), std::begin(this->source_registers));
    std::copy(std::begin(instr.source_memory), std::end(instr.source_memory), std::begin(this->source_memory));

    this->ip = instr.ip;
    this->is_branch = instr.is_branch;
    this->branch_taken = instr.branch_taken;

    std::copy(std::begin(instr.asid), std::begin(instr.asid), std::begin(this->asid));
  }

  ooo_model_instr(uint8_t cpu, loongarch_instr instr){
    std::copy(std::begin(instr.destination_registers), std::end(instr.destination_registers), std::begin(this->destination_registers));
    std::copy(std::begin(instr.destination_memory), std::end(instr.destination_memory), std::begin(this->destination_memory));
    std::copy(std::begin(instr.source_registers), std::end(instr.source_registers), std::begin(this->source_registers));
    std::copy(std::begin(instr.source_memory), std::end(instr.source_memory), std::begin(this->source_memory));

    this->ip = instr.ip;
    this->is_branch = instr.is_branch;
    this->branch_taken = instr.branch_taken;
    this->ret_val = instr.ret_val;
    this->inst = instr.inst;
    LA_OPCODE op = get_ins_op(instr.inst);
    this->op = op;
    this->ls_size = get_load_size(op) | get_store_size(op);
    this->unsign_ext = is_load_unsign_ext(op);

    lsassertm(op != LISA_INVALID, "invalid opcode");

    GM_LA_OPCODE_FORMAT format = lisa_format_table[op];
    LISA_REG_ACCESS_FORMAT acc_format = lisa_reg_access_table[op];
    if (!acc_format.valid) {
        fprintf(stderr, "reg access format not defined. pc=%llx\n", instr.ip);
        exit(1);
    }

    uint32_t source_reg_num = 0;

    // Count Read Register Number
    for(int i = 0; i < 4; i++) {
        if(acc_format.opnd[i] == GPR_READ || acc_format.opnd[i] == GPR_READWRITE ||
           acc_format.opnd[i] == FPR_READ || acc_format.opnd[i] == FPR_READWRITE ){
            source_reg_num++;
        }
    }

    // Read Register
    for(uint i = 0; i < source_reg_num; i++){
        this->source_reg_val[i] = regfile[cpu].read(this->source_registers[i]);
    }

    // immediate
    int imm_index = 0;
    int64_t imm[2] = {0};
    for(int i = 0; i < 4; i++) {
        GM_OPERAND_TYPE opnd_type = format.opnd[i];
        if(IR2_OPND_IMM == ir2_opnd_type_table[opnd_type])
            imm[imm_index++] = (int64_t) extract_opnd_val(instr.inst, opnd_type);
    }

    for(int i = 0; i < 2; i++){
        this->source_reg_val[source_reg_num+i] = imm[i];
    }

    // For LISA_BSTRPICK_D & LISA_BSTRPICK_W, we load two imm to src[1], Because IDM
    // only has two value slot.
    if(op == LISA_BSTRPICK_D || op == LISA_BSTRPICK_W){
        this->source_reg_val[1] = (imm[0] << 8) | imm[1];
    }

    lsassertm(imm_index <= 2, "invalid imm");

    #ifdef PRINT_TRACE_INFO
      prinf_info();
    #endif
    if(instr.ip == PRINT_TRACE_IP)
      prinf_info();

    asid[0] = cpu;
    asid[1] = cpu;

    // update reg file
    if(this->destination_registers[0]){
      regfile[cpu].write(this->destination_registers[0], this->ret_val);
    } else if(this->op == LISA_BL){
      regfile[cpu].write(REG_LOONGARCH_RA, this->ret_val);
    }

    #ifdef COLLECT_INFO
      collect_info(instr, op);
    #endif
  }

  void collect_info(loongarch_instr instr, LA_OPCODE op){
    total_inst_num++;
    bool is_load = op_is_load(op);
    uint8_t cur_load_type = NONE;

    if(is_load){
        total_load_num++;

        uint64_t pc = instr.ip;
        uint64_t vaddr = instr.source_memory[0];
        uint64_t res = instr.ret_val;

        std::unordered_map<uint64_t, load_info_t>::iterator hit_item;
        hit_item = pc_info.find(pc);
        if(hit_item != pc_info.end()){
            uint64_t old_vaddr = hit_item->second.last_vaddr;
            int64_t  old_stride = hit_item->second.stride;
            uint64_t old_stride_conf = hit_item->second.stride_conf;
            uint64_t old_res = hit_item->second.last_res;
            uint8_t  old_pt_conf = hit_item->second.pt_conf;
            int64_t  old_pt_offset = hit_item->second.pt_offset;

            // Update
            hit_item->second.last_vaddr = vaddr;
            hit_item->second.last_res = res;
            hit_item->second.total_count += 1;


            // Stride
            int64_t stride = vaddr - old_vaddr;
            if(stride == 0) {
                hit_item->second.stride_conf = old_stride_conf;
            } else if(old_stride_conf == 1) {
                hit_item->second.stride_conf = 2;
            } else if(stride == old_stride){
                if(old_stride_conf < 3)
                    hit_item->second.stride_conf += 1;
            } else{
                if(old_stride_conf > 0)
                    hit_item->second.stride_conf -= 1;
            }

            if(old_stride_conf == 1)
                hit_item->second.stride = stride;

            if(old_stride_conf > 1 && stride == old_stride && stride != 0){ // TODO: conf2 && stride==old_stride || conf3
                hit_item->second.stride_count += 1;

                // TODO:
                cur_load_type = ORIGINAL_STRIDE;
            }

            // Pointer Chain
            int64_t pt_offset = vaddr - old_res;
            bool same_addr = vaddr == old_vaddr; // TO aviod the same vaddr & the same ret_val

            if(same_addr){
                hit_item->second.pt_conf = hit_item->second.pt_conf;
            } else if(old_pt_conf == 1){
                hit_item->second.pt_conf = 2;
            } else if(pt_offset == old_pt_offset){
                if(old_pt_conf < 3)
                    hit_item->second.pt_conf += 1;
            } else{
                if(old_pt_conf > 0){
                    hit_item->second.pt_conf -= 1;
                }
            }

            if(old_pt_conf == 1)
                hit_item->second.pt_offset = pt_offset;

            if(old_pt_conf > 1 && pt_offset == old_pt_offset && !same_addr){ // TODO: conf2 && offset==old_offset || conf3
                hit_item->second.pt_count += 1;

                // TODO:
                cur_load_type = ORIGINAL_PT_CHAIN;
            }
        } else { // First Encounter
            load_info_t new_info = {
                .total_count  = 1,
                .last_vaddr   = vaddr,
                .stride       = 0,
                .stride_conf  = 1,
                .stride_count = 0,
                .pt_conf      = 1,
                .pt_offset    = 0,
                .last_res     = res,
                .pt_count     = 0,
                .dma_count    = 0,
            };
            pc_info.insert(std::pair<uint64_t, load_info_t>(pc, new_info));
        }
    }

    if(instr.ip==PRINT_TRACE_IP)
        std::cout << "Info of pc:" << PRINT_TRACE_IP
                  << "\n total_count : " <<  pc_info[instr.ip].total_count
                  << "\n stride_conf : " << +pc_info[instr.ip].stride_conf
                  << "\n stride_count: " <<  pc_info[instr.ip].stride_count
                  << "\n pt_conf     : " << +pc_info[instr.ip].pt_conf
                  << "\n pt_count    : " <<  pc_info[instr.ip].pt_count
                  << "\n"<< std::endl;


    if(cur_load_type && instr.destination_registers[0]){
        regfile_load_type[instr.destination_registers[0]] = cur_load_type;
        regfile_op[instr.destination_registers[0]] = op;
    } else {
        bool contain = false;
        for(int i = 0; i < NUM_INSTR_SOURCES_LOONGARCH; i++){
            if(regfile_load_type[instr.source_registers[i]] != NONE && instr.source_registers[i]){
                contain = true;
                uint8_t type = NONE;
                if(regfile_load_type[instr.source_registers[i]] == ORIGINAL_STRIDE){
                    type = INFECTED_STRIDE;
                } else if(regfile_load_type[instr.source_registers[i]] == ORIGINAL_PT_CHAIN){
                    type = INFECTED_PT_CHAIN;
                } else {
                    type = regfile_load_type[instr.source_registers[i]];
                }
                regfile_load_type[instr.destination_registers[0]] = type;
                regfile_op[instr.destination_registers[0]] = op;
            }
        }
        if(!contain && instr.destination_registers[0])
            regfile_load_type[instr.destination_registers[0]] = NONE;
        if(is_load && contain)
            pc_info[instr.ip].dma_count++;
    }

    return ;
  }
};

#endif
