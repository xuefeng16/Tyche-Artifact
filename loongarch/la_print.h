#ifndef _LA_PRINT_H_
#define _LA_PRINT_H_

#include "ins.h"
#ifdef __cplusplus
extern "C" {
#endif
const char *ins_name(Ins *ins);
const char *gpr_name(uint32_t gpr);

void sprint_op_champsim(uint16_t op, char *msg);
void sprint_op(LA_OPCODE op, char *msg);
void sprint_ins(Ins *ins, char * msg);
void sprint_disasm(uint32_t opcode, char *msg);

void print_op(LA_OPCODE op);
void print_ins(Ins *ins);
void print_disasm(uint32_t opcode);
#ifdef __cplusplus
}
#endif
#endif
