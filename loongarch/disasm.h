#ifndef _LA_DISASM_H_
#define _LA_DISASM_H_

#include "ins.h"

#ifdef __cplusplus
extern "C" {
#endif
void la_disasm(uint32_t opcode, Ins *ins);
LA_OPCODE get_ins_op(uint32_t insn);
int extract_opnd_val(uint32_t insn, GM_OPERAND_TYPE type);
#ifdef __cplusplus
}
#endif
#endif
