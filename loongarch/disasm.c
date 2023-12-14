#include "disasm.h"
#include <stdbool.h>
#include "error.h"

static bool is_la_sign_opnd[] = {
    0,//OPD_INVALID
    0,//OPD_CA
    0,//OPD_CD
    0,//OPD_CJ
    0,//OPD_CODE
    0,//OPD_CONDF
    0,//OPD_CONDH
    0,//OPD_CONDL
    0,//OPD_CSR
    0,//OPD_FA
    0,//OPD_FCSRH
    0,//OPD_FCSRL
    0,//OPD_FD
    0,//OPD_FJ
    0,//OPD_FK
    0,//OPD_HINTL
    0,//OPD_HINTS
    1,//OPD_I13
    0,//OPD_IDXS
    0,//OPD_IDXM
    0,//OPD_IDXL
    0,//OPD_IDXLL
    0,//OPD_LEVEL
    0,//OPD_LSBD
    0,//OPD_LSBW
    0,//OPD_MODE
    0,//OPD_MSBD
    0,//OPD_MSBW
    1,//OPD_OFFS
    1,//OPD_OFFL
    1,//OPD_OFFLL
    0,//OPD_OPCACHE
    0,//OPD_OPX86
    0,//OPD_PTR
    0,//OPD_RD
    0,//OPD_RJ
    0,//OPD_RK
    0,//OPD_SA2
    0,//OPD_SA3
    0,//OPD_SD
    0,//OPD_SEQ
    1,//OPD_SI10
    1,//OPD_SI11
    1,//OPD_SI12
    1,//OPD_SI14
    1,//OPD_SI16
    1,//OPD_SI20
    1,//OPD_SI5
    1,//OPD_SI8
    1,//OPD_SI9
    0,//OPD_SJ
    0,//OPD_UI1
    0,//OPD_UI12
    0,//OPD_UI2
    0,//OPD_UI3
    0,//OPD_UI4
    0,//OPD_UI5H
    0,//OPD_UI5L
    0,//OPD_UI6
    0,//OPD_UI7
    0,//OPD_UI8
    0,//OPD_VA
    0,//OPD_VD
    0,//OPD_VJ
    0,//OPD_VK
    0,//OPD_XA
    0,//OPD_XD
    0,//OPD_XJ
    0,//OPD_XK
};

int extract_opnd_val(uint32_t insn, GM_OPERAND_TYPE type)
{
    GM_OPERAND_PLACE_RELATION bit_field = bit_field_table[type];
    int bit_start = bit_field.bit_range_0.start;
    int bit_end = bit_field.bit_range_0.end;
    int bit_len = bit_end - bit_start + 1;
    int val = (insn >> bit_start) & ((1 << bit_len) - 1);

    bit_start = bit_field.bit_range_1.start;
    bit_end = bit_field.bit_range_1.end;
    if (bit_start >= 0 && bit_end >= 0) {
        int field1_val = insn << (31 - bit_end) >> (31 - bit_end + bit_start);
        val |= field1_val << bit_len;
    }

    if (is_la_sign_opnd[type]) {
        if (bit_end >= 0) {
            bit_len += bit_field.bit_range_1.end - bit_field.bit_range_1.start + 1;
        }
        val = val << (32 - bit_len) >> (32 - bit_len);
    }

    return val;
}

void la_disasm(uint32_t opcode, Ins *ins)
{
    LA_OPCODE op = get_ins_op(opcode);
    lsassertm(op != LISA_INVALID, "invalid opcode");

    ins->op = op;
    ins->opnd_count = 0;

    GM_LA_OPCODE_FORMAT format = lisa_format_table[op];

    for (int i = 0; i < 4; i++) {
        GM_OPERAND_TYPE opnd_type = format.opnd[i];
        if (opnd_type == OPD_INVALID) {
            break;
        }

        ins->opnd[i].val = extract_opnd_val(opcode, opnd_type);
        ins->opnd_count++;
    }
}
