#include "ins.h"
#include "error.h"
#include <stdio.h>

/* === Ins Inspection API === */
bool op_is_branch(LA_OPCODE op)
{
    return (LISA_BEQZ <= op && op <= LISA_BGEU);
}

bool op_is_direct_branch(LA_OPCODE op)
{
    return ((LISA_BEQZ <= op && op <= LISA_BCNEZ) || (LISA_B <= op && op <= LISA_BGEU));
}

bool op_is_indirect_branch(LA_OPCODE op)
{
    return ((op == LISA_JIRL) || (LISA_JISCR0 <= op && op <= LISA_JISCR1));
}

bool op_is_condition_branch(LA_OPCODE op)
{
    return ((LISA_BEQZ <= op && op <= LISA_BCNEZ)
            || (LISA_BEQ <= op && op <= LISA_BGEU));
}

bool op_is_float_branch(LA_OPCODE op)
{
    return (LISA_BCEQZ == op || LISA_BCNEZ == op);
}

bool op_is_syscall(LA_OPCODE op)
{
    return (op == LISA_SYSCALL);
}

bool op_is_ldst(LA_OPCODE op)
{
    return (op_is_load(op) || op_is_store(op));
}

bool op_is_load(LA_OPCODE op)
{
    switch (op) {
    case LISA_LL_W:
    case LISA_LL_D:
    case LISA_LDPTR_W:
    case LISA_LDPTR_D:
    case LISA_LD_B:
    case LISA_LD_H:
    case LISA_LD_W:
    case LISA_LD_D:
    case LISA_LD_BU:
    case LISA_LD_HU:
    case LISA_LD_WU:
    case LISA_PRELD:
    case LISA_FLD_S:
    case LISA_FLD_D:
    case LISA_VLD:
    case LISA_XVLD:
    case LISA_LDL_W:
    case LISA_LDR_W:
    case LISA_LDL_D:
    case LISA_LDR_D:
    case LISA_VLDREPL_D:
    case LISA_VLDREPL_W:
    case LISA_VLDREPL_H:
    case LISA_VLDREPL_B:
    case LISA_XVLDREPL_D:
    case LISA_XVLDREPL_W:
    case LISA_XVLDREPL_H:
    case LISA_XVLDREPL_B:
    case LISA_LDX_B:
    case LISA_LDX_H:
    case LISA_LDX_W:
    case LISA_LDX_D:
    case LISA_LDX_BU:
    case LISA_LDX_HU:
    case LISA_LDX_WU:
    case LISA_PRELDX:
    case LISA_FLDX_S:
    case LISA_FLDX_D:
    case LISA_VLDX:
    case LISA_XVLDX:
    case LISA_FLDGT_S:
    case LISA_FLDGT_D:
    case LISA_FLDLE_S:
    case LISA_FLDLE_D:
    case LISA_LDGT_B:
    case LISA_LDGT_H:
    case LISA_LDGT_W:
    case LISA_LDGT_D:
    case LISA_LDLE_B:
    case LISA_LDLE_H:
    case LISA_LDLE_W:
    case LISA_LDLE_D:
        return true;
    default:
        return false;
    }
}

bool op_is_load_ld(LA_OPCODE op){
    switch (op) {
    case LISA_LD_B:
    case LISA_LD_H:
    case LISA_LD_W:
    case LISA_LD_D:
    case LISA_LD_BU:
    case LISA_LD_HU:
    case LISA_LD_WU:
        return true;
    default:
        return false;
    }
}

bool op_is_load_ldptr(LA_OPCODE op){
    switch (op) {
    case LISA_LDPTR_W:
    case LISA_LDPTR_D:
        return true;
    default:
        return false;
    }
}

uint8_t get_load_size(LA_OPCODE op){
    switch (op) {
    case LISA_LD_B:
    case LISA_LD_BU:
    case LISA_VLDREPL_B:
    case LISA_XVLDREPL_B:
    case LISA_LDX_B:
    case LISA_LDX_BU:
    case LISA_LDGT_B:
    case LISA_LDLE_B:
        return SIZE_BYTE;
    case LISA_LD_H:
    case LISA_LD_HU:
    case LISA_VLDREPL_H:
    case LISA_XVLDREPL_H:
    case LISA_LDX_H:
    case LISA_LDX_HU:
    case LISA_LDGT_H:
    case LISA_LDLE_H:
        return SIZE_HWORD;
    case LISA_LL_W:
    case LISA_LDPTR_W:
    case LISA_LD_W:
    case LISA_LD_WU:
    case LISA_LDL_W:
    case LISA_LDR_W:
    case LISA_VLDREPL_W:
    case LISA_XVLDREPL_W:
    case LISA_LDX_W:
    case LISA_LDX_WU:
    case LISA_LDGT_W:
    case LISA_LDLE_W:
    case LISA_FLD_S:
    case LISA_FLDX_S:
        return SIZE_WORD;
    case LISA_LL_D:
    case LISA_LDPTR_D:
    case LISA_LD_D:
    case LISA_FLD_D:
    case LISA_LDL_D:
    case LISA_LDR_D:
    case LISA_VLDREPL_D:
    case LISA_XVLDREPL_D:
    case LISA_LDX_D:
    case LISA_FLDX_D:
    case LISA_FLDGT_D:
    case LISA_FLDLE_S:
    case LISA_FLDLE_D:
    case LISA_LDGT_D:
    case LISA_LDLE_D:
        return SIZE_DWORD;
    default:
    //case LISA_VLD:
    //case LISA_XVLD:
    //case LISA_PRELD:
    //case LISA_PRELDX:
    //case LISA_VLDX:
    //case LISA_XVLDX:
    //case LISA_FLDGT_S:
        return SIZE_NONE;
    }
}

bool is_load_unsign_ext(LA_OPCODE op)
{
    switch (op) {
    case LISA_LD_BU:
    case LISA_LD_HU:
    case LISA_LD_WU:
    case LISA_LDX_BU:
    case LISA_LDX_HU:
    case LISA_LDX_WU:
        return true;
    default:
        return false;
    }
}

bool op_is_store(LA_OPCODE op)
{
    switch (op) {
    case LISA_SC_W:
    case LISA_SC_D:
    case LISA_STPTR_W:
    case LISA_STPTR_D:
    case LISA_ST_B:
    case LISA_ST_H:
    case LISA_ST_W:
    case LISA_ST_D:
    case LISA_FST_S:
    case LISA_FST_D:
    case LISA_VST:
    case LISA_XVST:
    case LISA_STL_W:
    case LISA_STR_W:
    case LISA_STL_D:
    case LISA_STR_D:
    case LISA_VSTELM_D:
    case LISA_VSTELM_W:
    case LISA_VSTELM_H:
    case LISA_VSTELM_B:
    case LISA_XVSTELM_D:
    case LISA_XVSTELM_W:
    case LISA_XVSTELM_H:
    case LISA_XVSTELM_B:
    case LISA_STX_B:
    case LISA_STX_H:
    case LISA_STX_W:
    case LISA_STX_D:
    case LISA_FSTX_S:
    case LISA_FSTX_D:
    case LISA_VSTX:
    case LISA_XVSTX:
    case LISA_FSTGT_S:
    case LISA_FSTGT_D:
    case LISA_FSTLE_S:
    case LISA_FSTLE_D:
    case LISA_STGT_B:
    case LISA_STGT_H:
    case LISA_STGT_W:
    case LISA_STGT_D:
    case LISA_STLE_B:
    case LISA_STLE_H:
    case LISA_STLE_W:
    case LISA_STLE_D:
        return true;
    default:
        return false;
    }
}

uint8_t get_store_size(LA_OPCODE op)
{
    switch (op) {
    case LISA_ST_B:
    case LISA_VSTELM_B:
    case LISA_XVSTELM_B:
    case LISA_STX_B:
    case LISA_STGT_B:
    case LISA_STLE_B:
        return SIZE_BYTE;
    case LISA_ST_H:
    case LISA_VSTELM_H:
    case LISA_XVSTELM_H:
    case LISA_STX_H:
    case LISA_STGT_H:
    case LISA_STLE_H:
        return SIZE_HWORD;
    case LISA_SC_W:
    case LISA_STPTR_W:
    case LISA_ST_W:
    case LISA_STR_W:
    case LISA_STL_W:
    case LISA_VSTELM_W:
    case LISA_XVSTELM_W:
    case LISA_STX_W:
    case LISA_STGT_W:
    case LISA_STLE_W:
    case LISA_FST_S:
    case LISA_FSTX_S:
        return SIZE_WORD;
    case LISA_SC_D:
    case LISA_STPTR_D:
    case LISA_ST_D:
    case LISA_FST_D:
    case LISA_STL_D:
    case LISA_STR_D:
    case LISA_VSTELM_D:
    case LISA_XVSTELM_D:
    case LISA_STX_D:
    case LISA_FSTX_D:
    case LISA_FSTGT_D:
    case LISA_FSTLE_D:
    case LISA_STGT_D:
    case LISA_STLE_D:
        return SIZE_DWORD;
    default:
    //case LISA_VST:
    //case LISA_XVST:
    //case LISA_VSTX:
    //case LISA_XVSTX:
    //case LISA_FSTGT_S:
    //case LISA_FSTLE_S:
        return SIZE_NONE;
    }
}

bool op_is_float_load(LA_OPCODE op)
{
    switch (op) {
    case LISA_FLD_S:
    case LISA_FLD_D:
    case LISA_VLD:
    case LISA_XVLD:
    case LISA_VLDREPL_D:
    case LISA_VLDREPL_W:
    case LISA_VLDREPL_H:
    case LISA_VLDREPL_B:
    case LISA_XVLDREPL_D:
    case LISA_XVLDREPL_W:
    case LISA_XVLDREPL_H:
    case LISA_XVLDREPL_B:
    case LISA_FLDX_S:
    case LISA_FLDX_D:
    case LISA_VLDX:
    case LISA_XVLDX:
    case LISA_FLDGT_S:
    case LISA_FLDGT_D:
    case LISA_FLDLE_S:
    case LISA_FLDLE_D:
        return true;
    default:
        return false;
    }
}

bool op_is_float_store(LA_OPCODE op)
{
    switch (op) {
    case LISA_FST_S:
    case LISA_FST_D:
    case LISA_VST:
    case LISA_XVST:
    case LISA_VSTELM_D:
    case LISA_VSTELM_W:
    case LISA_VSTELM_H:
    case LISA_VSTELM_B:
    case LISA_XVSTELM_D:
    case LISA_XVSTELM_W:
    case LISA_XVSTELM_H:
    case LISA_XVSTELM_B:
    case LISA_FSTX_S:
    case LISA_FSTX_D:
    case LISA_VSTX:
    case LISA_XVSTX:
    case LISA_FSTGT_S:
    case LISA_FSTGT_D:
    case LISA_FSTLE_S:
    case LISA_FSTLE_D:
        return true;
    default:
        return false;
    }
}

bool op_is_am(LA_OPCODE op)
{
    switch (op) {
    case LISA_AMSWAP_W:
    case LISA_AMSWAP_D:
    case LISA_AMADD_W:
    case LISA_AMADD_D:
    case LISA_AMAND_W:
    case LISA_AMAND_D:
    case LISA_AMOR_W:
    case LISA_AMOR_D:
    case LISA_AMXOR_W:
    case LISA_AMXOR_D:
    case LISA_AMMAX_W:
    case LISA_AMMAX_D:
    case LISA_AMMIN_W:
    case LISA_AMMIN_D:
    case LISA_AMMAX_WU:
    case LISA_AMMAX_DU:
    case LISA_AMMIN_WU:
    case LISA_AMMIN_DU:
    case LISA_AMSWAP_DB_W:
    case LISA_AMSWAP_DB_D:
    case LISA_AMADD_DB_W:
    case LISA_AMADD_DB_D:
    case LISA_AMAND_DB_W:
    case LISA_AMAND_DB_D:
    case LISA_AMOR_DB_W:
    case LISA_AMOR_DB_D:
    case LISA_AMXOR_DB_W:
    case LISA_AMXOR_DB_D:
    case LISA_AMMAX_DB_W:
    case LISA_AMMAX_DB_D:
    case LISA_AMMIN_DB_W:
    case LISA_AMMIN_DB_D:
    case LISA_AMMAX_DB_WU:
    case LISA_AMMAX_DB_DU:
    case LISA_AMMIN_DB_WU:
    case LISA_AMMIN_DB_DU:
        return true;
    default:
        return false;
    }
}

bool op_is_ll(LA_OPCODE op)
{
    return (op == LISA_LL_W || op == LISA_LL_D);
}

bool op_is_sc(LA_OPCODE op)
{
    return (op == LISA_SC_W || op == LISA_SC_D);
}

LA_OPND_TYPE get_opnd_type(Ins *ins, int i)
{
    GM_LA_OPCODE_FORMAT format = lisa_format_table[ins->op];
    GM_OPERAND_TYPE la_opnd_type = format.opnd[i];
    IR2_OPND_TYPE ir2_opnd_type = ir2_opnd_type_table[la_opnd_type];
    return ir2_opnd_type;
}

LISA_REG_ACCESS_TYPE get_reg_access_type(Ins *ins, int i)
{
    LISA_REG_ACCESS_FORMAT format = lisa_reg_access_table[ins->op];
    // lsassertm(format.valid, "reg access format not defined. opcode=%d\n", ins->op);
    if (!format.valid) {
        fprintf(stderr, "reg access format not defined. opcode=%d\n", ins->op);
        return REG_ACCESS_INVALID;
    }
    return format.opnd[i];
}

bool is_reg_access_type_valid(Ins *ins)
{
    return lisa_reg_access_table[ins->op].valid;
}

bool opnd_is_reg(Ins *ins, int i)
{
    IR2_OPND_TYPE type = get_opnd_type(ins, i);
    return (type == IR2_OPND_GPR ||
            type == IR2_OPND_SCR ||
            type == IR2_OPND_FPR ||
            type == IR2_OPND_FCSR);
}

bool opnd_is_imm(Ins *ins, int i)
{
    return (IR2_OPND_IMM == get_opnd_type(ins, i));
}

bool opnd_is_gpr(Ins *ins, int i)
{
    return (IR2_OPND_GPR == get_opnd_type(ins, i));
}

bool opnd_is_gpr_read(Ins *ins, int i)
{
    return (GPR_READ == get_reg_access_type(ins, i));
}

bool opnd_is_gpr_write(Ins *ins, int i)
{
    return (GPR_WRITE == get_reg_access_type(ins, i));
}

bool opnd_is_gpr_readwrite(Ins *ins, int i)
{
    return (GPR_READWRITE == get_reg_access_type(ins, i));
}

bool opnd_is_read(Ins *ins, int i)
{
    LISA_REG_ACCESS_TYPE type = get_reg_access_type(ins, i);
    return (type == GPR_READ || type == GPR_READWRITE ||
            type == FPR_READ || type == FPR_READWRITE ||
            type == FCSR_READ || type == FCC_READ);
}

bool opnd_is_write(Ins *ins, int i)
{
    LISA_REG_ACCESS_TYPE type = get_reg_access_type(ins, i);
    return (type == GPR_WRITE || type == GPR_READWRITE ||
            type == FPR_WRITE || type == FPR_READWRITE ||
            type == FCSR_WRITE || type == FCC_WRITE);
}

bool opnd_is_readonly(Ins *ins, int i)
{
    LISA_REG_ACCESS_TYPE type = get_reg_access_type(ins, i);
    return (type == GPR_READ || type == FPR_READ ||
            type == FCSR_READ || type == FCC_READ);
}

bool opnd_is_writeonly(Ins *ins, int i)
{
    LISA_REG_ACCESS_TYPE type = get_reg_access_type(ins, i);
    return (type == GPR_WRITE || type == FPR_WRITE ||
            type == FCSR_WRITE || type == FCC_WRITE);
}

bool opnd_is_readwrite(Ins *ins, int i)
{
    LISA_REG_ACCESS_TYPE type = get_reg_access_type(ins, i);
    return (type == GPR_READWRITE || type == FPR_READWRITE);
}

#include "bitopts.h"
uint64_t ins_target_addr(Ins *ins, uint64_t pc)
{
    lsassert(op_is_direct_branch(ins->op));
    lsassertm(pc != 0x0, "pc == 0");

    uint64_t offset;
    uint64_t target;
    switch (ins->op) {
        case LISA_BEQ:
        case LISA_BNE:
        case LISA_BLT:
        case LISA_BGE:
        case LISA_BLTU:
        case LISA_BGEU:
            offset = sign_extend(ins->opnd[2].val << 2, 18);
            break;
        case LISA_BEQZ:
        case LISA_BNEZ:
            offset = sign_extend(ins->opnd[1].val << 2, 23);
            break;
        case LISA_B:
        case LISA_BL:
            offset = sign_extend(ins->opnd[0].val << 2, 28);
            break;
        case LISA_BCEQZ:
        case LISA_BCNEZ:
            offset = sign_extend(ins->opnd[1].val << 2, 23);
            break;
        default:
            lsassert(0);
            offset = 0;
            break;
    }

    target = pc + offset;
    return target;
}
