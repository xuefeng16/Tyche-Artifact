#include "disasm.h"

LA_OPCODE get_ins_op(uint32_t insn)
{
    switch ((insn >> 26) & 0x3f) {
    case 0x0:
        /* 000000.. ........ ........ ........ */
        switch ((insn >> 22) & 0xf) {
        case 0x0:
            /* 00000000 00...... ........ ........ */
            switch ((insn >> 18) & 0xf) {
            case 0x0:
                /* 00000000 000000.. ........ ........ */
                switch ((insn >> 15) & 0x7) {
                case 0x0:
                    /* 00000000 00000000 0....... ........ */
                    switch ((insn >> 10) & 0x1f) {
                    case 0x2:
                        /* 00000000 00000000 000010.. ........ */
                        switch ((insn >> 2) & 0x7) {
                        case 0x0:
                            /* 00000000 00000000 000010.. ...000.. */
                            /* target/loongarch/insns.decode:351 */
                            return LISA_GR2SCR;
                        }
                        break;
                    case 0x3:
                        /* 00000000 00000000 000011.. ........ */
                        switch ((insn >> 7) & 0x7) {
                        case 0x0:
                            /* 00000000 00000000 00001100 0....... */
                            /* target/loongarch/insns.decode:352 */
                            return LISA_SCR2GR;
                        }
                        break;
                    case 0x4:
                        /* 00000000 00000000 000100.. ........ */
                        /* target/loongarch/insns.decode:353 */
                        return LISA_CLO_W;
                    case 0x5:
                        /* 00000000 00000000 000101.. ........ */
                        /* target/loongarch/insns.decode:354 */
                        return LISA_CLZ_W;
                    case 0x6:
                        /* 00000000 00000000 000110.. ........ */
                        /* target/loongarch/insns.decode:355 */
                        return LISA_CTO_W;
                    case 0x7:
                        /* 00000000 00000000 000111.. ........ */
                        /* target/loongarch/insns.decode:356 */
                        return LISA_CTZ_W;
                    case 0x8:
                        /* 00000000 00000000 001000.. ........ */
                        /* target/loongarch/insns.decode:357 */
                        return LISA_CLO_D;
                    case 0x9:
                        /* 00000000 00000000 001001.. ........ */
                        /* target/loongarch/insns.decode:358 */
                        return LISA_CLZ_D;
                    case 0xa:
                        /* 00000000 00000000 001010.. ........ */
                        /* target/loongarch/insns.decode:359 */
                        return LISA_CTO_D;
                    case 0xb:
                        /* 00000000 00000000 001011.. ........ */
                        /* target/loongarch/insns.decode:360 */
                        return LISA_CTZ_D;
                    case 0xc:
                        /* 00000000 00000000 001100.. ........ */
                        /* target/loongarch/insns.decode:361 */
                        return LISA_REVB_2H;
                    case 0xd:
                        /* 00000000 00000000 001101.. ........ */
                        /* target/loongarch/insns.decode:362 */
                        return LISA_REVB_4H;
                    case 0xe:
                        /* 00000000 00000000 001110.. ........ */
                        /* target/loongarch/insns.decode:363 */
                        return LISA_REVB_2W;
                    case 0xf:
                        /* 00000000 00000000 001111.. ........ */
                        /* target/loongarch/insns.decode:364 */
                        return LISA_REVB_D;
                    case 0x10:
                        /* 00000000 00000000 010000.. ........ */
                        /* target/loongarch/insns.decode:365 */
                        return LISA_REVH_2W;
                    case 0x11:
                        /* 00000000 00000000 010001.. ........ */
                        /* target/loongarch/insns.decode:366 */
                        return LISA_REVH_D;
                    case 0x12:
                        /* 00000000 00000000 010010.. ........ */
                        /* target/loongarch/insns.decode:367 */
                        return LISA_BITREV_4B;
                    case 0x13:
                        /* 00000000 00000000 010011.. ........ */
                        /* target/loongarch/insns.decode:368 */
                        return LISA_BITREV_8B;
                    case 0x14:
                        /* 00000000 00000000 010100.. ........ */
                        /* target/loongarch/insns.decode:369 */
                        return LISA_BITREV_W;
                    case 0x15:
                        /* 00000000 00000000 010101.. ........ */
                        /* target/loongarch/insns.decode:370 */
                        return LISA_BITREV_D;
                    case 0x16:
                        /* 00000000 00000000 010110.. ........ */
                        /* target/loongarch/insns.decode:371 */
                        return LISA_EXT_W_H;
                    case 0x17:
                        /* 00000000 00000000 010111.. ........ */
                        /* target/loongarch/insns.decode:372 */
                        return LISA_EXT_W_B;
                    case 0x18:
                        /* 00000000 00000000 011000.. ........ */
                        /* target/loongarch/insns.decode:373 */
                        return LISA_RDTIMEL_W;
                    case 0x19:
                        /* 00000000 00000000 011001.. ........ */
                        /* target/loongarch/insns.decode:374 */
                        return LISA_RDTIMEH_W;
                    case 0x1a:
                        /* 00000000 00000000 011010.. ........ */
                        /* target/loongarch/insns.decode:375 */
                        return LISA_RDTIME_D;
                    case 0x1b:
                        /* 00000000 00000000 011011.. ........ */
                        /* target/loongarch/insns.decode:376 */
                        return LISA_CPUCFG;
                    case 0x1e:
                        /* 00000000 00000000 011110.. ........ */
                        /* target/loongarch/insns.decode:2289 */
                        return LISA_X86LOOPE;
                    case 0x1f:
                        /* 00000000 00000000 011111.. ........ */
                        /* target/loongarch/insns.decode:2290 */
                        return LISA_X86LOOPNE;
                    }
                    break;
                case 0x1:
                    /* 00000000 00000000 1....... ........ */
                    switch (insn & 0x00007c1f) {
                    case 0x00000000:
                        /* 00000000 00000000 100000.. ...00000 */
                        /* target/loongarch/insns.decode:2291 */
                        return LISA_X86INC_B;
                    case 0x00000001:
                        /* 00000000 00000000 100000.. ...00001 */
                        /* target/loongarch/insns.decode:2292 */
                        return LISA_X86INC_H;
                    case 0x00000002:
                        /* 00000000 00000000 100000.. ...00010 */
                        /* target/loongarch/insns.decode:2293 */
                        return LISA_X86INC_W;
                    case 0x00000003:
                        /* 00000000 00000000 100000.. ...00011 */
                        /* target/loongarch/insns.decode:2294 */
                        return LISA_X86INC_D;
                    case 0x00000004:
                        /* 00000000 00000000 100000.. ...00100 */
                        /* target/loongarch/insns.decode:2295 */
                        return LISA_X86DEC_B;
                    case 0x00000005:
                        /* 00000000 00000000 100000.. ...00101 */
                        /* target/loongarch/insns.decode:2296 */
                        return LISA_X86DEC_H;
                    case 0x00000006:
                        /* 00000000 00000000 100000.. ...00110 */
                        /* target/loongarch/insns.decode:2297 */
                        return LISA_X86DEC_W;
                    case 0x00000007:
                        /* 00000000 00000000 100000.. ...00111 */
                        /* target/loongarch/insns.decode:2298 */
                        return LISA_X86DEC_D;
                    case 0x00000008:
                        /* 00000000 00000000 100000.. ...01000 */
                        switch ((insn >> 5) & 0x1f) {
                        case 0x0:
                            /* 00000000 00000000 10000000 00001000 */
                            /* target/loongarch/insns.decode:2299 */
                            return LISA_X86SETTM;
                        case 0x1:
                            /* 00000000 00000000 10000000 00101000 */
                            /* target/loongarch/insns.decode:2300 */
                            return LISA_X86CLRTM;
                        }
                        break;
                    case 0x00000009:
                        /* 00000000 00000000 100000.. ...01001 */
                        switch ((insn >> 5) & 0x1f) {
                        case 0x0:
                            /* 00000000 00000000 10000000 00001001 */
                            /* target/loongarch/insns.decode:2301 */
                            return LISA_X86INCTOP;
                        case 0x1:
                            /* 00000000 00000000 10000000 00101001 */
                            /* target/loongarch/insns.decode:2302 */
                            return LISA_X86DECTOP;
                        }
                        break;
                    }
                    break;
                case 0x2:
                    /* 00000000 00000001 0....... ........ */
                    switch (insn & 0x0000001f) {
                    case 0x00000000:
                        /* 00000000 00000001 0....... ...00000 */
                        /* target/loongarch/insns.decode:377 */
                        return LISA_ASRTLE_D;
                    }
                    break;
                case 0x3:
                    /* 00000000 00000001 1....... ........ */
                    switch (insn & 0x0000001f) {
                    case 0x00000000:
                        /* 00000000 00000001 1....... ...00000 */
                        /* target/loongarch/insns.decode:378 */
                        return LISA_ASRTGT_D;
                    }
                    break;
                }
                break;
            case 0x1:
                /* 00000000 000001.. ........ ........ */
                switch ((insn >> 17) & 0x1) {
                case 0x0:
                    /* 00000000 0000010. ........ ........ */
                    /* target/loongarch/insns.decode:379 */
                    return LISA_ALSL_W;
                case 0x1:
                    /* 00000000 0000011. ........ ........ */
                    /* target/loongarch/insns.decode:380 */
                    return LISA_ALSL_WU;
                }
                break;
            case 0x2:
                /* 00000000 000010.. ........ ........ */
                switch ((insn >> 17) & 0x1) {
                case 0x0:
                    /* 00000000 0000100. ........ ........ */
                    /* target/loongarch/insns.decode:381 */
                    return LISA_BYTEPICK_W;
                }
                break;
            case 0x3:
                /* 00000000 000011.. ........ ........ */
                /* target/loongarch/insns.decode:382 */
                return LISA_BYTEPICK_D;
            case 0x4:
                /* 00000000 000100.. ........ ........ */
                switch ((insn >> 15) & 0x7) {
                case 0x0:
                    /* 00000000 00010000 0....... ........ */
                    /* target/loongarch/insns.decode:383 */
                    return LISA_ADD_W;
                case 0x1:
                    /* 00000000 00010000 1....... ........ */
                    /* target/loongarch/insns.decode:384 */
                    return LISA_ADD_D;
                case 0x2:
                    /* 00000000 00010001 0....... ........ */
                    /* target/loongarch/insns.decode:385 */
                    return LISA_SUB_W;
                case 0x3:
                    /* 00000000 00010001 1....... ........ */
                    /* target/loongarch/insns.decode:386 */
                    return LISA_SUB_D;
                case 0x4:
                    /* 00000000 00010010 0....... ........ */
                    /* target/loongarch/insns.decode:387 */
                    return LISA_SLT;
                case 0x5:
                    /* 00000000 00010010 1....... ........ */
                    /* target/loongarch/insns.decode:388 */
                    return LISA_SLTU;
                case 0x6:
                    /* 00000000 00010011 0....... ........ */
                    /* target/loongarch/insns.decode:389 */
                    return LISA_MASKEQZ;
                case 0x7:
                    /* 00000000 00010011 1....... ........ */
                    /* target/loongarch/insns.decode:390 */
                    return LISA_MASKNEZ;
                }
                break;
            case 0x5:
                /* 00000000 000101.. ........ ........ */
                switch ((insn >> 15) & 0x7) {
                case 0x0:
                    /* 00000000 00010100 0....... ........ */
                    /* target/loongarch/insns.decode:391 */
                    return LISA_NOR;
                case 0x1:
                    /* 00000000 00010100 1....... ........ */
                    /* target/loongarch/insns.decode:392 */
                    return LISA_AND;
                case 0x2:
                    /* 00000000 00010101 0....... ........ */
                    /* target/loongarch/insns.decode:393 */
                    return LISA_OR;
                case 0x3:
                    /* 00000000 00010101 1....... ........ */
                    /* target/loongarch/insns.decode:394 */
                    return LISA_XOR;
                case 0x4:
                    /* 00000000 00010110 0....... ........ */
                    /* target/loongarch/insns.decode:395 */
                    return LISA_ORN;
                case 0x5:
                    /* 00000000 00010110 1....... ........ */
                    /* target/loongarch/insns.decode:396 */
                    return LISA_ANDN;
                case 0x6:
                    /* 00000000 00010111 0....... ........ */
                    /* target/loongarch/insns.decode:397 */
                    return LISA_SLL_W;
                case 0x7:
                    /* 00000000 00010111 1....... ........ */
                    /* target/loongarch/insns.decode:398 */
                    return LISA_SRL_W;
                }
                break;
            case 0x6:
                /* 00000000 000110.. ........ ........ */
                switch ((insn >> 15) & 0x7) {
                case 0x0:
                    /* 00000000 00011000 0....... ........ */
                    /* target/loongarch/insns.decode:399 */
                    return LISA_SRA_W;
                case 0x1:
                    /* 00000000 00011000 1....... ........ */
                    /* target/loongarch/insns.decode:400 */
                    return LISA_SLL_D;
                case 0x2:
                    /* 00000000 00011001 0....... ........ */
                    /* target/loongarch/insns.decode:401 */
                    return LISA_SRL_D;
                case 0x3:
                    /* 00000000 00011001 1....... ........ */
                    /* target/loongarch/insns.decode:402 */
                    return LISA_SRA_D;
                case 0x6:
                    /* 00000000 00011011 0....... ........ */
                    /* target/loongarch/insns.decode:403 */
                    return LISA_ROTR_W;
                case 0x7:
                    /* 00000000 00011011 1....... ........ */
                    /* target/loongarch/insns.decode:404 */
                    return LISA_ROTR_D;
                }
                break;
            case 0x7:
                /* 00000000 000111.. ........ ........ */
                switch ((insn >> 15) & 0x7) {
                case 0x0:
                    /* 00000000 00011100 0....... ........ */
                    /* target/loongarch/insns.decode:405 */
                    return LISA_MUL_W;
                case 0x1:
                    /* 00000000 00011100 1....... ........ */
                    /* target/loongarch/insns.decode:406 */
                    return LISA_MULH_W;
                case 0x2:
                    /* 00000000 00011101 0....... ........ */
                    /* target/loongarch/insns.decode:407 */
                    return LISA_MULH_WU;
                case 0x3:
                    /* 00000000 00011101 1....... ........ */
                    /* target/loongarch/insns.decode:408 */
                    return LISA_MUL_D;
                case 0x4:
                    /* 00000000 00011110 0....... ........ */
                    /* target/loongarch/insns.decode:409 */
                    return LISA_MULH_D;
                case 0x5:
                    /* 00000000 00011110 1....... ........ */
                    /* target/loongarch/insns.decode:410 */
                    return LISA_MULH_DU;
                case 0x6:
                    /* 00000000 00011111 0....... ........ */
                    /* target/loongarch/insns.decode:411 */
                    return LISA_MULW_D_W;
                case 0x7:
                    /* 00000000 00011111 1....... ........ */
                    /* target/loongarch/insns.decode:412 */
                    return LISA_MULW_D_WU;
                }
                break;
            case 0x8:
                /* 00000000 001000.. ........ ........ */
                switch ((insn >> 15) & 0x7) {
                case 0x0:
                    /* 00000000 00100000 0....... ........ */
                    /* target/loongarch/insns.decode:413 */
                    return LISA_DIV_W;
                case 0x1:
                    /* 00000000 00100000 1....... ........ */
                    /* target/loongarch/insns.decode:414 */
                    return LISA_MOD_W;
                case 0x2:
                    /* 00000000 00100001 0....... ........ */
                    /* target/loongarch/insns.decode:415 */
                    return LISA_DIV_WU;
                case 0x3:
                    /* 00000000 00100001 1....... ........ */
                    /* target/loongarch/insns.decode:416 */
                    return LISA_MOD_WU;
                case 0x4:
                    /* 00000000 00100010 0....... ........ */
                    /* target/loongarch/insns.decode:417 */
                    return LISA_DIV_D;
                case 0x5:
                    /* 00000000 00100010 1....... ........ */
                    /* target/loongarch/insns.decode:418 */
                    return LISA_MOD_D;
                case 0x6:
                    /* 00000000 00100011 0....... ........ */
                    /* target/loongarch/insns.decode:419 */
                    return LISA_DIV_DU;
                case 0x7:
                    /* 00000000 00100011 1....... ........ */
                    /* target/loongarch/insns.decode:420 */
                    return LISA_MOD_DU;
                }
                break;
            case 0x9:
                /* 00000000 001001.. ........ ........ */
                switch ((insn >> 15) & 0x7) {
                case 0x0:
                    /* 00000000 00100100 0....... ........ */
                    /* target/loongarch/insns.decode:421 */
                    return LISA_CRC_W_B_W;
                case 0x1:
                    /* 00000000 00100100 1....... ........ */
                    /* target/loongarch/insns.decode:422 */
                    return LISA_CRC_W_H_W;
                case 0x2:
                    /* 00000000 00100101 0....... ........ */
                    /* target/loongarch/insns.decode:423 */
                    return LISA_CRC_W_W_W;
                case 0x3:
                    /* 00000000 00100101 1....... ........ */
                    /* target/loongarch/insns.decode:424 */
                    return LISA_CRC_W_D_W;
                case 0x4:
                    /* 00000000 00100110 0....... ........ */
                    /* target/loongarch/insns.decode:425 */
                    return LISA_CRCC_W_B_W;
                case 0x5:
                    /* 00000000 00100110 1....... ........ */
                    /* target/loongarch/insns.decode:426 */
                    return LISA_CRCC_W_H_W;
                case 0x6:
                    /* 00000000 00100111 0....... ........ */
                    /* target/loongarch/insns.decode:427 */
                    return LISA_CRCC_W_W_W;
                case 0x7:
                    /* 00000000 00100111 1....... ........ */
                    /* target/loongarch/insns.decode:428 */
                    return LISA_CRCC_W_D_W;
                }
                break;
            case 0xa:
                /* 00000000 001010.. ........ ........ */
                switch ((insn >> 15) & 0x7) {
                case 0x4:
                    /* 00000000 00101010 0....... ........ */
                    /* target/loongarch/insns.decode:429 */
                    return LISA_BREAK;
                case 0x6:
                    /* 00000000 00101011 0....... ........ */
                    /* target/loongarch/insns.decode:431 */
                    return LISA_SYSCALL;
                }
                break;
            case 0xb:
                /* 00000000 001011.. ........ ........ */
                switch ((insn >> 17) & 0x1) {
                case 0x0:
                    /* 00000000 0010110. ........ ........ */
                    /* target/loongarch/insns.decode:432 */
                    return LISA_ALSL_D;
                }
                break;
            case 0xc:
                /* 00000000 001100.. ........ ........ */
                switch ((insn >> 15) & 0x7) {
                case 0x0:
                    /* 00000000 00110000 0....... ........ */
                    /* target/loongarch/insns.decode:2307 */
                    return LISA_ADC_B;
                case 0x1:
                    /* 00000000 00110000 1....... ........ */
                    /* target/loongarch/insns.decode:2309 */
                    return LISA_ADC_H;
                case 0x2:
                    /* 00000000 00110001 0....... ........ */
                    /* target/loongarch/insns.decode:2310 */
                    return LISA_ADC_W;
                case 0x3:
                    /* 00000000 00110001 1....... ........ */
                    /* target/loongarch/insns.decode:2308 */
                    return LISA_ADC_D;
                case 0x4:
                    /* 00000000 00110010 0....... ........ */
                    /* target/loongarch/insns.decode:2311 */
                    return LISA_SBC_B;
                case 0x5:
                    /* 00000000 00110010 1....... ........ */
                    /* target/loongarch/insns.decode:2313 */
                    return LISA_SBC_H;
                case 0x6:
                    /* 00000000 00110011 0....... ........ */
                    /* target/loongarch/insns.decode:2314 */
                    return LISA_SBC_W;
                case 0x7:
                    /* 00000000 00110011 1....... ........ */
                    /* target/loongarch/insns.decode:2312 */
                    return LISA_SBC_D;
                }
                break;
            case 0xd:
                /* 00000000 001101.. ........ ........ */
                switch ((insn >> 15) & 0x7) {
                case 0x0:
                    /* 00000000 00110100 0....... ........ */
                    /* target/loongarch/insns.decode:2315 */
                    return LISA_RCR_B;
                case 0x1:
                    /* 00000000 00110100 1....... ........ */
                    /* target/loongarch/insns.decode:2317 */
                    return LISA_RCR_H;
                case 0x2:
                    /* 00000000 00110101 0....... ........ */
                    /* target/loongarch/insns.decode:2318 */
                    return LISA_RCR_W;
                case 0x3:
                    /* 00000000 00110101 1....... ........ */
                    /* target/loongarch/insns.decode:2316 */
                    return LISA_RCR_D;
                case 0x5:
                    /* 00000000 00110110 1....... ........ */
                    switch (insn & 0x000043e0) {
                    case 0x00000000:
                        /* 00000000 00110110 10....00 000..... */
                        /* target/loongarch/insns.decode:2319 */
                        return LISA_SETX86J;
                    }
                    break;
                }
                break;
            case 0xf:
                /* 00000000 001111.. ........ ........ */
                switch (insn & 0x0003801f) {
                case 0x00028000:
                    /* 00000000 00111110 1....... ...00000 */
                    /* target/loongarch/insns.decode:2320 */
                    return LISA_X86MUL_B;
                case 0x00028001:
                    /* 00000000 00111110 1....... ...00001 */
                    /* target/loongarch/insns.decode:2324 */
                    return LISA_X86MUL_H;
                case 0x00028002:
                    /* 00000000 00111110 1....... ...00010 */
                    /* target/loongarch/insns.decode:2326 */
                    return LISA_X86MUL_W;
                case 0x00028003:
                    /* 00000000 00111110 1....... ...00011 */
                    /* target/loongarch/insns.decode:2322 */
                    return LISA_X86MUL_D;
                case 0x00028004:
                    /* 00000000 00111110 1....... ...00100 */
                    /* target/loongarch/insns.decode:2321 */
                    return LISA_X86MUL_BU;
                case 0x00028005:
                    /* 00000000 00111110 1....... ...00101 */
                    /* target/loongarch/insns.decode:2325 */
                    return LISA_X86MUL_HU;
                case 0x00028006:
                    /* 00000000 00111110 1....... ...00110 */
                    /* target/loongarch/insns.decode:2327 */
                    return LISA_X86MUL_WU;
                case 0x00028007:
                    /* 00000000 00111110 1....... ...00111 */
                    /* target/loongarch/insns.decode:2323 */
                    return LISA_X86MUL_DU;
                case 0x00030000:
                    /* 00000000 00111111 0....... ...00000 */
                    /* target/loongarch/insns.decode:2333 */
                    return LISA_X86ADD_WU;
                case 0x00030001:
                    /* 00000000 00111111 0....... ...00001 */
                    /* target/loongarch/insns.decode:2330 */
                    return LISA_X86ADD_DU;
                case 0x00030002:
                    /* 00000000 00111111 0....... ...00010 */
                    /* target/loongarch/insns.decode:2339 */
                    return LISA_X86SUB_WU;
                case 0x00030003:
                    /* 00000000 00111111 0....... ...00011 */
                    /* target/loongarch/insns.decode:2336 */
                    return LISA_X86SUB_DU;
                case 0x00030004:
                    /* 00000000 00111111 0....... ...00100 */
                    /* target/loongarch/insns.decode:2328 */
                    return LISA_X86ADD_B;
                case 0x00030005:
                    /* 00000000 00111111 0....... ...00101 */
                    /* target/loongarch/insns.decode:2331 */
                    return LISA_X86ADD_H;
                case 0x00030006:
                    /* 00000000 00111111 0....... ...00110 */
                    /* target/loongarch/insns.decode:2332 */
                    return LISA_X86ADD_W;
                case 0x00030007:
                    /* 00000000 00111111 0....... ...00111 */
                    /* target/loongarch/insns.decode:2329 */
                    return LISA_X86ADD_D;
                case 0x00030008:
                    /* 00000000 00111111 0....... ...01000 */
                    /* target/loongarch/insns.decode:2334 */
                    return LISA_X86SUB_B;
                case 0x00030009:
                    /* 00000000 00111111 0....... ...01001 */
                    /* target/loongarch/insns.decode:2337 */
                    return LISA_X86SUB_H;
                case 0x0003000a:
                    /* 00000000 00111111 0....... ...01010 */
                    /* target/loongarch/insns.decode:2338 */
                    return LISA_X86SUB_W;
                case 0x0003000b:
                    /* 00000000 00111111 0....... ...01011 */
                    /* target/loongarch/insns.decode:2335 */
                    return LISA_X86SUB_D;
                case 0x0003000c:
                    /* 00000000 00111111 0....... ...01100 */
                    /* target/loongarch/insns.decode:2340 */
                    return LISA_X86ADC_B;
                case 0x0003000d:
                    /* 00000000 00111111 0....... ...01101 */
                    /* target/loongarch/insns.decode:2342 */
                    return LISA_X86ADC_H;
                case 0x0003000e:
                    /* 00000000 00111111 0....... ...01110 */
                    /* target/loongarch/insns.decode:2343 */
                    return LISA_X86ADC_W;
                case 0x0003000f:
                    /* 00000000 00111111 0....... ...01111 */
                    /* target/loongarch/insns.decode:2341 */
                    return LISA_X86ADC_D;
                case 0x00030010:
                    /* 00000000 00111111 0....... ...10000 */
                    /* target/loongarch/insns.decode:2344 */
                    return LISA_X86SBC_B;
                case 0x00030011:
                    /* 00000000 00111111 0....... ...10001 */
                    /* target/loongarch/insns.decode:2346 */
                    return LISA_X86SBC_H;
                case 0x00030012:
                    /* 00000000 00111111 0....... ...10010 */
                    /* target/loongarch/insns.decode:2347 */
                    return LISA_X86SBC_W;
                case 0x00030013:
                    /* 00000000 00111111 0....... ...10011 */
                    /* target/loongarch/insns.decode:2345 */
                    return LISA_X86SBC_D;
                case 0x00030014:
                    /* 00000000 00111111 0....... ...10100 */
                    /* target/loongarch/insns.decode:2348 */
                    return LISA_X86SLL_B;
                case 0x00030015:
                    /* 00000000 00111111 0....... ...10101 */
                    /* target/loongarch/insns.decode:2350 */
                    return LISA_X86SLL_H;
                case 0x00030016:
                    /* 00000000 00111111 0....... ...10110 */
                    /* target/loongarch/insns.decode:2351 */
                    return LISA_X86SLL_W;
                case 0x00030017:
                    /* 00000000 00111111 0....... ...10111 */
                    /* target/loongarch/insns.decode:2349 */
                    return LISA_X86SLL_D;
                case 0x00030018:
                    /* 00000000 00111111 0....... ...11000 */
                    /* target/loongarch/insns.decode:2352 */
                    return LISA_X86SRL_B;
                case 0x00030019:
                    /* 00000000 00111111 0....... ...11001 */
                    /* target/loongarch/insns.decode:2354 */
                    return LISA_X86SRL_H;
                case 0x0003001a:
                    /* 00000000 00111111 0....... ...11010 */
                    /* target/loongarch/insns.decode:2355 */
                    return LISA_X86SRL_W;
                case 0x0003001b:
                    /* 00000000 00111111 0....... ...11011 */
                    /* target/loongarch/insns.decode:2353 */
                    return LISA_X86SRL_D;
                case 0x0003001c:
                    /* 00000000 00111111 0....... ...11100 */
                    /* target/loongarch/insns.decode:2356 */
                    return LISA_X86SRA_B;
                case 0x0003001d:
                    /* 00000000 00111111 0....... ...11101 */
                    /* target/loongarch/insns.decode:2358 */
                    return LISA_X86SRA_H;
                case 0x0003001e:
                    /* 00000000 00111111 0....... ...11110 */
                    /* target/loongarch/insns.decode:2359 */
                    return LISA_X86SRA_W;
                case 0x0003001f:
                    /* 00000000 00111111 0....... ...11111 */
                    /* target/loongarch/insns.decode:2357 */
                    return LISA_X86SRA_D;
                case 0x00038000:
                    /* 00000000 00111111 1....... ...00000 */
                    /* target/loongarch/insns.decode:2360 */
                    return LISA_X86ROTR_B;
                case 0x00038001:
                    /* 00000000 00111111 1....... ...00001 */
                    /* target/loongarch/insns.decode:2362 */
                    return LISA_X86ROTR_H;
                case 0x00038002:
                    /* 00000000 00111111 1....... ...00010 */
                    /* target/loongarch/insns.decode:2361 */
                    return LISA_X86ROTR_D;
                case 0x00038003:
                    /* 00000000 00111111 1....... ...00011 */
                    /* target/loongarch/insns.decode:2363 */
                    return LISA_X86ROTR_W;
                case 0x00038004:
                    /* 00000000 00111111 1....... ...00100 */
                    /* target/loongarch/insns.decode:2364 */
                    return LISA_X86ROTL_B;
                case 0x00038005:
                    /* 00000000 00111111 1....... ...00101 */
                    /* target/loongarch/insns.decode:2366 */
                    return LISA_X86ROTL_H;
                case 0x00038006:
                    /* 00000000 00111111 1....... ...00110 */
                    /* target/loongarch/insns.decode:2367 */
                    return LISA_X86ROTL_W;
                case 0x00038007:
                    /* 00000000 00111111 1....... ...00111 */
                    /* target/loongarch/insns.decode:2365 */
                    return LISA_X86ROTL_D;
                case 0x00038008:
                    /* 00000000 00111111 1....... ...01000 */
                    /* target/loongarch/insns.decode:2368 */
                    return LISA_X86RCR_B;
                case 0x00038009:
                    /* 00000000 00111111 1....... ...01001 */
                    /* target/loongarch/insns.decode:2370 */
                    return LISA_X86RCR_H;
                case 0x0003800a:
                    /* 00000000 00111111 1....... ...01010 */
                    /* target/loongarch/insns.decode:2371 */
                    return LISA_X86RCR_W;
                case 0x0003800b:
                    /* 00000000 00111111 1....... ...01011 */
                    /* target/loongarch/insns.decode:2369 */
                    return LISA_X86RCR_D;
                case 0x0003800c:
                    /* 00000000 00111111 1....... ...01100 */
                    /* target/loongarch/insns.decode:2372 */
                    return LISA_X86RCL_B;
                case 0x0003800d:
                    /* 00000000 00111111 1....... ...01101 */
                    /* target/loongarch/insns.decode:2374 */
                    return LISA_X86RCL_H;
                case 0x0003800e:
                    /* 00000000 00111111 1....... ...01110 */
                    /* target/loongarch/insns.decode:2375 */
                    return LISA_X86RCL_W;
                case 0x0003800f:
                    /* 00000000 00111111 1....... ...01111 */
                    /* target/loongarch/insns.decode:2373 */
                    return LISA_X86RCL_D;
                case 0x00038010:
                    /* 00000000 00111111 1....... ...10000 */
                    /* target/loongarch/insns.decode:2376 */
                    return LISA_X86AND_B;
                case 0x00038011:
                    /* 00000000 00111111 1....... ...10001 */
                    /* target/loongarch/insns.decode:2378 */
                    return LISA_X86AND_H;
                case 0x00038012:
                    /* 00000000 00111111 1....... ...10010 */
                    /* target/loongarch/insns.decode:2379 */
                    return LISA_X86AND_W;
                case 0x00038013:
                    /* 00000000 00111111 1....... ...10011 */
                    /* target/loongarch/insns.decode:2377 */
                    return LISA_X86AND_D;
                case 0x00038014:
                    /* 00000000 00111111 1....... ...10100 */
                    /* target/loongarch/insns.decode:2380 */
                    return LISA_X86OR_B;
                case 0x00038015:
                    /* 00000000 00111111 1....... ...10101 */
                    /* target/loongarch/insns.decode:2382 */
                    return LISA_X86OR_H;
                case 0x00038016:
                    /* 00000000 00111111 1....... ...10110 */
                    /* target/loongarch/insns.decode:2383 */
                    return LISA_X86OR_W;
                case 0x00038017:
                    /* 00000000 00111111 1....... ...10111 */
                    /* target/loongarch/insns.decode:2381 */
                    return LISA_X86OR_D;
                case 0x00038018:
                    /* 00000000 00111111 1....... ...11000 */
                    /* target/loongarch/insns.decode:2384 */
                    return LISA_X86XOR_B;
                case 0x00038019:
                    /* 00000000 00111111 1....... ...11001 */
                    /* target/loongarch/insns.decode:2386 */
                    return LISA_X86XOR_H;
                case 0x0003801a:
                    /* 00000000 00111111 1....... ...11010 */
                    /* target/loongarch/insns.decode:2387 */
                    return LISA_X86XOR_W;
                case 0x0003801b:
                    /* 00000000 00111111 1....... ...11011 */
                    /* target/loongarch/insns.decode:2385 */
                    return LISA_X86XOR_D;
                }
                break;
            }
            break;
        case 0x1:
            /* 00000000 01...... ........ ........ */
            switch ((insn >> 21) & 0x1) {
            case 0x0:
                /* 00000000 010..... ........ ........ */
                switch ((insn >> 18) & 0x7) {
                case 0x0:
                    /* 00000000 010000.. ........ ........ */
                    switch ((insn >> 16) & 0x3) {
                    case 0x0:
                        /* 00000000 01000000 ........ ........ */
                        switch ((insn >> 15) & 0x1) {
                        case 0x1:
                            /* 00000000 01000000 1....... ........ */
                            /* target/loongarch/insns.decode:433 */
                            return LISA_SLLI_W;
                        }
                        break;
                    case 0x1:
                        /* 00000000 01000001 ........ ........ */
                        /* target/loongarch/insns.decode:434 */
                        return LISA_SLLI_D;
                    }
                    break;
                case 0x1:
                    /* 00000000 010001.. ........ ........ */
                    switch ((insn >> 16) & 0x3) {
                    case 0x0:
                        /* 00000000 01000100 ........ ........ */
                        switch ((insn >> 15) & 0x1) {
                        case 0x1:
                            /* 00000000 01000100 1....... ........ */
                            /* target/loongarch/insns.decode:435 */
                            return LISA_SRLI_W;
                        }
                        break;
                    case 0x1:
                        /* 00000000 01000101 ........ ........ */
                        /* target/loongarch/insns.decode:436 */
                        return LISA_SRLI_D;
                    }
                    break;
                case 0x2:
                    /* 00000000 010010.. ........ ........ */
                    switch ((insn >> 16) & 0x3) {
                    case 0x0:
                        /* 00000000 01001000 ........ ........ */
                        switch ((insn >> 15) & 0x1) {
                        case 0x1:
                            /* 00000000 01001000 1....... ........ */
                            /* target/loongarch/insns.decode:437 */
                            return LISA_SRAI_W;
                        }
                        break;
                    case 0x1:
                        /* 00000000 01001001 ........ ........ */
                        /* target/loongarch/insns.decode:438 */
                        return LISA_SRAI_D;
                    }
                    break;
                case 0x3:
                    /* 00000000 010011.. ........ ........ */
                    switch ((insn >> 16) & 0x3) {
                    case 0x0:
                        /* 00000000 01001100 ........ ........ */
                        switch ((insn >> 15) & 0x1) {
                        case 0x0:
                            /* 00000000 01001100 0....... ........ */
                            switch ((insn >> 14) & 0x1) {
                            case 0x0:
                                /* 00000000 01001100 00...... ........ */
                                switch ((insn >> 13) & 0x1) {
                                case 0x1:
                                    /* 00000000 01001100 001..... ........ */
                                    /* target/loongarch/insns.decode:439 */
                                    return LISA_ROTRI_B;
                                }
                                break;
                            case 0x1:
                                /* 00000000 01001100 01...... ........ */
                                /* target/loongarch/insns.decode:440 */
                                return LISA_ROTRI_H;
                            }
                            break;
                        case 0x1:
                            /* 00000000 01001100 1....... ........ */
                            /* target/loongarch/insns.decode:441 */
                            return LISA_ROTRI_W;
                        }
                        break;
                    case 0x1:
                        /* 00000000 01001101 ........ ........ */
                        /* target/loongarch/insns.decode:442 */
                        return LISA_ROTRI_D;
                    }
                    break;
                case 0x4:
                    /* 00000000 010100.. ........ ........ */
                    switch ((insn >> 16) & 0x3) {
                    case 0x0:
                        /* 00000000 01010000 ........ ........ */
                        switch ((insn >> 15) & 0x1) {
                        case 0x0:
                            /* 00000000 01010000 0....... ........ */
                            switch ((insn >> 14) & 0x1) {
                            case 0x0:
                                /* 00000000 01010000 00...... ........ */
                                switch ((insn >> 13) & 0x1) {
                                case 0x1:
                                    /* 00000000 01010000 001..... ........ */
                                    /* target/loongarch/insns.decode:2388 */
                                    return LISA_RCRI_B;
                                }
                                break;
                            case 0x1:
                                /* 00000000 01010000 01...... ........ */
                                /* target/loongarch/insns.decode:2389 */
                                return LISA_RCRI_H;
                            }
                            break;
                        case 0x1:
                            /* 00000000 01010000 1....... ........ */
                            /* target/loongarch/insns.decode:2390 */
                            return LISA_RCRI_W;
                        }
                        break;
                    case 0x1:
                        /* 00000000 01010001 ........ ........ */
                        /* target/loongarch/insns.decode:2391 */
                        return LISA_RCRI_D;
                    }
                    break;
                case 0x5:
                    /* 00000000 010101.. ........ ........ */
                    switch (insn & 0x0003001f) {
                    case 0x00000000:
                        /* 00000000 01010100 ........ ...00000 */
                        switch ((insn >> 13) & 0x7) {
                        case 0x1:
                            /* 00000000 01010100 001..... ...00000 */
                            /* target/loongarch/insns.decode:2392 */
                            return LISA_X86SLLI_B;
                        }
                        break;
                    case 0x00000001:
                        /* 00000000 01010100 ........ ...00001 */
                        switch ((insn >> 14) & 0x3) {
                        case 0x1:
                            /* 00000000 01010100 01...... ...00001 */
                            /* target/loongarch/insns.decode:2393 */
                            return LISA_X86SLLI_H;
                        }
                        break;
                    case 0x00000002:
                        /* 00000000 01010100 ........ ...00010 */
                        switch ((insn >> 15) & 0x1) {
                        case 0x1:
                            /* 00000000 01010100 1....... ...00010 */
                            /* target/loongarch/insns.decode:2394 */
                            return LISA_X86SLLI_W;
                        }
                        break;
                    case 0x00000004:
                        /* 00000000 01010100 ........ ...00100 */
                        switch ((insn >> 13) & 0x7) {
                        case 0x1:
                            /* 00000000 01010100 001..... ...00100 */
                            /* target/loongarch/insns.decode:2396 */
                            return LISA_X86SRLI_B;
                        }
                        break;
                    case 0x00000005:
                        /* 00000000 01010100 ........ ...00101 */
                        switch ((insn >> 14) & 0x3) {
                        case 0x1:
                            /* 00000000 01010100 01...... ...00101 */
                            /* target/loongarch/insns.decode:2397 */
                            return LISA_X86SRLI_H;
                        }
                        break;
                    case 0x00000006:
                        /* 00000000 01010100 ........ ...00110 */
                        switch ((insn >> 15) & 0x1) {
                        case 0x1:
                            /* 00000000 01010100 1....... ...00110 */
                            /* target/loongarch/insns.decode:2398 */
                            return LISA_X86SRLI_W;
                        }
                        break;
                    case 0x00000008:
                        /* 00000000 01010100 ........ ...01000 */
                        switch ((insn >> 13) & 0x7) {
                        case 0x1:
                            /* 00000000 01010100 001..... ...01000 */
                            /* target/loongarch/insns.decode:2400 */
                            return LISA_X86SRAI_B;
                        }
                        break;
                    case 0x00000009:
                        /* 00000000 01010100 ........ ...01001 */
                        switch ((insn >> 14) & 0x3) {
                        case 0x1:
                            /* 00000000 01010100 01...... ...01001 */
                            /* target/loongarch/insns.decode:2401 */
                            return LISA_X86SRAI_H;
                        }
                        break;
                    case 0x0000000a:
                        /* 00000000 01010100 ........ ...01010 */
                        switch ((insn >> 15) & 0x1) {
                        case 0x1:
                            /* 00000000 01010100 1....... ...01010 */
                            /* target/loongarch/insns.decode:2402 */
                            return LISA_X86SRAI_W;
                        }
                        break;
                    case 0x0000000c:
                        /* 00000000 01010100 ........ ...01100 */
                        switch ((insn >> 13) & 0x7) {
                        case 0x1:
                            /* 00000000 01010100 001..... ...01100 */
                            /* target/loongarch/insns.decode:2404 */
                            return LISA_X86ROTRI_B;
                        }
                        break;
                    case 0x0000000d:
                        /* 00000000 01010100 ........ ...01101 */
                        switch ((insn >> 14) & 0x3) {
                        case 0x1:
                            /* 00000000 01010100 01...... ...01101 */
                            /* target/loongarch/insns.decode:2405 */
                            return LISA_X86ROTRI_H;
                        }
                        break;
                    case 0x0000000e:
                        /* 00000000 01010100 ........ ...01110 */
                        switch ((insn >> 15) & 0x1) {
                        case 0x1:
                            /* 00000000 01010100 1....... ...01110 */
                            /* target/loongarch/insns.decode:2406 */
                            return LISA_X86ROTRI_W;
                        }
                        break;
                    case 0x00000010:
                        /* 00000000 01010100 ........ ...10000 */
                        switch ((insn >> 13) & 0x7) {
                        case 0x1:
                            /* 00000000 01010100 001..... ...10000 */
                            /* target/loongarch/insns.decode:2408 */
                            return LISA_X86RCRI_B;
                        }
                        break;
                    case 0x00000011:
                        /* 00000000 01010100 ........ ...10001 */
                        switch ((insn >> 14) & 0x3) {
                        case 0x1:
                            /* 00000000 01010100 01...... ...10001 */
                            /* target/loongarch/insns.decode:2409 */
                            return LISA_X86RCRI_H;
                        }
                        break;
                    case 0x00000012:
                        /* 00000000 01010100 ........ ...10010 */
                        switch ((insn >> 15) & 0x1) {
                        case 0x1:
                            /* 00000000 01010100 1....... ...10010 */
                            /* target/loongarch/insns.decode:2410 */
                            return LISA_X86RCRI_W;
                        }
                        break;
                    case 0x00000014:
                        /* 00000000 01010100 ........ ...10100 */
                        switch ((insn >> 13) & 0x7) {
                        case 0x1:
                            /* 00000000 01010100 001..... ...10100 */
                            /* target/loongarch/insns.decode:2412 */
                            return LISA_X86ROTLI_B;
                        }
                        break;
                    case 0x00000015:
                        /* 00000000 01010100 ........ ...10101 */
                        switch ((insn >> 14) & 0x3) {
                        case 0x1:
                            /* 00000000 01010100 01...... ...10101 */
                            /* target/loongarch/insns.decode:2413 */
                            return LISA_X86ROTLI_H;
                        }
                        break;
                    case 0x00000016:
                        /* 00000000 01010100 ........ ...10110 */
                        switch ((insn >> 15) & 0x1) {
                        case 0x1:
                            /* 00000000 01010100 1....... ...10110 */
                            /* target/loongarch/insns.decode:2414 */
                            return LISA_X86ROTLI_W;
                        }
                        break;
                    case 0x00000018:
                        /* 00000000 01010100 ........ ...11000 */
                        switch ((insn >> 13) & 0x7) {
                        case 0x1:
                            /* 00000000 01010100 001..... ...11000 */
                            /* target/loongarch/insns.decode:2416 */
                            return LISA_X86RCLI_B;
                        }
                        break;
                    case 0x00000019:
                        /* 00000000 01010100 ........ ...11001 */
                        switch ((insn >> 14) & 0x3) {
                        case 0x1:
                            /* 00000000 01010100 01...... ...11001 */
                            /* target/loongarch/insns.decode:2417 */
                            return LISA_X86RCLI_H;
                        }
                        break;
                    case 0x0000001a:
                        /* 00000000 01010100 ........ ...11010 */
                        switch ((insn >> 15) & 0x1) {
                        case 0x1:
                            /* 00000000 01010100 1....... ...11010 */
                            /* target/loongarch/insns.decode:2418 */
                            return LISA_X86RCLI_W;
                        }
                        break;
                    case 0x00010003:
                        /* 00000000 01010101 ........ ...00011 */
                        /* target/loongarch/insns.decode:2395 */
                        return LISA_X86SLLI_D;
                    case 0x00010007:
                        /* 00000000 01010101 ........ ...00111 */
                        /* target/loongarch/insns.decode:2399 */
                        return LISA_X86SRLI_D;
                    case 0x0001000b:
                        /* 00000000 01010101 ........ ...01011 */
                        /* target/loongarch/insns.decode:2403 */
                        return LISA_X86SRAI_D;
                    case 0x0001000f:
                        /* 00000000 01010101 ........ ...01111 */
                        /* target/loongarch/insns.decode:2407 */
                        return LISA_X86ROTRI_D;
                    case 0x00010013:
                        /* 00000000 01010101 ........ ...10011 */
                        /* target/loongarch/insns.decode:2411 */
                        return LISA_X86RCRI_D;
                    case 0x00010017:
                        /* 00000000 01010101 ........ ...10111 */
                        /* target/loongarch/insns.decode:2415 */
                        return LISA_X86ROTLI_D;
                    case 0x0001001b:
                        /* 00000000 01010101 ........ ...11011 */
                        /* target/loongarch/insns.decode:2419 */
                        return LISA_X86RCLI_D;
                    }
                    break;
                case 0x7:
                    /* 00000000 010111.. ........ ........ */
                    switch ((insn >> 5) & 0x1f) {
                    case 0x0:
                        /* 00000000 010111.. ......00 000..... */
                        /* target/loongarch/insns.decode:2420 */
                        return LISA_X86MFFLAG;
                    case 0x1:
                        /* 00000000 010111.. ......00 001..... */
                        /* target/loongarch/insns.decode:2421 */
                        return LISA_X86MTFLAG;
                    }
                    break;
                }
                break;
            case 0x1:
                /* 00000000 011..... ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 00000000 011..... 0....... ........ */
                    /* target/loongarch/insns.decode:443 */
                    return LISA_BSTRINS_W;
                case 0x1:
                    /* 00000000 011..... 1....... ........ */
                    /* target/loongarch/insns.decode:444 */
                    return LISA_BSTRPICK_W;
                }
                break;
            }
            break;
        case 0x2:
            /* 00000000 10...... ........ ........ */
            /* target/loongarch/insns.decode:445 */
            return LISA_BSTRINS_D;
        case 0x3:
            /* 00000000 11...... ........ ........ */
            /* target/loongarch/insns.decode:446 */
            return LISA_BSTRPICK_D;
        case 0x4:
            /* 00000001 00...... ........ ........ */
            switch ((insn >> 15) & 0x7f) {
            case 0x1:
                /* 00000001 00000000 1....... ........ */
                /* target/loongarch/insns.decode:449 */
                return LISA_FADD_S;
            case 0x2:
                /* 00000001 00000001 0....... ........ */
                /* target/loongarch/insns.decode:450 */
                return LISA_FADD_D;
            case 0x5:
                /* 00000001 00000010 1....... ........ */
                /* target/loongarch/insns.decode:451 */
                return LISA_FSUB_S;
            case 0x6:
                /* 00000001 00000011 0....... ........ */
                /* target/loongarch/insns.decode:452 */
                return LISA_FSUB_D;
            case 0x9:
                /* 00000001 00000100 1....... ........ */
                /* target/loongarch/insns.decode:453 */
                return LISA_FMUL_S;
            case 0xa:
                /* 00000001 00000101 0....... ........ */
                /* target/loongarch/insns.decode:454 */
                return LISA_FMUL_D;
            case 0xd:
                /* 00000001 00000110 1....... ........ */
                /* target/loongarch/insns.decode:455 */
                return LISA_FDIV_S;
            case 0xe:
                /* 00000001 00000111 0....... ........ */
                /* target/loongarch/insns.decode:456 */
                return LISA_FDIV_D;
            case 0x11:
                /* 00000001 00001000 1....... ........ */
                /* target/loongarch/insns.decode:457 */
                return LISA_FMAX_S;
            case 0x12:
                /* 00000001 00001001 0....... ........ */
                /* target/loongarch/insns.decode:458 */
                return LISA_FMAX_D;
            case 0x15:
                /* 00000001 00001010 1....... ........ */
                /* target/loongarch/insns.decode:459 */
                return LISA_FMIN_S;
            case 0x16:
                /* 00000001 00001011 0....... ........ */
                /* target/loongarch/insns.decode:460 */
                return LISA_FMIN_D;
            case 0x19:
                /* 00000001 00001100 1....... ........ */
                /* target/loongarch/insns.decode:461 */
                return LISA_FMAXA_S;
            case 0x1a:
                /* 00000001 00001101 0....... ........ */
                /* target/loongarch/insns.decode:462 */
                return LISA_FMAXA_D;
            case 0x1d:
                /* 00000001 00001110 1....... ........ */
                /* target/loongarch/insns.decode:463 */
                return LISA_FMINA_S;
            case 0x1e:
                /* 00000001 00001111 0....... ........ */
                /* target/loongarch/insns.decode:464 */
                return LISA_FMINA_D;
            case 0x21:
                /* 00000001 00010000 1....... ........ */
                /* target/loongarch/insns.decode:465 */
                return LISA_FSCALEB_S;
            case 0x22:
                /* 00000001 00010001 0....... ........ */
                /* target/loongarch/insns.decode:466 */
                return LISA_FSCALEB_D;
            case 0x25:
                /* 00000001 00010010 1....... ........ */
                /* target/loongarch/insns.decode:467 */
                return LISA_FCOPYSIGN_S;
            case 0x26:
                /* 00000001 00010011 0....... ........ */
                /* target/loongarch/insns.decode:468 */
                return LISA_FCOPYSIGN_D;
            case 0x28:
                /* 00000001 00010100 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x1:
                    /* 00000001 00010100 000001.. ........ */
                    /* target/loongarch/insns.decode:469 */
                    return LISA_FABS_S;
                case 0x2:
                    /* 00000001 00010100 000010.. ........ */
                    /* target/loongarch/insns.decode:470 */
                    return LISA_FABS_D;
                case 0x5:
                    /* 00000001 00010100 000101.. ........ */
                    /* target/loongarch/insns.decode:471 */
                    return LISA_FNEG_S;
                case 0x6:
                    /* 00000001 00010100 000110.. ........ */
                    /* target/loongarch/insns.decode:472 */
                    return LISA_FNEG_D;
                case 0x9:
                    /* 00000001 00010100 001001.. ........ */
                    /* target/loongarch/insns.decode:473 */
                    return LISA_FLOGB_S;
                case 0xa:
                    /* 00000001 00010100 001010.. ........ */
                    /* target/loongarch/insns.decode:474 */
                    return LISA_FLOGB_D;
                case 0xd:
                    /* 00000001 00010100 001101.. ........ */
                    /* target/loongarch/insns.decode:475 */
                    return LISA_FCLASS_S;
                case 0xe:
                    /* 00000001 00010100 001110.. ........ */
                    /* target/loongarch/insns.decode:476 */
                    return LISA_FCLASS_D;
                case 0x11:
                    /* 00000001 00010100 010001.. ........ */
                    /* target/loongarch/insns.decode:477 */
                    return LISA_FSQRT_S;
                case 0x12:
                    /* 00000001 00010100 010010.. ........ */
                    /* target/loongarch/insns.decode:478 */
                    return LISA_FSQRT_D;
                case 0x15:
                    /* 00000001 00010100 010101.. ........ */
                    /* target/loongarch/insns.decode:479 */
                    return LISA_FRECIP_S;
                case 0x16:
                    /* 00000001 00010100 010110.. ........ */
                    /* target/loongarch/insns.decode:480 */
                    return LISA_FRECIP_D;
                case 0x19:
                    /* 00000001 00010100 011001.. ........ */
                    /* target/loongarch/insns.decode:481 */
                    return LISA_FRSQRT_S;
                case 0x1a:
                    /* 00000001 00010100 011010.. ........ */
                    /* target/loongarch/insns.decode:482 */
                    return LISA_FRSQRT_D;
                }
                break;
            case 0x29:
                /* 00000001 00010100 1....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x5:
                    /* 00000001 00010100 100101.. ........ */
                    /* target/loongarch/insns.decode:483 */
                    return LISA_FMOV_S;
                case 0x6:
                    /* 00000001 00010100 100110.. ........ */
                    /* target/loongarch/insns.decode:484 */
                    return LISA_FMOV_D;
                case 0x9:
                    /* 00000001 00010100 101001.. ........ */
                    /* target/loongarch/insns.decode:485 */
                    return LISA_MOVGR2FR_W;
                case 0xa:
                    /* 00000001 00010100 101010.. ........ */
                    /* target/loongarch/insns.decode:486 */
                    return LISA_MOVGR2FR_D;
                case 0xb:
                    /* 00000001 00010100 101011.. ........ */
                    /* target/loongarch/insns.decode:487 */
                    return LISA_MOVGR2FRH_W;
                case 0xd:
                    /* 00000001 00010100 101101.. ........ */
                    /* target/loongarch/insns.decode:488 */
                    return LISA_MOVFR2GR_S;
                case 0xe:
                    /* 00000001 00010100 101110.. ........ */
                    /* target/loongarch/insns.decode:489 */
                    return LISA_MOVFR2GR_D;
                case 0xf:
                    /* 00000001 00010100 101111.. ........ */
                    /* target/loongarch/insns.decode:490 */
                    return LISA_MOVFRH2GR_S;
                case 0x10:
                    /* 00000001 00010100 110000.. ........ */
                    /* target/loongarch/insns.decode:491 */
                    return LISA_MOVGR2FCSR;
                case 0x12:
                    /* 00000001 00010100 110010.. ........ */
                    /* target/loongarch/insns.decode:492 */
                    return LISA_MOVFCSR2GR;
                case 0x14:
                    /* 00000001 00010100 110100.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 00000001 00010100 110100.. ...00... */
                        /* target/loongarch/insns.decode:493 */
                        return LISA_MOVFR2CF;
                    }
                    break;
                case 0x15:
                    /* 00000001 00010100 110101.. ........ */
                    switch ((insn >> 8) & 0x3) {
                    case 0x0:
                        /* 00000001 00010100 11010100 ........ */
                        /* target/loongarch/insns.decode:494 */
                        return LISA_MOVCF2FR;
                    }
                    break;
                case 0x16:
                    /* 00000001 00010100 110110.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 00000001 00010100 110110.. ...00... */
                        /* target/loongarch/insns.decode:495 */
                        return LISA_MOVGR2CF;
                    }
                    break;
                case 0x17:
                    /* 00000001 00010100 110111.. ........ */
                    switch ((insn >> 8) & 0x3) {
                    case 0x0:
                        /* 00000001 00010100 11011100 ........ */
                        /* target/loongarch/insns.decode:496 */
                        return LISA_MOVCF2GR;
                    }
                    break;
                case 0x18:
                    /* 00000001 00010100 111000.. ........ */
                    /* target/loongarch/insns.decode:497 */
                    return LISA_FCVT_LD_D;
                case 0x19:
                    /* 00000001 00010100 111001.. ........ */
                    /* target/loongarch/insns.decode:498 */
                    return LISA_FCVT_UD_D;
                }
                break;
            case 0x2a:
                /* 00000001 00010101 0....... ........ */
                /* target/loongarch/insns.decode:499 */
                return LISA_FCVT_D_LD;
            case 0x32:
                /* 00000001 00011001 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x6:
                    /* 00000001 00011001 000110.. ........ */
                    /* target/loongarch/insns.decode:500 */
                    return LISA_FCVT_S_D;
                case 0x9:
                    /* 00000001 00011001 001001.. ........ */
                    /* target/loongarch/insns.decode:501 */
                    return LISA_FCVT_D_S;
                }
                break;
            case 0x34:
                /* 00000001 00011010 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x1:
                    /* 00000001 00011010 000001.. ........ */
                    /* target/loongarch/insns.decode:502 */
                    return LISA_FTINTRM_W_S;
                case 0x2:
                    /* 00000001 00011010 000010.. ........ */
                    /* target/loongarch/insns.decode:503 */
                    return LISA_FTINTRM_W_D;
                case 0x9:
                    /* 00000001 00011010 001001.. ........ */
                    /* target/loongarch/insns.decode:504 */
                    return LISA_FTINTRM_L_S;
                case 0xa:
                    /* 00000001 00011010 001010.. ........ */
                    /* target/loongarch/insns.decode:505 */
                    return LISA_FTINTRM_L_D;
                case 0x11:
                    /* 00000001 00011010 010001.. ........ */
                    /* target/loongarch/insns.decode:506 */
                    return LISA_FTINTRP_W_S;
                case 0x12:
                    /* 00000001 00011010 010010.. ........ */
                    /* target/loongarch/insns.decode:507 */
                    return LISA_FTINTRP_W_D;
                case 0x19:
                    /* 00000001 00011010 011001.. ........ */
                    /* target/loongarch/insns.decode:508 */
                    return LISA_FTINTRP_L_S;
                case 0x1a:
                    /* 00000001 00011010 011010.. ........ */
                    /* target/loongarch/insns.decode:509 */
                    return LISA_FTINTRP_L_D;
                }
                break;
            case 0x35:
                /* 00000001 00011010 1....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x1:
                    /* 00000001 00011010 100001.. ........ */
                    /* target/loongarch/insns.decode:510 */
                    return LISA_FTINTRZ_W_S;
                case 0x2:
                    /* 00000001 00011010 100010.. ........ */
                    /* target/loongarch/insns.decode:511 */
                    return LISA_FTINTRZ_W_D;
                case 0x9:
                    /* 00000001 00011010 101001.. ........ */
                    /* target/loongarch/insns.decode:512 */
                    return LISA_FTINTRZ_L_S;
                case 0xa:
                    /* 00000001 00011010 101010.. ........ */
                    /* target/loongarch/insns.decode:513 */
                    return LISA_FTINTRZ_L_D;
                case 0x11:
                    /* 00000001 00011010 110001.. ........ */
                    /* target/loongarch/insns.decode:514 */
                    return LISA_FTINTRNE_W_S;
                case 0x12:
                    /* 00000001 00011010 110010.. ........ */
                    /* target/loongarch/insns.decode:515 */
                    return LISA_FTINTRNE_W_D;
                case 0x19:
                    /* 00000001 00011010 111001.. ........ */
                    /* target/loongarch/insns.decode:516 */
                    return LISA_FTINTRNE_L_S;
                case 0x1a:
                    /* 00000001 00011010 111010.. ........ */
                    /* target/loongarch/insns.decode:517 */
                    return LISA_FTINTRNE_L_D;
                }
                break;
            case 0x36:
                /* 00000001 00011011 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x1:
                    /* 00000001 00011011 000001.. ........ */
                    /* target/loongarch/insns.decode:518 */
                    return LISA_FTINT_W_S;
                case 0x2:
                    /* 00000001 00011011 000010.. ........ */
                    /* target/loongarch/insns.decode:519 */
                    return LISA_FTINT_W_D;
                case 0x9:
                    /* 00000001 00011011 001001.. ........ */
                    /* target/loongarch/insns.decode:520 */
                    return LISA_FTINT_L_S;
                case 0xa:
                    /* 00000001 00011011 001010.. ........ */
                    /* target/loongarch/insns.decode:521 */
                    return LISA_FTINT_L_D;
                }
                break;
            case 0x3a:
                /* 00000001 00011101 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x4:
                    /* 00000001 00011101 000100.. ........ */
                    /* target/loongarch/insns.decode:522 */
                    return LISA_FFINT_S_W;
                case 0x6:
                    /* 00000001 00011101 000110.. ........ */
                    /* target/loongarch/insns.decode:523 */
                    return LISA_FFINT_S_L;
                case 0x8:
                    /* 00000001 00011101 001000.. ........ */
                    /* target/loongarch/insns.decode:524 */
                    return LISA_FFINT_D_W;
                case 0xa:
                    /* 00000001 00011101 001010.. ........ */
                    /* target/loongarch/insns.decode:525 */
                    return LISA_FFINT_D_L;
                }
                break;
            case 0x3c:
                /* 00000001 00011110 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x11:
                    /* 00000001 00011110 010001.. ........ */
                    /* target/loongarch/insns.decode:526 */
                    return LISA_FRINT_S;
                case 0x12:
                    /* 00000001 00011110 010010.. ........ */
                    /* target/loongarch/insns.decode:527 */
                    return LISA_FRINT_D;
                }
                break;
            }
            break;
        case 0x8:
            /* 00000010 00...... ........ ........ */
            /* target/loongarch/insns.decode:530 */
            return LISA_SLTI;
        case 0x9:
            /* 00000010 01...... ........ ........ */
            /* target/loongarch/insns.decode:531 */
            return LISA_SLTUI;
        case 0xa:
            /* 00000010 10...... ........ ........ */
            /* target/loongarch/insns.decode:532 */
            return LISA_ADDI_W;
        case 0xb:
            /* 00000010 11...... ........ ........ */
            /* target/loongarch/insns.decode:533 */
            return LISA_ADDI_D;
        case 0xc:
            /* 00000011 00...... ........ ........ */
            /* target/loongarch/insns.decode:534 */
            return LISA_LU52I_D;
        case 0xd:
            /* 00000011 01...... ........ ........ */
            /* target/loongarch/insns.decode:535 */
            return LISA_ANDI;
        case 0xe:
            /* 00000011 10...... ........ ........ */
            /* target/loongarch/insns.decode:536 */
            return LISA_ORI;
        case 0xf:
            /* 00000011 11...... ........ ........ */
            /* target/loongarch/insns.decode:537 */
            return LISA_XORI;
        }
        break;
    case 0x2:
        /* 000010.. ........ ........ ........ */
        switch ((insn >> 20) & 0x3f) {
        case 0x1:
            /* 00001000 0001.... ........ ........ */
            /* target/loongarch/insns.decode:564 */
            return LISA_FMADD_S;
        case 0x2:
            /* 00001000 0010.... ........ ........ */
            /* target/loongarch/insns.decode:565 */
            return LISA_FMADD_D;
        case 0x5:
            /* 00001000 0101.... ........ ........ */
            /* target/loongarch/insns.decode:566 */
            return LISA_FMSUB_S;
        case 0x6:
            /* 00001000 0110.... ........ ........ */
            /* target/loongarch/insns.decode:567 */
            return LISA_FMSUB_D;
        case 0x9:
            /* 00001000 1001.... ........ ........ */
            /* target/loongarch/insns.decode:568 */
            return LISA_FNMADD_S;
        case 0xa:
            /* 00001000 1010.... ........ ........ */
            /* target/loongarch/insns.decode:569 */
            return LISA_FNMADD_D;
        case 0xd:
            /* 00001000 1101.... ........ ........ */
            /* target/loongarch/insns.decode:570 */
            return LISA_FNMSUB_S;
        case 0xe:
            /* 00001000 1110.... ........ ........ */
            /* target/loongarch/insns.decode:571 */
            return LISA_FNMSUB_D;
        case 0x11:
            /* 00001001 0001.... ........ ........ */
            /* target/loongarch/insns.decode:722 */
            return LISA_VFMADD_S;
        case 0x12:
            /* 00001001 0010.... ........ ........ */
            /* target/loongarch/insns.decode:723 */
            return LISA_VFMADD_D;
        case 0x15:
            /* 00001001 0101.... ........ ........ */
            /* target/loongarch/insns.decode:724 */
            return LISA_VFMSUB_S;
        case 0x16:
            /* 00001001 0110.... ........ ........ */
            /* target/loongarch/insns.decode:725 */
            return LISA_VFMSUB_D;
        case 0x19:
            /* 00001001 1001.... ........ ........ */
            /* target/loongarch/insns.decode:726 */
            return LISA_VFNMADD_S;
        case 0x1a:
            /* 00001001 1010.... ........ ........ */
            /* target/loongarch/insns.decode:727 */
            return LISA_VFNMADD_D;
        case 0x1d:
            /* 00001001 1101.... ........ ........ */
            /* target/loongarch/insns.decode:728 */
            return LISA_VFNMSUB_S;
        case 0x1e:
            /* 00001001 1110.... ........ ........ */
            /* target/loongarch/insns.decode:729 */
            return LISA_VFNMSUB_D;
        case 0x21:
            /* 00001010 0001.... ........ ........ */
            /* target/loongarch/insns.decode:730 */
            return LISA_XVFMADD_S;
        case 0x22:
            /* 00001010 0010.... ........ ........ */
            /* target/loongarch/insns.decode:731 */
            return LISA_XVFMADD_D;
        case 0x25:
            /* 00001010 0101.... ........ ........ */
            /* target/loongarch/insns.decode:732 */
            return LISA_XVFMSUB_S;
        case 0x26:
            /* 00001010 0110.... ........ ........ */
            /* target/loongarch/insns.decode:733 */
            return LISA_XVFMSUB_D;
        case 0x29:
            /* 00001010 1001.... ........ ........ */
            /* target/loongarch/insns.decode:734 */
            return LISA_XVFNMADD_S;
        case 0x2a:
            /* 00001010 1010.... ........ ........ */
            /* target/loongarch/insns.decode:735 */
            return LISA_XVFNMADD_D;
        case 0x2d:
            /* 00001010 1101.... ........ ........ */
            /* target/loongarch/insns.decode:736 */
            return LISA_XVFNMSUB_S;
        case 0x2e:
            /* 00001010 1110.... ........ ........ */
            /* target/loongarch/insns.decode:737 */
            return LISA_XVFNMSUB_D;
        }
        break;
    case 0x3:
        /* 000011.. ........ ........ ........ */
        switch ((insn >> 20) & 0x3f) {
        case 0x1:
            /* 00001100 0001.... ........ ........ */
            switch ((insn >> 3) & 0x3) {
            case 0x0:
                /* 00001100 0001.... ........ ...00... */
                /* target/loongarch/insns.decode:572 */
                return LISA_FCMP_COND_S;
            }
            break;
        case 0x2:
            /* 00001100 0010.... ........ ........ */
            switch ((insn >> 3) & 0x3) {
            case 0x0:
                /* 00001100 0010.... ........ ...00... */
                /* target/loongarch/insns.decode:573 */
                return LISA_FCMP_COND_D;
            }
            break;
        case 0x5:
            /* 00001100 0101.... ........ ........ */
            /* target/loongarch/insns.decode:738 */
            return LISA_VFCMP_COND_S;
        case 0x6:
            /* 00001100 0110.... ........ ........ */
            /* target/loongarch/insns.decode:739 */
            return LISA_VFCMP_COND_D;
        case 0x9:
            /* 00001100 1001.... ........ ........ */
            /* target/loongarch/insns.decode:740 */
            return LISA_XVFCMP_COND_S;
        case 0xa:
            /* 00001100 1010.... ........ ........ */
            /* target/loongarch/insns.decode:741 */
            return LISA_XVFCMP_COND_D;
        case 0x10:
            /* 00001101 0000.... ........ ........ */
            switch ((insn >> 18) & 0x3) {
            case 0x0:
                /* 00001101 000000.. ........ ........ */
                /* target/loongarch/insns.decode:574 */
                return LISA_FSEL;
            }
            break;
        case 0x11:
            /* 00001101 0001.... ........ ........ */
            /* target/loongarch/insns.decode:742 */
            return LISA_VBITSEL_V;
        case 0x12:
            /* 00001101 0010.... ........ ........ */
            /* target/loongarch/insns.decode:743 */
            return LISA_XVBITSEL_V;
        case 0x15:
            /* 00001101 0101.... ........ ........ */
            /* target/loongarch/insns.decode:744 */
            return LISA_VSHUF_B;
        case 0x16:
            /* 00001101 0110.... ........ ........ */
            /* target/loongarch/insns.decode:745 */
            return LISA_XVSHUF_B;
        case 0x19:
            /* 00001101 1001.... ........ ........ */
            /* target/loongarch/insns.decode:746 */
            return LISA_VEXTR_V;
        case 0x1a:
            /* 00001101 1010.... ........ ........ */
            /* target/loongarch/insns.decode:747 */
            return LISA_XVEXTR_V;
        case 0x29:
            /* 00001110 1001.... ........ ........ */
            /* target/loongarch/insns.decode:748 */
            return LISA_VFMADDSUB_S;
        case 0x2a:
            /* 00001110 1010.... ........ ........ */
            /* target/loongarch/insns.decode:749 */
            return LISA_VFMADDSUB_D;
        case 0x2d:
            /* 00001110 1101.... ........ ........ */
            /* target/loongarch/insns.decode:750 */
            return LISA_VFMSUBADD_S;
        case 0x2e:
            /* 00001110 1110.... ........ ........ */
            /* target/loongarch/insns.decode:751 */
            return LISA_VFMSUBADD_D;
        case 0x31:
            /* 00001111 0001.... ........ ........ */
            /* target/loongarch/insns.decode:752 */
            return LISA_XVFMADDSUB_S;
        case 0x32:
            /* 00001111 0010.... ........ ........ */
            /* target/loongarch/insns.decode:753 */
            return LISA_XVFMADDSUB_D;
        case 0x35:
            /* 00001111 0101.... ........ ........ */
            /* target/loongarch/insns.decode:754 */
            return LISA_XVFMSUBADD_S;
        case 0x36:
            /* 00001111 0110.... ........ ........ */
            /* target/loongarch/insns.decode:755 */
            return LISA_XVFMSUBADD_D;
        }
        break;
    case 0x4:
        /* 000100.. ........ ........ ........ */
        /* target/loongarch/insns.decode:577 */
        return LISA_ADDU16I_D;
    case 0x5:
        /* 000101.. ........ ........ ........ */
        switch ((insn >> 25) & 0x1) {
        case 0x0:
            /* 0001010. ........ ........ ........ */
            /* target/loongarch/insns.decode:578 */
            return LISA_LU12I_W;
        case 0x1:
            /* 0001011. ........ ........ ........ */
            /* target/loongarch/insns.decode:579 */
            return LISA_LU32I_D;
        }
        break;
    case 0x6:
        /* 000110.. ........ ........ ........ */
        switch ((insn >> 25) & 0x1) {
        case 0x0:
            /* 0001100. ........ ........ ........ */
            /* target/loongarch/insns.decode:580 */
            return LISA_PCADDI;
        case 0x1:
            /* 0001101. ........ ........ ........ */
            /* target/loongarch/insns.decode:581 */
            return LISA_PCALAU12I;
        }
        break;
    case 0x7:
        /* 000111.. ........ ........ ........ */
        switch ((insn >> 25) & 0x1) {
        case 0x0:
            /* 0001110. ........ ........ ........ */
            /* target/loongarch/insns.decode:582 */
            return LISA_PCADDU12I;
        case 0x1:
            /* 0001111. ........ ........ ........ */
            /* target/loongarch/insns.decode:583 */
            return LISA_PCADDU18I;
        }
        break;
    case 0x8:
        /* 001000.. ........ ........ ........ */
        switch ((insn >> 24) & 0x3) {
        case 0x0:
            /* 00100000 ........ ........ ........ */
            /* target/loongarch/insns.decode:586 */
            return LISA_LL_W;
        case 0x1:
            /* 00100001 ........ ........ ........ */
            /* target/loongarch/insns.decode:587 */
            return LISA_SC_W;
        case 0x2:
            /* 00100010 ........ ........ ........ */
            /* target/loongarch/insns.decode:588 */
            return LISA_LL_D;
        case 0x3:
            /* 00100011 ........ ........ ........ */
            /* target/loongarch/insns.decode:589 */
            return LISA_SC_D;
        }
        break;
    case 0x9:
        /* 001001.. ........ ........ ........ */
        switch ((insn >> 24) & 0x3) {
        case 0x0:
            /* 00100100 ........ ........ ........ */
            /* target/loongarch/insns.decode:590 */
            return LISA_LDPTR_W;
        case 0x1:
            /* 00100101 ........ ........ ........ */
            /* target/loongarch/insns.decode:591 */
            return LISA_STPTR_W;
        case 0x2:
            /* 00100110 ........ ........ ........ */
            /* target/loongarch/insns.decode:592 */
            return LISA_LDPTR_D;
        case 0x3:
            /* 00100111 ........ ........ ........ */
            /* target/loongarch/insns.decode:593 */
            return LISA_STPTR_D;
        }
        break;
    case 0xa:
        /* 001010.. ........ ........ ........ */
        switch ((insn >> 22) & 0xf) {
        case 0x0:
            /* 00101000 00...... ........ ........ */
            /* target/loongarch/insns.decode:594 */
            return LISA_LD_B;
        case 0x1:
            /* 00101000 01...... ........ ........ */
            /* target/loongarch/insns.decode:595 */
            return LISA_LD_H;
        case 0x2:
            /* 00101000 10...... ........ ........ */
            /* target/loongarch/insns.decode:596 */
            return LISA_LD_W;
        case 0x3:
            /* 00101000 11...... ........ ........ */
            /* target/loongarch/insns.decode:597 */
            return LISA_LD_D;
        case 0x4:
            /* 00101001 00...... ........ ........ */
            /* target/loongarch/insns.decode:598 */
            return LISA_ST_B;
        case 0x5:
            /* 00101001 01...... ........ ........ */
            /* target/loongarch/insns.decode:599 */
            return LISA_ST_H;
        case 0x6:
            /* 00101001 10...... ........ ........ */
            /* target/loongarch/insns.decode:600 */
            return LISA_ST_W;
        case 0x7:
            /* 00101001 11...... ........ ........ */
            /* target/loongarch/insns.decode:601 */
            return LISA_ST_D;
        case 0x8:
            /* 00101010 00...... ........ ........ */
            /* target/loongarch/insns.decode:602 */
            return LISA_LD_BU;
        case 0x9:
            /* 00101010 01...... ........ ........ */
            /* target/loongarch/insns.decode:603 */
            return LISA_LD_HU;
        case 0xa:
            /* 00101010 10...... ........ ........ */
            /* target/loongarch/insns.decode:604 */
            return LISA_LD_WU;
        case 0xb:
            /* 00101010 11...... ........ ........ */
            /* target/loongarch/insns.decode:605 */
            return LISA_PRELD;
        case 0xc:
            /* 00101011 00...... ........ ........ */
            /* target/loongarch/insns.decode:606 */
            return LISA_FLD_S;
        case 0xd:
            /* 00101011 01...... ........ ........ */
            /* target/loongarch/insns.decode:607 */
            return LISA_FST_S;
        case 0xe:
            /* 00101011 10...... ........ ........ */
            /* target/loongarch/insns.decode:608 */
            return LISA_FLD_D;
        case 0xf:
            /* 00101011 11...... ........ ........ */
            /* target/loongarch/insns.decode:609 */
            return LISA_FST_D;
        }
        break;
    case 0xb:
        /* 001011.. ........ ........ ........ */
        switch ((insn >> 22) & 0xf) {
        case 0x0:
            /* 00101100 00...... ........ ........ */
            /* target/loongarch/insns.decode:714 */
            return LISA_VLD;
        case 0x1:
            /* 00101100 01...... ........ ........ */
            /* target/loongarch/insns.decode:715 */
            return LISA_VST;
        case 0x2:
            /* 00101100 10...... ........ ........ */
            /* target/loongarch/insns.decode:716 */
            return LISA_XVLD;
        case 0x3:
            /* 00101100 11...... ........ ........ */
            /* target/loongarch/insns.decode:717 */
            return LISA_XVST;
        }
        break;
    case 0xc:
        /* 001100.. ........ ........ ........ */
        switch ((insn >> 23) & 0x7) {
        case 0x0:
            /* 00110000 0....... ........ ........ */
            switch ((insn >> 21) & 0x3) {
            case 0x0:
                /* 00110000 000..... ........ ........ */
                switch ((insn >> 19) & 0x3) {
                case 0x2:
                    /* 00110000 00010... ........ ........ */
                    /* target/loongarch/insns.decode:718 */
                    return LISA_VLDREPL_D;
                }
                break;
            case 0x1:
                /* 00110000 001..... ........ ........ */
                switch ((insn >> 20) & 0x1) {
                case 0x0:
                    /* 00110000 0010.... ........ ........ */
                    /* target/loongarch/insns.decode:719 */
                    return LISA_VLDREPL_W;
                }
                break;
            case 0x2:
                /* 00110000 010..... ........ ........ */
                /* target/loongarch/insns.decode:720 */
                return LISA_VLDREPL_H;
            }
            break;
        case 0x1:
            /* 00110000 1....... ........ ........ */
            switch ((insn >> 22) & 0x1) {
            case 0x0:
                /* 00110000 10...... ........ ........ */
                /* target/loongarch/insns.decode:721 */
                return LISA_VLDREPL_B;
            }
            break;
        case 0x2:
            /* 00110001 0....... ........ ........ */
            switch ((insn >> 21) & 0x3) {
            case 0x0:
                /* 00110001 000..... ........ ........ */
                switch ((insn >> 19) & 0x3) {
                case 0x2:
                    /* 00110001 00010... ........ ........ */
                    /* target/loongarch/insns.decode:757 */
                    return LISA_VSTELM_D;
                }
                break;
            case 0x1:
                /* 00110001 001..... ........ ........ */
                switch ((insn >> 20) & 0x1) {
                case 0x0:
                    /* 00110001 0010.... ........ ........ */
                    /* target/loongarch/insns.decode:758 */
                    return LISA_VSTELM_W;
                }
                break;
            case 0x2:
                /* 00110001 010..... ........ ........ */
                /* target/loongarch/insns.decode:759 */
                return LISA_VSTELM_H;
            }
            break;
        case 0x3:
            /* 00110001 1....... ........ ........ */
            switch ((insn >> 22) & 0x1) {
            case 0x0:
                /* 00110001 10...... ........ ........ */
                /* target/loongarch/insns.decode:760 */
                return LISA_VSTELM_B;
            }
            break;
        case 0x4:
            /* 00110010 0....... ........ ........ */
            switch ((insn >> 21) & 0x3) {
            case 0x0:
                /* 00110010 000..... ........ ........ */
                switch ((insn >> 19) & 0x3) {
                case 0x2:
                    /* 00110010 00010... ........ ........ */
                    /* target/loongarch/insns.decode:761 */
                    return LISA_XVLDREPL_D;
                }
                break;
            case 0x1:
                /* 00110010 001..... ........ ........ */
                switch ((insn >> 20) & 0x1) {
                case 0x0:
                    /* 00110010 0010.... ........ ........ */
                    /* target/loongarch/insns.decode:762 */
                    return LISA_XVLDREPL_W;
                }
                break;
            case 0x2:
                /* 00110010 010..... ........ ........ */
                /* target/loongarch/insns.decode:763 */
                return LISA_XVLDREPL_H;
            }
            break;
        case 0x5:
            /* 00110010 1....... ........ ........ */
            switch ((insn >> 22) & 0x1) {
            case 0x0:
                /* 00110010 10...... ........ ........ */
                /* target/loongarch/insns.decode:764 */
                return LISA_XVLDREPL_B;
            }
            break;
        case 0x6:
            /* 00110011 0....... ........ ........ */
            switch ((insn >> 22) & 0x1) {
            case 0x0:
                /* 00110011 00...... ........ ........ */
                switch ((insn >> 21) & 0x1) {
                case 0x0:
                    /* 00110011 000..... ........ ........ */
                    switch ((insn >> 20) & 0x1) {
                    case 0x1:
                        /* 00110011 0001.... ........ ........ */
                        /* target/loongarch/insns.decode:765 */
                        return LISA_XVSTELM_D;
                    }
                    break;
                case 0x1:
                    /* 00110011 001..... ........ ........ */
                    /* target/loongarch/insns.decode:766 */
                    return LISA_XVSTELM_W;
                }
                break;
            case 0x1:
                /* 00110011 01...... ........ ........ */
                /* target/loongarch/insns.decode:767 */
                return LISA_XVSTELM_H;
            }
            break;
        case 0x7:
            /* 00110011 1....... ........ ........ */
            /* target/loongarch/insns.decode:768 */
            return LISA_XVSTELM_B;
        }
        break;
    case 0xe:
        /* 001110.. ........ ........ ........ */
        switch ((insn >> 15) & 0x7ff) {
        case 0x0:
            /* 00111000 00000000 0....... ........ */
            /* target/loongarch/insns.decode:610 */
            return LISA_LDX_B;
        case 0x8:
            /* 00111000 00000100 0....... ........ */
            /* target/loongarch/insns.decode:611 */
            return LISA_LDX_H;
        case 0x10:
            /* 00111000 00001000 0....... ........ */
            /* target/loongarch/insns.decode:612 */
            return LISA_LDX_W;
        case 0x18:
            /* 00111000 00001100 0....... ........ */
            /* target/loongarch/insns.decode:613 */
            return LISA_LDX_D;
        case 0x20:
            /* 00111000 00010000 0....... ........ */
            /* target/loongarch/insns.decode:614 */
            return LISA_STX_B;
        case 0x28:
            /* 00111000 00010100 0....... ........ */
            /* target/loongarch/insns.decode:615 */
            return LISA_STX_H;
        case 0x30:
            /* 00111000 00011000 0....... ........ */
            /* target/loongarch/insns.decode:616 */
            return LISA_STX_W;
        case 0x38:
            /* 00111000 00011100 0....... ........ */
            /* target/loongarch/insns.decode:617 */
            return LISA_STX_D;
        case 0x40:
            /* 00111000 00100000 0....... ........ */
            /* target/loongarch/insns.decode:618 */
            return LISA_LDX_BU;
        case 0x48:
            /* 00111000 00100100 0....... ........ */
            /* target/loongarch/insns.decode:619 */
            return LISA_LDX_HU;
        case 0x50:
            /* 00111000 00101000 0....... ........ */
            /* target/loongarch/insns.decode:620 */
            return LISA_LDX_WU;
        case 0x58:
            /* 00111000 00101100 0....... ........ */
            /* target/loongarch/insns.decode:621 */
            return LISA_PRELDX;
        case 0x60:
            /* 00111000 00110000 0....... ........ */
            /* target/loongarch/insns.decode:622 */
            return LISA_FLDX_S;
        case 0x68:
            /* 00111000 00110100 0....... ........ */
            /* target/loongarch/insns.decode:623 */
            return LISA_FLDX_D;
        case 0x70:
            /* 00111000 00111000 0....... ........ */
            /* target/loongarch/insns.decode:624 */
            return LISA_FSTX_S;
        case 0x78:
            /* 00111000 00111100 0....... ........ */
            /* target/loongarch/insns.decode:625 */
            return LISA_FSTX_D;
        case 0x80:
            /* 00111000 01000000 0....... ........ */
            /* target/loongarch/insns.decode:688 */
            return LISA_VLDX;
        case 0x88:
            /* 00111000 01000100 0....... ........ */
            /* target/loongarch/insns.decode:689 */
            return LISA_VSTX;
        case 0x90:
            /* 00111000 01001000 0....... ........ */
            /* target/loongarch/insns.decode:690 */
            return LISA_XVLDX;
        case 0x98:
            /* 00111000 01001100 0....... ........ */
            /* target/loongarch/insns.decode:691 */
            return LISA_XVSTX;
        case 0xc0:
            /* 00111000 01100000 0....... ........ */
            /* target/loongarch/insns.decode:626 */
            return LISA_AMSWAP_W;
        case 0xc1:
            /* 00111000 01100000 1....... ........ */
            /* target/loongarch/insns.decode:627 */
            return LISA_AMSWAP_D;
        case 0xc2:
            /* 00111000 01100001 0....... ........ */
            /* target/loongarch/insns.decode:628 */
            return LISA_AMADD_W;
        case 0xc3:
            /* 00111000 01100001 1....... ........ */
            /* target/loongarch/insns.decode:629 */
            return LISA_AMADD_D;
        case 0xc4:
            /* 00111000 01100010 0....... ........ */
            /* target/loongarch/insns.decode:630 */
            return LISA_AMAND_W;
        case 0xc5:
            /* 00111000 01100010 1....... ........ */
            /* target/loongarch/insns.decode:631 */
            return LISA_AMAND_D;
        case 0xc6:
            /* 00111000 01100011 0....... ........ */
            /* target/loongarch/insns.decode:632 */
            return LISA_AMOR_W;
        case 0xc7:
            /* 00111000 01100011 1....... ........ */
            /* target/loongarch/insns.decode:633 */
            return LISA_AMOR_D;
        case 0xc8:
            /* 00111000 01100100 0....... ........ */
            /* target/loongarch/insns.decode:634 */
            return LISA_AMXOR_W;
        case 0xc9:
            /* 00111000 01100100 1....... ........ */
            /* target/loongarch/insns.decode:635 */
            return LISA_AMXOR_D;
        case 0xca:
            /* 00111000 01100101 0....... ........ */
            /* target/loongarch/insns.decode:636 */
            return LISA_AMMAX_W;
        case 0xcb:
            /* 00111000 01100101 1....... ........ */
            /* target/loongarch/insns.decode:637 */
            return LISA_AMMAX_D;
        case 0xcc:
            /* 00111000 01100110 0....... ........ */
            /* target/loongarch/insns.decode:638 */
            return LISA_AMMIN_W;
        case 0xcd:
            /* 00111000 01100110 1....... ........ */
            /* target/loongarch/insns.decode:639 */
            return LISA_AMMIN_D;
        case 0xce:
            /* 00111000 01100111 0....... ........ */
            /* target/loongarch/insns.decode:640 */
            return LISA_AMMAX_WU;
        case 0xcf:
            /* 00111000 01100111 1....... ........ */
            /* target/loongarch/insns.decode:641 */
            return LISA_AMMAX_DU;
        case 0xd0:
            /* 00111000 01101000 0....... ........ */
            /* target/loongarch/insns.decode:642 */
            return LISA_AMMIN_WU;
        case 0xd1:
            /* 00111000 01101000 1....... ........ */
            /* target/loongarch/insns.decode:643 */
            return LISA_AMMIN_DU;
        case 0xd2:
            /* 00111000 01101001 0....... ........ */
            /* target/loongarch/insns.decode:644 */
            return LISA_AMSWAP_DB_W;
        case 0xd3:
            /* 00111000 01101001 1....... ........ */
            /* target/loongarch/insns.decode:645 */
            return LISA_AMSWAP_DB_D;
        case 0xd4:
            /* 00111000 01101010 0....... ........ */
            /* target/loongarch/insns.decode:646 */
            return LISA_AMADD_DB_W;
        case 0xd5:
            /* 00111000 01101010 1....... ........ */
            /* target/loongarch/insns.decode:647 */
            return LISA_AMADD_DB_D;
        case 0xd6:
            /* 00111000 01101011 0....... ........ */
            /* target/loongarch/insns.decode:648 */
            return LISA_AMAND_DB_W;
        case 0xd7:
            /* 00111000 01101011 1....... ........ */
            /* target/loongarch/insns.decode:649 */
            return LISA_AMAND_DB_D;
        case 0xd8:
            /* 00111000 01101100 0....... ........ */
            /* target/loongarch/insns.decode:650 */
            return LISA_AMOR_DB_W;
        case 0xd9:
            /* 00111000 01101100 1....... ........ */
            /* target/loongarch/insns.decode:651 */
            return LISA_AMOR_DB_D;
        case 0xda:
            /* 00111000 01101101 0....... ........ */
            /* target/loongarch/insns.decode:652 */
            return LISA_AMXOR_DB_W;
        case 0xdb:
            /* 00111000 01101101 1....... ........ */
            /* target/loongarch/insns.decode:653 */
            return LISA_AMXOR_DB_D;
        case 0xdc:
            /* 00111000 01101110 0....... ........ */
            /* target/loongarch/insns.decode:654 */
            return LISA_AMMAX_DB_W;
        case 0xdd:
            /* 00111000 01101110 1....... ........ */
            /* target/loongarch/insns.decode:655 */
            return LISA_AMMAX_DB_D;
        case 0xde:
            /* 00111000 01101111 0....... ........ */
            /* target/loongarch/insns.decode:656 */
            return LISA_AMMIN_DB_W;
        case 0xdf:
            /* 00111000 01101111 1....... ........ */
            /* target/loongarch/insns.decode:657 */
            return LISA_AMMIN_DB_D;
        case 0xe0:
            /* 00111000 01110000 0....... ........ */
            /* target/loongarch/insns.decode:658 */
            return LISA_AMMAX_DB_WU;
        case 0xe1:
            /* 00111000 01110000 1....... ........ */
            /* target/loongarch/insns.decode:659 */
            return LISA_AMMAX_DB_DU;
        case 0xe2:
            /* 00111000 01110001 0....... ........ */
            /* target/loongarch/insns.decode:660 */
            return LISA_AMMIN_DB_WU;
        case 0xe3:
            /* 00111000 01110001 1....... ........ */
            /* target/loongarch/insns.decode:661 */
            return LISA_AMMIN_DB_DU;
        case 0xe4:
            /* 00111000 01110010 0....... ........ */
            /* target/loongarch/insns.decode:662 */
            return LISA_DBAR;
        case 0xe5:
            /* 00111000 01110010 1....... ........ */
            /* target/loongarch/insns.decode:663 */
            return LISA_IBAR;
        case 0xe8:
            /* 00111000 01110100 0....... ........ */
            /* target/loongarch/insns.decode:664 */
            return LISA_FLDGT_S;
        case 0xe9:
            /* 00111000 01110100 1....... ........ */
            /* target/loongarch/insns.decode:665 */
            return LISA_FLDGT_D;
        case 0xea:
            /* 00111000 01110101 0....... ........ */
            /* target/loongarch/insns.decode:666 */
            return LISA_FLDLE_S;
        case 0xeb:
            /* 00111000 01110101 1....... ........ */
            /* target/loongarch/insns.decode:667 */
            return LISA_FLDLE_D;
        case 0xec:
            /* 00111000 01110110 0....... ........ */
            /* target/loongarch/insns.decode:668 */
            return LISA_FSTGT_S;
        case 0xed:
            /* 00111000 01110110 1....... ........ */
            /* target/loongarch/insns.decode:669 */
            return LISA_FSTGT_D;
        case 0xee:
            /* 00111000 01110111 0....... ........ */
            /* target/loongarch/insns.decode:670 */
            return LISA_FSTLE_S;
        case 0xef:
            /* 00111000 01110111 1....... ........ */
            /* target/loongarch/insns.decode:671 */
            return LISA_FSTLE_D;
        case 0xf0:
            /* 00111000 01111000 0....... ........ */
            /* target/loongarch/insns.decode:672 */
            return LISA_LDGT_B;
        case 0xf1:
            /* 00111000 01111000 1....... ........ */
            /* target/loongarch/insns.decode:673 */
            return LISA_LDGT_H;
        case 0xf2:
            /* 00111000 01111001 0....... ........ */
            /* target/loongarch/insns.decode:674 */
            return LISA_LDGT_W;
        case 0xf3:
            /* 00111000 01111001 1....... ........ */
            /* target/loongarch/insns.decode:675 */
            return LISA_LDGT_D;
        case 0xf4:
            /* 00111000 01111010 0....... ........ */
            /* target/loongarch/insns.decode:676 */
            return LISA_LDLE_B;
        case 0xf5:
            /* 00111000 01111010 1....... ........ */
            /* target/loongarch/insns.decode:677 */
            return LISA_LDLE_H;
        case 0xf6:
            /* 00111000 01111011 0....... ........ */
            /* target/loongarch/insns.decode:678 */
            return LISA_LDLE_W;
        case 0xf7:
            /* 00111000 01111011 1....... ........ */
            /* target/loongarch/insns.decode:679 */
            return LISA_LDLE_D;
        case 0xf8:
            /* 00111000 01111100 0....... ........ */
            /* target/loongarch/insns.decode:680 */
            return LISA_STGT_B;
        case 0xf9:
            /* 00111000 01111100 1....... ........ */
            /* target/loongarch/insns.decode:681 */
            return LISA_STGT_H;
        case 0xfa:
            /* 00111000 01111101 0....... ........ */
            /* target/loongarch/insns.decode:682 */
            return LISA_STGT_W;
        case 0xfb:
            /* 00111000 01111101 1....... ........ */
            /* target/loongarch/insns.decode:683 */
            return LISA_STGT_D;
        case 0xfc:
            /* 00111000 01111110 0....... ........ */
            /* target/loongarch/insns.decode:684 */
            return LISA_STLE_B;
        case 0xfd:
            /* 00111000 01111110 1....... ........ */
            /* target/loongarch/insns.decode:685 */
            return LISA_STLE_H;
        case 0xfe:
            /* 00111000 01111111 0....... ........ */
            /* target/loongarch/insns.decode:686 */
            return LISA_STLE_W;
        case 0xff:
            /* 00111000 01111111 1....... ........ */
            /* target/loongarch/insns.decode:687 */
            return LISA_STLE_D;
        }
        break;
    case 0x10:
        /* 010000.. ........ ........ ........ */
        /* target/loongarch/insns.decode:694 */
        return LISA_BEQZ;
    case 0x11:
        /* 010001.. ........ ........ ........ */
        /* target/loongarch/insns.decode:695 */
        return LISA_BNEZ;
    case 0x12:
        /* 010010.. ........ ........ ........ */
        switch ((insn >> 8) & 0x3) {
        case 0x0:
            /* 010010.. ........ ......00 ........ */
            /* target/loongarch/insns.decode:696 */
            return LISA_BCEQZ;
        case 0x1:
            /* 010010.. ........ ......01 ........ */
            /* target/loongarch/insns.decode:697 */
            return LISA_BCNEZ;
        }
        break;
    case 0x13:
        /* 010011.. ........ ........ ........ */
        /* target/loongarch/insns.decode:698 */
        return LISA_JIRL;
    case 0x14:
        /* 010100.. ........ ........ ........ */
        /* target/loongarch/insns.decode:699 */
        return LISA_B;
    case 0x15:
        /* 010101.. ........ ........ ........ */
        /* target/loongarch/insns.decode:700 */
        return LISA_BL;
    case 0x16:
        /* 010110.. ........ ........ ........ */
        /* target/loongarch/insns.decode:701 */
        return LISA_BEQ;
    case 0x17:
        /* 010111.. ........ ........ ........ */
        /* target/loongarch/insns.decode:702 */
        return LISA_BNE;
    case 0x18:
        /* 011000.. ........ ........ ........ */
        /* target/loongarch/insns.decode:703 */
        return LISA_BLT;
    case 0x19:
        /* 011001.. ........ ........ ........ */
        /* target/loongarch/insns.decode:704 */
        return LISA_BGE;
    case 0x1a:
        /* 011010.. ........ ........ ........ */
        /* target/loongarch/insns.decode:705 */
        return LISA_BLTU;
    case 0x1b:
        /* 011011.. ........ ........ ........ */
        /* target/loongarch/insns.decode:706 */
        return LISA_BGEU;
    case 0x1c:
        /* 011100.. ........ ........ ........ */
        switch ((insn >> 18) & 0xff) {
        case 0x0:
            /* 01110000 000000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 00000000 0....... ........ */
                /* target/loongarch/insns.decode:769 */
                return LISA_VSEQ_B;
            case 0x1:
                /* 01110000 00000000 1....... ........ */
                /* target/loongarch/insns.decode:770 */
                return LISA_VSEQ_H;
            case 0x2:
                /* 01110000 00000001 0....... ........ */
                /* target/loongarch/insns.decode:771 */
                return LISA_VSEQ_W;
            case 0x3:
                /* 01110000 00000001 1....... ........ */
                /* target/loongarch/insns.decode:772 */
                return LISA_VSEQ_D;
            case 0x4:
                /* 01110000 00000010 0....... ........ */
                /* target/loongarch/insns.decode:773 */
                return LISA_VSLE_B;
            case 0x5:
                /* 01110000 00000010 1....... ........ */
                /* target/loongarch/insns.decode:774 */
                return LISA_VSLE_H;
            case 0x6:
                /* 01110000 00000011 0....... ........ */
                /* target/loongarch/insns.decode:775 */
                return LISA_VSLE_W;
            case 0x7:
                /* 01110000 00000011 1....... ........ */
                /* target/loongarch/insns.decode:776 */
                return LISA_VSLE_D;
            }
            break;
        case 0x1:
            /* 01110000 000001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 00000100 0....... ........ */
                /* target/loongarch/insns.decode:777 */
                return LISA_VSLE_BU;
            case 0x1:
                /* 01110000 00000100 1....... ........ */
                /* target/loongarch/insns.decode:778 */
                return LISA_VSLE_HU;
            case 0x2:
                /* 01110000 00000101 0....... ........ */
                /* target/loongarch/insns.decode:779 */
                return LISA_VSLE_WU;
            case 0x3:
                /* 01110000 00000101 1....... ........ */
                /* target/loongarch/insns.decode:780 */
                return LISA_VSLE_DU;
            case 0x4:
                /* 01110000 00000110 0....... ........ */
                /* target/loongarch/insns.decode:781 */
                return LISA_VSLT_B;
            case 0x5:
                /* 01110000 00000110 1....... ........ */
                /* target/loongarch/insns.decode:782 */
                return LISA_VSLT_H;
            case 0x6:
                /* 01110000 00000111 0....... ........ */
                /* target/loongarch/insns.decode:783 */
                return LISA_VSLT_W;
            case 0x7:
                /* 01110000 00000111 1....... ........ */
                /* target/loongarch/insns.decode:784 */
                return LISA_VSLT_D;
            }
            break;
        case 0x2:
            /* 01110000 000010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 00001000 0....... ........ */
                /* target/loongarch/insns.decode:785 */
                return LISA_VSLT_BU;
            case 0x1:
                /* 01110000 00001000 1....... ........ */
                /* target/loongarch/insns.decode:786 */
                return LISA_VSLT_HU;
            case 0x2:
                /* 01110000 00001001 0....... ........ */
                /* target/loongarch/insns.decode:787 */
                return LISA_VSLT_WU;
            case 0x3:
                /* 01110000 00001001 1....... ........ */
                /* target/loongarch/insns.decode:788 */
                return LISA_VSLT_DU;
            case 0x4:
                /* 01110000 00001010 0....... ........ */
                /* target/loongarch/insns.decode:789 */
                return LISA_VADD_B;
            case 0x5:
                /* 01110000 00001010 1....... ........ */
                /* target/loongarch/insns.decode:790 */
                return LISA_VADD_H;
            case 0x6:
                /* 01110000 00001011 0....... ........ */
                /* target/loongarch/insns.decode:791 */
                return LISA_VADD_W;
            case 0x7:
                /* 01110000 00001011 1....... ........ */
                /* target/loongarch/insns.decode:792 */
                return LISA_VADD_D;
            }
            break;
        case 0x3:
            /* 01110000 000011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 00001100 0....... ........ */
                /* target/loongarch/insns.decode:793 */
                return LISA_VSUB_B;
            case 0x1:
                /* 01110000 00001100 1....... ........ */
                /* target/loongarch/insns.decode:794 */
                return LISA_VSUB_H;
            case 0x2:
                /* 01110000 00001101 0....... ........ */
                /* target/loongarch/insns.decode:795 */
                return LISA_VSUB_W;
            case 0x3:
                /* 01110000 00001101 1....... ........ */
                /* target/loongarch/insns.decode:796 */
                return LISA_VSUB_D;
            }
            break;
        case 0x7:
            /* 01110000 000111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110000 00011110 0....... ........ */
                /* target/loongarch/insns.decode:797 */
                return LISA_VADDWEV_H_B;
            case 0x5:
                /* 01110000 00011110 1....... ........ */
                /* target/loongarch/insns.decode:798 */
                return LISA_VADDWEV_W_H;
            case 0x6:
                /* 01110000 00011111 0....... ........ */
                /* target/loongarch/insns.decode:799 */
                return LISA_VADDWEV_D_W;
            case 0x7:
                /* 01110000 00011111 1....... ........ */
                /* target/loongarch/insns.decode:800 */
                return LISA_VADDWEV_Q_D;
            }
            break;
        case 0x8:
            /* 01110000 001000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 00100000 0....... ........ */
                /* target/loongarch/insns.decode:801 */
                return LISA_VSUBWEV_H_B;
            case 0x1:
                /* 01110000 00100000 1....... ........ */
                /* target/loongarch/insns.decode:802 */
                return LISA_VSUBWEV_W_H;
            case 0x2:
                /* 01110000 00100001 0....... ........ */
                /* target/loongarch/insns.decode:803 */
                return LISA_VSUBWEV_D_W;
            case 0x3:
                /* 01110000 00100001 1....... ........ */
                /* target/loongarch/insns.decode:804 */
                return LISA_VSUBWEV_Q_D;
            case 0x4:
                /* 01110000 00100010 0....... ........ */
                /* target/loongarch/insns.decode:805 */
                return LISA_VADDWOD_H_B;
            case 0x5:
                /* 01110000 00100010 1....... ........ */
                /* target/loongarch/insns.decode:806 */
                return LISA_VADDWOD_W_H;
            case 0x6:
                /* 01110000 00100011 0....... ........ */
                /* target/loongarch/insns.decode:807 */
                return LISA_VADDWOD_D_W;
            case 0x7:
                /* 01110000 00100011 1....... ........ */
                /* target/loongarch/insns.decode:808 */
                return LISA_VADDWOD_Q_D;
            }
            break;
        case 0x9:
            /* 01110000 001001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 00100100 0....... ........ */
                /* target/loongarch/insns.decode:809 */
                return LISA_VSUBWOD_H_B;
            case 0x1:
                /* 01110000 00100100 1....... ........ */
                /* target/loongarch/insns.decode:810 */
                return LISA_VSUBWOD_W_H;
            case 0x2:
                /* 01110000 00100101 0....... ........ */
                /* target/loongarch/insns.decode:811 */
                return LISA_VSUBWOD_D_W;
            case 0x3:
                /* 01110000 00100101 1....... ........ */
                /* target/loongarch/insns.decode:812 */
                return LISA_VSUBWOD_Q_D;
            }
            break;
        case 0xb:
            /* 01110000 001011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110000 00101110 0....... ........ */
                /* target/loongarch/insns.decode:829 */
                return LISA_VADDWEV_H_BU;
            case 0x5:
                /* 01110000 00101110 1....... ........ */
                /* target/loongarch/insns.decode:830 */
                return LISA_VADDWEV_W_HU;
            case 0x6:
                /* 01110000 00101111 0....... ........ */
                /* target/loongarch/insns.decode:831 */
                return LISA_VADDWEV_D_WU;
            case 0x7:
                /* 01110000 00101111 1....... ........ */
                /* target/loongarch/insns.decode:832 */
                return LISA_VADDWEV_Q_DU;
            }
            break;
        case 0xc:
            /* 01110000 001100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 00110000 0....... ........ */
                /* target/loongarch/insns.decode:833 */
                return LISA_VSUBWEV_H_BU;
            case 0x1:
                /* 01110000 00110000 1....... ........ */
                /* target/loongarch/insns.decode:834 */
                return LISA_VSUBWEV_W_HU;
            case 0x2:
                /* 01110000 00110001 0....... ........ */
                /* target/loongarch/insns.decode:835 */
                return LISA_VSUBWEV_D_WU;
            case 0x3:
                /* 01110000 00110001 1....... ........ */
                /* target/loongarch/insns.decode:836 */
                return LISA_VSUBWEV_Q_DU;
            case 0x4:
                /* 01110000 00110010 0....... ........ */
                /* target/loongarch/insns.decode:837 */
                return LISA_VADDWOD_H_BU;
            case 0x5:
                /* 01110000 00110010 1....... ........ */
                /* target/loongarch/insns.decode:838 */
                return LISA_VADDWOD_W_HU;
            case 0x6:
                /* 01110000 00110011 0....... ........ */
                /* target/loongarch/insns.decode:839 */
                return LISA_VADDWOD_D_WU;
            case 0x7:
                /* 01110000 00110011 1....... ........ */
                /* target/loongarch/insns.decode:840 */
                return LISA_VADDWOD_Q_DU;
            }
            break;
        case 0xd:
            /* 01110000 001101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 00110100 0....... ........ */
                /* target/loongarch/insns.decode:841 */
                return LISA_VSUBWOD_H_BU;
            case 0x1:
                /* 01110000 00110100 1....... ........ */
                /* target/loongarch/insns.decode:842 */
                return LISA_VSUBWOD_W_HU;
            case 0x2:
                /* 01110000 00110101 0....... ........ */
                /* target/loongarch/insns.decode:843 */
                return LISA_VSUBWOD_D_WU;
            case 0x3:
                /* 01110000 00110101 1....... ........ */
                /* target/loongarch/insns.decode:844 */
                return LISA_VSUBWOD_Q_DU;
            }
            break;
        case 0xf:
            /* 01110000 001111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110000 00111110 0....... ........ */
                /* target/loongarch/insns.decode:845 */
                return LISA_VADDWEV_H_BU_B;
            case 0x5:
                /* 01110000 00111110 1....... ........ */
                /* target/loongarch/insns.decode:846 */
                return LISA_VADDWEV_W_HU_H;
            case 0x6:
                /* 01110000 00111111 0....... ........ */
                /* target/loongarch/insns.decode:847 */
                return LISA_VADDWEV_D_WU_W;
            case 0x7:
                /* 01110000 00111111 1....... ........ */
                /* target/loongarch/insns.decode:848 */
                return LISA_VADDWEV_Q_DU_D;
            }
            break;
        case 0x10:
            /* 01110000 010000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01000000 0....... ........ */
                /* target/loongarch/insns.decode:849 */
                return LISA_VADDWOD_H_BU_B;
            case 0x1:
                /* 01110000 01000000 1....... ........ */
                /* target/loongarch/insns.decode:850 */
                return LISA_VADDWOD_W_HU_H;
            case 0x2:
                /* 01110000 01000001 0....... ........ */
                /* target/loongarch/insns.decode:851 */
                return LISA_VADDWOD_D_WU_W;
            case 0x3:
                /* 01110000 01000001 1....... ........ */
                /* target/loongarch/insns.decode:852 */
                return LISA_VADDWOD_Q_DU_D;
            }
            break;
        case 0x11:
            /* 01110000 010001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110000 01000110 0....... ........ */
                /* target/loongarch/insns.decode:853 */
                return LISA_VSADD_B;
            case 0x5:
                /* 01110000 01000110 1....... ........ */
                /* target/loongarch/insns.decode:854 */
                return LISA_VSADD_H;
            case 0x6:
                /* 01110000 01000111 0....... ........ */
                /* target/loongarch/insns.decode:855 */
                return LISA_VSADD_W;
            case 0x7:
                /* 01110000 01000111 1....... ........ */
                /* target/loongarch/insns.decode:856 */
                return LISA_VSADD_D;
            }
            break;
        case 0x12:
            /* 01110000 010010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01001000 0....... ........ */
                /* target/loongarch/insns.decode:857 */
                return LISA_VSSUB_B;
            case 0x1:
                /* 01110000 01001000 1....... ........ */
                /* target/loongarch/insns.decode:858 */
                return LISA_VSSUB_H;
            case 0x2:
                /* 01110000 01001001 0....... ........ */
                /* target/loongarch/insns.decode:859 */
                return LISA_VSSUB_W;
            case 0x3:
                /* 01110000 01001001 1....... ........ */
                /* target/loongarch/insns.decode:860 */
                return LISA_VSSUB_D;
            case 0x4:
                /* 01110000 01001010 0....... ........ */
                /* target/loongarch/insns.decode:861 */
                return LISA_VSADD_BU;
            case 0x5:
                /* 01110000 01001010 1....... ........ */
                /* target/loongarch/insns.decode:862 */
                return LISA_VSADD_HU;
            case 0x6:
                /* 01110000 01001011 0....... ........ */
                /* target/loongarch/insns.decode:863 */
                return LISA_VSADD_WU;
            case 0x7:
                /* 01110000 01001011 1....... ........ */
                /* target/loongarch/insns.decode:864 */
                return LISA_VSADD_DU;
            }
            break;
        case 0x13:
            /* 01110000 010011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01001100 0....... ........ */
                /* target/loongarch/insns.decode:865 */
                return LISA_VSSUB_BU;
            case 0x1:
                /* 01110000 01001100 1....... ........ */
                /* target/loongarch/insns.decode:866 */
                return LISA_VSSUB_HU;
            case 0x2:
                /* 01110000 01001101 0....... ........ */
                /* target/loongarch/insns.decode:867 */
                return LISA_VSSUB_WU;
            case 0x3:
                /* 01110000 01001101 1....... ........ */
                /* target/loongarch/insns.decode:868 */
                return LISA_VSSUB_DU;
            }
            break;
        case 0x15:
            /* 01110000 010101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01010100 0....... ........ */
                /* target/loongarch/insns.decode:869 */
                return LISA_VHADDW_H_B;
            case 0x1:
                /* 01110000 01010100 1....... ........ */
                /* target/loongarch/insns.decode:870 */
                return LISA_VHADDW_W_H;
            case 0x2:
                /* 01110000 01010101 0....... ........ */
                /* target/loongarch/insns.decode:871 */
                return LISA_VHADDW_D_W;
            case 0x3:
                /* 01110000 01010101 1....... ........ */
                /* target/loongarch/insns.decode:872 */
                return LISA_VHADDW_Q_D;
            case 0x4:
                /* 01110000 01010110 0....... ........ */
                /* target/loongarch/insns.decode:873 */
                return LISA_VHSUBW_H_B;
            case 0x5:
                /* 01110000 01010110 1....... ........ */
                /* target/loongarch/insns.decode:874 */
                return LISA_VHSUBW_W_H;
            case 0x6:
                /* 01110000 01010111 0....... ........ */
                /* target/loongarch/insns.decode:875 */
                return LISA_VHSUBW_D_W;
            case 0x7:
                /* 01110000 01010111 1....... ........ */
                /* target/loongarch/insns.decode:876 */
                return LISA_VHSUBW_Q_D;
            }
            break;
        case 0x16:
            /* 01110000 010110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01011000 0....... ........ */
                /* target/loongarch/insns.decode:877 */
                return LISA_VHADDW_HU_BU;
            case 0x1:
                /* 01110000 01011000 1....... ........ */
                /* target/loongarch/insns.decode:878 */
                return LISA_VHADDW_WU_HU;
            case 0x2:
                /* 01110000 01011001 0....... ........ */
                /* target/loongarch/insns.decode:879 */
                return LISA_VHADDW_DU_WU;
            case 0x3:
                /* 01110000 01011001 1....... ........ */
                /* target/loongarch/insns.decode:880 */
                return LISA_VHADDW_QU_DU;
            case 0x4:
                /* 01110000 01011010 0....... ........ */
                /* target/loongarch/insns.decode:881 */
                return LISA_VHSUBW_HU_BU;
            case 0x5:
                /* 01110000 01011010 1....... ........ */
                /* target/loongarch/insns.decode:882 */
                return LISA_VHSUBW_WU_HU;
            case 0x6:
                /* 01110000 01011011 0....... ........ */
                /* target/loongarch/insns.decode:883 */
                return LISA_VHSUBW_DU_WU;
            case 0x7:
                /* 01110000 01011011 1....... ........ */
                /* target/loongarch/insns.decode:884 */
                return LISA_VHSUBW_QU_DU;
            }
            break;
        case 0x17:
            /* 01110000 010111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01011100 0....... ........ */
                /* target/loongarch/insns.decode:885 */
                return LISA_VADDA_B;
            case 0x1:
                /* 01110000 01011100 1....... ........ */
                /* target/loongarch/insns.decode:886 */
                return LISA_VADDA_H;
            case 0x2:
                /* 01110000 01011101 0....... ........ */
                /* target/loongarch/insns.decode:887 */
                return LISA_VADDA_W;
            case 0x3:
                /* 01110000 01011101 1....... ........ */
                /* target/loongarch/insns.decode:888 */
                return LISA_VADDA_D;
            }
            break;
        case 0x18:
            /* 01110000 011000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01100000 0....... ........ */
                /* target/loongarch/insns.decode:889 */
                return LISA_VABSD_B;
            case 0x1:
                /* 01110000 01100000 1....... ........ */
                /* target/loongarch/insns.decode:890 */
                return LISA_VABSD_H;
            case 0x2:
                /* 01110000 01100001 0....... ........ */
                /* target/loongarch/insns.decode:891 */
                return LISA_VABSD_W;
            case 0x3:
                /* 01110000 01100001 1....... ........ */
                /* target/loongarch/insns.decode:892 */
                return LISA_VABSD_D;
            case 0x4:
                /* 01110000 01100010 0....... ........ */
                /* target/loongarch/insns.decode:893 */
                return LISA_VABSD_BU;
            case 0x5:
                /* 01110000 01100010 1....... ........ */
                /* target/loongarch/insns.decode:894 */
                return LISA_VABSD_HU;
            case 0x6:
                /* 01110000 01100011 0....... ........ */
                /* target/loongarch/insns.decode:895 */
                return LISA_VABSD_WU;
            case 0x7:
                /* 01110000 01100011 1....... ........ */
                /* target/loongarch/insns.decode:896 */
                return LISA_VABSD_DU;
            }
            break;
        case 0x19:
            /* 01110000 011001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01100100 0....... ........ */
                /* target/loongarch/insns.decode:897 */
                return LISA_VAVG_B;
            case 0x1:
                /* 01110000 01100100 1....... ........ */
                /* target/loongarch/insns.decode:898 */
                return LISA_VAVG_H;
            case 0x2:
                /* 01110000 01100101 0....... ........ */
                /* target/loongarch/insns.decode:899 */
                return LISA_VAVG_W;
            case 0x3:
                /* 01110000 01100101 1....... ........ */
                /* target/loongarch/insns.decode:900 */
                return LISA_VAVG_D;
            case 0x4:
                /* 01110000 01100110 0....... ........ */
                /* target/loongarch/insns.decode:901 */
                return LISA_VAVG_BU;
            case 0x5:
                /* 01110000 01100110 1....... ........ */
                /* target/loongarch/insns.decode:902 */
                return LISA_VAVG_HU;
            case 0x6:
                /* 01110000 01100111 0....... ........ */
                /* target/loongarch/insns.decode:903 */
                return LISA_VAVG_WU;
            case 0x7:
                /* 01110000 01100111 1....... ........ */
                /* target/loongarch/insns.decode:904 */
                return LISA_VAVG_DU;
            }
            break;
        case 0x1a:
            /* 01110000 011010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01101000 0....... ........ */
                /* target/loongarch/insns.decode:905 */
                return LISA_VAVGR_B;
            case 0x1:
                /* 01110000 01101000 1....... ........ */
                /* target/loongarch/insns.decode:906 */
                return LISA_VAVGR_H;
            case 0x2:
                /* 01110000 01101001 0....... ........ */
                /* target/loongarch/insns.decode:907 */
                return LISA_VAVGR_W;
            case 0x3:
                /* 01110000 01101001 1....... ........ */
                /* target/loongarch/insns.decode:908 */
                return LISA_VAVGR_D;
            case 0x4:
                /* 01110000 01101010 0....... ........ */
                /* target/loongarch/insns.decode:909 */
                return LISA_VAVGR_BU;
            case 0x5:
                /* 01110000 01101010 1....... ........ */
                /* target/loongarch/insns.decode:910 */
                return LISA_VAVGR_HU;
            case 0x6:
                /* 01110000 01101011 0....... ........ */
                /* target/loongarch/insns.decode:911 */
                return LISA_VAVGR_WU;
            case 0x7:
                /* 01110000 01101011 1....... ........ */
                /* target/loongarch/insns.decode:912 */
                return LISA_VAVGR_DU;
            }
            break;
        case 0x1c:
            /* 01110000 011100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01110000 0....... ........ */
                /* target/loongarch/insns.decode:913 */
                return LISA_VMAX_B;
            case 0x1:
                /* 01110000 01110000 1....... ........ */
                /* target/loongarch/insns.decode:914 */
                return LISA_VMAX_H;
            case 0x2:
                /* 01110000 01110001 0....... ........ */
                /* target/loongarch/insns.decode:915 */
                return LISA_VMAX_W;
            case 0x3:
                /* 01110000 01110001 1....... ........ */
                /* target/loongarch/insns.decode:916 */
                return LISA_VMAX_D;
            case 0x4:
                /* 01110000 01110010 0....... ........ */
                /* target/loongarch/insns.decode:917 */
                return LISA_VMIN_B;
            case 0x5:
                /* 01110000 01110010 1....... ........ */
                /* target/loongarch/insns.decode:918 */
                return LISA_VMIN_H;
            case 0x6:
                /* 01110000 01110011 0....... ........ */
                /* target/loongarch/insns.decode:919 */
                return LISA_VMIN_W;
            case 0x7:
                /* 01110000 01110011 1....... ........ */
                /* target/loongarch/insns.decode:920 */
                return LISA_VMIN_D;
            }
            break;
        case 0x1d:
            /* 01110000 011101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 01110100 0....... ........ */
                /* target/loongarch/insns.decode:921 */
                return LISA_VMAX_BU;
            case 0x1:
                /* 01110000 01110100 1....... ........ */
                /* target/loongarch/insns.decode:922 */
                return LISA_VMAX_HU;
            case 0x2:
                /* 01110000 01110101 0....... ........ */
                /* target/loongarch/insns.decode:923 */
                return LISA_VMAX_WU;
            case 0x3:
                /* 01110000 01110101 1....... ........ */
                /* target/loongarch/insns.decode:924 */
                return LISA_VMAX_DU;
            case 0x4:
                /* 01110000 01110110 0....... ........ */
                /* target/loongarch/insns.decode:925 */
                return LISA_VMIN_BU;
            case 0x5:
                /* 01110000 01110110 1....... ........ */
                /* target/loongarch/insns.decode:926 */
                return LISA_VMIN_HU;
            case 0x6:
                /* 01110000 01110111 0....... ........ */
                /* target/loongarch/insns.decode:927 */
                return LISA_VMIN_WU;
            case 0x7:
                /* 01110000 01110111 1....... ........ */
                /* target/loongarch/insns.decode:928 */
                return LISA_VMIN_DU;
            }
            break;
        case 0x21:
            /* 01110000 100001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 10000100 0....... ........ */
                /* target/loongarch/insns.decode:929 */
                return LISA_VMUL_B;
            case 0x1:
                /* 01110000 10000100 1....... ........ */
                /* target/loongarch/insns.decode:930 */
                return LISA_VMUL_H;
            case 0x2:
                /* 01110000 10000101 0....... ........ */
                /* target/loongarch/insns.decode:931 */
                return LISA_VMUL_W;
            case 0x3:
                /* 01110000 10000101 1....... ........ */
                /* target/loongarch/insns.decode:932 */
                return LISA_VMUL_D;
            case 0x4:
                /* 01110000 10000110 0....... ........ */
                /* target/loongarch/insns.decode:933 */
                return LISA_VMUH_B;
            case 0x5:
                /* 01110000 10000110 1....... ........ */
                /* target/loongarch/insns.decode:934 */
                return LISA_VMUH_H;
            case 0x6:
                /* 01110000 10000111 0....... ........ */
                /* target/loongarch/insns.decode:935 */
                return LISA_VMUH_W;
            case 0x7:
                /* 01110000 10000111 1....... ........ */
                /* target/loongarch/insns.decode:936 */
                return LISA_VMUH_D;
            }
            break;
        case 0x22:
            /* 01110000 100010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 10001000 0....... ........ */
                /* target/loongarch/insns.decode:937 */
                return LISA_VMUH_BU;
            case 0x1:
                /* 01110000 10001000 1....... ........ */
                /* target/loongarch/insns.decode:938 */
                return LISA_VMUH_HU;
            case 0x2:
                /* 01110000 10001001 0....... ........ */
                /* target/loongarch/insns.decode:939 */
                return LISA_VMUH_WU;
            case 0x3:
                /* 01110000 10001001 1....... ........ */
                /* target/loongarch/insns.decode:940 */
                return LISA_VMUH_DU;
            }
            break;
        case 0x24:
            /* 01110000 100100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 10010000 0....... ........ */
                /* target/loongarch/insns.decode:941 */
                return LISA_VMULWEV_H_B;
            case 0x1:
                /* 01110000 10010000 1....... ........ */
                /* target/loongarch/insns.decode:942 */
                return LISA_VMULWEV_W_H;
            case 0x2:
                /* 01110000 10010001 0....... ........ */
                /* target/loongarch/insns.decode:943 */
                return LISA_VMULWEV_D_W;
            case 0x3:
                /* 01110000 10010001 1....... ........ */
                /* target/loongarch/insns.decode:944 */
                return LISA_VMULWEV_Q_D;
            case 0x4:
                /* 01110000 10010010 0....... ........ */
                /* target/loongarch/insns.decode:945 */
                return LISA_VMULWOD_H_B;
            case 0x5:
                /* 01110000 10010010 1....... ........ */
                /* target/loongarch/insns.decode:946 */
                return LISA_VMULWOD_W_H;
            case 0x6:
                /* 01110000 10010011 0....... ........ */
                /* target/loongarch/insns.decode:947 */
                return LISA_VMULWOD_D_W;
            case 0x7:
                /* 01110000 10010011 1....... ........ */
                /* target/loongarch/insns.decode:948 */
                return LISA_VMULWOD_Q_D;
            }
            break;
        case 0x26:
            /* 01110000 100110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 10011000 0....... ........ */
                /* target/loongarch/insns.decode:949 */
                return LISA_VMULWEV_H_BU;
            case 0x1:
                /* 01110000 10011000 1....... ........ */
                /* target/loongarch/insns.decode:950 */
                return LISA_VMULWEV_W_HU;
            case 0x2:
                /* 01110000 10011001 0....... ........ */
                /* target/loongarch/insns.decode:951 */
                return LISA_VMULWEV_D_WU;
            case 0x3:
                /* 01110000 10011001 1....... ........ */
                /* target/loongarch/insns.decode:952 */
                return LISA_VMULWEV_Q_DU;
            case 0x4:
                /* 01110000 10011010 0....... ........ */
                /* target/loongarch/insns.decode:953 */
                return LISA_VMULWOD_H_BU;
            case 0x5:
                /* 01110000 10011010 1....... ........ */
                /* target/loongarch/insns.decode:954 */
                return LISA_VMULWOD_W_HU;
            case 0x6:
                /* 01110000 10011011 0....... ........ */
                /* target/loongarch/insns.decode:955 */
                return LISA_VMULWOD_D_WU;
            case 0x7:
                /* 01110000 10011011 1....... ........ */
                /* target/loongarch/insns.decode:956 */
                return LISA_VMULWOD_Q_DU;
            }
            break;
        case 0x28:
            /* 01110000 101000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 10100000 0....... ........ */
                /* target/loongarch/insns.decode:957 */
                return LISA_VMULWEV_H_BU_B;
            case 0x1:
                /* 01110000 10100000 1....... ........ */
                /* target/loongarch/insns.decode:958 */
                return LISA_VMULWEV_W_HU_H;
            case 0x2:
                /* 01110000 10100001 0....... ........ */
                /* target/loongarch/insns.decode:959 */
                return LISA_VMULWEV_D_WU_W;
            case 0x3:
                /* 01110000 10100001 1....... ........ */
                /* target/loongarch/insns.decode:960 */
                return LISA_VMULWEV_Q_DU_D;
            case 0x4:
                /* 01110000 10100010 0....... ........ */
                /* target/loongarch/insns.decode:961 */
                return LISA_VMULWOD_H_BU_B;
            case 0x5:
                /* 01110000 10100010 1....... ........ */
                /* target/loongarch/insns.decode:962 */
                return LISA_VMULWOD_W_HU_H;
            case 0x6:
                /* 01110000 10100011 0....... ........ */
                /* target/loongarch/insns.decode:963 */
                return LISA_VMULWOD_D_WU_W;
            case 0x7:
                /* 01110000 10100011 1....... ........ */
                /* target/loongarch/insns.decode:964 */
                return LISA_VMULWOD_Q_DU_D;
            }
            break;
        case 0x2a:
            /* 01110000 101010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 10101000 0....... ........ */
                /* target/loongarch/insns.decode:965 */
                return LISA_VMADD_B;
            case 0x1:
                /* 01110000 10101000 1....... ........ */
                /* target/loongarch/insns.decode:966 */
                return LISA_VMADD_H;
            case 0x2:
                /* 01110000 10101001 0....... ........ */
                /* target/loongarch/insns.decode:967 */
                return LISA_VMADD_W;
            case 0x3:
                /* 01110000 10101001 1....... ........ */
                /* target/loongarch/insns.decode:968 */
                return LISA_VMADD_D;
            case 0x4:
                /* 01110000 10101010 0....... ........ */
                /* target/loongarch/insns.decode:969 */
                return LISA_VMSUB_B;
            case 0x5:
                /* 01110000 10101010 1....... ........ */
                /* target/loongarch/insns.decode:970 */
                return LISA_VMSUB_H;
            case 0x6:
                /* 01110000 10101011 0....... ........ */
                /* target/loongarch/insns.decode:971 */
                return LISA_VMSUB_W;
            case 0x7:
                /* 01110000 10101011 1....... ........ */
                /* target/loongarch/insns.decode:972 */
                return LISA_VMSUB_D;
            }
            break;
        case 0x2b:
            /* 01110000 101011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 10101100 0....... ........ */
                /* target/loongarch/insns.decode:973 */
                return LISA_VMADDWEV_H_B;
            case 0x1:
                /* 01110000 10101100 1....... ........ */
                /* target/loongarch/insns.decode:974 */
                return LISA_VMADDWEV_W_H;
            case 0x2:
                /* 01110000 10101101 0....... ........ */
                /* target/loongarch/insns.decode:975 */
                return LISA_VMADDWEV_D_W;
            case 0x3:
                /* 01110000 10101101 1....... ........ */
                /* target/loongarch/insns.decode:976 */
                return LISA_VMADDWEV_Q_D;
            case 0x4:
                /* 01110000 10101110 0....... ........ */
                /* target/loongarch/insns.decode:977 */
                return LISA_VMADDWOD_H_B;
            case 0x5:
                /* 01110000 10101110 1....... ........ */
                /* target/loongarch/insns.decode:978 */
                return LISA_VMADDWOD_W_H;
            case 0x6:
                /* 01110000 10101111 0....... ........ */
                /* target/loongarch/insns.decode:979 */
                return LISA_VMADDWOD_D_W;
            case 0x7:
                /* 01110000 10101111 1....... ........ */
                /* target/loongarch/insns.decode:980 */
                return LISA_VMADDWOD_Q_D;
            }
            break;
        case 0x2d:
            /* 01110000 101101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 10110100 0....... ........ */
                /* target/loongarch/insns.decode:981 */
                return LISA_VMADDWEV_H_BU;
            case 0x1:
                /* 01110000 10110100 1....... ........ */
                /* target/loongarch/insns.decode:982 */
                return LISA_VMADDWEV_W_HU;
            case 0x2:
                /* 01110000 10110101 0....... ........ */
                /* target/loongarch/insns.decode:983 */
                return LISA_VMADDWEV_D_WU;
            case 0x3:
                /* 01110000 10110101 1....... ........ */
                /* target/loongarch/insns.decode:984 */
                return LISA_VMADDWEV_Q_DU;
            case 0x4:
                /* 01110000 10110110 0....... ........ */
                /* target/loongarch/insns.decode:985 */
                return LISA_VMADDWOD_H_BU;
            case 0x5:
                /* 01110000 10110110 1....... ........ */
                /* target/loongarch/insns.decode:986 */
                return LISA_VMADDWOD_W_HU;
            case 0x6:
                /* 01110000 10110111 0....... ........ */
                /* target/loongarch/insns.decode:987 */
                return LISA_VMADDWOD_D_WU;
            case 0x7:
                /* 01110000 10110111 1....... ........ */
                /* target/loongarch/insns.decode:988 */
                return LISA_VMADDWOD_Q_DU;
            }
            break;
        case 0x2f:
            /* 01110000 101111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 10111100 0....... ........ */
                /* target/loongarch/insns.decode:989 */
                return LISA_VMADDWEV_H_BU_B;
            case 0x1:
                /* 01110000 10111100 1....... ........ */
                /* target/loongarch/insns.decode:990 */
                return LISA_VMADDWEV_W_HU_H;
            case 0x2:
                /* 01110000 10111101 0....... ........ */
                /* target/loongarch/insns.decode:991 */
                return LISA_VMADDWEV_D_WU_W;
            case 0x3:
                /* 01110000 10111101 1....... ........ */
                /* target/loongarch/insns.decode:992 */
                return LISA_VMADDWEV_Q_DU_D;
            case 0x4:
                /* 01110000 10111110 0....... ........ */
                /* target/loongarch/insns.decode:993 */
                return LISA_VMADDWOD_H_BU_B;
            case 0x5:
                /* 01110000 10111110 1....... ........ */
                /* target/loongarch/insns.decode:994 */
                return LISA_VMADDWOD_W_HU_H;
            case 0x6:
                /* 01110000 10111111 0....... ........ */
                /* target/loongarch/insns.decode:995 */
                return LISA_VMADDWOD_D_WU_W;
            case 0x7:
                /* 01110000 10111111 1....... ........ */
                /* target/loongarch/insns.decode:996 */
                return LISA_VMADDWOD_Q_DU_D;
            }
            break;
        case 0x38:
            /* 01110000 111000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 11100000 0....... ........ */
                /* target/loongarch/insns.decode:997 */
                return LISA_VDIV_B;
            case 0x1:
                /* 01110000 11100000 1....... ........ */
                /* target/loongarch/insns.decode:998 */
                return LISA_VDIV_H;
            case 0x2:
                /* 01110000 11100001 0....... ........ */
                /* target/loongarch/insns.decode:999 */
                return LISA_VDIV_W;
            case 0x3:
                /* 01110000 11100001 1....... ........ */
                /* target/loongarch/insns.decode:1000 */
                return LISA_VDIV_D;
            case 0x4:
                /* 01110000 11100010 0....... ........ */
                /* target/loongarch/insns.decode:1001 */
                return LISA_VMOD_B;
            case 0x5:
                /* 01110000 11100010 1....... ........ */
                /* target/loongarch/insns.decode:1002 */
                return LISA_VMOD_H;
            case 0x6:
                /* 01110000 11100011 0....... ........ */
                /* target/loongarch/insns.decode:1003 */
                return LISA_VMOD_W;
            case 0x7:
                /* 01110000 11100011 1....... ........ */
                /* target/loongarch/insns.decode:1004 */
                return LISA_VMOD_D;
            }
            break;
        case 0x39:
            /* 01110000 111001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 11100100 0....... ........ */
                /* target/loongarch/insns.decode:1005 */
                return LISA_VDIV_BU;
            case 0x1:
                /* 01110000 11100100 1....... ........ */
                /* target/loongarch/insns.decode:1006 */
                return LISA_VDIV_HU;
            case 0x2:
                /* 01110000 11100101 0....... ........ */
                /* target/loongarch/insns.decode:1007 */
                return LISA_VDIV_WU;
            case 0x3:
                /* 01110000 11100101 1....... ........ */
                /* target/loongarch/insns.decode:1008 */
                return LISA_VDIV_DU;
            case 0x4:
                /* 01110000 11100110 0....... ........ */
                /* target/loongarch/insns.decode:1009 */
                return LISA_VMOD_BU;
            case 0x5:
                /* 01110000 11100110 1....... ........ */
                /* target/loongarch/insns.decode:1010 */
                return LISA_VMOD_HU;
            case 0x6:
                /* 01110000 11100111 0....... ........ */
                /* target/loongarch/insns.decode:1011 */
                return LISA_VMOD_WU;
            case 0x7:
                /* 01110000 11100111 1....... ........ */
                /* target/loongarch/insns.decode:1012 */
                return LISA_VMOD_DU;
            }
            break;
        case 0x3a:
            /* 01110000 111010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 11101000 0....... ........ */
                /* target/loongarch/insns.decode:1013 */
                return LISA_VSLL_B;
            case 0x1:
                /* 01110000 11101000 1....... ........ */
                /* target/loongarch/insns.decode:1014 */
                return LISA_VSLL_H;
            case 0x2:
                /* 01110000 11101001 0....... ........ */
                /* target/loongarch/insns.decode:1015 */
                return LISA_VSLL_W;
            case 0x3:
                /* 01110000 11101001 1....... ........ */
                /* target/loongarch/insns.decode:1016 */
                return LISA_VSLL_D;
            case 0x4:
                /* 01110000 11101010 0....... ........ */
                /* target/loongarch/insns.decode:1017 */
                return LISA_VSRL_B;
            case 0x5:
                /* 01110000 11101010 1....... ........ */
                /* target/loongarch/insns.decode:1018 */
                return LISA_VSRL_H;
            case 0x6:
                /* 01110000 11101011 0....... ........ */
                /* target/loongarch/insns.decode:1019 */
                return LISA_VSRL_W;
            case 0x7:
                /* 01110000 11101011 1....... ........ */
                /* target/loongarch/insns.decode:1020 */
                return LISA_VSRL_D;
            }
            break;
        case 0x3b:
            /* 01110000 111011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 11101100 0....... ........ */
                /* target/loongarch/insns.decode:1021 */
                return LISA_VSRA_B;
            case 0x1:
                /* 01110000 11101100 1....... ........ */
                /* target/loongarch/insns.decode:1022 */
                return LISA_VSRA_H;
            case 0x2:
                /* 01110000 11101101 0....... ........ */
                /* target/loongarch/insns.decode:1023 */
                return LISA_VSRA_W;
            case 0x3:
                /* 01110000 11101101 1....... ........ */
                /* target/loongarch/insns.decode:1024 */
                return LISA_VSRA_D;
            case 0x4:
                /* 01110000 11101110 0....... ........ */
                /* target/loongarch/insns.decode:1025 */
                return LISA_VROTR_B;
            case 0x5:
                /* 01110000 11101110 1....... ........ */
                /* target/loongarch/insns.decode:1026 */
                return LISA_VROTR_H;
            case 0x6:
                /* 01110000 11101111 0....... ........ */
                /* target/loongarch/insns.decode:1027 */
                return LISA_VROTR_W;
            case 0x7:
                /* 01110000 11101111 1....... ........ */
                /* target/loongarch/insns.decode:1028 */
                return LISA_VROTR_D;
            }
            break;
        case 0x3c:
            /* 01110000 111100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110000 11110000 0....... ........ */
                /* target/loongarch/insns.decode:1029 */
                return LISA_VSRLR_B;
            case 0x1:
                /* 01110000 11110000 1....... ........ */
                /* target/loongarch/insns.decode:1030 */
                return LISA_VSRLR_H;
            case 0x2:
                /* 01110000 11110001 0....... ........ */
                /* target/loongarch/insns.decode:1031 */
                return LISA_VSRLR_W;
            case 0x3:
                /* 01110000 11110001 1....... ........ */
                /* target/loongarch/insns.decode:1032 */
                return LISA_VSRLR_D;
            case 0x4:
                /* 01110000 11110010 0....... ........ */
                /* target/loongarch/insns.decode:1033 */
                return LISA_VSRAR_B;
            case 0x5:
                /* 01110000 11110010 1....... ........ */
                /* target/loongarch/insns.decode:1034 */
                return LISA_VSRAR_H;
            case 0x6:
                /* 01110000 11110011 0....... ........ */
                /* target/loongarch/insns.decode:1035 */
                return LISA_VSRAR_W;
            case 0x7:
                /* 01110000 11110011 1....... ........ */
                /* target/loongarch/insns.decode:1036 */
                return LISA_VSRAR_D;
            }
            break;
        case 0x3d:
            /* 01110000 111101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110000 11110100 1....... ........ */
                /* target/loongarch/insns.decode:1037 */
                return LISA_VSRLN_B_H;
            case 0x2:
                /* 01110000 11110101 0....... ........ */
                /* target/loongarch/insns.decode:1038 */
                return LISA_VSRLN_H_W;
            case 0x3:
                /* 01110000 11110101 1....... ........ */
                /* target/loongarch/insns.decode:1039 */
                return LISA_VSRLN_W_D;
            case 0x5:
                /* 01110000 11110110 1....... ........ */
                /* target/loongarch/insns.decode:1040 */
                return LISA_VSRAN_B_H;
            case 0x6:
                /* 01110000 11110111 0....... ........ */
                /* target/loongarch/insns.decode:1041 */
                return LISA_VSRAN_H_W;
            case 0x7:
                /* 01110000 11110111 1....... ........ */
                /* target/loongarch/insns.decode:1042 */
                return LISA_VSRAN_W_D;
            }
            break;
        case 0x3e:
            /* 01110000 111110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110000 11111000 1....... ........ */
                /* target/loongarch/insns.decode:1043 */
                return LISA_VSRLRN_B_H;
            case 0x2:
                /* 01110000 11111001 0....... ........ */
                /* target/loongarch/insns.decode:1044 */
                return LISA_VSRLRN_H_W;
            case 0x3:
                /* 01110000 11111001 1....... ........ */
                /* target/loongarch/insns.decode:1045 */
                return LISA_VSRLRN_W_D;
            case 0x5:
                /* 01110000 11111010 1....... ........ */
                /* target/loongarch/insns.decode:1046 */
                return LISA_VSRARN_B_H;
            case 0x6:
                /* 01110000 11111011 0....... ........ */
                /* target/loongarch/insns.decode:1047 */
                return LISA_VSRARN_H_W;
            case 0x7:
                /* 01110000 11111011 1....... ........ */
                /* target/loongarch/insns.decode:1048 */
                return LISA_VSRARN_W_D;
            }
            break;
        case 0x3f:
            /* 01110000 111111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110000 11111100 1....... ........ */
                /* target/loongarch/insns.decode:1049 */
                return LISA_VSSRLN_B_H;
            case 0x2:
                /* 01110000 11111101 0....... ........ */
                /* target/loongarch/insns.decode:1050 */
                return LISA_VSSRLN_H_W;
            case 0x3:
                /* 01110000 11111101 1....... ........ */
                /* target/loongarch/insns.decode:1051 */
                return LISA_VSSRLN_W_D;
            case 0x5:
                /* 01110000 11111110 1....... ........ */
                /* target/loongarch/insns.decode:1052 */
                return LISA_VSSRAN_B_H;
            case 0x6:
                /* 01110000 11111111 0....... ........ */
                /* target/loongarch/insns.decode:1053 */
                return LISA_VSSRAN_H_W;
            case 0x7:
                /* 01110000 11111111 1....... ........ */
                /* target/loongarch/insns.decode:1054 */
                return LISA_VSSRAN_W_D;
            }
            break;
        case 0x40:
            /* 01110001 000000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110001 00000000 1....... ........ */
                /* target/loongarch/insns.decode:1055 */
                return LISA_VSSRLRN_B_H;
            case 0x2:
                /* 01110001 00000001 0....... ........ */
                /* target/loongarch/insns.decode:1056 */
                return LISA_VSSRLRN_H_W;
            case 0x3:
                /* 01110001 00000001 1....... ........ */
                /* target/loongarch/insns.decode:1057 */
                return LISA_VSSRLRN_W_D;
            case 0x5:
                /* 01110001 00000010 1....... ........ */
                /* target/loongarch/insns.decode:1058 */
                return LISA_VSSRARN_B_H;
            case 0x6:
                /* 01110001 00000011 0....... ........ */
                /* target/loongarch/insns.decode:1059 */
                return LISA_VSSRARN_H_W;
            case 0x7:
                /* 01110001 00000011 1....... ........ */
                /* target/loongarch/insns.decode:1060 */
                return LISA_VSSRARN_W_D;
            }
            break;
        case 0x41:
            /* 01110001 000001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110001 00000100 1....... ........ */
                /* target/loongarch/insns.decode:1061 */
                return LISA_VSSRLN_BU_H;
            case 0x2:
                /* 01110001 00000101 0....... ........ */
                /* target/loongarch/insns.decode:1062 */
                return LISA_VSSRLN_HU_W;
            case 0x3:
                /* 01110001 00000101 1....... ........ */
                /* target/loongarch/insns.decode:1063 */
                return LISA_VSSRLN_WU_D;
            case 0x5:
                /* 01110001 00000110 1....... ........ */
                /* target/loongarch/insns.decode:1064 */
                return LISA_VSSRAN_BU_H;
            case 0x6:
                /* 01110001 00000111 0....... ........ */
                /* target/loongarch/insns.decode:1065 */
                return LISA_VSSRAN_HU_W;
            case 0x7:
                /* 01110001 00000111 1....... ........ */
                /* target/loongarch/insns.decode:1066 */
                return LISA_VSSRAN_WU_D;
            }
            break;
        case 0x42:
            /* 01110001 000010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110001 00001000 1....... ........ */
                /* target/loongarch/insns.decode:1067 */
                return LISA_VSSRLRN_BU_H;
            case 0x2:
                /* 01110001 00001001 0....... ........ */
                /* target/loongarch/insns.decode:1068 */
                return LISA_VSSRLRN_HU_W;
            case 0x3:
                /* 01110001 00001001 1....... ........ */
                /* target/loongarch/insns.decode:1069 */
                return LISA_VSSRLRN_WU_D;
            case 0x5:
                /* 01110001 00001010 1....... ........ */
                /* target/loongarch/insns.decode:1070 */
                return LISA_VSSRARN_BU_H;
            case 0x6:
                /* 01110001 00001011 0....... ........ */
                /* target/loongarch/insns.decode:1071 */
                return LISA_VSSRARN_HU_W;
            case 0x7:
                /* 01110001 00001011 1....... ........ */
                /* target/loongarch/insns.decode:1072 */
                return LISA_VSSRARN_WU_D;
            }
            break;
        case 0x43:
            /* 01110001 000011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110001 00001100 0....... ........ */
                /* target/loongarch/insns.decode:1073 */
                return LISA_VBITCLR_B;
            case 0x1:
                /* 01110001 00001100 1....... ........ */
                /* target/loongarch/insns.decode:1074 */
                return LISA_VBITCLR_H;
            case 0x2:
                /* 01110001 00001101 0....... ........ */
                /* target/loongarch/insns.decode:1075 */
                return LISA_VBITCLR_W;
            case 0x3:
                /* 01110001 00001101 1....... ........ */
                /* target/loongarch/insns.decode:1076 */
                return LISA_VBITCLR_D;
            case 0x4:
                /* 01110001 00001110 0....... ........ */
                /* target/loongarch/insns.decode:1077 */
                return LISA_VBITSET_B;
            case 0x5:
                /* 01110001 00001110 1....... ........ */
                /* target/loongarch/insns.decode:1078 */
                return LISA_VBITSET_H;
            case 0x6:
                /* 01110001 00001111 0....... ........ */
                /* target/loongarch/insns.decode:1079 */
                return LISA_VBITSET_W;
            case 0x7:
                /* 01110001 00001111 1....... ........ */
                /* target/loongarch/insns.decode:1080 */
                return LISA_VBITSET_D;
            }
            break;
        case 0x44:
            /* 01110001 000100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110001 00010000 0....... ........ */
                /* target/loongarch/insns.decode:1081 */
                return LISA_VBITREV_B;
            case 0x1:
                /* 01110001 00010000 1....... ........ */
                /* target/loongarch/insns.decode:1082 */
                return LISA_VBITREV_H;
            case 0x2:
                /* 01110001 00010001 0....... ........ */
                /* target/loongarch/insns.decode:1083 */
                return LISA_VBITREV_W;
            case 0x3:
                /* 01110001 00010001 1....... ........ */
                /* target/loongarch/insns.decode:1084 */
                return LISA_VBITREV_D;
            }
            break;
        case 0x45:
            /* 01110001 000101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110001 00010110 0....... ........ */
                /* target/loongarch/insns.decode:1085 */
                return LISA_VPACKEV_B;
            case 0x5:
                /* 01110001 00010110 1....... ........ */
                /* target/loongarch/insns.decode:1086 */
                return LISA_VPACKEV_H;
            case 0x6:
                /* 01110001 00010111 0....... ........ */
                /* target/loongarch/insns.decode:1087 */
                return LISA_VPACKEV_W;
            case 0x7:
                /* 01110001 00010111 1....... ........ */
                /* target/loongarch/insns.decode:1088 */
                return LISA_VPACKEV_D;
            }
            break;
        case 0x46:
            /* 01110001 000110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110001 00011000 0....... ........ */
                /* target/loongarch/insns.decode:1089 */
                return LISA_VPACKOD_B;
            case 0x1:
                /* 01110001 00011000 1....... ........ */
                /* target/loongarch/insns.decode:1090 */
                return LISA_VPACKOD_H;
            case 0x2:
                /* 01110001 00011001 0....... ........ */
                /* target/loongarch/insns.decode:1091 */
                return LISA_VPACKOD_W;
            case 0x3:
                /* 01110001 00011001 1....... ........ */
                /* target/loongarch/insns.decode:1092 */
                return LISA_VPACKOD_D;
            case 0x4:
                /* 01110001 00011010 0....... ........ */
                /* target/loongarch/insns.decode:1093 */
                return LISA_VILVL_B;
            case 0x5:
                /* 01110001 00011010 1....... ........ */
                /* target/loongarch/insns.decode:1094 */
                return LISA_VILVL_H;
            case 0x6:
                /* 01110001 00011011 0....... ........ */
                /* target/loongarch/insns.decode:1095 */
                return LISA_VILVL_W;
            case 0x7:
                /* 01110001 00011011 1....... ........ */
                /* target/loongarch/insns.decode:1096 */
                return LISA_VILVL_D;
            }
            break;
        case 0x47:
            /* 01110001 000111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110001 00011100 0....... ........ */
                /* target/loongarch/insns.decode:1097 */
                return LISA_VILVH_B;
            case 0x1:
                /* 01110001 00011100 1....... ........ */
                /* target/loongarch/insns.decode:1098 */
                return LISA_VILVH_H;
            case 0x2:
                /* 01110001 00011101 0....... ........ */
                /* target/loongarch/insns.decode:1099 */
                return LISA_VILVH_W;
            case 0x3:
                /* 01110001 00011101 1....... ........ */
                /* target/loongarch/insns.decode:1100 */
                return LISA_VILVH_D;
            case 0x4:
                /* 01110001 00011110 0....... ........ */
                /* target/loongarch/insns.decode:1101 */
                return LISA_VPICKEV_B;
            case 0x5:
                /* 01110001 00011110 1....... ........ */
                /* target/loongarch/insns.decode:1102 */
                return LISA_VPICKEV_H;
            case 0x6:
                /* 01110001 00011111 0....... ........ */
                /* target/loongarch/insns.decode:1103 */
                return LISA_VPICKEV_W;
            case 0x7:
                /* 01110001 00011111 1....... ........ */
                /* target/loongarch/insns.decode:1104 */
                return LISA_VPICKEV_D;
            }
            break;
        case 0x48:
            /* 01110001 001000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110001 00100000 0....... ........ */
                /* target/loongarch/insns.decode:1105 */
                return LISA_VPICKOD_B;
            case 0x1:
                /* 01110001 00100000 1....... ........ */
                /* target/loongarch/insns.decode:1106 */
                return LISA_VPICKOD_H;
            case 0x2:
                /* 01110001 00100001 0....... ........ */
                /* target/loongarch/insns.decode:1107 */
                return LISA_VPICKOD_W;
            case 0x3:
                /* 01110001 00100001 1....... ........ */
                /* target/loongarch/insns.decode:1108 */
                return LISA_VPICKOD_D;
            case 0x4:
                /* 01110001 00100010 0....... ........ */
                /* target/loongarch/insns.decode:1109 */
                return LISA_VREPLVE_B;
            case 0x5:
                /* 01110001 00100010 1....... ........ */
                /* target/loongarch/insns.decode:1110 */
                return LISA_VREPLVE_H;
            case 0x6:
                /* 01110001 00100011 0....... ........ */
                /* target/loongarch/insns.decode:1111 */
                return LISA_VREPLVE_W;
            case 0x7:
                /* 01110001 00100011 1....... ........ */
                /* target/loongarch/insns.decode:1112 */
                return LISA_VREPLVE_D;
            }
            break;
        case 0x49:
            /* 01110001 001001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110001 00100110 0....... ........ */
                /* target/loongarch/insns.decode:1113 */
                return LISA_VAND_V;
            case 0x5:
                /* 01110001 00100110 1....... ........ */
                /* target/loongarch/insns.decode:1114 */
                return LISA_VOR_V;
            case 0x6:
                /* 01110001 00100111 0....... ........ */
                /* target/loongarch/insns.decode:1115 */
                return LISA_VXOR_V;
            case 0x7:
                /* 01110001 00100111 1....... ........ */
                /* target/loongarch/insns.decode:1116 */
                return LISA_VNOR_V;
            }
            break;
        case 0x4a:
            /* 01110001 001010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110001 00101000 0....... ........ */
                /* target/loongarch/insns.decode:1117 */
                return LISA_VANDN_V;
            case 0x1:
                /* 01110001 00101000 1....... ........ */
                /* target/loongarch/insns.decode:1118 */
                return LISA_VORN_V;
            case 0x6:
                /* 01110001 00101011 0....... ........ */
                /* target/loongarch/insns.decode:1119 */
                return LISA_VFRSTP_B;
            case 0x7:
                /* 01110001 00101011 1....... ........ */
                /* target/loongarch/insns.decode:1120 */
                return LISA_VFRSTP_H;
            }
            break;
        case 0x4b:
            /* 01110001 001011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x2:
                /* 01110001 00101101 0....... ........ */
                /* target/loongarch/insns.decode:1121 */
                return LISA_VADD_Q;
            case 0x3:
                /* 01110001 00101101 1....... ........ */
                /* target/loongarch/insns.decode:1122 */
                return LISA_VSUB_Q;
            case 0x4:
                /* 01110001 00101110 0....... ........ */
                /* target/loongarch/insns.decode:1123 */
                return LISA_VSIGNCOV_B;
            case 0x5:
                /* 01110001 00101110 1....... ........ */
                /* target/loongarch/insns.decode:1124 */
                return LISA_VSIGNCOV_H;
            case 0x6:
                /* 01110001 00101111 0....... ........ */
                /* target/loongarch/insns.decode:1125 */
                return LISA_VSIGNCOV_W;
            case 0x7:
                /* 01110001 00101111 1....... ........ */
                /* target/loongarch/insns.decode:1126 */
                return LISA_VSIGNCOV_D;
            }
            break;
        case 0x4c:
            /* 01110001 001100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110001 00110000 1....... ........ */
                /* target/loongarch/insns.decode:1127 */
                return LISA_VFADD_S;
            case 0x2:
                /* 01110001 00110001 0....... ........ */
                /* target/loongarch/insns.decode:1128 */
                return LISA_VFADD_D;
            case 0x5:
                /* 01110001 00110010 1....... ........ */
                /* target/loongarch/insns.decode:1129 */
                return LISA_VFSUB_S;
            case 0x6:
                /* 01110001 00110011 0....... ........ */
                /* target/loongarch/insns.decode:1130 */
                return LISA_VFSUB_D;
            }
            break;
        case 0x4e:
            /* 01110001 001110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110001 00111000 1....... ........ */
                /* target/loongarch/insns.decode:1131 */
                return LISA_VFMUL_S;
            case 0x2:
                /* 01110001 00111001 0....... ........ */
                /* target/loongarch/insns.decode:1132 */
                return LISA_VFMUL_D;
            case 0x5:
                /* 01110001 00111010 1....... ........ */
                /* target/loongarch/insns.decode:1133 */
                return LISA_VFDIV_S;
            case 0x6:
                /* 01110001 00111011 0....... ........ */
                /* target/loongarch/insns.decode:1134 */
                return LISA_VFDIV_D;
            }
            break;
        case 0x4f:
            /* 01110001 001111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110001 00111100 1....... ........ */
                /* target/loongarch/insns.decode:1135 */
                return LISA_VFMAX_S;
            case 0x2:
                /* 01110001 00111101 0....... ........ */
                /* target/loongarch/insns.decode:1136 */
                return LISA_VFMAX_D;
            case 0x5:
                /* 01110001 00111110 1....... ........ */
                /* target/loongarch/insns.decode:1137 */
                return LISA_VFMIN_S;
            case 0x6:
                /* 01110001 00111111 0....... ........ */
                /* target/loongarch/insns.decode:1138 */
                return LISA_VFMIN_D;
            }
            break;
        case 0x50:
            /* 01110001 010000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110001 01000000 1....... ........ */
                /* target/loongarch/insns.decode:1139 */
                return LISA_VFMAXA_S;
            case 0x2:
                /* 01110001 01000001 0....... ........ */
                /* target/loongarch/insns.decode:1140 */
                return LISA_VFMAXA_D;
            case 0x5:
                /* 01110001 01000010 1....... ........ */
                /* target/loongarch/insns.decode:1141 */
                return LISA_VFMINA_S;
            case 0x6:
                /* 01110001 01000011 0....... ........ */
                /* target/loongarch/insns.decode:1142 */
                return LISA_VFMINA_D;
            }
            break;
        case 0x51:
            /* 01110001 010001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110001 01000100 1....... ........ */
                /* target/loongarch/insns.decode:1143 */
                return LISA_VFSCALEB_S;
            case 0x2:
                /* 01110001 01000101 0....... ........ */
                /* target/loongarch/insns.decode:1144 */
                return LISA_VFSCALEB_D;
            case 0x4:
                /* 01110001 01000110 0....... ........ */
                /* target/loongarch/insns.decode:1145 */
                return LISA_VFCVT_H_S;
            case 0x5:
                /* 01110001 01000110 1....... ........ */
                /* target/loongarch/insns.decode:1146 */
                return LISA_VFCVT_S_D;
            }
            break;
        case 0x52:
            /* 01110001 010010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110001 01001000 0....... ........ */
                /* target/loongarch/insns.decode:1147 */
                return LISA_VFFINT_S_L;
            case 0x3:
                /* 01110001 01001001 1....... ........ */
                /* target/loongarch/insns.decode:1148 */
                return LISA_VFTINT_W_D;
            case 0x4:
                /* 01110001 01001010 0....... ........ */
                /* target/loongarch/insns.decode:1149 */
                return LISA_VFTINTRM_W_D;
            case 0x5:
                /* 01110001 01001010 1....... ........ */
                /* target/loongarch/insns.decode:1150 */
                return LISA_VFTINTRP_W_D;
            case 0x6:
                /* 01110001 01001011 0....... ........ */
                /* target/loongarch/insns.decode:1151 */
                return LISA_VFTINTRZ_W_D;
            case 0x7:
                /* 01110001 01001011 1....... ........ */
                /* target/loongarch/insns.decode:1152 */
                return LISA_VFTINTRNE_W_D;
            }
            break;
        case 0x5e:
            /* 01110001 011110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x5:
                /* 01110001 01111010 1....... ........ */
                /* target/loongarch/insns.decode:1153 */
                return LISA_VSHUF_H;
            case 0x6:
                /* 01110001 01111011 0....... ........ */
                /* target/loongarch/insns.decode:1154 */
                return LISA_VSHUF_W;
            case 0x7:
                /* 01110001 01111011 1....... ........ */
                /* target/loongarch/insns.decode:1155 */
                return LISA_VSHUF_D;
            }
            break;
        case 0xa0:
            /* 01110010 100000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110010 10000000 0....... ........ */
                /* target/loongarch/insns.decode:1156 */
                return LISA_VSEQI_B;
            case 0x1:
                /* 01110010 10000000 1....... ........ */
                /* target/loongarch/insns.decode:1157 */
                return LISA_VSEQI_H;
            case 0x2:
                /* 01110010 10000001 0....... ........ */
                /* target/loongarch/insns.decode:1158 */
                return LISA_VSEQI_W;
            case 0x3:
                /* 01110010 10000001 1....... ........ */
                /* target/loongarch/insns.decode:1159 */
                return LISA_VSEQI_D;
            case 0x4:
                /* 01110010 10000010 0....... ........ */
                /* target/loongarch/insns.decode:1160 */
                return LISA_VSLEI_B;
            case 0x5:
                /* 01110010 10000010 1....... ........ */
                /* target/loongarch/insns.decode:1161 */
                return LISA_VSLEI_H;
            case 0x6:
                /* 01110010 10000011 0....... ........ */
                /* target/loongarch/insns.decode:1162 */
                return LISA_VSLEI_W;
            case 0x7:
                /* 01110010 10000011 1....... ........ */
                /* target/loongarch/insns.decode:1163 */
                return LISA_VSLEI_D;
            }
            break;
        case 0xa1:
            /* 01110010 100001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110010 10000100 0....... ........ */
                /* target/loongarch/insns.decode:1164 */
                return LISA_VSLEI_BU;
            case 0x1:
                /* 01110010 10000100 1....... ........ */
                /* target/loongarch/insns.decode:1165 */
                return LISA_VSLEI_HU;
            case 0x2:
                /* 01110010 10000101 0....... ........ */
                /* target/loongarch/insns.decode:1166 */
                return LISA_VSLEI_WU;
            case 0x3:
                /* 01110010 10000101 1....... ........ */
                /* target/loongarch/insns.decode:1167 */
                return LISA_VSLEI_DU;
            case 0x4:
                /* 01110010 10000110 0....... ........ */
                /* target/loongarch/insns.decode:1168 */
                return LISA_VSLTI_B;
            case 0x5:
                /* 01110010 10000110 1....... ........ */
                /* target/loongarch/insns.decode:1169 */
                return LISA_VSLTI_H;
            case 0x6:
                /* 01110010 10000111 0....... ........ */
                /* target/loongarch/insns.decode:1170 */
                return LISA_VSLTI_W;
            case 0x7:
                /* 01110010 10000111 1....... ........ */
                /* target/loongarch/insns.decode:1171 */
                return LISA_VSLTI_D;
            }
            break;
        case 0xa2:
            /* 01110010 100010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110010 10001000 0....... ........ */
                /* target/loongarch/insns.decode:1172 */
                return LISA_VSLTI_BU;
            case 0x1:
                /* 01110010 10001000 1....... ........ */
                /* target/loongarch/insns.decode:1173 */
                return LISA_VSLTI_HU;
            case 0x2:
                /* 01110010 10001001 0....... ........ */
                /* target/loongarch/insns.decode:1174 */
                return LISA_VSLTI_WU;
            case 0x3:
                /* 01110010 10001001 1....... ........ */
                /* target/loongarch/insns.decode:1175 */
                return LISA_VSLTI_DU;
            case 0x4:
                /* 01110010 10001010 0....... ........ */
                /* target/loongarch/insns.decode:1176 */
                return LISA_VADDI_BU;
            case 0x5:
                /* 01110010 10001010 1....... ........ */
                /* target/loongarch/insns.decode:1177 */
                return LISA_VADDI_HU;
            case 0x6:
                /* 01110010 10001011 0....... ........ */
                /* target/loongarch/insns.decode:1178 */
                return LISA_VADDI_WU;
            case 0x7:
                /* 01110010 10001011 1....... ........ */
                /* target/loongarch/insns.decode:1179 */
                return LISA_VADDI_DU;
            }
            break;
        case 0xa3:
            /* 01110010 100011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110010 10001100 0....... ........ */
                /* target/loongarch/insns.decode:1180 */
                return LISA_VSUBI_BU;
            case 0x1:
                /* 01110010 10001100 1....... ........ */
                /* target/loongarch/insns.decode:1181 */
                return LISA_VSUBI_HU;
            case 0x2:
                /* 01110010 10001101 0....... ........ */
                /* target/loongarch/insns.decode:1182 */
                return LISA_VSUBI_WU;
            case 0x3:
                /* 01110010 10001101 1....... ........ */
                /* target/loongarch/insns.decode:1183 */
                return LISA_VSUBI_DU;
            case 0x4:
                /* 01110010 10001110 0....... ........ */
                /* target/loongarch/insns.decode:1184 */
                return LISA_VBSLL_V;
            case 0x5:
                /* 01110010 10001110 1....... ........ */
                /* target/loongarch/insns.decode:1185 */
                return LISA_VBSRL_V;
            }
            break;
        case 0xa4:
            /* 01110010 100100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110010 10010000 0....... ........ */
                /* target/loongarch/insns.decode:1186 */
                return LISA_VMAXI_B;
            case 0x1:
                /* 01110010 10010000 1....... ........ */
                /* target/loongarch/insns.decode:1187 */
                return LISA_VMAXI_H;
            case 0x2:
                /* 01110010 10010001 0....... ........ */
                /* target/loongarch/insns.decode:1188 */
                return LISA_VMAXI_W;
            case 0x3:
                /* 01110010 10010001 1....... ........ */
                /* target/loongarch/insns.decode:1189 */
                return LISA_VMAXI_D;
            case 0x4:
                /* 01110010 10010010 0....... ........ */
                /* target/loongarch/insns.decode:1190 */
                return LISA_VMINI_B;
            case 0x5:
                /* 01110010 10010010 1....... ........ */
                /* target/loongarch/insns.decode:1191 */
                return LISA_VMINI_H;
            case 0x6:
                /* 01110010 10010011 0....... ........ */
                /* target/loongarch/insns.decode:1192 */
                return LISA_VMINI_W;
            case 0x7:
                /* 01110010 10010011 1....... ........ */
                /* target/loongarch/insns.decode:1193 */
                return LISA_VMINI_D;
            }
            break;
        case 0xa5:
            /* 01110010 100101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110010 10010100 0....... ........ */
                /* target/loongarch/insns.decode:1194 */
                return LISA_VMAXI_BU;
            case 0x1:
                /* 01110010 10010100 1....... ........ */
                /* target/loongarch/insns.decode:1195 */
                return LISA_VMAXI_HU;
            case 0x2:
                /* 01110010 10010101 0....... ........ */
                /* target/loongarch/insns.decode:1196 */
                return LISA_VMAXI_WU;
            case 0x3:
                /* 01110010 10010101 1....... ........ */
                /* target/loongarch/insns.decode:1197 */
                return LISA_VMAXI_DU;
            case 0x4:
                /* 01110010 10010110 0....... ........ */
                /* target/loongarch/insns.decode:1198 */
                return LISA_VMINI_BU;
            case 0x5:
                /* 01110010 10010110 1....... ........ */
                /* target/loongarch/insns.decode:1199 */
                return LISA_VMINI_HU;
            case 0x6:
                /* 01110010 10010111 0....... ........ */
                /* target/loongarch/insns.decode:1200 */
                return LISA_VMINI_WU;
            case 0x7:
                /* 01110010 10010111 1....... ........ */
                /* target/loongarch/insns.decode:1201 */
                return LISA_VMINI_DU;
            }
            break;
        case 0xa6:
            /* 01110010 100110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110010 10011010 0....... ........ */
                /* target/loongarch/insns.decode:1202 */
                return LISA_VFRSTPI_B;
            case 0x5:
                /* 01110010 10011010 1....... ........ */
                /* target/loongarch/insns.decode:1203 */
                return LISA_VFRSTPI_H;
            case 0x6:
                /* 01110010 10011011 0....... ........ */
                /* target/loongarch/insns.decode:1204 */
                return LISA_VCLRSTRI_V;
            case 0x7:
                /* 01110010 10011011 1....... ........ */
                /* target/loongarch/insns.decode:1205 */
                return LISA_VMEPATMSK_V;
            }
            break;
        case 0xa7:
            /* 01110010 100111.. ........ ........ */
            switch ((insn >> 10) & 0xff) {
            case 0x0:
                /* 01110010 10011100 000000.. ........ */
                /* target/loongarch/insns.decode:1206 */
                return LISA_VCLO_B;
            case 0x1:
                /* 01110010 10011100 000001.. ........ */
                /* target/loongarch/insns.decode:1207 */
                return LISA_VCLO_H;
            case 0x2:
                /* 01110010 10011100 000010.. ........ */
                /* target/loongarch/insns.decode:1208 */
                return LISA_VCLO_W;
            case 0x3:
                /* 01110010 10011100 000011.. ........ */
                /* target/loongarch/insns.decode:1209 */
                return LISA_VCLO_D;
            case 0x4:
                /* 01110010 10011100 000100.. ........ */
                /* target/loongarch/insns.decode:1210 */
                return LISA_VCLZ_B;
            case 0x5:
                /* 01110010 10011100 000101.. ........ */
                /* target/loongarch/insns.decode:1211 */
                return LISA_VCLZ_H;
            case 0x6:
                /* 01110010 10011100 000110.. ........ */
                /* target/loongarch/insns.decode:1212 */
                return LISA_VCLZ_W;
            case 0x7:
                /* 01110010 10011100 000111.. ........ */
                /* target/loongarch/insns.decode:1213 */
                return LISA_VCLZ_D;
            case 0x8:
                /* 01110010 10011100 001000.. ........ */
                /* target/loongarch/insns.decode:1214 */
                return LISA_VPCNT_B;
            case 0x9:
                /* 01110010 10011100 001001.. ........ */
                /* target/loongarch/insns.decode:1215 */
                return LISA_VPCNT_H;
            case 0xa:
                /* 01110010 10011100 001010.. ........ */
                /* target/loongarch/insns.decode:1216 */
                return LISA_VPCNT_W;
            case 0xb:
                /* 01110010 10011100 001011.. ........ */
                /* target/loongarch/insns.decode:1217 */
                return LISA_VPCNT_D;
            case 0xc:
                /* 01110010 10011100 001100.. ........ */
                /* target/loongarch/insns.decode:1218 */
                return LISA_VNEG_B;
            case 0xd:
                /* 01110010 10011100 001101.. ........ */
                /* target/loongarch/insns.decode:1219 */
                return LISA_VNEG_H;
            case 0xe:
                /* 01110010 10011100 001110.. ........ */
                /* target/loongarch/insns.decode:1220 */
                return LISA_VNEG_W;
            case 0xf:
                /* 01110010 10011100 001111.. ........ */
                /* target/loongarch/insns.decode:1221 */
                return LISA_VNEG_D;
            case 0x10:
                /* 01110010 10011100 010000.. ........ */
                /* target/loongarch/insns.decode:1222 */
                return LISA_VMSKLTZ_B;
            case 0x11:
                /* 01110010 10011100 010001.. ........ */
                /* target/loongarch/insns.decode:1223 */
                return LISA_VMSKLTZ_H;
            case 0x12:
                /* 01110010 10011100 010010.. ........ */
                /* target/loongarch/insns.decode:1224 */
                return LISA_VMSKLTZ_W;
            case 0x13:
                /* 01110010 10011100 010011.. ........ */
                /* target/loongarch/insns.decode:1225 */
                return LISA_VMSKLTZ_D;
            case 0x14:
                /* 01110010 10011100 010100.. ........ */
                /* target/loongarch/insns.decode:1226 */
                return LISA_VMSKGEZ_B;
            case 0x18:
                /* 01110010 10011100 011000.. ........ */
                /* target/loongarch/insns.decode:1227 */
                return LISA_VMSKNZ_B;
            case 0x1c:
                /* 01110010 10011100 011100.. ........ */
                /* target/loongarch/insns.decode:1228 */
                return LISA_VMSKCOPY_B;
            case 0x20:
                /* 01110010 10011100 100000.. ........ */
                /* target/loongarch/insns.decode:1229 */
                return LISA_VMSKFILL_B;
            case 0x24:
                /* 01110010 10011100 100100.. ........ */
                /* target/loongarch/insns.decode:1230 */
                return LISA_VFRSTM_B;
            case 0x25:
                /* 01110010 10011100 100101.. ........ */
                /* target/loongarch/insns.decode:1231 */
                return LISA_VFRSTM_H;
            case 0x26:
                /* 01110010 10011100 100110.. ........ */
                switch ((insn >> 3) & 0x3) {
                case 0x0:
                    /* 01110010 10011100 100110.. ...00... */
                    /* target/loongarch/insns.decode:1232 */
                    return LISA_VSETEQZ_V;
                }
                break;
            case 0x27:
                /* 01110010 10011100 100111.. ........ */
                switch ((insn >> 3) & 0x3) {
                case 0x0:
                    /* 01110010 10011100 100111.. ...00... */
                    /* target/loongarch/insns.decode:1233 */
                    return LISA_VSETNEZ_V;
                }
                break;
            case 0x28:
                /* 01110010 10011100 101000.. ........ */
                switch ((insn >> 3) & 0x3) {
                case 0x0:
                    /* 01110010 10011100 101000.. ...00... */
                    /* target/loongarch/insns.decode:1234 */
                    return LISA_VSETANYEQZ_B;
                }
                break;
            case 0x29:
                /* 01110010 10011100 101001.. ........ */
                switch ((insn >> 3) & 0x3) {
                case 0x0:
                    /* 01110010 10011100 101001.. ...00... */
                    /* target/loongarch/insns.decode:1235 */
                    return LISA_VSETANYEQZ_H;
                }
                break;
            case 0x2a:
                /* 01110010 10011100 101010.. ........ */
                switch ((insn >> 3) & 0x3) {
                case 0x0:
                    /* 01110010 10011100 101010.. ...00... */
                    /* target/loongarch/insns.decode:1236 */
                    return LISA_VSETANYEQZ_W;
                }
                break;
            case 0x2b:
                /* 01110010 10011100 101011.. ........ */
                switch ((insn >> 3) & 0x3) {
                case 0x0:
                    /* 01110010 10011100 101011.. ...00... */
                    /* target/loongarch/insns.decode:1237 */
                    return LISA_VSETANYEQZ_D;
                }
                break;
            case 0x2c:
                /* 01110010 10011100 101100.. ........ */
                switch ((insn >> 3) & 0x3) {
                case 0x0:
                    /* 01110010 10011100 101100.. ...00... */
                    /* target/loongarch/insns.decode:1238 */
                    return LISA_VSETALLNEZ_B;
                }
                break;
            case 0x2d:
                /* 01110010 10011100 101101.. ........ */
                switch ((insn >> 3) & 0x3) {
                case 0x0:
                    /* 01110010 10011100 101101.. ...00... */
                    /* target/loongarch/insns.decode:1239 */
                    return LISA_VSETALLNEZ_H;
                }
                break;
            case 0x2e:
                /* 01110010 10011100 101110.. ........ */
                switch ((insn >> 3) & 0x3) {
                case 0x0:
                    /* 01110010 10011100 101110.. ...00... */
                    /* target/loongarch/insns.decode:1240 */
                    return LISA_VSETALLNEZ_W;
                }
                break;
            case 0x2f:
                /* 01110010 10011100 101111.. ........ */
                switch ((insn >> 3) & 0x3) {
                case 0x0:
                    /* 01110010 10011100 101111.. ...00... */
                    /* target/loongarch/insns.decode:1241 */
                    return LISA_VSETALLNEZ_D;
                }
                break;
            case 0x31:
                /* 01110010 10011100 110001.. ........ */
                /* target/loongarch/insns.decode:1242 */
                return LISA_VFLOGB_S;
            case 0x32:
                /* 01110010 10011100 110010.. ........ */
                /* target/loongarch/insns.decode:1243 */
                return LISA_VFLOGB_D;
            case 0x35:
                /* 01110010 10011100 110101.. ........ */
                /* target/loongarch/insns.decode:1244 */
                return LISA_VFCLASS_S;
            case 0x36:
                /* 01110010 10011100 110110.. ........ */
                /* target/loongarch/insns.decode:1245 */
                return LISA_VFCLASS_D;
            case 0x39:
                /* 01110010 10011100 111001.. ........ */
                /* target/loongarch/insns.decode:1246 */
                return LISA_VFSQRT_S;
            case 0x3a:
                /* 01110010 10011100 111010.. ........ */
                /* target/loongarch/insns.decode:1247 */
                return LISA_VFSQRT_D;
            case 0x3d:
                /* 01110010 10011100 111101.. ........ */
                /* target/loongarch/insns.decode:1248 */
                return LISA_VFRECIP_S;
            case 0x3e:
                /* 01110010 10011100 111110.. ........ */
                /* target/loongarch/insns.decode:1249 */
                return LISA_VFRECIP_D;
            case 0x41:
                /* 01110010 10011101 000001.. ........ */
                /* target/loongarch/insns.decode:1250 */
                return LISA_VFRSQRT_S;
            case 0x42:
                /* 01110010 10011101 000010.. ........ */
                /* target/loongarch/insns.decode:1251 */
                return LISA_VFRSQRT_D;
            case 0x4d:
                /* 01110010 10011101 001101.. ........ */
                /* target/loongarch/insns.decode:1252 */
                return LISA_VFRINT_S;
            case 0x4e:
                /* 01110010 10011101 001110.. ........ */
                /* target/loongarch/insns.decode:1253 */
                return LISA_VFRINT_D;
            case 0x51:
                /* 01110010 10011101 010001.. ........ */
                /* target/loongarch/insns.decode:1254 */
                return LISA_VFRINTRM_S;
            case 0x52:
                /* 01110010 10011101 010010.. ........ */
                /* target/loongarch/insns.decode:1255 */
                return LISA_VFRINTRM_D;
            case 0x55:
                /* 01110010 10011101 010101.. ........ */
                /* target/loongarch/insns.decode:1256 */
                return LISA_VFRINTRP_S;
            case 0x56:
                /* 01110010 10011101 010110.. ........ */
                /* target/loongarch/insns.decode:1257 */
                return LISA_VFRINTRP_D;
            case 0x59:
                /* 01110010 10011101 011001.. ........ */
                /* target/loongarch/insns.decode:1258 */
                return LISA_VFRINTRZ_S;
            case 0x5a:
                /* 01110010 10011101 011010.. ........ */
                /* target/loongarch/insns.decode:1259 */
                return LISA_VFRINTRZ_D;
            case 0x5d:
                /* 01110010 10011101 011101.. ........ */
                /* target/loongarch/insns.decode:1260 */
                return LISA_VFRINTRNE_S;
            case 0x5e:
                /* 01110010 10011101 011110.. ........ */
                /* target/loongarch/insns.decode:1261 */
                return LISA_VFRINTRNE_D;
            case 0x61:
                /* 01110010 10011101 100001.. ........ */
                /* target/loongarch/insns.decode:1262 */
                return LISA_VEXTL_W_B;
            case 0x62:
                /* 01110010 10011101 100010.. ........ */
                /* target/loongarch/insns.decode:1263 */
                return LISA_VEXTL_D_B;
            case 0x65:
                /* 01110010 10011101 100101.. ........ */
                /* target/loongarch/insns.decode:1264 */
                return LISA_VEXTL_D_H;
            case 0x6b:
                /* 01110010 10011101 101011.. ........ */
                /* target/loongarch/insns.decode:1265 */
                return LISA_VEXTL_W_BU;
            case 0x6c:
                /* 01110010 10011101 101100.. ........ */
                /* target/loongarch/insns.decode:1266 */
                return LISA_VEXTL_D_BU;
            case 0x6f:
                /* 01110010 10011101 101111.. ........ */
                /* target/loongarch/insns.decode:1267 */
                return LISA_VEXTL_D_HU;
            case 0x74:
                /* 01110010 10011101 110100.. ........ */
                /* target/loongarch/insns.decode:1268 */
                return LISA_VHADD8_D_BU;
            case 0x75:
                /* 01110010 10011101 110101.. ........ */
                /* target/loongarch/insns.decode:1269 */
                return LISA_VHMINPOS_W_HU;
            case 0x76:
                /* 01110010 10011101 110110.. ........ */
                /* target/loongarch/insns.decode:1270 */
                return LISA_VHMINPOS_D_HU;
            case 0x77:
                /* 01110010 10011101 110111.. ........ */
                /* target/loongarch/insns.decode:1271 */
                return LISA_VHMINPOS_Q_HU;
            case 0x78:
                /* 01110010 10011101 111000.. ........ */
                /* target/loongarch/insns.decode:1272 */
                return LISA_VCLRTAIL_B;
            case 0x79:
                /* 01110010 10011101 111001.. ........ */
                /* target/loongarch/insns.decode:1273 */
                return LISA_VCLRTAIL_H;
            case 0x7a:
                /* 01110010 10011101 111010.. ........ */
                /* target/loongarch/insns.decode:1274 */
                return LISA_VFCVTL_S_H;
            case 0x7b:
                /* 01110010 10011101 111011.. ........ */
                /* target/loongarch/insns.decode:1275 */
                return LISA_VFCVTH_S_H;
            case 0x7c:
                /* 01110010 10011101 111100.. ........ */
                /* target/loongarch/insns.decode:1276 */
                return LISA_VFCVTL_D_S;
            case 0x7d:
                /* 01110010 10011101 111101.. ........ */
                /* target/loongarch/insns.decode:1277 */
                return LISA_VFCVTH_D_S;
            case 0x80:
                /* 01110010 10011110 000000.. ........ */
                /* target/loongarch/insns.decode:1278 */
                return LISA_VFFINT_S_W;
            case 0x81:
                /* 01110010 10011110 000001.. ........ */
                /* target/loongarch/insns.decode:1279 */
                return LISA_VFFINT_S_WU;
            case 0x82:
                /* 01110010 10011110 000010.. ........ */
                /* target/loongarch/insns.decode:1280 */
                return LISA_VFFINT_D_L;
            case 0x83:
                /* 01110010 10011110 000011.. ........ */
                /* target/loongarch/insns.decode:1281 */
                return LISA_VFFINT_D_LU;
            case 0x84:
                /* 01110010 10011110 000100.. ........ */
                /* target/loongarch/insns.decode:1282 */
                return LISA_VFFINTL_D_W;
            case 0x85:
                /* 01110010 10011110 000101.. ........ */
                /* target/loongarch/insns.decode:1283 */
                return LISA_VFFINTH_D_W;
            case 0x8c:
                /* 01110010 10011110 001100.. ........ */
                /* target/loongarch/insns.decode:1284 */
                return LISA_VFTINT_W_S;
            case 0x8d:
                /* 01110010 10011110 001101.. ........ */
                /* target/loongarch/insns.decode:1285 */
                return LISA_VFTINT_L_D;
            case 0x8e:
                /* 01110010 10011110 001110.. ........ */
                /* target/loongarch/insns.decode:1286 */
                return LISA_VFTINTRM_W_S;
            case 0x8f:
                /* 01110010 10011110 001111.. ........ */
                /* target/loongarch/insns.decode:1287 */
                return LISA_VFTINTRM_L_D;
            case 0x90:
                /* 01110010 10011110 010000.. ........ */
                /* target/loongarch/insns.decode:1288 */
                return LISA_VFTINTRP_W_S;
            case 0x91:
                /* 01110010 10011110 010001.. ........ */
                /* target/loongarch/insns.decode:1289 */
                return LISA_VFTINTRP_L_D;
            case 0x92:
                /* 01110010 10011110 010010.. ........ */
                /* target/loongarch/insns.decode:1290 */
                return LISA_VFTINTRZ_W_S;
            case 0x93:
                /* 01110010 10011110 010011.. ........ */
                /* target/loongarch/insns.decode:1291 */
                return LISA_VFTINTRZ_L_D;
            case 0x94:
                /* 01110010 10011110 010100.. ........ */
                /* target/loongarch/insns.decode:1292 */
                return LISA_VFTINTRNE_W_S;
            case 0x95:
                /* 01110010 10011110 010101.. ........ */
                /* target/loongarch/insns.decode:1293 */
                return LISA_VFTINTRNE_L_D;
            case 0x96:
                /* 01110010 10011110 010110.. ........ */
                /* target/loongarch/insns.decode:1294 */
                return LISA_VFTINT_WU_S;
            case 0x97:
                /* 01110010 10011110 010111.. ........ */
                /* target/loongarch/insns.decode:1295 */
                return LISA_VFTINT_LU_D;
            case 0x9c:
                /* 01110010 10011110 011100.. ........ */
                /* target/loongarch/insns.decode:1296 */
                return LISA_VFTINTRZ_WU_S;
            case 0x9d:
                /* 01110010 10011110 011101.. ........ */
                /* target/loongarch/insns.decode:1297 */
                return LISA_VFTINTRZ_LU_D;
            case 0xa0:
                /* 01110010 10011110 100000.. ........ */
                /* target/loongarch/insns.decode:1298 */
                return LISA_VFTINTL_L_S;
            case 0xa1:
                /* 01110010 10011110 100001.. ........ */
                /* target/loongarch/insns.decode:1299 */
                return LISA_VFTINTH_L_S;
            case 0xa2:
                /* 01110010 10011110 100010.. ........ */
                /* target/loongarch/insns.decode:1300 */
                return LISA_VFTINTRML_L_S;
            case 0xa3:
                /* 01110010 10011110 100011.. ........ */
                /* target/loongarch/insns.decode:1301 */
                return LISA_VFTINTRMH_L_S;
            case 0xa4:
                /* 01110010 10011110 100100.. ........ */
                /* target/loongarch/insns.decode:1302 */
                return LISA_VFTINTRPL_L_S;
            case 0xa5:
                /* 01110010 10011110 100101.. ........ */
                /* target/loongarch/insns.decode:1303 */
                return LISA_VFTINTRPH_L_S;
            case 0xa6:
                /* 01110010 10011110 100110.. ........ */
                /* target/loongarch/insns.decode:1304 */
                return LISA_VFTINTRZL_L_S;
            case 0xa7:
                /* 01110010 10011110 100111.. ........ */
                /* target/loongarch/insns.decode:1305 */
                return LISA_VFTINTRZH_L_S;
            case 0xa8:
                /* 01110010 10011110 101000.. ........ */
                /* target/loongarch/insns.decode:1306 */
                return LISA_VFTINTRNEL_L_S;
            case 0xa9:
                /* 01110010 10011110 101001.. ........ */
                /* target/loongarch/insns.decode:1307 */
                return LISA_VFTINTRNEH_L_S;
            case 0xb8:
                /* 01110010 10011110 111000.. ........ */
                /* target/loongarch/insns.decode:1308 */
                return LISA_VEXTH_H_B;
            case 0xb9:
                /* 01110010 10011110 111001.. ........ */
                /* target/loongarch/insns.decode:1309 */
                return LISA_VEXTH_W_H;
            case 0xba:
                /* 01110010 10011110 111010.. ........ */
                /* target/loongarch/insns.decode:1310 */
                return LISA_VEXTH_D_W;
            case 0xbb:
                /* 01110010 10011110 111011.. ........ */
                /* target/loongarch/insns.decode:1311 */
                return LISA_VEXTH_Q_D;
            case 0xbc:
                /* 01110010 10011110 111100.. ........ */
                /* target/loongarch/insns.decode:1312 */
                return LISA_VEXTH_HU_BU;
            case 0xbd:
                /* 01110010 10011110 111101.. ........ */
                /* target/loongarch/insns.decode:1313 */
                return LISA_VEXTH_WU_HU;
            case 0xbe:
                /* 01110010 10011110 111110.. ........ */
                /* target/loongarch/insns.decode:1314 */
                return LISA_VEXTH_DU_WU;
            case 0xbf:
                /* 01110010 10011110 111111.. ........ */
                /* target/loongarch/insns.decode:1315 */
                return LISA_VEXTH_QU_DU;
            case 0xc0:
                /* 01110010 10011111 000000.. ........ */
                /* target/loongarch/insns.decode:1316 */
                return LISA_VREPLGR2VR_B;
            case 0xc1:
                /* 01110010 10011111 000001.. ........ */
                /* target/loongarch/insns.decode:1317 */
                return LISA_VREPLGR2VR_H;
            case 0xc2:
                /* 01110010 10011111 000010.. ........ */
                /* target/loongarch/insns.decode:1318 */
                return LISA_VREPLGR2VR_W;
            case 0xc3:
                /* 01110010 10011111 000011.. ........ */
                /* target/loongarch/insns.decode:1319 */
                return LISA_VREPLGR2VR_D;
            }
            break;
        case 0xa8:
            /* 01110010 101000.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110010 10100000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110010 10100000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110010 10100000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110010 10100000 001..... ........ */
                            /* target/loongarch/insns.decode:1320 */
                            return LISA_VROTRI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110010 10100000 01...... ........ */
                        /* target/loongarch/insns.decode:1321 */
                        return LISA_VROTRI_H;
                    }
                    break;
                case 0x1:
                    /* 01110010 10100000 1....... ........ */
                    /* target/loongarch/insns.decode:1322 */
                    return LISA_VROTRI_W;
                }
                break;
            case 0x1:
                /* 01110010 10100001 ........ ........ */
                /* target/loongarch/insns.decode:1323 */
                return LISA_VROTRI_D;
            }
            break;
        case 0xa9:
            /* 01110010 101001.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110010 10100100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110010 10100100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110010 10100100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110010 10100100 001..... ........ */
                            /* target/loongarch/insns.decode:1324 */
                            return LISA_VSRLRI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110010 10100100 01...... ........ */
                        /* target/loongarch/insns.decode:1325 */
                        return LISA_VSRLRI_H;
                    }
                    break;
                case 0x1:
                    /* 01110010 10100100 1....... ........ */
                    /* target/loongarch/insns.decode:1326 */
                    return LISA_VSRLRI_W;
                }
                break;
            case 0x1:
                /* 01110010 10100101 ........ ........ */
                /* target/loongarch/insns.decode:1327 */
                return LISA_VSRLRI_D;
            }
            break;
        case 0xaa:
            /* 01110010 101010.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110010 10101000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110010 10101000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110010 10101000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110010 10101000 001..... ........ */
                            /* target/loongarch/insns.decode:1328 */
                            return LISA_VSRARI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110010 10101000 01...... ........ */
                        /* target/loongarch/insns.decode:1329 */
                        return LISA_VSRARI_H;
                    }
                    break;
                case 0x1:
                    /* 01110010 10101000 1....... ........ */
                    /* target/loongarch/insns.decode:1330 */
                    return LISA_VSRARI_W;
                }
                break;
            case 0x1:
                /* 01110010 10101001 ........ ........ */
                /* target/loongarch/insns.decode:1331 */
                return LISA_VSRARI_D;
            }
            break;
        case 0xba:
            /* 01110010 111010.. ........ ........ */
            switch ((insn >> 14) & 0xf) {
            case 0xe:
                /* 01110010 11101011 10...... ........ */
                /* target/loongarch/insns.decode:1332 */
                return LISA_VINSGR2VR_B;
            case 0xf:
                /* 01110010 11101011 11...... ........ */
                switch ((insn >> 13) & 0x1) {
                case 0x0:
                    /* 01110010 11101011 110..... ........ */
                    /* target/loongarch/insns.decode:1333 */
                    return LISA_VINSGR2VR_H;
                case 0x1:
                    /* 01110010 11101011 111..... ........ */
                    switch ((insn >> 12) & 0x1) {
                    case 0x0:
                        /* 01110010 11101011 1110.... ........ */
                        /* target/loongarch/insns.decode:1334 */
                        return LISA_VINSGR2VR_W;
                    case 0x1:
                        /* 01110010 11101011 1111.... ........ */
                        switch ((insn >> 11) & 0x1) {
                        case 0x0:
                            /* 01110010 11101011 11110... ........ */
                            /* target/loongarch/insns.decode:1335 */
                            return LISA_VINSGR2VR_D;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        case 0xbb:
            /* 01110010 111011.. ........ ........ */
            switch ((insn >> 14) & 0xf) {
            case 0xe:
                /* 01110010 11101111 10...... ........ */
                /* target/loongarch/insns.decode:1336 */
                return LISA_VPICKVE2GR_B;
            case 0xf:
                /* 01110010 11101111 11...... ........ */
                switch ((insn >> 13) & 0x1) {
                case 0x0:
                    /* 01110010 11101111 110..... ........ */
                    /* target/loongarch/insns.decode:1337 */
                    return LISA_VPICKVE2GR_H;
                case 0x1:
                    /* 01110010 11101111 111..... ........ */
                    switch ((insn >> 12) & 0x1) {
                    case 0x0:
                        /* 01110010 11101111 1110.... ........ */
                        /* target/loongarch/insns.decode:1338 */
                        return LISA_VPICKVE2GR_W;
                    case 0x1:
                        /* 01110010 11101111 1111.... ........ */
                        switch ((insn >> 11) & 0x1) {
                        case 0x0:
                            /* 01110010 11101111 11110... ........ */
                            /* target/loongarch/insns.decode:1339 */
                            return LISA_VPICKVE2GR_D;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        case 0xbc:
            /* 01110010 111100.. ........ ........ */
            switch ((insn >> 14) & 0xf) {
            case 0xe:
                /* 01110010 11110011 10...... ........ */
                /* target/loongarch/insns.decode:1340 */
                return LISA_VPICKVE2GR_BU;
            case 0xf:
                /* 01110010 11110011 11...... ........ */
                switch ((insn >> 13) & 0x1) {
                case 0x0:
                    /* 01110010 11110011 110..... ........ */
                    /* target/loongarch/insns.decode:1341 */
                    return LISA_VPICKVE2GR_HU;
                case 0x1:
                    /* 01110010 11110011 111..... ........ */
                    switch ((insn >> 12) & 0x1) {
                    case 0x0:
                        /* 01110010 11110011 1110.... ........ */
                        /* target/loongarch/insns.decode:1342 */
                        return LISA_VPICKVE2GR_WU;
                    case 0x1:
                        /* 01110010 11110011 1111.... ........ */
                        switch ((insn >> 11) & 0x1) {
                        case 0x0:
                            /* 01110010 11110011 11110... ........ */
                            /* target/loongarch/insns.decode:1343 */
                            return LISA_VPICKVE2GR_DU;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        case 0xbd:
            /* 01110010 111101.. ........ ........ */
            switch ((insn >> 14) & 0xf) {
            case 0xe:
                /* 01110010 11110111 10...... ........ */
                /* target/loongarch/insns.decode:1344 */
                return LISA_VREPLVEI_B;
            case 0xf:
                /* 01110010 11110111 11...... ........ */
                switch ((insn >> 13) & 0x1) {
                case 0x0:
                    /* 01110010 11110111 110..... ........ */
                    /* target/loongarch/insns.decode:1345 */
                    return LISA_VREPLVEI_H;
                case 0x1:
                    /* 01110010 11110111 111..... ........ */
                    switch ((insn >> 12) & 0x1) {
                    case 0x0:
                        /* 01110010 11110111 1110.... ........ */
                        /* target/loongarch/insns.decode:1346 */
                        return LISA_VREPLVEI_W;
                    case 0x1:
                        /* 01110010 11110111 1111.... ........ */
                        switch ((insn >> 11) & 0x1) {
                        case 0x0:
                            /* 01110010 11110111 11110... ........ */
                            /* target/loongarch/insns.decode:1347 */
                            return LISA_VREPLVEI_D;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        case 0xbe:
            /* 01110010 111110.. ........ ........ */
            switch ((insn >> 14) & 0xf) {
            case 0xe:
                /* 01110010 11111011 10...... ........ */
                /* target/loongarch/insns.decode:1348 */
                return LISA_VEXTRCOLI_B;
            case 0xf:
                /* 01110010 11111011 11...... ........ */
                switch ((insn >> 13) & 0x1) {
                case 0x0:
                    /* 01110010 11111011 110..... ........ */
                    /* target/loongarch/insns.decode:1349 */
                    return LISA_VEXTRCOLI_H;
                case 0x1:
                    /* 01110010 11111011 111..... ........ */
                    switch ((insn >> 12) & 0x1) {
                    case 0x0:
                        /* 01110010 11111011 1110.... ........ */
                        /* target/loongarch/insns.decode:1350 */
                        return LISA_VEXTRCOLI_W;
                    case 0x1:
                        /* 01110010 11111011 1111.... ........ */
                        switch ((insn >> 11) & 0x1) {
                        case 0x0:
                            /* 01110010 11111011 11110... ........ */
                            /* target/loongarch/insns.decode:1351 */
                            return LISA_VEXTRCOLI_D;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        case 0xc2:
            /* 01110011 000010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110011 00001000 0....... ........ */
                switch ((insn >> 14) & 0x1) {
                case 0x0:
                    /* 01110011 00001000 00...... ........ */
                    switch ((insn >> 13) & 0x1) {
                    case 0x1:
                        /* 01110011 00001000 001..... ........ */
                        /* target/loongarch/insns.decode:1352 */
                        return LISA_VSLLWIL_H_B;
                    }
                    break;
                case 0x1:
                    /* 01110011 00001000 01...... ........ */
                    /* target/loongarch/insns.decode:1353 */
                    return LISA_VSLLWIL_W_H;
                }
                break;
            case 0x1:
                /* 01110011 00001000 1....... ........ */
                /* target/loongarch/insns.decode:1354 */
                return LISA_VSLLWIL_D_W;
            case 0x2:
                /* 01110011 00001001 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x0:
                    /* 01110011 00001001 000000.. ........ */
                    /* target/loongarch/insns.decode:1355 */
                    return LISA_VEXTL_Q_D;
                }
                break;
            }
            break;
        case 0xc3:
            /* 01110011 000011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110011 00001100 0....... ........ */
                switch ((insn >> 14) & 0x1) {
                case 0x0:
                    /* 01110011 00001100 00...... ........ */
                    switch ((insn >> 13) & 0x1) {
                    case 0x1:
                        /* 01110011 00001100 001..... ........ */
                        /* target/loongarch/insns.decode:1356 */
                        return LISA_VSLLWIL_HU_BU;
                    }
                    break;
                case 0x1:
                    /* 01110011 00001100 01...... ........ */
                    /* target/loongarch/insns.decode:1357 */
                    return LISA_VSLLWIL_WU_HU;
                }
                break;
            case 0x1:
                /* 01110011 00001100 1....... ........ */
                /* target/loongarch/insns.decode:1358 */
                return LISA_VSLLWIL_DU_WU;
            case 0x2:
                /* 01110011 00001101 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x0:
                    /* 01110011 00001101 000000.. ........ */
                    /* target/loongarch/insns.decode:1359 */
                    return LISA_VEXTL_QU_DU;
                }
                break;
            }
            break;
        case 0xc4:
            /* 01110011 000100.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110011 00010000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110011 00010000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110011 00010000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110011 00010000 001..... ........ */
                            /* target/loongarch/insns.decode:1360 */
                            return LISA_VBITCLRI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00010000 01...... ........ */
                        /* target/loongarch/insns.decode:1361 */
                        return LISA_VBITCLRI_H;
                    }
                    break;
                case 0x1:
                    /* 01110011 00010000 1....... ........ */
                    /* target/loongarch/insns.decode:1362 */
                    return LISA_VBITCLRI_W;
                }
                break;
            case 0x1:
                /* 01110011 00010001 ........ ........ */
                /* target/loongarch/insns.decode:1363 */
                return LISA_VBITCLRI_D;
            }
            break;
        case 0xc5:
            /* 01110011 000101.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110011 00010100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110011 00010100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110011 00010100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110011 00010100 001..... ........ */
                            /* target/loongarch/insns.decode:1364 */
                            return LISA_VBITSETI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00010100 01...... ........ */
                        /* target/loongarch/insns.decode:1365 */
                        return LISA_VBITSETI_H;
                    }
                    break;
                case 0x1:
                    /* 01110011 00010100 1....... ........ */
                    /* target/loongarch/insns.decode:1366 */
                    return LISA_VBITSETI_W;
                }
                break;
            case 0x1:
                /* 01110011 00010101 ........ ........ */
                /* target/loongarch/insns.decode:1367 */
                return LISA_VBITSETI_D;
            }
            break;
        case 0xc6:
            /* 01110011 000110.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110011 00011000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110011 00011000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110011 00011000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110011 00011000 001..... ........ */
                            /* target/loongarch/insns.decode:1368 */
                            return LISA_VBITREVI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00011000 01...... ........ */
                        /* target/loongarch/insns.decode:1369 */
                        return LISA_VBITREVI_H;
                    }
                    break;
                case 0x1:
                    /* 01110011 00011000 1....... ........ */
                    /* target/loongarch/insns.decode:1370 */
                    return LISA_VBITREVI_W;
                }
                break;
            case 0x1:
                /* 01110011 00011001 ........ ........ */
                /* target/loongarch/insns.decode:1371 */
                return LISA_VBITREVI_D;
            }
            break;
        case 0xc7:
            /* 01110011 000111.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110011 00011100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110011 00011100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110011 00011100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110011 00011100 001..... ........ */
                            /* target/loongarch/insns.decode:1372 */
                            return LISA_VBSTRC12I_B;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00011100 01...... ........ */
                        /* target/loongarch/insns.decode:1373 */
                        return LISA_VBSTRC12I_H;
                    }
                    break;
                case 0x1:
                    /* 01110011 00011100 1....... ........ */
                    /* target/loongarch/insns.decode:1374 */
                    return LISA_VBSTRC12I_W;
                }
                break;
            case 0x1:
                /* 01110011 00011101 ........ ........ */
                /* target/loongarch/insns.decode:1375 */
                return LISA_VBSTRC12I_D;
            }
            break;
        case 0xc8:
            /* 01110011 001000.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110011 00100000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110011 00100000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110011 00100000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110011 00100000 001..... ........ */
                            /* target/loongarch/insns.decode:1376 */
                            return LISA_VBSTRC21I_B;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00100000 01...... ........ */
                        /* target/loongarch/insns.decode:1377 */
                        return LISA_VBSTRC21I_H;
                    }
                    break;
                case 0x1:
                    /* 01110011 00100000 1....... ........ */
                    /* target/loongarch/insns.decode:1378 */
                    return LISA_VBSTRC21I_W;
                }
                break;
            case 0x1:
                /* 01110011 00100001 ........ ........ */
                /* target/loongarch/insns.decode:1379 */
                return LISA_VBSTRC21I_D;
            }
            break;
        case 0xc9:
            /* 01110011 001001.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110011 00100100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110011 00100100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110011 00100100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110011 00100100 001..... ........ */
                            /* target/loongarch/insns.decode:1380 */
                            return LISA_VSAT_B;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00100100 01...... ........ */
                        /* target/loongarch/insns.decode:1381 */
                        return LISA_VSAT_H;
                    }
                    break;
                case 0x1:
                    /* 01110011 00100100 1....... ........ */
                    /* target/loongarch/insns.decode:1382 */
                    return LISA_VSAT_W;
                }
                break;
            case 0x1:
                /* 01110011 00100101 ........ ........ */
                /* target/loongarch/insns.decode:1383 */
                return LISA_VSAT_D;
            }
            break;
        case 0xca:
            /* 01110011 001010.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110011 00101000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110011 00101000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110011 00101000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110011 00101000 001..... ........ */
                            /* target/loongarch/insns.decode:1384 */
                            return LISA_VSAT_BU;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00101000 01...... ........ */
                        /* target/loongarch/insns.decode:1385 */
                        return LISA_VSAT_HU;
                    }
                    break;
                case 0x1:
                    /* 01110011 00101000 1....... ........ */
                    /* target/loongarch/insns.decode:1386 */
                    return LISA_VSAT_WU;
                }
                break;
            case 0x1:
                /* 01110011 00101001 ........ ........ */
                /* target/loongarch/insns.decode:1387 */
                return LISA_VSAT_DU;
            }
            break;
        case 0xcb:
            /* 01110011 001011.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110011 00101100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110011 00101100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110011 00101100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110011 00101100 001..... ........ */
                            /* target/loongarch/insns.decode:1388 */
                            return LISA_VSLLI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00101100 01...... ........ */
                        /* target/loongarch/insns.decode:1389 */
                        return LISA_VSLLI_H;
                    }
                    break;
                case 0x1:
                    /* 01110011 00101100 1....... ........ */
                    /* target/loongarch/insns.decode:1390 */
                    return LISA_VSLLI_W;
                }
                break;
            case 0x1:
                /* 01110011 00101101 ........ ........ */
                /* target/loongarch/insns.decode:1391 */
                return LISA_VSLLI_D;
            }
            break;
        case 0xcc:
            /* 01110011 001100.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110011 00110000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110011 00110000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110011 00110000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110011 00110000 001..... ........ */
                            /* target/loongarch/insns.decode:1392 */
                            return LISA_VSRLI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00110000 01...... ........ */
                        /* target/loongarch/insns.decode:1393 */
                        return LISA_VSRLI_H;
                    }
                    break;
                case 0x1:
                    /* 01110011 00110000 1....... ........ */
                    /* target/loongarch/insns.decode:1394 */
                    return LISA_VSRLI_W;
                }
                break;
            case 0x1:
                /* 01110011 00110001 ........ ........ */
                /* target/loongarch/insns.decode:1395 */
                return LISA_VSRLI_D;
            }
            break;
        case 0xcd:
            /* 01110011 001101.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110011 00110100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110011 00110100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110011 00110100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110011 00110100 001..... ........ */
                            /* target/loongarch/insns.decode:1396 */
                            return LISA_VSRAI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00110100 01...... ........ */
                        /* target/loongarch/insns.decode:1397 */
                        return LISA_VSRAI_H;
                    }
                    break;
                case 0x1:
                    /* 01110011 00110100 1....... ........ */
                    /* target/loongarch/insns.decode:1398 */
                    return LISA_VSRAI_W;
                }
                break;
            case 0x1:
                /* 01110011 00110101 ........ ........ */
                /* target/loongarch/insns.decode:1399 */
                return LISA_VSRAI_D;
            }
            break;
        case 0xce:
            /* 01110011 001110.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0011100. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 00111000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 00111000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 00111000 01...... ........ */
                            /* target/loongarch/insns.decode:1400 */
                            return LISA_VSRLRNENI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00111000 1....... ........ */
                        /* target/loongarch/insns.decode:1401 */
                        return LISA_VSRLRNENI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 00111001 ........ ........ */
                    /* target/loongarch/insns.decode:1402 */
                    return LISA_VSRLRNENI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0011101. ........ ........ */
                /* target/loongarch/insns.decode:1403 */
                return LISA_VSRLRNENI_D_Q;
            }
            break;
        case 0xcf:
            /* 01110011 001111.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0011110. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 00111100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 00111100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 00111100 01...... ........ */
                            /* target/loongarch/insns.decode:1404 */
                            return LISA_VSRARNENI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 00111100 1....... ........ */
                        /* target/loongarch/insns.decode:1405 */
                        return LISA_VSRARNENI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 00111101 ........ ........ */
                    /* target/loongarch/insns.decode:1406 */
                    return LISA_VSRARNENI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0011111. ........ ........ */
                /* target/loongarch/insns.decode:1407 */
                return LISA_VSRARNENI_D_Q;
            }
            break;
        case 0xd0:
            /* 01110011 010000.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0100000. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01000000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01000000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01000000 01...... ........ */
                            /* target/loongarch/insns.decode:1408 */
                            return LISA_VSRLNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01000000 1....... ........ */
                        /* target/loongarch/insns.decode:1409 */
                        return LISA_VSRLNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01000001 ........ ........ */
                    /* target/loongarch/insns.decode:1410 */
                    return LISA_VSRLNI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0100001. ........ ........ */
                /* target/loongarch/insns.decode:1411 */
                return LISA_VSRLNI_D_Q;
            }
            break;
        case 0xd1:
            /* 01110011 010001.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0100010. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01000100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01000100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01000100 01...... ........ */
                            /* target/loongarch/insns.decode:1412 */
                            return LISA_VSRLRNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01000100 1....... ........ */
                        /* target/loongarch/insns.decode:1413 */
                        return LISA_VSRLRNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01000101 ........ ........ */
                    /* target/loongarch/insns.decode:1414 */
                    return LISA_VSRLRNI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0100011. ........ ........ */
                /* target/loongarch/insns.decode:1415 */
                return LISA_VSRLRNI_D_Q;
            }
            break;
        case 0xd2:
            /* 01110011 010010.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0100100. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01001000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01001000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01001000 01...... ........ */
                            /* target/loongarch/insns.decode:1416 */
                            return LISA_VSSRLNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01001000 1....... ........ */
                        /* target/loongarch/insns.decode:1417 */
                        return LISA_VSSRLNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01001001 ........ ........ */
                    /* target/loongarch/insns.decode:1418 */
                    return LISA_VSSRLNI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0100101. ........ ........ */
                /* target/loongarch/insns.decode:1419 */
                return LISA_VSSRLNI_D_Q;
            }
            break;
        case 0xd3:
            /* 01110011 010011.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0100110. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01001100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01001100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01001100 01...... ........ */
                            /* target/loongarch/insns.decode:1420 */
                            return LISA_VSSRLNI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01001100 1....... ........ */
                        /* target/loongarch/insns.decode:1421 */
                        return LISA_VSSRLNI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01001101 ........ ........ */
                    /* target/loongarch/insns.decode:1422 */
                    return LISA_VSSRLNI_WU_D;
                }
                break;
            case 0x1:
                /* 01110011 0100111. ........ ........ */
                /* target/loongarch/insns.decode:1423 */
                return LISA_VSSRLNI_DU_Q;
            }
            break;
        case 0xd4:
            /* 01110011 010100.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0101000. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01010000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01010000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01010000 01...... ........ */
                            /* target/loongarch/insns.decode:1424 */
                            return LISA_VSSRLRNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01010000 1....... ........ */
                        /* target/loongarch/insns.decode:1425 */
                        return LISA_VSSRLRNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01010001 ........ ........ */
                    /* target/loongarch/insns.decode:1426 */
                    return LISA_VSSRLRNI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0101001. ........ ........ */
                /* target/loongarch/insns.decode:1427 */
                return LISA_VSSRLRNI_D_Q;
            }
            break;
        case 0xd5:
            /* 01110011 010101.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0101010. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01010100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01010100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01010100 01...... ........ */
                            /* target/loongarch/insns.decode:1428 */
                            return LISA_VSSRLRNI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01010100 1....... ........ */
                        /* target/loongarch/insns.decode:1429 */
                        return LISA_VSSRLRNI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01010101 ........ ........ */
                    /* target/loongarch/insns.decode:1430 */
                    return LISA_VSSRLRNI_WU_D;
                }
                break;
            case 0x1:
                /* 01110011 0101011. ........ ........ */
                /* target/loongarch/insns.decode:1431 */
                return LISA_VSSRLRNI_DU_Q;
            }
            break;
        case 0xd6:
            /* 01110011 010110.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0101100. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01011000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01011000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01011000 01...... ........ */
                            /* target/loongarch/insns.decode:1432 */
                            return LISA_VSRANI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01011000 1....... ........ */
                        /* target/loongarch/insns.decode:1433 */
                        return LISA_VSRANI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01011001 ........ ........ */
                    /* target/loongarch/insns.decode:1434 */
                    return LISA_VSRANI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0101101. ........ ........ */
                /* target/loongarch/insns.decode:1435 */
                return LISA_VSRANI_D_Q;
            }
            break;
        case 0xd7:
            /* 01110011 010111.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0101110. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01011100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01011100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01011100 01...... ........ */
                            /* target/loongarch/insns.decode:1436 */
                            return LISA_VSRARNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01011100 1....... ........ */
                        /* target/loongarch/insns.decode:1437 */
                        return LISA_VSRARNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01011101 ........ ........ */
                    /* target/loongarch/insns.decode:1438 */
                    return LISA_VSRARNI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0101111. ........ ........ */
                /* target/loongarch/insns.decode:1439 */
                return LISA_VSRARNI_D_Q;
            }
            break;
        case 0xd8:
            /* 01110011 011000.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0110000. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01100000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01100000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01100000 01...... ........ */
                            /* target/loongarch/insns.decode:1440 */
                            return LISA_VSSRANI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01100000 1....... ........ */
                        /* target/loongarch/insns.decode:1441 */
                        return LISA_VSSRANI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01100001 ........ ........ */
                    /* target/loongarch/insns.decode:1442 */
                    return LISA_VSSRANI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0110001. ........ ........ */
                /* target/loongarch/insns.decode:1443 */
                return LISA_VSSRANI_D_Q;
            }
            break;
        case 0xd9:
            /* 01110011 011001.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0110010. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01100100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01100100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01100100 01...... ........ */
                            /* target/loongarch/insns.decode:1444 */
                            return LISA_VSSRANI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01100100 1....... ........ */
                        /* target/loongarch/insns.decode:1445 */
                        return LISA_VSSRANI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01100101 ........ ........ */
                    /* target/loongarch/insns.decode:1446 */
                    return LISA_VSSRANI_WU_D;
                }
                break;
            case 0x1:
                /* 01110011 0110011. ........ ........ */
                /* target/loongarch/insns.decode:1447 */
                return LISA_VSSRANI_DU_Q;
            }
            break;
        case 0xda:
            /* 01110011 011010.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0110100. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01101000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01101000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01101000 01...... ........ */
                            /* target/loongarch/insns.decode:1448 */
                            return LISA_VSSRARNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01101000 1....... ........ */
                        /* target/loongarch/insns.decode:1449 */
                        return LISA_VSSRARNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01101001 ........ ........ */
                    /* target/loongarch/insns.decode:1450 */
                    return LISA_VSSRARNI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0110101. ........ ........ */
                /* target/loongarch/insns.decode:1451 */
                return LISA_VSSRARNI_D_Q;
            }
            break;
        case 0xdb:
            /* 01110011 011011.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0110110. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01101100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01101100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01101100 01...... ........ */
                            /* target/loongarch/insns.decode:1452 */
                            return LISA_VSSRARNI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01101100 1....... ........ */
                        /* target/loongarch/insns.decode:1453 */
                        return LISA_VSSRARNI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01101101 ........ ........ */
                    /* target/loongarch/insns.decode:1454 */
                    return LISA_VSSRARNI_WU_D;
                }
                break;
            case 0x1:
                /* 01110011 0110111. ........ ........ */
                /* target/loongarch/insns.decode:1455 */
                return LISA_VSSRARNI_DU_Q;
            }
            break;
        case 0xdc:
            /* 01110011 011100.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0111000. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01110000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01110000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01110000 01...... ........ */
                            /* target/loongarch/insns.decode:1456 */
                            return LISA_VSSRLRNENI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01110000 1....... ........ */
                        /* target/loongarch/insns.decode:1457 */
                        return LISA_VSSRLRNENI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01110001 ........ ........ */
                    /* target/loongarch/insns.decode:1458 */
                    return LISA_VSSRLRNENI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0111001. ........ ........ */
                /* target/loongarch/insns.decode:1459 */
                return LISA_VSSRLRNENI_D_Q;
            }
            break;
        case 0xdd:
            /* 01110011 011101.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0111010. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01110100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01110100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01110100 01...... ........ */
                            /* target/loongarch/insns.decode:1460 */
                            return LISA_VSSRLRNENI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01110100 1....... ........ */
                        /* target/loongarch/insns.decode:1461 */
                        return LISA_VSSRLRNENI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01110101 ........ ........ */
                    /* target/loongarch/insns.decode:1462 */
                    return LISA_VSSRLRNENI_WU_D;
                }
                break;
            case 0x1:
                /* 01110011 0111011. ........ ........ */
                /* target/loongarch/insns.decode:1463 */
                return LISA_VSSRLRNENI_DU_Q;
            }
            break;
        case 0xde:
            /* 01110011 011110.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0111100. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01111000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01111000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01111000 01...... ........ */
                            /* target/loongarch/insns.decode:1464 */
                            return LISA_VSSRARNENI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01111000 1....... ........ */
                        /* target/loongarch/insns.decode:1465 */
                        return LISA_VSSRARNENI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01111001 ........ ........ */
                    /* target/loongarch/insns.decode:1466 */
                    return LISA_VSSRARNENI_W_D;
                }
                break;
            case 0x1:
                /* 01110011 0111101. ........ ........ */
                /* target/loongarch/insns.decode:1467 */
                return LISA_VSSRARNENI_D_Q;
            }
            break;
        case 0xdf:
            /* 01110011 011111.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110011 0111110. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110011 01111100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110011 01111100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110011 01111100 01...... ........ */
                            /* target/loongarch/insns.decode:1468 */
                            return LISA_VSSRARNENI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110011 01111100 1....... ........ */
                        /* target/loongarch/insns.decode:1469 */
                        return LISA_VSSRARNENI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110011 01111101 ........ ........ */
                    /* target/loongarch/insns.decode:1470 */
                    return LISA_VSSRARNENI_WU_D;
                }
                break;
            case 0x1:
                /* 01110011 0111111. ........ ........ */
                /* target/loongarch/insns.decode:1471 */
                return LISA_VSSRARNENI_DU_Q;
            }
            break;
        case 0xe0:
            /* 01110011 100000.. ........ ........ */
            /* target/loongarch/insns.decode:1472 */
            return LISA_VEXTRINS_D;
        case 0xe1:
            /* 01110011 100001.. ........ ........ */
            /* target/loongarch/insns.decode:1473 */
            return LISA_VEXTRINS_W;
        case 0xe2:
            /* 01110011 100010.. ........ ........ */
            /* target/loongarch/insns.decode:1474 */
            return LISA_VEXTRINS_H;
        case 0xe3:
            /* 01110011 100011.. ........ ........ */
            /* target/loongarch/insns.decode:1475 */
            return LISA_VEXTRINS_B;
        case 0xe4:
            /* 01110011 100100.. ........ ........ */
            /* target/loongarch/insns.decode:1476 */
            return LISA_VSHUF4I_B;
        case 0xe5:
            /* 01110011 100101.. ........ ........ */
            /* target/loongarch/insns.decode:1477 */
            return LISA_VSHUF4I_H;
        case 0xe6:
            /* 01110011 100110.. ........ ........ */
            /* target/loongarch/insns.decode:1478 */
            return LISA_VSHUF4I_W;
        case 0xe7:
            /* 01110011 100111.. ........ ........ */
            /* target/loongarch/insns.decode:1479 */
            return LISA_VSHUF4I_D;
        case 0xe8:
            /* 01110011 101000.. ........ ........ */
            /* target/loongarch/insns.decode:1480 */
            return LISA_VSHUFI1_B;
        case 0xe9:
            /* 01110011 101001.. ........ ........ */
            /* target/loongarch/insns.decode:1481 */
            return LISA_VSHUFI2_B;
        case 0xea:
            /* 01110011 101010.. ........ ........ */
            /* target/loongarch/insns.decode:1482 */
            return LISA_VSHUFI3_B;
        case 0xeb:
            /* 01110011 101011.. ........ ........ */
            /* target/loongarch/insns.decode:1483 */
            return LISA_VSHUFI4_B;
        case 0xec:
            /* 01110011 101100.. ........ ........ */
            /* target/loongarch/insns.decode:1484 */
            return LISA_VSHUFI1_H;
        case 0xed:
            /* 01110011 101101.. ........ ........ */
            /* target/loongarch/insns.decode:1485 */
            return LISA_VSHUFI2_H;
        case 0xee:
            /* 01110011 101110.. ........ ........ */
            /* target/loongarch/insns.decode:1486 */
            return LISA_VSELI_H;
        case 0xef:
            /* 01110011 101111.. ........ ........ */
            /* target/loongarch/insns.decode:1487 */
            return LISA_VSELI_W;
        case 0xf0:
            /* 01110011 110000.. ........ ........ */
            /* target/loongarch/insns.decode:1488 */
            return LISA_VSELI_D;
        case 0xf1:
            /* 01110011 110001.. ........ ........ */
            /* target/loongarch/insns.decode:1489 */
            return LISA_VBITSELI_B;
        case 0xf2:
            /* 01110011 110010.. ........ ........ */
            /* target/loongarch/insns.decode:1490 */
            return LISA_VBITMVZI_B;
        case 0xf3:
            /* 01110011 110011.. ........ ........ */
            /* target/loongarch/insns.decode:1491 */
            return LISA_VBITMVNZI_B;
        case 0xf4:
            /* 01110011 110100.. ........ ........ */
            /* target/loongarch/insns.decode:1492 */
            return LISA_VANDI_B;
        case 0xf5:
            /* 01110011 110101.. ........ ........ */
            /* target/loongarch/insns.decode:1493 */
            return LISA_VORI_B;
        case 0xf6:
            /* 01110011 110110.. ........ ........ */
            /* target/loongarch/insns.decode:1494 */
            return LISA_VXORI_B;
        case 0xf7:
            /* 01110011 110111.. ........ ........ */
            /* target/loongarch/insns.decode:1495 */
            return LISA_VNORI_B;
        case 0xf8:
            /* 01110011 111000.. ........ ........ */
            /* target/loongarch/insns.decode:1496 */
            return LISA_VLDI;
        case 0xf9:
            /* 01110011 111001.. ........ ........ */
            /* target/loongarch/insns.decode:1497 */
            return LISA_VPERMI_W;
        }
        break;
    case 0x1d:
        /* 011101.. ........ ........ ........ */
        switch ((insn >> 18) & 0xff) {
        case 0x0:
            /* 01110100 000000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 00000000 0....... ........ */
                /* target/loongarch/insns.decode:1498 */
                return LISA_XVSEQ_B;
            case 0x1:
                /* 01110100 00000000 1....... ........ */
                /* target/loongarch/insns.decode:1499 */
                return LISA_XVSEQ_H;
            case 0x2:
                /* 01110100 00000001 0....... ........ */
                /* target/loongarch/insns.decode:1500 */
                return LISA_XVSEQ_W;
            case 0x3:
                /* 01110100 00000001 1....... ........ */
                /* target/loongarch/insns.decode:1501 */
                return LISA_XVSEQ_D;
            case 0x4:
                /* 01110100 00000010 0....... ........ */
                /* target/loongarch/insns.decode:1502 */
                return LISA_XVSLE_B;
            case 0x5:
                /* 01110100 00000010 1....... ........ */
                /* target/loongarch/insns.decode:1503 */
                return LISA_XVSLE_H;
            case 0x6:
                /* 01110100 00000011 0....... ........ */
                /* target/loongarch/insns.decode:1504 */
                return LISA_XVSLE_W;
            case 0x7:
                /* 01110100 00000011 1....... ........ */
                /* target/loongarch/insns.decode:1505 */
                return LISA_XVSLE_D;
            }
            break;
        case 0x1:
            /* 01110100 000001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 00000100 0....... ........ */
                /* target/loongarch/insns.decode:1506 */
                return LISA_XVSLE_BU;
            case 0x1:
                /* 01110100 00000100 1....... ........ */
                /* target/loongarch/insns.decode:1507 */
                return LISA_XVSLE_HU;
            case 0x2:
                /* 01110100 00000101 0....... ........ */
                /* target/loongarch/insns.decode:1508 */
                return LISA_XVSLE_WU;
            case 0x3:
                /* 01110100 00000101 1....... ........ */
                /* target/loongarch/insns.decode:1509 */
                return LISA_XVSLE_DU;
            case 0x4:
                /* 01110100 00000110 0....... ........ */
                /* target/loongarch/insns.decode:1510 */
                return LISA_XVSLT_B;
            case 0x5:
                /* 01110100 00000110 1....... ........ */
                /* target/loongarch/insns.decode:1511 */
                return LISA_XVSLT_H;
            case 0x6:
                /* 01110100 00000111 0....... ........ */
                /* target/loongarch/insns.decode:1512 */
                return LISA_XVSLT_W;
            case 0x7:
                /* 01110100 00000111 1....... ........ */
                /* target/loongarch/insns.decode:1513 */
                return LISA_XVSLT_D;
            }
            break;
        case 0x2:
            /* 01110100 000010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 00001000 0....... ........ */
                /* target/loongarch/insns.decode:1514 */
                return LISA_XVSLT_BU;
            case 0x1:
                /* 01110100 00001000 1....... ........ */
                /* target/loongarch/insns.decode:1515 */
                return LISA_XVSLT_HU;
            case 0x2:
                /* 01110100 00001001 0....... ........ */
                /* target/loongarch/insns.decode:1516 */
                return LISA_XVSLT_WU;
            case 0x3:
                /* 01110100 00001001 1....... ........ */
                /* target/loongarch/insns.decode:1517 */
                return LISA_XVSLT_DU;
            case 0x4:
                /* 01110100 00001010 0....... ........ */
                /* target/loongarch/insns.decode:1518 */
                return LISA_XVADD_B;
            case 0x5:
                /* 01110100 00001010 1....... ........ */
                /* target/loongarch/insns.decode:1519 */
                return LISA_XVADD_H;
            case 0x6:
                /* 01110100 00001011 0....... ........ */
                /* target/loongarch/insns.decode:1520 */
                return LISA_XVADD_W;
            case 0x7:
                /* 01110100 00001011 1....... ........ */
                /* target/loongarch/insns.decode:1521 */
                return LISA_XVADD_D;
            }
            break;
        case 0x3:
            /* 01110100 000011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 00001100 0....... ........ */
                /* target/loongarch/insns.decode:1522 */
                return LISA_XVSUB_B;
            case 0x1:
                /* 01110100 00001100 1....... ........ */
                /* target/loongarch/insns.decode:1523 */
                return LISA_XVSUB_H;
            case 0x2:
                /* 01110100 00001101 0....... ........ */
                /* target/loongarch/insns.decode:1524 */
                return LISA_XVSUB_W;
            case 0x3:
                /* 01110100 00001101 1....... ........ */
                /* target/loongarch/insns.decode:1525 */
                return LISA_XVSUB_D;
            }
            break;
        case 0x7:
            /* 01110100 000111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110100 00011110 0....... ........ */
                /* target/loongarch/insns.decode:1526 */
                return LISA_XVADDWEV_H_B;
            case 0x5:
                /* 01110100 00011110 1....... ........ */
                /* target/loongarch/insns.decode:1527 */
                return LISA_XVADDWEV_W_H;
            case 0x6:
                /* 01110100 00011111 0....... ........ */
                /* target/loongarch/insns.decode:1528 */
                return LISA_XVADDWEV_D_W;
            case 0x7:
                /* 01110100 00011111 1....... ........ */
                /* target/loongarch/insns.decode:1529 */
                return LISA_XVADDWEV_Q_D;
            }
            break;
        case 0x8:
            /* 01110100 001000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 00100000 0....... ........ */
                /* target/loongarch/insns.decode:1530 */
                return LISA_XVSUBWEV_H_B;
            case 0x1:
                /* 01110100 00100000 1....... ........ */
                /* target/loongarch/insns.decode:1531 */
                return LISA_XVSUBWEV_W_H;
            case 0x2:
                /* 01110100 00100001 0....... ........ */
                /* target/loongarch/insns.decode:1532 */
                return LISA_XVSUBWEV_D_W;
            case 0x3:
                /* 01110100 00100001 1....... ........ */
                /* target/loongarch/insns.decode:1533 */
                return LISA_XVSUBWEV_Q_D;
            case 0x4:
                /* 01110100 00100010 0....... ........ */
                /* target/loongarch/insns.decode:1534 */
                return LISA_XVADDWOD_H_B;
            case 0x5:
                /* 01110100 00100010 1....... ........ */
                /* target/loongarch/insns.decode:1535 */
                return LISA_XVADDWOD_W_H;
            case 0x6:
                /* 01110100 00100011 0....... ........ */
                /* target/loongarch/insns.decode:1536 */
                return LISA_XVADDWOD_D_W;
            case 0x7:
                /* 01110100 00100011 1....... ........ */
                /* target/loongarch/insns.decode:1537 */
                return LISA_XVADDWOD_Q_D;
            }
            break;
        case 0x9:
            /* 01110100 001001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 00100100 0....... ........ */
                /* target/loongarch/insns.decode:1538 */
                return LISA_XVSUBWOD_H_B;
            case 0x1:
                /* 01110100 00100100 1....... ........ */
                /* target/loongarch/insns.decode:1539 */
                return LISA_XVSUBWOD_W_H;
            case 0x2:
                /* 01110100 00100101 0....... ........ */
                /* target/loongarch/insns.decode:1540 */
                return LISA_XVSUBWOD_D_W;
            case 0x3:
                /* 01110100 00100101 1....... ........ */
                /* target/loongarch/insns.decode:1541 */
                return LISA_XVSUBWOD_Q_D;
            }
            break;
        case 0xb:
            /* 01110100 001011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110100 00101110 0....... ........ */
                /* target/loongarch/insns.decode:1542 */
                return LISA_XVADDWEV_H_BU;
            case 0x5:
                /* 01110100 00101110 1....... ........ */
                /* target/loongarch/insns.decode:1543 */
                return LISA_XVADDWEV_W_HU;
            case 0x6:
                /* 01110100 00101111 0....... ........ */
                /* target/loongarch/insns.decode:1544 */
                return LISA_XVADDWEV_D_WU;
            case 0x7:
                /* 01110100 00101111 1....... ........ */
                /* target/loongarch/insns.decode:1545 */
                return LISA_XVADDWEV_Q_DU;
            }
            break;
        case 0xc:
            /* 01110100 001100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 00110000 0....... ........ */
                /* target/loongarch/insns.decode:1546 */
                return LISA_XVSUBWEV_H_BU;
            case 0x1:
                /* 01110100 00110000 1....... ........ */
                /* target/loongarch/insns.decode:1547 */
                return LISA_XVSUBWEV_W_HU;
            case 0x2:
                /* 01110100 00110001 0....... ........ */
                /* target/loongarch/insns.decode:1548 */
                return LISA_XVSUBWEV_D_WU;
            case 0x3:
                /* 01110100 00110001 1....... ........ */
                /* target/loongarch/insns.decode:1549 */
                return LISA_XVSUBWEV_Q_DU;
            case 0x4:
                /* 01110100 00110010 0....... ........ */
                /* target/loongarch/insns.decode:1550 */
                return LISA_XVADDWOD_H_BU;
            case 0x5:
                /* 01110100 00110010 1....... ........ */
                /* target/loongarch/insns.decode:1551 */
                return LISA_XVADDWOD_W_HU;
            case 0x6:
                /* 01110100 00110011 0....... ........ */
                /* target/loongarch/insns.decode:1552 */
                return LISA_XVADDWOD_D_WU;
            case 0x7:
                /* 01110100 00110011 1....... ........ */
                /* target/loongarch/insns.decode:1553 */
                return LISA_XVADDWOD_Q_DU;
            }
            break;
        case 0xd:
            /* 01110100 001101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 00110100 0....... ........ */
                /* target/loongarch/insns.decode:1554 */
                return LISA_XVSUBWOD_H_BU;
            case 0x1:
                /* 01110100 00110100 1....... ........ */
                /* target/loongarch/insns.decode:1555 */
                return LISA_XVSUBWOD_W_HU;
            case 0x2:
                /* 01110100 00110101 0....... ........ */
                /* target/loongarch/insns.decode:1556 */
                return LISA_XVSUBWOD_D_WU;
            case 0x3:
                /* 01110100 00110101 1....... ........ */
                /* target/loongarch/insns.decode:1557 */
                return LISA_XVSUBWOD_Q_DU;
            }
            break;
        case 0xf:
            /* 01110100 001111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110100 00111110 0....... ........ */
                /* target/loongarch/insns.decode:1558 */
                return LISA_XVADDWEV_H_BU_B;
            case 0x5:
                /* 01110100 00111110 1....... ........ */
                /* target/loongarch/insns.decode:1559 */
                return LISA_XVADDWEV_W_HU_H;
            case 0x6:
                /* 01110100 00111111 0....... ........ */
                /* target/loongarch/insns.decode:1560 */
                return LISA_XVADDWEV_D_WU_W;
            case 0x7:
                /* 01110100 00111111 1....... ........ */
                /* target/loongarch/insns.decode:1561 */
                return LISA_XVADDWEV_Q_DU_D;
            }
            break;
        case 0x10:
            /* 01110100 010000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01000000 0....... ........ */
                /* target/loongarch/insns.decode:1562 */
                return LISA_XVADDWOD_H_BU_B;
            case 0x1:
                /* 01110100 01000000 1....... ........ */
                /* target/loongarch/insns.decode:1563 */
                return LISA_XVADDWOD_W_HU_H;
            case 0x2:
                /* 01110100 01000001 0....... ........ */
                /* target/loongarch/insns.decode:1564 */
                return LISA_XVADDWOD_D_WU_W;
            case 0x3:
                /* 01110100 01000001 1....... ........ */
                /* target/loongarch/insns.decode:1565 */
                return LISA_XVADDWOD_Q_DU_D;
            }
            break;
        case 0x11:
            /* 01110100 010001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110100 01000110 0....... ........ */
                /* target/loongarch/insns.decode:1566 */
                return LISA_XVSADD_B;
            case 0x5:
                /* 01110100 01000110 1....... ........ */
                /* target/loongarch/insns.decode:1567 */
                return LISA_XVSADD_H;
            case 0x6:
                /* 01110100 01000111 0....... ........ */
                /* target/loongarch/insns.decode:1568 */
                return LISA_XVSADD_W;
            case 0x7:
                /* 01110100 01000111 1....... ........ */
                /* target/loongarch/insns.decode:1569 */
                return LISA_XVSADD_D;
            }
            break;
        case 0x12:
            /* 01110100 010010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01001000 0....... ........ */
                /* target/loongarch/insns.decode:1570 */
                return LISA_XVSSUB_B;
            case 0x1:
                /* 01110100 01001000 1....... ........ */
                /* target/loongarch/insns.decode:1571 */
                return LISA_XVSSUB_H;
            case 0x2:
                /* 01110100 01001001 0....... ........ */
                /* target/loongarch/insns.decode:1572 */
                return LISA_XVSSUB_W;
            case 0x3:
                /* 01110100 01001001 1....... ........ */
                /* target/loongarch/insns.decode:1573 */
                return LISA_XVSSUB_D;
            case 0x4:
                /* 01110100 01001010 0....... ........ */
                /* target/loongarch/insns.decode:1574 */
                return LISA_XVSADD_BU;
            case 0x5:
                /* 01110100 01001010 1....... ........ */
                /* target/loongarch/insns.decode:1575 */
                return LISA_XVSADD_HU;
            case 0x6:
                /* 01110100 01001011 0....... ........ */
                /* target/loongarch/insns.decode:1576 */
                return LISA_XVSADD_WU;
            case 0x7:
                /* 01110100 01001011 1....... ........ */
                /* target/loongarch/insns.decode:1577 */
                return LISA_XVSADD_DU;
            }
            break;
        case 0x13:
            /* 01110100 010011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01001100 0....... ........ */
                /* target/loongarch/insns.decode:1578 */
                return LISA_XVSSUB_BU;
            case 0x1:
                /* 01110100 01001100 1....... ........ */
                /* target/loongarch/insns.decode:1579 */
                return LISA_XVSSUB_HU;
            case 0x2:
                /* 01110100 01001101 0....... ........ */
                /* target/loongarch/insns.decode:1580 */
                return LISA_XVSSUB_WU;
            case 0x3:
                /* 01110100 01001101 1....... ........ */
                /* target/loongarch/insns.decode:1581 */
                return LISA_XVSSUB_DU;
            }
            break;
        case 0x15:
            /* 01110100 010101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01010100 0....... ........ */
                /* target/loongarch/insns.decode:1582 */
                return LISA_XVHADDW_H_B;
            case 0x1:
                /* 01110100 01010100 1....... ........ */
                /* target/loongarch/insns.decode:1583 */
                return LISA_XVHADDW_W_H;
            case 0x2:
                /* 01110100 01010101 0....... ........ */
                /* target/loongarch/insns.decode:1584 */
                return LISA_XVHADDW_D_W;
            case 0x3:
                /* 01110100 01010101 1....... ........ */
                /* target/loongarch/insns.decode:1585 */
                return LISA_XVHADDW_Q_D;
            case 0x4:
                /* 01110100 01010110 0....... ........ */
                /* target/loongarch/insns.decode:1586 */
                return LISA_XVHSUBW_H_B;
            case 0x5:
                /* 01110100 01010110 1....... ........ */
                /* target/loongarch/insns.decode:1587 */
                return LISA_XVHSUBW_W_H;
            case 0x6:
                /* 01110100 01010111 0....... ........ */
                /* target/loongarch/insns.decode:1588 */
                return LISA_XVHSUBW_D_W;
            case 0x7:
                /* 01110100 01010111 1....... ........ */
                /* target/loongarch/insns.decode:1589 */
                return LISA_XVHSUBW_Q_D;
            }
            break;
        case 0x16:
            /* 01110100 010110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01011000 0....... ........ */
                /* target/loongarch/insns.decode:1590 */
                return LISA_XVHADDW_HU_BU;
            case 0x1:
                /* 01110100 01011000 1....... ........ */
                /* target/loongarch/insns.decode:1591 */
                return LISA_XVHADDW_WU_HU;
            case 0x2:
                /* 01110100 01011001 0....... ........ */
                /* target/loongarch/insns.decode:1592 */
                return LISA_XVHADDW_DU_WU;
            case 0x3:
                /* 01110100 01011001 1....... ........ */
                /* target/loongarch/insns.decode:1593 */
                return LISA_XVHADDW_QU_DU;
            case 0x4:
                /* 01110100 01011010 0....... ........ */
                /* target/loongarch/insns.decode:1594 */
                return LISA_XVHSUBW_HU_BU;
            case 0x5:
                /* 01110100 01011010 1....... ........ */
                /* target/loongarch/insns.decode:1595 */
                return LISA_XVHSUBW_WU_HU;
            case 0x6:
                /* 01110100 01011011 0....... ........ */
                /* target/loongarch/insns.decode:1596 */
                return LISA_XVHSUBW_DU_WU;
            case 0x7:
                /* 01110100 01011011 1....... ........ */
                /* target/loongarch/insns.decode:1597 */
                return LISA_XVHSUBW_QU_DU;
            }
            break;
        case 0x17:
            /* 01110100 010111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01011100 0....... ........ */
                /* target/loongarch/insns.decode:1598 */
                return LISA_XVADDA_B;
            case 0x1:
                /* 01110100 01011100 1....... ........ */
                /* target/loongarch/insns.decode:1599 */
                return LISA_XVADDA_H;
            case 0x2:
                /* 01110100 01011101 0....... ........ */
                /* target/loongarch/insns.decode:1600 */
                return LISA_XVADDA_W;
            case 0x3:
                /* 01110100 01011101 1....... ........ */
                /* target/loongarch/insns.decode:1601 */
                return LISA_XVADDA_D;
            }
            break;
        case 0x18:
            /* 01110100 011000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01100000 0....... ........ */
                /* target/loongarch/insns.decode:1602 */
                return LISA_XVABSD_B;
            case 0x1:
                /* 01110100 01100000 1....... ........ */
                /* target/loongarch/insns.decode:1603 */
                return LISA_XVABSD_H;
            case 0x2:
                /* 01110100 01100001 0....... ........ */
                /* target/loongarch/insns.decode:1604 */
                return LISA_XVABSD_W;
            case 0x3:
                /* 01110100 01100001 1....... ........ */
                /* target/loongarch/insns.decode:1605 */
                return LISA_XVABSD_D;
            case 0x4:
                /* 01110100 01100010 0....... ........ */
                /* target/loongarch/insns.decode:1606 */
                return LISA_XVABSD_BU;
            case 0x5:
                /* 01110100 01100010 1....... ........ */
                /* target/loongarch/insns.decode:1607 */
                return LISA_XVABSD_HU;
            case 0x6:
                /* 01110100 01100011 0....... ........ */
                /* target/loongarch/insns.decode:1608 */
                return LISA_XVABSD_WU;
            case 0x7:
                /* 01110100 01100011 1....... ........ */
                /* target/loongarch/insns.decode:1609 */
                return LISA_XVABSD_DU;
            }
            break;
        case 0x19:
            /* 01110100 011001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01100100 0....... ........ */
                /* target/loongarch/insns.decode:1610 */
                return LISA_XVAVG_B;
            case 0x1:
                /* 01110100 01100100 1....... ........ */
                /* target/loongarch/insns.decode:1611 */
                return LISA_XVAVG_H;
            case 0x2:
                /* 01110100 01100101 0....... ........ */
                /* target/loongarch/insns.decode:1612 */
                return LISA_XVAVG_W;
            case 0x3:
                /* 01110100 01100101 1....... ........ */
                /* target/loongarch/insns.decode:1613 */
                return LISA_XVAVG_D;
            case 0x4:
                /* 01110100 01100110 0....... ........ */
                /* target/loongarch/insns.decode:1614 */
                return LISA_XVAVG_BU;
            case 0x5:
                /* 01110100 01100110 1....... ........ */
                /* target/loongarch/insns.decode:1615 */
                return LISA_XVAVG_HU;
            case 0x6:
                /* 01110100 01100111 0....... ........ */
                /* target/loongarch/insns.decode:1616 */
                return LISA_XVAVG_WU;
            case 0x7:
                /* 01110100 01100111 1....... ........ */
                /* target/loongarch/insns.decode:1617 */
                return LISA_XVAVG_DU;
            }
            break;
        case 0x1a:
            /* 01110100 011010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01101000 0....... ........ */
                /* target/loongarch/insns.decode:1618 */
                return LISA_XVAVGR_B;
            case 0x1:
                /* 01110100 01101000 1....... ........ */
                /* target/loongarch/insns.decode:1619 */
                return LISA_XVAVGR_H;
            case 0x2:
                /* 01110100 01101001 0....... ........ */
                /* target/loongarch/insns.decode:1620 */
                return LISA_XVAVGR_W;
            case 0x3:
                /* 01110100 01101001 1....... ........ */
                /* target/loongarch/insns.decode:1621 */
                return LISA_XVAVGR_D;
            case 0x4:
                /* 01110100 01101010 0....... ........ */
                /* target/loongarch/insns.decode:1622 */
                return LISA_XVAVGR_BU;
            case 0x5:
                /* 01110100 01101010 1....... ........ */
                /* target/loongarch/insns.decode:1623 */
                return LISA_XVAVGR_HU;
            case 0x6:
                /* 01110100 01101011 0....... ........ */
                /* target/loongarch/insns.decode:1624 */
                return LISA_XVAVGR_WU;
            case 0x7:
                /* 01110100 01101011 1....... ........ */
                /* target/loongarch/insns.decode:1625 */
                return LISA_XVAVGR_DU;
            }
            break;
        case 0x1c:
            /* 01110100 011100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01110000 0....... ........ */
                /* target/loongarch/insns.decode:1626 */
                return LISA_XVMAX_B;
            case 0x1:
                /* 01110100 01110000 1....... ........ */
                /* target/loongarch/insns.decode:1627 */
                return LISA_XVMAX_H;
            case 0x2:
                /* 01110100 01110001 0....... ........ */
                /* target/loongarch/insns.decode:1628 */
                return LISA_XVMAX_W;
            case 0x3:
                /* 01110100 01110001 1....... ........ */
                /* target/loongarch/insns.decode:1629 */
                return LISA_XVMAX_D;
            case 0x4:
                /* 01110100 01110010 0....... ........ */
                /* target/loongarch/insns.decode:1630 */
                return LISA_XVMIN_B;
            case 0x5:
                /* 01110100 01110010 1....... ........ */
                /* target/loongarch/insns.decode:1631 */
                return LISA_XVMIN_H;
            case 0x6:
                /* 01110100 01110011 0....... ........ */
                /* target/loongarch/insns.decode:1632 */
                return LISA_XVMIN_W;
            case 0x7:
                /* 01110100 01110011 1....... ........ */
                /* target/loongarch/insns.decode:1633 */
                return LISA_XVMIN_D;
            }
            break;
        case 0x1d:
            /* 01110100 011101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 01110100 0....... ........ */
                /* target/loongarch/insns.decode:1634 */
                return LISA_XVMAX_BU;
            case 0x1:
                /* 01110100 01110100 1....... ........ */
                /* target/loongarch/insns.decode:1635 */
                return LISA_XVMAX_HU;
            case 0x2:
                /* 01110100 01110101 0....... ........ */
                /* target/loongarch/insns.decode:1636 */
                return LISA_XVMAX_WU;
            case 0x3:
                /* 01110100 01110101 1....... ........ */
                /* target/loongarch/insns.decode:1637 */
                return LISA_XVMAX_DU;
            case 0x4:
                /* 01110100 01110110 0....... ........ */
                /* target/loongarch/insns.decode:1638 */
                return LISA_XVMIN_BU;
            case 0x5:
                /* 01110100 01110110 1....... ........ */
                /* target/loongarch/insns.decode:1639 */
                return LISA_XVMIN_HU;
            case 0x6:
                /* 01110100 01110111 0....... ........ */
                /* target/loongarch/insns.decode:1640 */
                return LISA_XVMIN_WU;
            case 0x7:
                /* 01110100 01110111 1....... ........ */
                /* target/loongarch/insns.decode:1641 */
                return LISA_XVMIN_DU;
            }
            break;
        case 0x21:
            /* 01110100 100001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 10000100 0....... ........ */
                /* target/loongarch/insns.decode:1642 */
                return LISA_XVMUL_B;
            case 0x1:
                /* 01110100 10000100 1....... ........ */
                /* target/loongarch/insns.decode:1643 */
                return LISA_XVMUL_H;
            case 0x2:
                /* 01110100 10000101 0....... ........ */
                /* target/loongarch/insns.decode:1644 */
                return LISA_XVMUL_W;
            case 0x3:
                /* 01110100 10000101 1....... ........ */
                /* target/loongarch/insns.decode:1645 */
                return LISA_XVMUL_D;
            case 0x4:
                /* 01110100 10000110 0....... ........ */
                /* target/loongarch/insns.decode:1646 */
                return LISA_XVMUH_B;
            case 0x5:
                /* 01110100 10000110 1....... ........ */
                /* target/loongarch/insns.decode:1647 */
                return LISA_XVMUH_H;
            case 0x6:
                /* 01110100 10000111 0....... ........ */
                /* target/loongarch/insns.decode:1648 */
                return LISA_XVMUH_W;
            case 0x7:
                /* 01110100 10000111 1....... ........ */
                /* target/loongarch/insns.decode:1649 */
                return LISA_XVMUH_D;
            }
            break;
        case 0x22:
            /* 01110100 100010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 10001000 0....... ........ */
                /* target/loongarch/insns.decode:1650 */
                return LISA_XVMUH_BU;
            case 0x1:
                /* 01110100 10001000 1....... ........ */
                /* target/loongarch/insns.decode:1651 */
                return LISA_XVMUH_HU;
            case 0x2:
                /* 01110100 10001001 0....... ........ */
                /* target/loongarch/insns.decode:1652 */
                return LISA_XVMUH_WU;
            case 0x3:
                /* 01110100 10001001 1....... ........ */
                /* target/loongarch/insns.decode:1653 */
                return LISA_XVMUH_DU;
            }
            break;
        case 0x24:
            /* 01110100 100100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 10010000 0....... ........ */
                /* target/loongarch/insns.decode:1654 */
                return LISA_XVMULWEV_H_B;
            case 0x1:
                /* 01110100 10010000 1....... ........ */
                /* target/loongarch/insns.decode:1655 */
                return LISA_XVMULWEV_W_H;
            case 0x2:
                /* 01110100 10010001 0....... ........ */
                /* target/loongarch/insns.decode:1656 */
                return LISA_XVMULWEV_D_W;
            case 0x3:
                /* 01110100 10010001 1....... ........ */
                /* target/loongarch/insns.decode:1657 */
                return LISA_XVMULWEV_Q_D;
            case 0x4:
                /* 01110100 10010010 0....... ........ */
                /* target/loongarch/insns.decode:1658 */
                return LISA_XVMULWOD_H_B;
            case 0x5:
                /* 01110100 10010010 1....... ........ */
                /* target/loongarch/insns.decode:1659 */
                return LISA_XVMULWOD_W_H;
            case 0x6:
                /* 01110100 10010011 0....... ........ */
                /* target/loongarch/insns.decode:1660 */
                return LISA_XVMULWOD_D_W;
            case 0x7:
                /* 01110100 10010011 1....... ........ */
                /* target/loongarch/insns.decode:1661 */
                return LISA_XVMULWOD_Q_D;
            }
            break;
        case 0x26:
            /* 01110100 100110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 10011000 0....... ........ */
                /* target/loongarch/insns.decode:1662 */
                return LISA_XVMULWEV_H_BU;
            case 0x1:
                /* 01110100 10011000 1....... ........ */
                /* target/loongarch/insns.decode:1663 */
                return LISA_XVMULWEV_W_HU;
            case 0x2:
                /* 01110100 10011001 0....... ........ */
                /* target/loongarch/insns.decode:1664 */
                return LISA_XVMULWEV_D_WU;
            case 0x3:
                /* 01110100 10011001 1....... ........ */
                /* target/loongarch/insns.decode:1665 */
                return LISA_XVMULWEV_Q_DU;
            case 0x4:
                /* 01110100 10011010 0....... ........ */
                /* target/loongarch/insns.decode:1666 */
                return LISA_XVMULWOD_H_BU;
            case 0x5:
                /* 01110100 10011010 1....... ........ */
                /* target/loongarch/insns.decode:1667 */
                return LISA_XVMULWOD_W_HU;
            case 0x6:
                /* 01110100 10011011 0....... ........ */
                /* target/loongarch/insns.decode:1668 */
                return LISA_XVMULWOD_D_WU;
            case 0x7:
                /* 01110100 10011011 1....... ........ */
                /* target/loongarch/insns.decode:1669 */
                return LISA_XVMULWOD_Q_DU;
            }
            break;
        case 0x2a:
            /* 01110100 101010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 10101000 0....... ........ */
                /* target/loongarch/insns.decode:1686 */
                return LISA_XVMADD_B;
            case 0x1:
                /* 01110100 10101000 1....... ........ */
                /* target/loongarch/insns.decode:1687 */
                return LISA_XVMADD_H;
            case 0x2:
                /* 01110100 10101001 0....... ........ */
                /* target/loongarch/insns.decode:1688 */
                return LISA_XVMADD_W;
            case 0x3:
                /* 01110100 10101001 1....... ........ */
                /* target/loongarch/insns.decode:1689 */
                return LISA_XVMADD_D;
            case 0x4:
                /* 01110100 10101010 0....... ........ */
                /* target/loongarch/insns.decode:1690 */
                return LISA_XVMSUB_B;
            case 0x5:
                /* 01110100 10101010 1....... ........ */
                /* target/loongarch/insns.decode:1691 */
                return LISA_XVMSUB_H;
            case 0x6:
                /* 01110100 10101011 0....... ........ */
                /* target/loongarch/insns.decode:1692 */
                return LISA_XVMSUB_W;
            case 0x7:
                /* 01110100 10101011 1....... ........ */
                /* target/loongarch/insns.decode:1693 */
                return LISA_XVMSUB_D;
            }
            break;
        case 0x2b:
            /* 01110100 101011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 10101100 0....... ........ */
                /* target/loongarch/insns.decode:1694 */
                return LISA_XVMADDWEV_H_B;
            case 0x1:
                /* 01110100 10101100 1....... ........ */
                /* target/loongarch/insns.decode:1695 */
                return LISA_XVMADDWEV_W_H;
            case 0x2:
                /* 01110100 10101101 0....... ........ */
                /* target/loongarch/insns.decode:1696 */
                return LISA_XVMADDWEV_D_W;
            case 0x3:
                /* 01110100 10101101 1....... ........ */
                /* target/loongarch/insns.decode:1697 */
                return LISA_XVMADDWEV_Q_D;
            case 0x4:
                /* 01110100 10101110 0....... ........ */
                /* target/loongarch/insns.decode:1698 */
                return LISA_XVMADDWOD_H_B;
            case 0x5:
                /* 01110100 10101110 1....... ........ */
                /* target/loongarch/insns.decode:1699 */
                return LISA_XVMADDWOD_W_H;
            case 0x6:
                /* 01110100 10101111 0....... ........ */
                /* target/loongarch/insns.decode:1700 */
                return LISA_XVMADDWOD_D_W;
            case 0x7:
                /* 01110100 10101111 1....... ........ */
                /* target/loongarch/insns.decode:1701 */
                return LISA_XVMADDWOD_Q_D;
            }
            break;
        case 0x2d:
            /* 01110100 101101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 10110100 0....... ........ */
                /* target/loongarch/insns.decode:1702 */
                return LISA_XVMADDWEV_H_BU;
            case 0x1:
                /* 01110100 10110100 1....... ........ */
                /* target/loongarch/insns.decode:1703 */
                return LISA_XVMADDWEV_W_HU;
            case 0x2:
                /* 01110100 10110101 0....... ........ */
                /* target/loongarch/insns.decode:1704 */
                return LISA_XVMADDWEV_D_WU;
            case 0x3:
                /* 01110100 10110101 1....... ........ */
                /* target/loongarch/insns.decode:1705 */
                return LISA_XVMADDWEV_Q_DU;
            case 0x4:
                /* 01110100 10110110 0....... ........ */
                /* target/loongarch/insns.decode:1706 */
                return LISA_XVMADDWOD_H_BU;
            case 0x5:
                /* 01110100 10110110 1....... ........ */
                /* target/loongarch/insns.decode:1707 */
                return LISA_XVMADDWOD_W_HU;
            case 0x6:
                /* 01110100 10110111 0....... ........ */
                /* target/loongarch/insns.decode:1708 */
                return LISA_XVMADDWOD_D_WU;
            case 0x7:
                /* 01110100 10110111 1....... ........ */
                /* target/loongarch/insns.decode:1709 */
                return LISA_XVMADDWOD_Q_DU;
            }
            break;
        case 0x2f:
            /* 01110100 101111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 10111100 0....... ........ */
                /* target/loongarch/insns.decode:1710 */
                return LISA_XVMADDWEV_H_BU_B;
            case 0x1:
                /* 01110100 10111100 1....... ........ */
                /* target/loongarch/insns.decode:1711 */
                return LISA_XVMADDWEV_W_HU_H;
            case 0x2:
                /* 01110100 10111101 0....... ........ */
                /* target/loongarch/insns.decode:1712 */
                return LISA_XVMADDWEV_D_WU_W;
            case 0x3:
                /* 01110100 10111101 1....... ........ */
                /* target/loongarch/insns.decode:1713 */
                return LISA_XVMADDWEV_Q_DU_D;
            case 0x4:
                /* 01110100 10111110 0....... ........ */
                /* target/loongarch/insns.decode:1714 */
                return LISA_XVMADDWOD_H_BU_B;
            case 0x5:
                /* 01110100 10111110 1....... ........ */
                /* target/loongarch/insns.decode:1715 */
                return LISA_XVMADDWOD_W_HU_H;
            case 0x6:
                /* 01110100 10111111 0....... ........ */
                /* target/loongarch/insns.decode:1716 */
                return LISA_XVMADDWOD_D_WU_W;
            case 0x7:
                /* 01110100 10111111 1....... ........ */
                /* target/loongarch/insns.decode:1717 */
                return LISA_XVMADDWOD_Q_DU_D;
            }
            break;
        case 0x38:
            /* 01110100 111000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 11100000 0....... ........ */
                /* target/loongarch/insns.decode:1718 */
                return LISA_XVDIV_B;
            case 0x1:
                /* 01110100 11100000 1....... ........ */
                /* target/loongarch/insns.decode:1719 */
                return LISA_XVDIV_H;
            case 0x2:
                /* 01110100 11100001 0....... ........ */
                /* target/loongarch/insns.decode:1720 */
                return LISA_XVDIV_W;
            case 0x3:
                /* 01110100 11100001 1....... ........ */
                /* target/loongarch/insns.decode:1721 */
                return LISA_XVDIV_D;
            case 0x4:
                /* 01110100 11100010 0....... ........ */
                /* target/loongarch/insns.decode:1722 */
                return LISA_XVMOD_B;
            case 0x5:
                /* 01110100 11100010 1....... ........ */
                /* target/loongarch/insns.decode:1723 */
                return LISA_XVMOD_H;
            case 0x6:
                /* 01110100 11100011 0....... ........ */
                /* target/loongarch/insns.decode:1724 */
                return LISA_XVMOD_W;
            case 0x7:
                /* 01110100 11100011 1....... ........ */
                /* target/loongarch/insns.decode:1725 */
                return LISA_XVMOD_D;
            }
            break;
        case 0x39:
            /* 01110100 111001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 11100100 0....... ........ */
                /* target/loongarch/insns.decode:1726 */
                return LISA_XVDIV_BU;
            case 0x1:
                /* 01110100 11100100 1....... ........ */
                /* target/loongarch/insns.decode:1727 */
                return LISA_XVDIV_HU;
            case 0x2:
                /* 01110100 11100101 0....... ........ */
                /* target/loongarch/insns.decode:1728 */
                return LISA_XVDIV_WU;
            case 0x3:
                /* 01110100 11100101 1....... ........ */
                /* target/loongarch/insns.decode:1729 */
                return LISA_XVDIV_DU;
            case 0x4:
                /* 01110100 11100110 0....... ........ */
                /* target/loongarch/insns.decode:1730 */
                return LISA_XVMOD_BU;
            case 0x5:
                /* 01110100 11100110 1....... ........ */
                /* target/loongarch/insns.decode:1731 */
                return LISA_XVMOD_HU;
            case 0x6:
                /* 01110100 11100111 0....... ........ */
                /* target/loongarch/insns.decode:1732 */
                return LISA_XVMOD_WU;
            case 0x7:
                /* 01110100 11100111 1....... ........ */
                /* target/loongarch/insns.decode:1733 */
                return LISA_XVMOD_DU;
            }
            break;
        case 0x3a:
            /* 01110100 111010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 11101000 0....... ........ */
                /* target/loongarch/insns.decode:1734 */
                return LISA_XVSLL_B;
            case 0x1:
                /* 01110100 11101000 1....... ........ */
                /* target/loongarch/insns.decode:1735 */
                return LISA_XVSLL_H;
            case 0x2:
                /* 01110100 11101001 0....... ........ */
                /* target/loongarch/insns.decode:1736 */
                return LISA_XVSLL_W;
            case 0x3:
                /* 01110100 11101001 1....... ........ */
                /* target/loongarch/insns.decode:1737 */
                return LISA_XVSLL_D;
            case 0x4:
                /* 01110100 11101010 0....... ........ */
                /* target/loongarch/insns.decode:1738 */
                return LISA_XVSRL_B;
            case 0x5:
                /* 01110100 11101010 1....... ........ */
                /* target/loongarch/insns.decode:1739 */
                return LISA_XVSRL_H;
            case 0x6:
                /* 01110100 11101011 0....... ........ */
                /* target/loongarch/insns.decode:1740 */
                return LISA_XVSRL_W;
            case 0x7:
                /* 01110100 11101011 1....... ........ */
                /* target/loongarch/insns.decode:1741 */
                return LISA_XVSRL_D;
            }
            break;
        case 0x3b:
            /* 01110100 111011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 11101100 0....... ........ */
                /* target/loongarch/insns.decode:1742 */
                return LISA_XVSRA_B;
            case 0x1:
                /* 01110100 11101100 1....... ........ */
                /* target/loongarch/insns.decode:1743 */
                return LISA_XVSRA_H;
            case 0x2:
                /* 01110100 11101101 0....... ........ */
                /* target/loongarch/insns.decode:1744 */
                return LISA_XVSRA_W;
            case 0x3:
                /* 01110100 11101101 1....... ........ */
                /* target/loongarch/insns.decode:1745 */
                return LISA_XVSRA_D;
            case 0x4:
                /* 01110100 11101110 0....... ........ */
                /* target/loongarch/insns.decode:1746 */
                return LISA_XVROTR_B;
            case 0x5:
                /* 01110100 11101110 1....... ........ */
                /* target/loongarch/insns.decode:1747 */
                return LISA_XVROTR_H;
            case 0x6:
                /* 01110100 11101111 0....... ........ */
                /* target/loongarch/insns.decode:1748 */
                return LISA_XVROTR_W;
            case 0x7:
                /* 01110100 11101111 1....... ........ */
                /* target/loongarch/insns.decode:1749 */
                return LISA_XVROTR_D;
            }
            break;
        case 0x3c:
            /* 01110100 111100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110100 11110000 0....... ........ */
                /* target/loongarch/insns.decode:1750 */
                return LISA_XVSRLR_B;
            case 0x1:
                /* 01110100 11110000 1....... ........ */
                /* target/loongarch/insns.decode:1751 */
                return LISA_XVSRLR_H;
            case 0x2:
                /* 01110100 11110001 0....... ........ */
                /* target/loongarch/insns.decode:1752 */
                return LISA_XVSRLR_W;
            case 0x3:
                /* 01110100 11110001 1....... ........ */
                /* target/loongarch/insns.decode:1753 */
                return LISA_XVSRLR_D;
            case 0x4:
                /* 01110100 11110010 0....... ........ */
                /* target/loongarch/insns.decode:1754 */
                return LISA_XVSRAR_B;
            case 0x5:
                /* 01110100 11110010 1....... ........ */
                /* target/loongarch/insns.decode:1755 */
                return LISA_XVSRAR_H;
            case 0x6:
                /* 01110100 11110011 0....... ........ */
                /* target/loongarch/insns.decode:1756 */
                return LISA_XVSRAR_W;
            case 0x7:
                /* 01110100 11110011 1....... ........ */
                /* target/loongarch/insns.decode:1757 */
                return LISA_XVSRAR_D;
            }
            break;
        case 0x3d:
            /* 01110100 111101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110100 11110100 1....... ........ */
                /* target/loongarch/insns.decode:1758 */
                return LISA_XVSRLN_B_H;
            case 0x2:
                /* 01110100 11110101 0....... ........ */
                /* target/loongarch/insns.decode:1759 */
                return LISA_XVSRLN_H_W;
            case 0x3:
                /* 01110100 11110101 1....... ........ */
                /* target/loongarch/insns.decode:1760 */
                return LISA_XVSRLN_W_D;
            case 0x5:
                /* 01110100 11110110 1....... ........ */
                /* target/loongarch/insns.decode:1761 */
                return LISA_XVSRAN_B_H;
            case 0x6:
                /* 01110100 11110111 0....... ........ */
                /* target/loongarch/insns.decode:1762 */
                return LISA_XVSRAN_H_W;
            case 0x7:
                /* 01110100 11110111 1....... ........ */
                /* target/loongarch/insns.decode:1763 */
                return LISA_XVSRAN_W_D;
            }
            break;
        case 0x3e:
            /* 01110100 111110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110100 11111000 1....... ........ */
                /* target/loongarch/insns.decode:1764 */
                return LISA_XVSRLRN_B_H;
            case 0x2:
                /* 01110100 11111001 0....... ........ */
                /* target/loongarch/insns.decode:1765 */
                return LISA_XVSRLRN_H_W;
            case 0x3:
                /* 01110100 11111001 1....... ........ */
                /* target/loongarch/insns.decode:1766 */
                return LISA_XVSRLRN_W_D;
            case 0x5:
                /* 01110100 11111010 1....... ........ */
                /* target/loongarch/insns.decode:1767 */
                return LISA_XVSRARN_B_H;
            case 0x6:
                /* 01110100 11111011 0....... ........ */
                /* target/loongarch/insns.decode:1768 */
                return LISA_XVSRARN_H_W;
            case 0x7:
                /* 01110100 11111011 1....... ........ */
                /* target/loongarch/insns.decode:1769 */
                return LISA_XVSRARN_W_D;
            }
            break;
        case 0x3f:
            /* 01110100 111111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110100 11111100 1....... ........ */
                /* target/loongarch/insns.decode:1770 */
                return LISA_XVSSRLN_B_H;
            case 0x2:
                /* 01110100 11111101 0....... ........ */
                /* target/loongarch/insns.decode:1771 */
                return LISA_XVSSRLN_H_W;
            case 0x3:
                /* 01110100 11111101 1....... ........ */
                /* target/loongarch/insns.decode:1772 */
                return LISA_XVSSRLN_W_D;
            case 0x5:
                /* 01110100 11111110 1....... ........ */
                /* target/loongarch/insns.decode:1773 */
                return LISA_XVSSRAN_B_H;
            case 0x6:
                /* 01110100 11111111 0....... ........ */
                /* target/loongarch/insns.decode:1774 */
                return LISA_XVSSRAN_H_W;
            case 0x7:
                /* 01110100 11111111 1....... ........ */
                /* target/loongarch/insns.decode:1775 */
                return LISA_XVSSRAN_W_D;
            }
            break;
        case 0x40:
            /* 01110101 000000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110101 00000000 1....... ........ */
                /* target/loongarch/insns.decode:1776 */
                return LISA_XVSSRLRN_B_H;
            case 0x2:
                /* 01110101 00000001 0....... ........ */
                /* target/loongarch/insns.decode:1777 */
                return LISA_XVSSRLRN_H_W;
            case 0x3:
                /* 01110101 00000001 1....... ........ */
                /* target/loongarch/insns.decode:1778 */
                return LISA_XVSSRLRN_W_D;
            case 0x5:
                /* 01110101 00000010 1....... ........ */
                /* target/loongarch/insns.decode:1779 */
                return LISA_XVSSRARN_B_H;
            case 0x6:
                /* 01110101 00000011 0....... ........ */
                /* target/loongarch/insns.decode:1780 */
                return LISA_XVSSRARN_H_W;
            case 0x7:
                /* 01110101 00000011 1....... ........ */
                /* target/loongarch/insns.decode:1781 */
                return LISA_XVSSRARN_W_D;
            }
            break;
        case 0x41:
            /* 01110101 000001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110101 00000100 1....... ........ */
                /* target/loongarch/insns.decode:1782 */
                return LISA_XVSSRLN_BU_H;
            case 0x2:
                /* 01110101 00000101 0....... ........ */
                /* target/loongarch/insns.decode:1783 */
                return LISA_XVSSRLN_HU_W;
            case 0x3:
                /* 01110101 00000101 1....... ........ */
                /* target/loongarch/insns.decode:1784 */
                return LISA_XVSSRLN_WU_D;
            case 0x5:
                /* 01110101 00000110 1....... ........ */
                /* target/loongarch/insns.decode:1785 */
                return LISA_XVSSRAN_BU_H;
            case 0x6:
                /* 01110101 00000111 0....... ........ */
                /* target/loongarch/insns.decode:1786 */
                return LISA_XVSSRAN_HU_W;
            case 0x7:
                /* 01110101 00000111 1....... ........ */
                /* target/loongarch/insns.decode:1787 */
                return LISA_XVSSRAN_WU_D;
            }
            break;
        case 0x42:
            /* 01110101 000010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110101 00001000 1....... ........ */
                /* target/loongarch/insns.decode:1788 */
                return LISA_XVSSRLRN_BU_H;
            case 0x2:
                /* 01110101 00001001 0....... ........ */
                /* target/loongarch/insns.decode:1789 */
                return LISA_XVSSRLRN_HU_W;
            case 0x3:
                /* 01110101 00001001 1....... ........ */
                /* target/loongarch/insns.decode:1790 */
                return LISA_XVSSRLRN_WU_D;
            case 0x5:
                /* 01110101 00001010 1....... ........ */
                /* target/loongarch/insns.decode:1791 */
                return LISA_XVSSRARN_BU_H;
            case 0x6:
                /* 01110101 00001011 0....... ........ */
                /* target/loongarch/insns.decode:1792 */
                return LISA_XVSSRARN_HU_W;
            case 0x7:
                /* 01110101 00001011 1....... ........ */
                /* target/loongarch/insns.decode:1793 */
                return LISA_XVSSRARN_WU_D;
            }
            break;
        case 0x43:
            /* 01110101 000011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 00001100 0....... ........ */
                /* target/loongarch/insns.decode:1794 */
                return LISA_XVBITCLR_B;
            case 0x1:
                /* 01110101 00001100 1....... ........ */
                /* target/loongarch/insns.decode:1795 */
                return LISA_XVBITCLR_H;
            case 0x2:
                /* 01110101 00001101 0....... ........ */
                /* target/loongarch/insns.decode:1796 */
                return LISA_XVBITCLR_W;
            case 0x3:
                /* 01110101 00001101 1....... ........ */
                /* target/loongarch/insns.decode:1797 */
                return LISA_XVBITCLR_D;
            case 0x4:
                /* 01110101 00001110 0....... ........ */
                /* target/loongarch/insns.decode:1798 */
                return LISA_XVBITSET_B;
            case 0x5:
                /* 01110101 00001110 1....... ........ */
                /* target/loongarch/insns.decode:1799 */
                return LISA_XVBITSET_H;
            case 0x6:
                /* 01110101 00001111 0....... ........ */
                /* target/loongarch/insns.decode:1800 */
                return LISA_XVBITSET_W;
            case 0x7:
                /* 01110101 00001111 1....... ........ */
                /* target/loongarch/insns.decode:1801 */
                return LISA_XVBITSET_D;
            }
            break;
        case 0x44:
            /* 01110101 000100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 00010000 0....... ........ */
                /* target/loongarch/insns.decode:1802 */
                return LISA_XVBITREV_B;
            case 0x1:
                /* 01110101 00010000 1....... ........ */
                /* target/loongarch/insns.decode:1803 */
                return LISA_XVBITREV_H;
            case 0x2:
                /* 01110101 00010001 0....... ........ */
                /* target/loongarch/insns.decode:1804 */
                return LISA_XVBITREV_W;
            case 0x3:
                /* 01110101 00010001 1....... ........ */
                /* target/loongarch/insns.decode:1805 */
                return LISA_XVBITREV_D;
            }
            break;
        case 0x45:
            /* 01110101 000101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110101 00010110 0....... ........ */
                /* target/loongarch/insns.decode:1806 */
                return LISA_XVPACKEV_B;
            case 0x5:
                /* 01110101 00010110 1....... ........ */
                /* target/loongarch/insns.decode:1807 */
                return LISA_XVPACKEV_H;
            case 0x6:
                /* 01110101 00010111 0....... ........ */
                /* target/loongarch/insns.decode:1808 */
                return LISA_XVPACKEV_W;
            case 0x7:
                /* 01110101 00010111 1....... ........ */
                /* target/loongarch/insns.decode:1809 */
                return LISA_XVPACKEV_D;
            }
            break;
        case 0x46:
            /* 01110101 000110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 00011000 0....... ........ */
                /* target/loongarch/insns.decode:1810 */
                return LISA_XVPACKOD_B;
            case 0x1:
                /* 01110101 00011000 1....... ........ */
                /* target/loongarch/insns.decode:1811 */
                return LISA_XVPACKOD_H;
            case 0x2:
                /* 01110101 00011001 0....... ........ */
                /* target/loongarch/insns.decode:1812 */
                return LISA_XVPACKOD_W;
            case 0x3:
                /* 01110101 00011001 1....... ........ */
                /* target/loongarch/insns.decode:1813 */
                return LISA_XVPACKOD_D;
            case 0x4:
                /* 01110101 00011010 0....... ........ */
                /* target/loongarch/insns.decode:1814 */
                return LISA_XVILVL_B;
            case 0x5:
                /* 01110101 00011010 1....... ........ */
                /* target/loongarch/insns.decode:1815 */
                return LISA_XVILVL_H;
            case 0x6:
                /* 01110101 00011011 0....... ........ */
                /* target/loongarch/insns.decode:1816 */
                return LISA_XVILVL_W;
            case 0x7:
                /* 01110101 00011011 1....... ........ */
                /* target/loongarch/insns.decode:1817 */
                return LISA_XVILVL_D;
            }
            break;
        case 0x47:
            /* 01110101 000111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 00011100 0....... ........ */
                /* target/loongarch/insns.decode:1818 */
                return LISA_XVILVH_B;
            case 0x1:
                /* 01110101 00011100 1....... ........ */
                /* target/loongarch/insns.decode:1819 */
                return LISA_XVILVH_H;
            case 0x2:
                /* 01110101 00011101 0....... ........ */
                /* target/loongarch/insns.decode:1820 */
                return LISA_XVILVH_W;
            case 0x3:
                /* 01110101 00011101 1....... ........ */
                /* target/loongarch/insns.decode:1821 */
                return LISA_XVILVH_D;
            case 0x4:
                /* 01110101 00011110 0....... ........ */
                /* target/loongarch/insns.decode:1822 */
                return LISA_XVPICKEV_B;
            case 0x5:
                /* 01110101 00011110 1....... ........ */
                /* target/loongarch/insns.decode:1823 */
                return LISA_XVPICKEV_H;
            case 0x6:
                /* 01110101 00011111 0....... ........ */
                /* target/loongarch/insns.decode:1824 */
                return LISA_XVPICKEV_W;
            case 0x7:
                /* 01110101 00011111 1....... ........ */
                /* target/loongarch/insns.decode:1825 */
                return LISA_XVPICKEV_D;
            }
            break;
        case 0x48:
            /* 01110101 001000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 00100000 0....... ........ */
                /* target/loongarch/insns.decode:1826 */
                return LISA_XVPICKOD_B;
            case 0x1:
                /* 01110101 00100000 1....... ........ */
                /* target/loongarch/insns.decode:1827 */
                return LISA_XVPICKOD_H;
            case 0x2:
                /* 01110101 00100001 0....... ........ */
                /* target/loongarch/insns.decode:1828 */
                return LISA_XVPICKOD_W;
            case 0x3:
                /* 01110101 00100001 1....... ........ */
                /* target/loongarch/insns.decode:1829 */
                return LISA_XVPICKOD_D;
            case 0x4:
                /* 01110101 00100010 0....... ........ */
                /* target/loongarch/insns.decode:1830 */
                return LISA_XVREPLVE_B;
            case 0x5:
                /* 01110101 00100010 1....... ........ */
                /* target/loongarch/insns.decode:1831 */
                return LISA_XVREPLVE_H;
            case 0x6:
                /* 01110101 00100011 0....... ........ */
                /* target/loongarch/insns.decode:1832 */
                return LISA_XVREPLVE_W;
            case 0x7:
                /* 01110101 00100011 1....... ........ */
                /* target/loongarch/insns.decode:1833 */
                return LISA_XVREPLVE_D;
            }
            break;
        case 0x49:
            /* 01110101 001001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x4:
                /* 01110101 00100110 0....... ........ */
                /* target/loongarch/insns.decode:1834 */
                return LISA_XVAND_V;
            case 0x5:
                /* 01110101 00100110 1....... ........ */
                /* target/loongarch/insns.decode:1835 */
                return LISA_XVOR_V;
            case 0x6:
                /* 01110101 00100111 0....... ........ */
                /* target/loongarch/insns.decode:1836 */
                return LISA_XVXOR_V;
            case 0x7:
                /* 01110101 00100111 1....... ........ */
                /* target/loongarch/insns.decode:1837 */
                return LISA_XVNOR_V;
            }
            break;
        case 0x4a:
            /* 01110101 001010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 00101000 0....... ........ */
                /* target/loongarch/insns.decode:1838 */
                return LISA_XVANDN_V;
            case 0x1:
                /* 01110101 00101000 1....... ........ */
                /* target/loongarch/insns.decode:1839 */
                return LISA_XVORN_V;
            case 0x6:
                /* 01110101 00101011 0....... ........ */
                /* target/loongarch/insns.decode:1840 */
                return LISA_XVFRSTP_B;
            case 0x7:
                /* 01110101 00101011 1....... ........ */
                /* target/loongarch/insns.decode:1841 */
                return LISA_XVFRSTP_H;
            }
            break;
        case 0x4b:
            /* 01110101 001011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x2:
                /* 01110101 00101101 0....... ........ */
                /* target/loongarch/insns.decode:1842 */
                return LISA_XVADD_Q;
            case 0x3:
                /* 01110101 00101101 1....... ........ */
                /* target/loongarch/insns.decode:1843 */
                return LISA_XVSUB_Q;
            case 0x4:
                /* 01110101 00101110 0....... ........ */
                /* target/loongarch/insns.decode:1844 */
                return LISA_XVSIGNCOV_B;
            case 0x5:
                /* 01110101 00101110 1....... ........ */
                /* target/loongarch/insns.decode:1845 */
                return LISA_XVSIGNCOV_H;
            case 0x6:
                /* 01110101 00101111 0....... ........ */
                /* target/loongarch/insns.decode:1846 */
                return LISA_XVSIGNCOV_W;
            case 0x7:
                /* 01110101 00101111 1....... ........ */
                /* target/loongarch/insns.decode:1847 */
                return LISA_XVSIGNCOV_D;
            }
            break;
        case 0x4c:
            /* 01110101 001100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110101 00110000 1....... ........ */
                /* target/loongarch/insns.decode:1848 */
                return LISA_XVFADD_S;
            case 0x2:
                /* 01110101 00110001 0....... ........ */
                /* target/loongarch/insns.decode:1849 */
                return LISA_XVFADD_D;
            case 0x5:
                /* 01110101 00110010 1....... ........ */
                /* target/loongarch/insns.decode:1850 */
                return LISA_XVFSUB_S;
            case 0x6:
                /* 01110101 00110011 0....... ........ */
                /* target/loongarch/insns.decode:1851 */
                return LISA_XVFSUB_D;
            }
            break;
        case 0x4d:
            /* 01110101 001101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110101 00110100 1....... ........ */
                /* target/loongarch/insns.decode:1852 */
                return LISA_XVFADDSUB_S;
            case 0x2:
                /* 01110101 00110101 0....... ........ */
                /* target/loongarch/insns.decode:1853 */
                return LISA_XVFADDSUB_D;
            case 0x5:
                /* 01110101 00110110 1....... ........ */
                /* target/loongarch/insns.decode:1854 */
                return LISA_XVFSUBADD_S;
            case 0x6:
                /* 01110101 00110111 0....... ........ */
                /* target/loongarch/insns.decode:1855 */
                return LISA_XVFSUBADD_D;
            }
            break;
        case 0x4e:
            /* 01110101 001110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110101 00111000 1....... ........ */
                /* target/loongarch/insns.decode:1856 */
                return LISA_XVFMUL_S;
            case 0x2:
                /* 01110101 00111001 0....... ........ */
                /* target/loongarch/insns.decode:1857 */
                return LISA_XVFMUL_D;
            case 0x5:
                /* 01110101 00111010 1....... ........ */
                /* target/loongarch/insns.decode:1858 */
                return LISA_XVFDIV_S;
            case 0x6:
                /* 01110101 00111011 0....... ........ */
                /* target/loongarch/insns.decode:1859 */
                return LISA_XVFDIV_D;
            }
            break;
        case 0x4f:
            /* 01110101 001111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110101 00111100 1....... ........ */
                /* target/loongarch/insns.decode:1860 */
                return LISA_XVFMAX_S;
            case 0x2:
                /* 01110101 00111101 0....... ........ */
                /* target/loongarch/insns.decode:1861 */
                return LISA_XVFMAX_D;
            case 0x5:
                /* 01110101 00111110 1....... ........ */
                /* target/loongarch/insns.decode:1862 */
                return LISA_XVFMIN_S;
            case 0x6:
                /* 01110101 00111111 0....... ........ */
                /* target/loongarch/insns.decode:1863 */
                return LISA_XVFMIN_D;
            }
            break;
        case 0x50:
            /* 01110101 010000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110101 01000000 1....... ........ */
                /* target/loongarch/insns.decode:1864 */
                return LISA_XVFMAXA_S;
            case 0x2:
                /* 01110101 01000001 0....... ........ */
                /* target/loongarch/insns.decode:1865 */
                return LISA_XVFMAXA_D;
            case 0x5:
                /* 01110101 01000010 1....... ........ */
                /* target/loongarch/insns.decode:1866 */
                return LISA_XVFMINA_S;
            case 0x6:
                /* 01110101 01000011 0....... ........ */
                /* target/loongarch/insns.decode:1867 */
                return LISA_XVFMINA_D;
            }
            break;
        case 0x51:
            /* 01110101 010001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x1:
                /* 01110101 01000100 1....... ........ */
                /* target/loongarch/insns.decode:1868 */
                return LISA_XVFSCALEB_S;
            case 0x2:
                /* 01110101 01000101 0....... ........ */
                /* target/loongarch/insns.decode:1869 */
                return LISA_XVFSCALEB_D;
            case 0x4:
                /* 01110101 01000110 0....... ........ */
                /* target/loongarch/insns.decode:1870 */
                return LISA_XVFCVT_H_S;
            case 0x5:
                /* 01110101 01000110 1....... ........ */
                /* target/loongarch/insns.decode:1871 */
                return LISA_XVFCVT_S_D;
            }
            break;
        case 0x52:
            /* 01110101 010010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 01001000 0....... ........ */
                /* target/loongarch/insns.decode:1872 */
                return LISA_XVFFINT_S_L;
            case 0x3:
                /* 01110101 01001001 1....... ........ */
                /* target/loongarch/insns.decode:1873 */
                return LISA_XVFTINT_W_D;
            case 0x4:
                /* 01110101 01001010 0....... ........ */
                /* target/loongarch/insns.decode:1874 */
                return LISA_XVFTINTRM_W_D;
            case 0x5:
                /* 01110101 01001010 1....... ........ */
                /* target/loongarch/insns.decode:1875 */
                return LISA_XVFTINTRP_W_D;
            case 0x6:
                /* 01110101 01001011 0....... ........ */
                /* target/loongarch/insns.decode:1876 */
                return LISA_XVFTINTRZ_W_D;
            case 0x7:
                /* 01110101 01001011 1....... ........ */
                /* target/loongarch/insns.decode:1877 */
                return LISA_XVFTINTRNE_W_D;
            }
            break;
        case 0x53:
            /* 01110101 010011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x5:
                /* 01110101 01001110 1....... ........ */
                /* target/loongarch/insns.decode:1878 */
                return LISA_XVHADD4_H_BU;
            case 0x6:
                /* 01110101 01001111 0....... ........ */
                /* target/loongarch/insns.decode:1879 */
                return LISA_XVSHUF4_W;
            case 0x7:
                /* 01110101 01001111 1....... ........ */
                /* target/loongarch/insns.decode:1880 */
                return LISA_XVSHUF2_D;
            }
            break;
        case 0x58:
            /* 01110101 011000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 01100000 0....... ........ */
                /* target/loongarch/insns.decode:1881 */
                return LISA_XVPMUL_W;
            case 0x1:
                /* 01110101 01100000 1....... ........ */
                /* target/loongarch/insns.decode:1882 */
                return LISA_XVPMUL_D;
            case 0x2:
                /* 01110101 01100001 0....... ........ */
                /* target/loongarch/insns.decode:1883 */
                return LISA_XVPMUH_W;
            case 0x3:
                /* 01110101 01100001 1....... ........ */
                /* target/loongarch/insns.decode:1884 */
                return LISA_XVPMUH_D;
            case 0x4:
                /* 01110101 01100010 0....... ........ */
                /* target/loongarch/insns.decode:1885 */
                return LISA_XVPMULACC_W;
            case 0x5:
                /* 01110101 01100010 1....... ........ */
                /* target/loongarch/insns.decode:1886 */
                return LISA_XVPMULACC_D;
            case 0x6:
                /* 01110101 01100011 0....... ........ */
                /* target/loongarch/insns.decode:1887 */
                return LISA_XVPMUHACC_W;
            case 0x7:
                /* 01110101 01100011 1....... ........ */
                /* target/loongarch/insns.decode:1888 */
                return LISA_XVPMUHACC_D;
            }
            break;
        case 0x59:
            /* 01110101 011001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 01100100 0....... ........ */
                /* target/loongarch/insns.decode:1889 */
                return LISA_XVPMULWL_H_B;
            case 0x1:
                /* 01110101 01100100 1....... ........ */
                /* target/loongarch/insns.decode:1890 */
                return LISA_XVPMULWL_W_H;
            case 0x2:
                /* 01110101 01100101 0....... ........ */
                /* target/loongarch/insns.decode:1891 */
                return LISA_XVPMULWL_D_W;
            case 0x3:
                /* 01110101 01100101 1....... ........ */
                /* target/loongarch/insns.decode:1892 */
                return LISA_XVPMULWL_Q_D;
            case 0x4:
                /* 01110101 01100110 0....... ........ */
                /* target/loongarch/insns.decode:1893 */
                return LISA_XVPMULWH_H_B;
            case 0x5:
                /* 01110101 01100110 1....... ........ */
                /* target/loongarch/insns.decode:1894 */
                return LISA_XVPMULWH_W_H;
            case 0x6:
                /* 01110101 01100111 0....... ........ */
                /* target/loongarch/insns.decode:1895 */
                return LISA_XVPMULWH_D_W;
            case 0x7:
                /* 01110101 01100111 1....... ........ */
                /* target/loongarch/insns.decode:1896 */
                return LISA_XVPMULWH_Q_D;
            }
            break;
        case 0x5a:
            /* 01110101 011010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 01101000 0....... ........ */
                /* target/loongarch/insns.decode:1897 */
                return LISA_XVPMADDWL_H_B;
            case 0x1:
                /* 01110101 01101000 1....... ........ */
                /* target/loongarch/insns.decode:1898 */
                return LISA_XVPMADDWL_W_H;
            case 0x2:
                /* 01110101 01101001 0....... ........ */
                /* target/loongarch/insns.decode:1899 */
                return LISA_XVPMADDWL_D_W;
            case 0x3:
                /* 01110101 01101001 1....... ........ */
                /* target/loongarch/insns.decode:1900 */
                return LISA_XVPMADDWL_Q_D;
            case 0x4:
                /* 01110101 01101010 0....... ........ */
                /* target/loongarch/insns.decode:1901 */
                return LISA_XVPMADDWH_H_B;
            case 0x5:
                /* 01110101 01101010 1....... ........ */
                /* target/loongarch/insns.decode:1902 */
                return LISA_XVPMADDWH_W_H;
            case 0x6:
                /* 01110101 01101011 0....... ........ */
                /* target/loongarch/insns.decode:1903 */
                return LISA_XVPMADDWH_D_W;
            case 0x7:
                /* 01110101 01101011 1....... ........ */
                /* target/loongarch/insns.decode:1904 */
                return LISA_XVPMADDWH_Q_D;
            }
            break;
        case 0x5b:
            /* 01110101 011011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 01101100 0....... ........ */
                /* target/loongarch/insns.decode:1905 */
                return LISA_XVPDP2_Q_D;
            case 0x1:
                /* 01110101 01101100 1....... ........ */
                /* target/loongarch/insns.decode:1906 */
                return LISA_XVPDP2ADD_Q_D;
            }
            break;
        case 0x5c:
            /* 01110101 011100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110101 01110000 0....... ........ */
                /* target/loongarch/insns.decode:1907 */
                return LISA_XVCDP4_RE_D_H;
            case 0x1:
                /* 01110101 01110000 1....... ........ */
                /* target/loongarch/insns.decode:1908 */
                return LISA_XVCDP4_IM_D_H;
            case 0x2:
                /* 01110101 01110001 0....... ........ */
                /* target/loongarch/insns.decode:1909 */
                return LISA_XVCDP4ADD_RE_D_H;
            case 0x3:
                /* 01110101 01110001 1....... ........ */
                /* target/loongarch/insns.decode:1910 */
                return LISA_XVCDP4ADD_IM_D_H;
            case 0x4:
                /* 01110101 01110010 0....... ........ */
                /* target/loongarch/insns.decode:1911 */
                return LISA_XVCDP2_RE_Q_W;
            case 0x5:
                /* 01110101 01110010 1....... ........ */
                /* target/loongarch/insns.decode:1912 */
                return LISA_XVCDP2_IM_Q_W;
            case 0x6:
                /* 01110101 01110011 0....... ........ */
                /* target/loongarch/insns.decode:1913 */
                return LISA_XVCDP2ADD_RE_Q_W;
            case 0x7:
                /* 01110101 01110011 1....... ........ */
                /* target/loongarch/insns.decode:1914 */
                return LISA_XVCDP2ADD_IM_Q_W;
            }
            break;
        case 0x5e:
            /* 01110101 011110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x2:
                /* 01110101 01111001 0....... ........ */
                /* target/loongarch/insns.decode:1915 */
                return LISA_XVSIGNSEL_W;
            case 0x3:
                /* 01110101 01111001 1....... ........ */
                /* target/loongarch/insns.decode:1916 */
                return LISA_XVSIGNSEL_D;
            case 0x5:
                /* 01110101 01111010 1....... ........ */
                /* target/loongarch/insns.decode:1917 */
                return LISA_XVSHUF_H;
            case 0x6:
                /* 01110101 01111011 0....... ........ */
                /* target/loongarch/insns.decode:1918 */
                return LISA_XVSHUF_W;
            case 0x7:
                /* 01110101 01111011 1....... ........ */
                /* target/loongarch/insns.decode:1919 */
                return LISA_XVSHUF_D;
            }
            break;
        case 0x5f:
            /* 01110101 011111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x2:
                /* 01110101 01111101 0....... ........ */
                /* target/loongarch/insns.decode:1920 */
                return LISA_XVPERM_W;
            }
            break;
        case 0xa0:
            /* 01110110 100000.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110110 10000000 0....... ........ */
                /* target/loongarch/insns.decode:1921 */
                return LISA_XVSEQI_B;
            case 0x1:
                /* 01110110 10000000 1....... ........ */
                /* target/loongarch/insns.decode:1922 */
                return LISA_XVSEQI_H;
            case 0x2:
                /* 01110110 10000001 0....... ........ */
                /* target/loongarch/insns.decode:1923 */
                return LISA_XVSEQI_W;
            case 0x3:
                /* 01110110 10000001 1....... ........ */
                /* target/loongarch/insns.decode:1924 */
                return LISA_XVSEQI_D;
            case 0x4:
                /* 01110110 10000010 0....... ........ */
                /* target/loongarch/insns.decode:1925 */
                return LISA_XVSLEI_B;
            case 0x5:
                /* 01110110 10000010 1....... ........ */
                /* target/loongarch/insns.decode:1926 */
                return LISA_XVSLEI_H;
            case 0x6:
                /* 01110110 10000011 0....... ........ */
                /* target/loongarch/insns.decode:1927 */
                return LISA_XVSLEI_W;
            case 0x7:
                /* 01110110 10000011 1....... ........ */
                /* target/loongarch/insns.decode:1928 */
                return LISA_XVSLEI_D;
            }
            break;
        case 0xa1:
            /* 01110110 100001.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110110 10000100 0....... ........ */
                /* target/loongarch/insns.decode:1929 */
                return LISA_XVSLEI_BU;
            case 0x1:
                /* 01110110 10000100 1....... ........ */
                /* target/loongarch/insns.decode:1930 */
                return LISA_XVSLEI_HU;
            case 0x2:
                /* 01110110 10000101 0....... ........ */
                /* target/loongarch/insns.decode:1931 */
                return LISA_XVSLEI_WU;
            case 0x3:
                /* 01110110 10000101 1....... ........ */
                /* target/loongarch/insns.decode:1932 */
                return LISA_XVSLEI_DU;
            case 0x4:
                /* 01110110 10000110 0....... ........ */
                /* target/loongarch/insns.decode:1933 */
                return LISA_XVSLTI_B;
            case 0x5:
                /* 01110110 10000110 1....... ........ */
                /* target/loongarch/insns.decode:1934 */
                return LISA_XVSLTI_H;
            case 0x6:
                /* 01110110 10000111 0....... ........ */
                /* target/loongarch/insns.decode:1935 */
                return LISA_XVSLTI_W;
            case 0x7:
                /* 01110110 10000111 1....... ........ */
                /* target/loongarch/insns.decode:1936 */
                return LISA_XVSLTI_D;
            }
            break;
        case 0xa2:
            /* 01110110 100010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110110 10001000 0....... ........ */
                /* target/loongarch/insns.decode:1937 */
                return LISA_XVSLTI_BU;
            case 0x1:
                /* 01110110 10001000 1....... ........ */
                /* target/loongarch/insns.decode:1938 */
                return LISA_XVSLTI_HU;
            case 0x2:
                /* 01110110 10001001 0....... ........ */
                /* target/loongarch/insns.decode:1939 */
                return LISA_XVSLTI_WU;
            case 0x3:
                /* 01110110 10001001 1....... ........ */
                /* target/loongarch/insns.decode:1940 */
                return LISA_XVSLTI_DU;
            case 0x4:
                /* 01110110 10001010 0....... ........ */
                /* target/loongarch/insns.decode:1941 */
                return LISA_XVADDI_BU;
            case 0x5:
                /* 01110110 10001010 1....... ........ */
                /* target/loongarch/insns.decode:1942 */
                return LISA_XVADDI_HU;
            case 0x6:
                /* 01110110 10001011 0....... ........ */
                /* target/loongarch/insns.decode:1943 */
                return LISA_XVADDI_WU;
            case 0x7:
                /* 01110110 10001011 1....... ........ */
                /* target/loongarch/insns.decode:1944 */
                return LISA_XVADDI_DU;
            }
            break;
        case 0xa3:
            /* 01110110 100011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110110 10001100 0....... ........ */
                /* target/loongarch/insns.decode:1945 */
                return LISA_XVSUBI_BU;
            case 0x1:
                /* 01110110 10001100 1....... ........ */
                /* target/loongarch/insns.decode:1946 */
                return LISA_XVSUBI_HU;
            case 0x2:
                /* 01110110 10001101 0....... ........ */
                /* target/loongarch/insns.decode:1947 */
                return LISA_XVSUBI_WU;
            case 0x3:
                /* 01110110 10001101 1....... ........ */
                /* target/loongarch/insns.decode:1948 */
                return LISA_XVSUBI_DU;
            case 0x4:
                /* 01110110 10001110 0....... ........ */
                /* target/loongarch/insns.decode:1949 */
                return LISA_XVBSLL_V;
            case 0x5:
                /* 01110110 10001110 1....... ........ */
                /* target/loongarch/insns.decode:1950 */
                return LISA_XVBSRL_V;
            }
            break;
        case 0xa4:
            /* 01110110 100100.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110110 10010000 0....... ........ */
                /* target/loongarch/insns.decode:1951 */
                return LISA_XVMAXI_B;
            case 0x1:
                /* 01110110 10010000 1....... ........ */
                /* target/loongarch/insns.decode:1952 */
                return LISA_XVMAXI_H;
            case 0x2:
                /* 01110110 10010001 0....... ........ */
                /* target/loongarch/insns.decode:1953 */
                return LISA_XVMAXI_W;
            case 0x3:
                /* 01110110 10010001 1....... ........ */
                /* target/loongarch/insns.decode:1954 */
                return LISA_XVMAXI_D;
            case 0x4:
                /* 01110110 10010010 0....... ........ */
                /* target/loongarch/insns.decode:1955 */
                return LISA_XVMINI_B;
            case 0x5:
                /* 01110110 10010010 1....... ........ */
                /* target/loongarch/insns.decode:1956 */
                return LISA_XVMINI_H;
            case 0x6:
                /* 01110110 10010011 0....... ........ */
                /* target/loongarch/insns.decode:1957 */
                return LISA_XVMINI_W;
            case 0x7:
                /* 01110110 10010011 1....... ........ */
                /* target/loongarch/insns.decode:1958 */
                return LISA_XVMINI_D;
            }
            break;
        case 0xa5:
            /* 01110110 100101.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110110 10010100 0....... ........ */
                /* target/loongarch/insns.decode:1959 */
                return LISA_XVMAXI_BU;
            case 0x1:
                /* 01110110 10010100 1....... ........ */
                /* target/loongarch/insns.decode:1960 */
                return LISA_XVMAXI_HU;
            case 0x2:
                /* 01110110 10010101 0....... ........ */
                /* target/loongarch/insns.decode:1961 */
                return LISA_XVMAXI_WU;
            case 0x3:
                /* 01110110 10010101 1....... ........ */
                /* target/loongarch/insns.decode:1962 */
                return LISA_XVMAXI_DU;
            case 0x4:
                /* 01110110 10010110 0....... ........ */
                /* target/loongarch/insns.decode:1963 */
                return LISA_XVMINI_BU;
            case 0x5:
                /* 01110110 10010110 1....... ........ */
                /* target/loongarch/insns.decode:1964 */
                return LISA_XVMINI_HU;
            case 0x6:
                /* 01110110 10010111 0....... ........ */
                /* target/loongarch/insns.decode:1965 */
                return LISA_XVMINI_WU;
            case 0x7:
                /* 01110110 10010111 1....... ........ */
                /* target/loongarch/insns.decode:1966 */
                return LISA_XVMINI_DU;
            }
            break;
        case 0xa6:
            /* 01110110 100110.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110110 10011000 0....... ........ */
                /* target/loongarch/insns.decode:1967 */
                return LISA_XVRANDSIGNI_B;
            case 0x1:
                /* 01110110 10011000 1....... ........ */
                /* target/loongarch/insns.decode:1968 */
                return LISA_XVRANDSIGNI_H;
            case 0x2:
                /* 01110110 10011001 0....... ........ */
                /* target/loongarch/insns.decode:1969 */
                return LISA_XVRORSIGNI_B;
            case 0x3:
                /* 01110110 10011001 1....... ........ */
                /* target/loongarch/insns.decode:1970 */
                return LISA_XVRORSIGNI_H;
            case 0x4:
                /* 01110110 10011010 0....... ........ */
                /* target/loongarch/insns.decode:1971 */
                return LISA_XVFRSTPI_B;
            case 0x5:
                /* 01110110 10011010 1....... ........ */
                /* target/loongarch/insns.decode:1972 */
                return LISA_XVFRSTPI_H;
            case 0x6:
                /* 01110110 10011011 0....... ........ */
                /* target/loongarch/insns.decode:1973 */
                return LISA_XVCLRSTRI_V;
            case 0x7:
                /* 01110110 10011011 1....... ........ */
                /* target/loongarch/insns.decode:1974 */
                return LISA_XVMEPATMSK_V;
            }
            break;
        case 0xa7:
            /* 01110110 100111.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110110 10011100 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x0:
                    /* 01110110 10011100 000000.. ........ */
                    /* target/loongarch/insns.decode:1975 */
                    return LISA_XVCLO_B;
                case 0x1:
                    /* 01110110 10011100 000001.. ........ */
                    /* target/loongarch/insns.decode:1976 */
                    return LISA_XVCLO_H;
                case 0x2:
                    /* 01110110 10011100 000010.. ........ */
                    /* target/loongarch/insns.decode:1977 */
                    return LISA_XVCLO_W;
                case 0x3:
                    /* 01110110 10011100 000011.. ........ */
                    /* target/loongarch/insns.decode:1978 */
                    return LISA_XVCLO_D;
                case 0x4:
                    /* 01110110 10011100 000100.. ........ */
                    /* target/loongarch/insns.decode:1979 */
                    return LISA_XVCLZ_B;
                case 0x5:
                    /* 01110110 10011100 000101.. ........ */
                    /* target/loongarch/insns.decode:1980 */
                    return LISA_XVCLZ_H;
                case 0x6:
                    /* 01110110 10011100 000110.. ........ */
                    /* target/loongarch/insns.decode:1981 */
                    return LISA_XVCLZ_W;
                case 0x7:
                    /* 01110110 10011100 000111.. ........ */
                    /* target/loongarch/insns.decode:1982 */
                    return LISA_XVCLZ_D;
                case 0x8:
                    /* 01110110 10011100 001000.. ........ */
                    /* target/loongarch/insns.decode:1983 */
                    return LISA_XVPCNT_B;
                case 0x9:
                    /* 01110110 10011100 001001.. ........ */
                    /* target/loongarch/insns.decode:1984 */
                    return LISA_XVPCNT_H;
                case 0xa:
                    /* 01110110 10011100 001010.. ........ */
                    /* target/loongarch/insns.decode:1985 */
                    return LISA_XVPCNT_W;
                case 0xb:
                    /* 01110110 10011100 001011.. ........ */
                    /* target/loongarch/insns.decode:1986 */
                    return LISA_XVPCNT_D;
                case 0xc:
                    /* 01110110 10011100 001100.. ........ */
                    /* target/loongarch/insns.decode:1987 */
                    return LISA_XVNEG_B;
                case 0xd:
                    /* 01110110 10011100 001101.. ........ */
                    /* target/loongarch/insns.decode:1988 */
                    return LISA_XVNEG_H;
                case 0xe:
                    /* 01110110 10011100 001110.. ........ */
                    /* target/loongarch/insns.decode:1989 */
                    return LISA_XVNEG_W;
                case 0xf:
                    /* 01110110 10011100 001111.. ........ */
                    /* target/loongarch/insns.decode:1990 */
                    return LISA_XVNEG_D;
                case 0x10:
                    /* 01110110 10011100 010000.. ........ */
                    /* target/loongarch/insns.decode:1991 */
                    return LISA_XVMSKLTZ_B;
                case 0x11:
                    /* 01110110 10011100 010001.. ........ */
                    /* target/loongarch/insns.decode:1992 */
                    return LISA_XVMSKLTZ_H;
                case 0x12:
                    /* 01110110 10011100 010010.. ........ */
                    /* target/loongarch/insns.decode:1993 */
                    return LISA_XVMSKLTZ_W;
                case 0x13:
                    /* 01110110 10011100 010011.. ........ */
                    /* target/loongarch/insns.decode:1994 */
                    return LISA_XVMSKLTZ_D;
                case 0x14:
                    /* 01110110 10011100 010100.. ........ */
                    /* target/loongarch/insns.decode:1995 */
                    return LISA_XVMSKGEZ_B;
                case 0x18:
                    /* 01110110 10011100 011000.. ........ */
                    /* target/loongarch/insns.decode:1996 */
                    return LISA_XVMSKNZ_B;
                case 0x1c:
                    /* 01110110 10011100 011100.. ........ */
                    /* target/loongarch/insns.decode:1997 */
                    return LISA_XVMSKCOPY_B;
                }
                break;
            case 0x1:
                /* 01110110 10011100 1....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x0:
                    /* 01110110 10011100 100000.. ........ */
                    /* target/loongarch/insns.decode:1998 */
                    return LISA_XVMSKFILL_B;
                case 0x4:
                    /* 01110110 10011100 100100.. ........ */
                    /* target/loongarch/insns.decode:1999 */
                    return LISA_XVFRSTM_B;
                case 0x5:
                    /* 01110110 10011100 100101.. ........ */
                    /* target/loongarch/insns.decode:2000 */
                    return LISA_XVFRSTM_H;
                case 0x6:
                    /* 01110110 10011100 100110.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 01110110 10011100 100110.. ...00... */
                        /* target/loongarch/insns.decode:2001 */
                        return LISA_XVSETEQZ_V;
                    }
                    break;
                case 0x7:
                    /* 01110110 10011100 100111.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 01110110 10011100 100111.. ...00... */
                        /* target/loongarch/insns.decode:2002 */
                        return LISA_XVSETNEZ_V;
                    }
                    break;
                case 0x8:
                    /* 01110110 10011100 101000.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 01110110 10011100 101000.. ...00... */
                        /* target/loongarch/insns.decode:2003 */
                        return LISA_XVSETANYEQZ_B;
                    }
                    break;
                case 0x9:
                    /* 01110110 10011100 101001.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 01110110 10011100 101001.. ...00... */
                        /* target/loongarch/insns.decode:2004 */
                        return LISA_XVSETANYEQZ_H;
                    }
                    break;
                case 0xa:
                    /* 01110110 10011100 101010.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 01110110 10011100 101010.. ...00... */
                        /* target/loongarch/insns.decode:2005 */
                        return LISA_XVSETANYEQZ_W;
                    }
                    break;
                case 0xb:
                    /* 01110110 10011100 101011.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 01110110 10011100 101011.. ...00... */
                        /* target/loongarch/insns.decode:2006 */
                        return LISA_XVSETANYEQZ_D;
                    }
                    break;
                case 0xc:
                    /* 01110110 10011100 101100.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 01110110 10011100 101100.. ...00... */
                        /* target/loongarch/insns.decode:2007 */
                        return LISA_XVSETALLNEZ_B;
                    }
                    break;
                case 0xd:
                    /* 01110110 10011100 101101.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 01110110 10011100 101101.. ...00... */
                        /* target/loongarch/insns.decode:2008 */
                        return LISA_XVSETALLNEZ_H;
                    }
                    break;
                case 0xe:
                    /* 01110110 10011100 101110.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 01110110 10011100 101110.. ...00... */
                        /* target/loongarch/insns.decode:2009 */
                        return LISA_XVSETALLNEZ_W;
                    }
                    break;
                case 0xf:
                    /* 01110110 10011100 101111.. ........ */
                    switch ((insn >> 3) & 0x3) {
                    case 0x0:
                        /* 01110110 10011100 101111.. ...00... */
                        /* target/loongarch/insns.decode:2010 */
                        return LISA_XVSETALLNEZ_D;
                    }
                    break;
                case 0x11:
                    /* 01110110 10011100 110001.. ........ */
                    /* target/loongarch/insns.decode:2011 */
                    return LISA_XVFLOGB_S;
                case 0x12:
                    /* 01110110 10011100 110010.. ........ */
                    /* target/loongarch/insns.decode:2012 */
                    return LISA_XVFLOGB_D;
                case 0x15:
                    /* 01110110 10011100 110101.. ........ */
                    /* target/loongarch/insns.decode:2013 */
                    return LISA_XVFCLASS_S;
                case 0x16:
                    /* 01110110 10011100 110110.. ........ */
                    /* target/loongarch/insns.decode:2014 */
                    return LISA_XVFCLASS_D;
                case 0x19:
                    /* 01110110 10011100 111001.. ........ */
                    /* target/loongarch/insns.decode:2015 */
                    return LISA_XVFSQRT_S;
                case 0x1a:
                    /* 01110110 10011100 111010.. ........ */
                    /* target/loongarch/insns.decode:2016 */
                    return LISA_XVFSQRT_D;
                case 0x1d:
                    /* 01110110 10011100 111101.. ........ */
                    /* target/loongarch/insns.decode:2017 */
                    return LISA_XVFRECIP_S;
                case 0x1e:
                    /* 01110110 10011100 111110.. ........ */
                    /* target/loongarch/insns.decode:2018 */
                    return LISA_XVFRECIP_D;
                }
                break;
            case 0x2:
                /* 01110110 10011101 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x1:
                    /* 01110110 10011101 000001.. ........ */
                    /* target/loongarch/insns.decode:2019 */
                    return LISA_XVFRSQRT_S;
                case 0x2:
                    /* 01110110 10011101 000010.. ........ */
                    /* target/loongarch/insns.decode:2020 */
                    return LISA_XVFRSQRT_D;
                case 0xd:
                    /* 01110110 10011101 001101.. ........ */
                    /* target/loongarch/insns.decode:2021 */
                    return LISA_XVFRINT_S;
                case 0xe:
                    /* 01110110 10011101 001110.. ........ */
                    /* target/loongarch/insns.decode:2022 */
                    return LISA_XVFRINT_D;
                case 0x11:
                    /* 01110110 10011101 010001.. ........ */
                    /* target/loongarch/insns.decode:2023 */
                    return LISA_XVFRINTRM_S;
                case 0x12:
                    /* 01110110 10011101 010010.. ........ */
                    /* target/loongarch/insns.decode:2024 */
                    return LISA_XVFRINTRM_D;
                case 0x15:
                    /* 01110110 10011101 010101.. ........ */
                    /* target/loongarch/insns.decode:2025 */
                    return LISA_XVFRINTRP_S;
                case 0x16:
                    /* 01110110 10011101 010110.. ........ */
                    /* target/loongarch/insns.decode:2026 */
                    return LISA_XVFRINTRP_D;
                case 0x19:
                    /* 01110110 10011101 011001.. ........ */
                    /* target/loongarch/insns.decode:2027 */
                    return LISA_XVFRINTRZ_S;
                case 0x1a:
                    /* 01110110 10011101 011010.. ........ */
                    /* target/loongarch/insns.decode:2028 */
                    return LISA_XVFRINTRZ_D;
                case 0x1d:
                    /* 01110110 10011101 011101.. ........ */
                    /* target/loongarch/insns.decode:2029 */
                    return LISA_XVFRINTRNE_S;
                case 0x1e:
                    /* 01110110 10011101 011110.. ........ */
                    /* target/loongarch/insns.decode:2030 */
                    return LISA_XVFRINTRNE_D;
                }
                break;
            case 0x3:
                /* 01110110 10011101 1....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x1:
                    /* 01110110 10011101 100001.. ........ */
                    /* target/loongarch/insns.decode:2031 */
                    return LISA_XVEXTL_W_B;
                case 0x2:
                    /* 01110110 10011101 100010.. ........ */
                    /* target/loongarch/insns.decode:2032 */
                    return LISA_XVEXTL_D_B;
                case 0x5:
                    /* 01110110 10011101 100101.. ........ */
                    /* target/loongarch/insns.decode:2033 */
                    return LISA_XVEXTL_D_H;
                case 0xb:
                    /* 01110110 10011101 101011.. ........ */
                    /* target/loongarch/insns.decode:2034 */
                    return LISA_XVEXTL_W_BU;
                case 0xc:
                    /* 01110110 10011101 101100.. ........ */
                    /* target/loongarch/insns.decode:2035 */
                    return LISA_XVEXTL_D_BU;
                case 0xf:
                    /* 01110110 10011101 101111.. ........ */
                    /* target/loongarch/insns.decode:2036 */
                    return LISA_XVEXTL_D_HU;
                case 0x14:
                    /* 01110110 10011101 110100.. ........ */
                    /* target/loongarch/insns.decode:2037 */
                    return LISA_XVHADD8_D_BU;
                case 0x15:
                    /* 01110110 10011101 110101.. ........ */
                    /* target/loongarch/insns.decode:2038 */
                    return LISA_XVHMINPOS_W_HU;
                case 0x16:
                    /* 01110110 10011101 110110.. ........ */
                    /* target/loongarch/insns.decode:2039 */
                    return LISA_XVHMINPOS_D_HU;
                case 0x17:
                    /* 01110110 10011101 110111.. ........ */
                    /* target/loongarch/insns.decode:2040 */
                    return LISA_XVHMINPOS_Q_HU;
                case 0x18:
                    /* 01110110 10011101 111000.. ........ */
                    /* target/loongarch/insns.decode:2041 */
                    return LISA_XVCLRTAIL_B;
                case 0x19:
                    /* 01110110 10011101 111001.. ........ */
                    /* target/loongarch/insns.decode:2042 */
                    return LISA_XVCLRTAIL_H;
                case 0x1a:
                    /* 01110110 10011101 111010.. ........ */
                    /* target/loongarch/insns.decode:2043 */
                    return LISA_XVFCVTL_S_H;
                case 0x1b:
                    /* 01110110 10011101 111011.. ........ */
                    /* target/loongarch/insns.decode:2044 */
                    return LISA_XVFCVTH_S_H;
                case 0x1c:
                    /* 01110110 10011101 111100.. ........ */
                    /* target/loongarch/insns.decode:2045 */
                    return LISA_XVFCVTL_D_S;
                case 0x1d:
                    /* 01110110 10011101 111101.. ........ */
                    /* target/loongarch/insns.decode:2046 */
                    return LISA_XVFCVTH_D_S;
                }
                break;
            case 0x4:
                /* 01110110 10011110 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x0:
                    /* 01110110 10011110 000000.. ........ */
                    /* target/loongarch/insns.decode:2047 */
                    return LISA_XVFFINT_S_W;
                case 0x1:
                    /* 01110110 10011110 000001.. ........ */
                    /* target/loongarch/insns.decode:2048 */
                    return LISA_XVFFINT_S_WU;
                case 0x2:
                    /* 01110110 10011110 000010.. ........ */
                    /* target/loongarch/insns.decode:2049 */
                    return LISA_XVFFINT_D_L;
                case 0x3:
                    /* 01110110 10011110 000011.. ........ */
                    /* target/loongarch/insns.decode:2050 */
                    return LISA_XVFFINT_D_LU;
                case 0x4:
                    /* 01110110 10011110 000100.. ........ */
                    /* target/loongarch/insns.decode:2051 */
                    return LISA_XVFFINTL_D_W;
                case 0x5:
                    /* 01110110 10011110 000101.. ........ */
                    /* target/loongarch/insns.decode:2052 */
                    return LISA_XVFFINTH_D_W;
                case 0xc:
                    /* 01110110 10011110 001100.. ........ */
                    /* target/loongarch/insns.decode:2053 */
                    return LISA_XVFTINT_W_S;
                case 0xd:
                    /* 01110110 10011110 001101.. ........ */
                    /* target/loongarch/insns.decode:2054 */
                    return LISA_XVFTINT_L_D;
                case 0xe:
                    /* 01110110 10011110 001110.. ........ */
                    /* target/loongarch/insns.decode:2055 */
                    return LISA_XVFTINTRM_W_S;
                case 0xf:
                    /* 01110110 10011110 001111.. ........ */
                    /* target/loongarch/insns.decode:2056 */
                    return LISA_XVFTINTRM_L_D;
                case 0x10:
                    /* 01110110 10011110 010000.. ........ */
                    /* target/loongarch/insns.decode:2057 */
                    return LISA_XVFTINTRP_W_S;
                case 0x11:
                    /* 01110110 10011110 010001.. ........ */
                    /* target/loongarch/insns.decode:2058 */
                    return LISA_XVFTINTRP_L_D;
                case 0x12:
                    /* 01110110 10011110 010010.. ........ */
                    /* target/loongarch/insns.decode:2059 */
                    return LISA_XVFTINTRZ_W_S;
                case 0x13:
                    /* 01110110 10011110 010011.. ........ */
                    /* target/loongarch/insns.decode:2060 */
                    return LISA_XVFTINTRZ_L_D;
                case 0x14:
                    /* 01110110 10011110 010100.. ........ */
                    /* target/loongarch/insns.decode:2061 */
                    return LISA_XVFTINTRNE_W_S;
                case 0x15:
                    /* 01110110 10011110 010101.. ........ */
                    /* target/loongarch/insns.decode:2062 */
                    return LISA_XVFTINTRNE_L_D;
                case 0x16:
                    /* 01110110 10011110 010110.. ........ */
                    /* target/loongarch/insns.decode:2063 */
                    return LISA_XVFTINT_WU_S;
                case 0x17:
                    /* 01110110 10011110 010111.. ........ */
                    /* target/loongarch/insns.decode:2064 */
                    return LISA_XVFTINT_LU_D;
                case 0x1c:
                    /* 01110110 10011110 011100.. ........ */
                    /* target/loongarch/insns.decode:2065 */
                    return LISA_XVFTINTRZ_WU_S;
                case 0x1d:
                    /* 01110110 10011110 011101.. ........ */
                    /* target/loongarch/insns.decode:2066 */
                    return LISA_XVFTINTRZ_LU_D;
                }
                break;
            case 0x5:
                /* 01110110 10011110 1....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x0:
                    /* 01110110 10011110 100000.. ........ */
                    /* target/loongarch/insns.decode:2067 */
                    return LISA_XVFTINTL_L_S;
                case 0x1:
                    /* 01110110 10011110 100001.. ........ */
                    /* target/loongarch/insns.decode:2068 */
                    return LISA_XVFTINTH_L_S;
                case 0x2:
                    /* 01110110 10011110 100010.. ........ */
                    /* target/loongarch/insns.decode:2069 */
                    return LISA_XVFTINTRML_L_S;
                case 0x3:
                    /* 01110110 10011110 100011.. ........ */
                    /* target/loongarch/insns.decode:2070 */
                    return LISA_XVFTINTRMH_L_S;
                case 0x4:
                    /* 01110110 10011110 100100.. ........ */
                    /* target/loongarch/insns.decode:2071 */
                    return LISA_XVFTINTRPL_L_S;
                case 0x5:
                    /* 01110110 10011110 100101.. ........ */
                    /* target/loongarch/insns.decode:2072 */
                    return LISA_XVFTINTRPH_L_S;
                case 0x6:
                    /* 01110110 10011110 100110.. ........ */
                    /* target/loongarch/insns.decode:2073 */
                    return LISA_XVFTINTRZL_L_S;
                case 0x7:
                    /* 01110110 10011110 100111.. ........ */
                    /* target/loongarch/insns.decode:2074 */
                    return LISA_XVFTINTRZH_L_S;
                case 0x8:
                    /* 01110110 10011110 101000.. ........ */
                    /* target/loongarch/insns.decode:2075 */
                    return LISA_XVFTINTRNEL_L_S;
                case 0x9:
                    /* 01110110 10011110 101001.. ........ */
                    /* target/loongarch/insns.decode:2076 */
                    return LISA_XVFTINTRNEH_L_S;
                case 0x18:
                    /* 01110110 10011110 111000.. ........ */
                    /* target/loongarch/insns.decode:2077 */
                    return LISA_XVEXTH_H_B;
                case 0x19:
                    /* 01110110 10011110 111001.. ........ */
                    /* target/loongarch/insns.decode:2078 */
                    return LISA_XVEXTH_W_H;
                case 0x1a:
                    /* 01110110 10011110 111010.. ........ */
                    /* target/loongarch/insns.decode:2079 */
                    return LISA_XVEXTH_D_W;
                case 0x1b:
                    /* 01110110 10011110 111011.. ........ */
                    /* target/loongarch/insns.decode:2080 */
                    return LISA_XVEXTH_Q_D;
                case 0x1c:
                    /* 01110110 10011110 111100.. ........ */
                    /* target/loongarch/insns.decode:2081 */
                    return LISA_XVEXTH_HU_BU;
                case 0x1d:
                    /* 01110110 10011110 111101.. ........ */
                    /* target/loongarch/insns.decode:2082 */
                    return LISA_XVEXTH_WU_HU;
                case 0x1e:
                    /* 01110110 10011110 111110.. ........ */
                    /* target/loongarch/insns.decode:2083 */
                    return LISA_XVEXTH_DU_WU;
                case 0x1f:
                    /* 01110110 10011110 111111.. ........ */
                    /* target/loongarch/insns.decode:2084 */
                    return LISA_XVEXTH_QU_DU;
                }
                break;
            case 0x6:
                /* 01110110 10011111 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x0:
                    /* 01110110 10011111 000000.. ........ */
                    /* target/loongarch/insns.decode:2085 */
                    return LISA_XVREPLGR2VR_B;
                case 0x1:
                    /* 01110110 10011111 000001.. ........ */
                    /* target/loongarch/insns.decode:2086 */
                    return LISA_XVREPLGR2VR_H;
                case 0x2:
                    /* 01110110 10011111 000010.. ........ */
                    /* target/loongarch/insns.decode:2087 */
                    return LISA_XVREPLGR2VR_W;
                case 0x3:
                    /* 01110110 10011111 000011.. ........ */
                    /* target/loongarch/insns.decode:2088 */
                    return LISA_XVREPLGR2VR_D;
                case 0x4:
                    /* 01110110 10011111 000100.. ........ */
                    /* target/loongarch/insns.decode:2089 */
                    return LISA_VEXT2XV_H_B;
                case 0x5:
                    /* 01110110 10011111 000101.. ........ */
                    /* target/loongarch/insns.decode:2090 */
                    return LISA_VEXT2XV_W_B;
                case 0x6:
                    /* 01110110 10011111 000110.. ........ */
                    /* target/loongarch/insns.decode:2091 */
                    return LISA_VEXT2XV_D_B;
                case 0x7:
                    /* 01110110 10011111 000111.. ........ */
                    /* target/loongarch/insns.decode:2092 */
                    return LISA_VEXT2XV_W_H;
                case 0x8:
                    /* 01110110 10011111 001000.. ........ */
                    /* target/loongarch/insns.decode:2093 */
                    return LISA_VEXT2XV_D_H;
                case 0x9:
                    /* 01110110 10011111 001001.. ........ */
                    /* target/loongarch/insns.decode:2094 */
                    return LISA_VEXT2XV_D_W;
                case 0xa:
                    /* 01110110 10011111 001010.. ........ */
                    /* target/loongarch/insns.decode:2095 */
                    return LISA_VEXT2XV_HU_BU;
                case 0xb:
                    /* 01110110 10011111 001011.. ........ */
                    /* target/loongarch/insns.decode:2096 */
                    return LISA_VEXT2XV_WU_BU;
                case 0xc:
                    /* 01110110 10011111 001100.. ........ */
                    /* target/loongarch/insns.decode:2097 */
                    return LISA_VEXT2XV_DU_BU;
                case 0xd:
                    /* 01110110 10011111 001101.. ........ */
                    /* target/loongarch/insns.decode:2098 */
                    return LISA_VEXT2XV_WU_HU;
                case 0xe:
                    /* 01110110 10011111 001110.. ........ */
                    /* target/loongarch/insns.decode:2099 */
                    return LISA_VEXT2XV_DU_HU;
                case 0xf:
                    /* 01110110 10011111 001111.. ........ */
                    /* target/loongarch/insns.decode:2100 */
                    return LISA_VEXT2XV_DU_WU;
                }
                break;
            case 0x7:
                /* 01110110 10011111 1....... ........ */
                /* target/loongarch/insns.decode:2101 */
                return LISA_XVHSELI_D;
            }
            break;
        case 0xa8:
            /* 01110110 101000.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110110 10100000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110110 10100000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110110 10100000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110110 10100000 001..... ........ */
                            /* target/loongarch/insns.decode:2102 */
                            return LISA_XVROTRI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110110 10100000 01...... ........ */
                        /* target/loongarch/insns.decode:2103 */
                        return LISA_XVROTRI_H;
                    }
                    break;
                case 0x1:
                    /* 01110110 10100000 1....... ........ */
                    /* target/loongarch/insns.decode:2104 */
                    return LISA_XVROTRI_W;
                }
                break;
            case 0x1:
                /* 01110110 10100001 ........ ........ */
                /* target/loongarch/insns.decode:2105 */
                return LISA_XVROTRI_D;
            }
            break;
        case 0xa9:
            /* 01110110 101001.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110110 10100100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110110 10100100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110110 10100100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110110 10100100 001..... ........ */
                            /* target/loongarch/insns.decode:2106 */
                            return LISA_XVSRLRI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110110 10100100 01...... ........ */
                        /* target/loongarch/insns.decode:2107 */
                        return LISA_XVSRLRI_H;
                    }
                    break;
                case 0x1:
                    /* 01110110 10100100 1....... ........ */
                    /* target/loongarch/insns.decode:2108 */
                    return LISA_XVSRLRI_W;
                }
                break;
            case 0x1:
                /* 01110110 10100101 ........ ........ */
                /* target/loongarch/insns.decode:2109 */
                return LISA_XVSRLRI_D;
            }
            break;
        case 0xaa:
            /* 01110110 101010.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110110 10101000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110110 10101000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110110 10101000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110110 10101000 001..... ........ */
                            /* target/loongarch/insns.decode:2110 */
                            return LISA_XVSRARI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110110 10101000 01...... ........ */
                        /* target/loongarch/insns.decode:2111 */
                        return LISA_XVSRARI_H;
                    }
                    break;
                case 0x1:
                    /* 01110110 10101000 1....... ........ */
                    /* target/loongarch/insns.decode:2112 */
                    return LISA_XVSRARI_W;
                }
                break;
            case 0x1:
                /* 01110110 10101001 ........ ........ */
                /* target/loongarch/insns.decode:2113 */
                return LISA_XVSRARI_D;
            }
            break;
        case 0xba:
            /* 01110110 111010.. ........ ........ */
            switch ((insn >> 13) & 0x1f) {
            case 0x1e:
                /* 01110110 11101011 110..... ........ */
                /* target/loongarch/insns.decode:2114 */
                return LISA_XVINSGR2VR_W;
            case 0x1f:
                /* 01110110 11101011 111..... ........ */
                switch ((insn >> 12) & 0x1) {
                case 0x0:
                    /* 01110110 11101011 1110.... ........ */
                    /* target/loongarch/insns.decode:2115 */
                    return LISA_XVINSGR2VR_D;
                }
                break;
            }
            break;
        case 0xbb:
            /* 01110110 111011.. ........ ........ */
            switch ((insn >> 13) & 0x1f) {
            case 0x1e:
                /* 01110110 11101111 110..... ........ */
                /* target/loongarch/insns.decode:2116 */
                return LISA_XVPICKVE2GR_W;
            case 0x1f:
                /* 01110110 11101111 111..... ........ */
                switch ((insn >> 12) & 0x1) {
                case 0x0:
                    /* 01110110 11101111 1110.... ........ */
                    /* target/loongarch/insns.decode:2117 */
                    return LISA_XVPICKVE2GR_D;
                }
                break;
            }
            break;
        case 0xbc:
            /* 01110110 111100.. ........ ........ */
            switch ((insn >> 13) & 0x1f) {
            case 0x1e:
                /* 01110110 11110011 110..... ........ */
                /* target/loongarch/insns.decode:2118 */
                return LISA_XVPICKVE2GR_WU;
            case 0x1f:
                /* 01110110 11110011 111..... ........ */
                switch ((insn >> 12) & 0x1) {
                case 0x0:
                    /* 01110110 11110011 1110.... ........ */
                    /* target/loongarch/insns.decode:2119 */
                    return LISA_XVPICKVE2GR_DU;
                }
                break;
            }
            break;
        case 0xbd:
            /* 01110110 111101.. ........ ........ */
            switch ((insn >> 14) & 0xf) {
            case 0xe:
                /* 01110110 11110111 10...... ........ */
                /* target/loongarch/insns.decode:2120 */
                return LISA_XVREPL128VEI_B;
            case 0xf:
                /* 01110110 11110111 11...... ........ */
                switch ((insn >> 13) & 0x1) {
                case 0x0:
                    /* 01110110 11110111 110..... ........ */
                    /* target/loongarch/insns.decode:2121 */
                    return LISA_XVREPL128VEI_H;
                case 0x1:
                    /* 01110110 11110111 111..... ........ */
                    switch ((insn >> 12) & 0x1) {
                    case 0x0:
                        /* 01110110 11110111 1110.... ........ */
                        /* target/loongarch/insns.decode:2122 */
                        return LISA_XVREPL128VEI_W;
                    case 0x1:
                        /* 01110110 11110111 1111.... ........ */
                        switch ((insn >> 11) & 0x1) {
                        case 0x0:
                            /* 01110110 11110111 11110... ........ */
                            /* target/loongarch/insns.decode:2123 */
                            return LISA_XVREPL128VEI_D;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        case 0xbe:
            /* 01110110 111110.. ........ ........ */
            switch ((insn >> 14) & 0xf) {
            case 0xe:
                /* 01110110 11111011 10...... ........ */
                /* target/loongarch/insns.decode:2124 */
                return LISA_XVEXTRCOLI_B;
            case 0xf:
                /* 01110110 11111011 11...... ........ */
                switch ((insn >> 13) & 0x1) {
                case 0x0:
                    /* 01110110 11111011 110..... ........ */
                    /* target/loongarch/insns.decode:2125 */
                    return LISA_XVEXTRCOLI_H;
                case 0x1:
                    /* 01110110 11111011 111..... ........ */
                    switch ((insn >> 12) & 0x1) {
                    case 0x0:
                        /* 01110110 11111011 1110.... ........ */
                        /* target/loongarch/insns.decode:2126 */
                        return LISA_XVEXTRCOLI_W;
                    case 0x1:
                        /* 01110110 11111011 1111.... ........ */
                        switch ((insn >> 11) & 0x1) {
                        case 0x0:
                            /* 01110110 11111011 11110... ........ */
                            /* target/loongarch/insns.decode:2127 */
                            return LISA_XVEXTRCOLI_D;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        case 0xbf:
            /* 01110110 111111.. ........ ........ */
            switch ((insn >> 13) & 0x1f) {
            case 0x1e:
                /* 01110110 11111111 110..... ........ */
                /* target/loongarch/insns.decode:2128 */
                return LISA_XVINSVE0_W;
            case 0x1f:
                /* 01110110 11111111 111..... ........ */
                switch ((insn >> 12) & 0x1) {
                case 0x0:
                    /* 01110110 11111111 1110.... ........ */
                    /* target/loongarch/insns.decode:2129 */
                    return LISA_XVINSVE0_D;
                }
                break;
            }
            break;
        case 0xc0:
            /* 01110111 000000.. ........ ........ */
            switch ((insn >> 13) & 0x1f) {
            case 0x1e:
                /* 01110111 00000011 110..... ........ */
                /* target/loongarch/insns.decode:2130 */
                return LISA_XVPICKVE_W;
            case 0x1f:
                /* 01110111 00000011 111..... ........ */
                switch ((insn >> 12) & 0x1) {
                case 0x0:
                    /* 01110111 00000011 1110.... ........ */
                    /* target/loongarch/insns.decode:2131 */
                    return LISA_XVPICKVE_D;
                }
                break;
            }
            break;
        case 0xc1:
            /* 01110111 000001.. ........ ........ */
            switch ((insn >> 10) & 0xff) {
            case 0xc0:
                /* 01110111 00000111 000000.. ........ */
                /* target/loongarch/insns.decode:2132 */
                return LISA_XVREPLVE0_B;
            case 0xe0:
                /* 01110111 00000111 100000.. ........ */
                /* target/loongarch/insns.decode:2133 */
                return LISA_XVREPLVE0_H;
            case 0xf0:
                /* 01110111 00000111 110000.. ........ */
                /* target/loongarch/insns.decode:2134 */
                return LISA_XVREPLVE0_W;
            case 0xf8:
                /* 01110111 00000111 111000.. ........ */
                /* target/loongarch/insns.decode:2135 */
                return LISA_XVREPLVE0_D;
            case 0xfc:
                /* 01110111 00000111 111100.. ........ */
                /* target/loongarch/insns.decode:2136 */
                return LISA_XVREPLVE0_Q;
            }
            break;
        case 0xc2:
            /* 01110111 000010.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110111 00001000 0....... ........ */
                switch ((insn >> 14) & 0x1) {
                case 0x0:
                    /* 01110111 00001000 00...... ........ */
                    switch ((insn >> 13) & 0x1) {
                    case 0x1:
                        /* 01110111 00001000 001..... ........ */
                        /* target/loongarch/insns.decode:2137 */
                        return LISA_XVSLLWIL_H_B;
                    }
                    break;
                case 0x1:
                    /* 01110111 00001000 01...... ........ */
                    /* target/loongarch/insns.decode:2138 */
                    return LISA_XVSLLWIL_W_H;
                }
                break;
            case 0x1:
                /* 01110111 00001000 1....... ........ */
                /* target/loongarch/insns.decode:2139 */
                return LISA_XVSLLWIL_D_W;
            case 0x2:
                /* 01110111 00001001 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x0:
                    /* 01110111 00001001 000000.. ........ */
                    /* target/loongarch/insns.decode:2140 */
                    return LISA_XVEXTL_Q_D;
                }
                break;
            }
            break;
        case 0xc3:
            /* 01110111 000011.. ........ ........ */
            switch ((insn >> 15) & 0x7) {
            case 0x0:
                /* 01110111 00001100 0....... ........ */
                switch ((insn >> 14) & 0x1) {
                case 0x0:
                    /* 01110111 00001100 00...... ........ */
                    switch ((insn >> 13) & 0x1) {
                    case 0x1:
                        /* 01110111 00001100 001..... ........ */
                        /* target/loongarch/insns.decode:2141 */
                        return LISA_XVSLLWIL_HU_BU;
                    }
                    break;
                case 0x1:
                    /* 01110111 00001100 01...... ........ */
                    /* target/loongarch/insns.decode:2142 */
                    return LISA_XVSLLWIL_WU_HU;
                }
                break;
            case 0x1:
                /* 01110111 00001100 1....... ........ */
                /* target/loongarch/insns.decode:2143 */
                return LISA_XVSLLWIL_DU_WU;
            case 0x2:
                /* 01110111 00001101 0....... ........ */
                switch ((insn >> 10) & 0x1f) {
                case 0x0:
                    /* 01110111 00001101 000000.. ........ */
                    /* target/loongarch/insns.decode:2144 */
                    return LISA_XVEXTL_QU_DU;
                }
                break;
            }
            break;
        case 0xc4:
            /* 01110111 000100.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110111 00010000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110111 00010000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110111 00010000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110111 00010000 001..... ........ */
                            /* target/loongarch/insns.decode:2145 */
                            return LISA_XVBITCLRI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00010000 01...... ........ */
                        /* target/loongarch/insns.decode:2146 */
                        return LISA_XVBITCLRI_H;
                    }
                    break;
                case 0x1:
                    /* 01110111 00010000 1....... ........ */
                    /* target/loongarch/insns.decode:2147 */
                    return LISA_XVBITCLRI_W;
                }
                break;
            case 0x1:
                /* 01110111 00010001 ........ ........ */
                /* target/loongarch/insns.decode:2148 */
                return LISA_XVBITCLRI_D;
            }
            break;
        case 0xc5:
            /* 01110111 000101.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110111 00010100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110111 00010100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110111 00010100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110111 00010100 001..... ........ */
                            /* target/loongarch/insns.decode:2149 */
                            return LISA_XVBITSETI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00010100 01...... ........ */
                        /* target/loongarch/insns.decode:2150 */
                        return LISA_XVBITSETI_H;
                    }
                    break;
                case 0x1:
                    /* 01110111 00010100 1....... ........ */
                    /* target/loongarch/insns.decode:2151 */
                    return LISA_XVBITSETI_W;
                }
                break;
            case 0x1:
                /* 01110111 00010101 ........ ........ */
                /* target/loongarch/insns.decode:2152 */
                return LISA_XVBITSETI_D;
            }
            break;
        case 0xc6:
            /* 01110111 000110.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110111 00011000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110111 00011000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110111 00011000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110111 00011000 001..... ........ */
                            /* target/loongarch/insns.decode:2153 */
                            return LISA_XVBITREVI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00011000 01...... ........ */
                        /* target/loongarch/insns.decode:2154 */
                        return LISA_XVBITREVI_H;
                    }
                    break;
                case 0x1:
                    /* 01110111 00011000 1....... ........ */
                    /* target/loongarch/insns.decode:2155 */
                    return LISA_XVBITREVI_W;
                }
                break;
            case 0x1:
                /* 01110111 00011001 ........ ........ */
                /* target/loongarch/insns.decode:2156 */
                return LISA_XVBITREVI_D;
            }
            break;
        case 0xc7:
            /* 01110111 000111.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110111 00011100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110111 00011100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110111 00011100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110111 00011100 001..... ........ */
                            /* target/loongarch/insns.decode:2157 */
                            return LISA_XVBSTRC12I_B;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00011100 01...... ........ */
                        /* target/loongarch/insns.decode:2158 */
                        return LISA_XVBSTRC12I_H;
                    }
                    break;
                case 0x1:
                    /* 01110111 00011100 1....... ........ */
                    /* target/loongarch/insns.decode:2159 */
                    return LISA_XVBSTRC12I_W;
                }
                break;
            case 0x1:
                /* 01110111 00011101 ........ ........ */
                /* target/loongarch/insns.decode:2160 */
                return LISA_XVBSTRC12I_D;
            }
            break;
        case 0xc8:
            /* 01110111 001000.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110111 00100000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110111 00100000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110111 00100000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110111 00100000 001..... ........ */
                            /* target/loongarch/insns.decode:2161 */
                            return LISA_XVBSTRC21I_B;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00100000 01...... ........ */
                        /* target/loongarch/insns.decode:2162 */
                        return LISA_XVBSTRC21I_H;
                    }
                    break;
                case 0x1:
                    /* 01110111 00100000 1....... ........ */
                    /* target/loongarch/insns.decode:2163 */
                    return LISA_XVBSTRC21I_W;
                }
                break;
            case 0x1:
                /* 01110111 00100001 ........ ........ */
                /* target/loongarch/insns.decode:2164 */
                return LISA_XVBSTRC21I_D;
            }
            break;
        case 0xc9:
            /* 01110111 001001.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110111 00100100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110111 00100100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110111 00100100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110111 00100100 001..... ........ */
                            /* target/loongarch/insns.decode:2165 */
                            return LISA_XVSAT_B;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00100100 01...... ........ */
                        /* target/loongarch/insns.decode:2166 */
                        return LISA_XVSAT_H;
                    }
                    break;
                case 0x1:
                    /* 01110111 00100100 1....... ........ */
                    /* target/loongarch/insns.decode:2167 */
                    return LISA_XVSAT_W;
                }
                break;
            case 0x1:
                /* 01110111 00100101 ........ ........ */
                /* target/loongarch/insns.decode:2168 */
                return LISA_XVSAT_D;
            }
            break;
        case 0xca:
            /* 01110111 001010.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110111 00101000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110111 00101000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110111 00101000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110111 00101000 001..... ........ */
                            /* target/loongarch/insns.decode:2169 */
                            return LISA_XVSAT_BU;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00101000 01...... ........ */
                        /* target/loongarch/insns.decode:2170 */
                        return LISA_XVSAT_HU;
                    }
                    break;
                case 0x1:
                    /* 01110111 00101000 1....... ........ */
                    /* target/loongarch/insns.decode:2171 */
                    return LISA_XVSAT_WU;
                }
                break;
            case 0x1:
                /* 01110111 00101001 ........ ........ */
                /* target/loongarch/insns.decode:2172 */
                return LISA_XVSAT_DU;
            }
            break;
        case 0xcb:
            /* 01110111 001011.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110111 00101100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110111 00101100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110111 00101100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110111 00101100 001..... ........ */
                            /* target/loongarch/insns.decode:2173 */
                            return LISA_XVSLLI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00101100 01...... ........ */
                        /* target/loongarch/insns.decode:2174 */
                        return LISA_XVSLLI_H;
                    }
                    break;
                case 0x1:
                    /* 01110111 00101100 1....... ........ */
                    /* target/loongarch/insns.decode:2175 */
                    return LISA_XVSLLI_W;
                }
                break;
            case 0x1:
                /* 01110111 00101101 ........ ........ */
                /* target/loongarch/insns.decode:2176 */
                return LISA_XVSLLI_D;
            }
            break;
        case 0xcc:
            /* 01110111 001100.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110111 00110000 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110111 00110000 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110111 00110000 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110111 00110000 001..... ........ */
                            /* target/loongarch/insns.decode:2177 */
                            return LISA_XVSRLI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00110000 01...... ........ */
                        /* target/loongarch/insns.decode:2178 */
                        return LISA_XVSRLI_H;
                    }
                    break;
                case 0x1:
                    /* 01110111 00110000 1....... ........ */
                    /* target/loongarch/insns.decode:2179 */
                    return LISA_XVSRLI_W;
                }
                break;
            case 0x1:
                /* 01110111 00110001 ........ ........ */
                /* target/loongarch/insns.decode:2180 */
                return LISA_XVSRLI_D;
            }
            break;
        case 0xcd:
            /* 01110111 001101.. ........ ........ */
            switch ((insn >> 16) & 0x3) {
            case 0x0:
                /* 01110111 00110100 ........ ........ */
                switch ((insn >> 15) & 0x1) {
                case 0x0:
                    /* 01110111 00110100 0....... ........ */
                    switch ((insn >> 14) & 0x1) {
                    case 0x0:
                        /* 01110111 00110100 00...... ........ */
                        switch ((insn >> 13) & 0x1) {
                        case 0x1:
                            /* 01110111 00110100 001..... ........ */
                            /* target/loongarch/insns.decode:2181 */
                            return LISA_XVSRAI_B;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00110100 01...... ........ */
                        /* target/loongarch/insns.decode:2182 */
                        return LISA_XVSRAI_H;
                    }
                    break;
                case 0x1:
                    /* 01110111 00110100 1....... ........ */
                    /* target/loongarch/insns.decode:2183 */
                    return LISA_XVSRAI_W;
                }
                break;
            case 0x1:
                /* 01110111 00110101 ........ ........ */
                /* target/loongarch/insns.decode:2184 */
                return LISA_XVSRAI_D;
            }
            break;
        case 0xce:
            /* 01110111 001110.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0011100. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 00111000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 00111000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 00111000 01...... ........ */
                            /* target/loongarch/insns.decode:2185 */
                            return LISA_XVSRLRNENI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00111000 1....... ........ */
                        /* target/loongarch/insns.decode:2186 */
                        return LISA_XVSRLRNENI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 00111001 ........ ........ */
                    /* target/loongarch/insns.decode:2187 */
                    return LISA_XVSRLRNENI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0011101. ........ ........ */
                /* target/loongarch/insns.decode:2188 */
                return LISA_XVSRLRNENI_D_Q;
            }
            break;
        case 0xcf:
            /* 01110111 001111.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0011110. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 00111100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 00111100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 00111100 01...... ........ */
                            /* target/loongarch/insns.decode:2189 */
                            return LISA_XVSRARNENI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 00111100 1....... ........ */
                        /* target/loongarch/insns.decode:2190 */
                        return LISA_XVSRARNENI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 00111101 ........ ........ */
                    /* target/loongarch/insns.decode:2191 */
                    return LISA_XVSRARNENI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0011111. ........ ........ */
                /* target/loongarch/insns.decode:2192 */
                return LISA_XVSRARNENI_D_Q;
            }
            break;
        case 0xd0:
            /* 01110111 010000.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0100000. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01000000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01000000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01000000 01...... ........ */
                            /* target/loongarch/insns.decode:2193 */
                            return LISA_XVSRLNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01000000 1....... ........ */
                        /* target/loongarch/insns.decode:2194 */
                        return LISA_XVSRLNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01000001 ........ ........ */
                    /* target/loongarch/insns.decode:2195 */
                    return LISA_XVSRLNI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0100001. ........ ........ */
                /* target/loongarch/insns.decode:2196 */
                return LISA_XVSRLNI_D_Q;
            }
            break;
        case 0xd1:
            /* 01110111 010001.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0100010. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01000100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01000100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01000100 01...... ........ */
                            /* target/loongarch/insns.decode:2197 */
                            return LISA_XVSRLRNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01000100 1....... ........ */
                        /* target/loongarch/insns.decode:2198 */
                        return LISA_XVSRLRNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01000101 ........ ........ */
                    /* target/loongarch/insns.decode:2199 */
                    return LISA_XVSRLRNI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0100011. ........ ........ */
                /* target/loongarch/insns.decode:2200 */
                return LISA_XVSRLRNI_D_Q;
            }
            break;
        case 0xd2:
            /* 01110111 010010.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0100100. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01001000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01001000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01001000 01...... ........ */
                            /* target/loongarch/insns.decode:2201 */
                            return LISA_XVSSRLNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01001000 1....... ........ */
                        /* target/loongarch/insns.decode:2202 */
                        return LISA_XVSSRLNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01001001 ........ ........ */
                    /* target/loongarch/insns.decode:2203 */
                    return LISA_XVSSRLNI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0100101. ........ ........ */
                /* target/loongarch/insns.decode:2204 */
                return LISA_XVSSRLNI_D_Q;
            }
            break;
        case 0xd3:
            /* 01110111 010011.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0100110. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01001100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01001100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01001100 01...... ........ */
                            /* target/loongarch/insns.decode:2205 */
                            return LISA_XVSSRLNI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01001100 1....... ........ */
                        /* target/loongarch/insns.decode:2206 */
                        return LISA_XVSSRLNI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01001101 ........ ........ */
                    /* target/loongarch/insns.decode:2207 */
                    return LISA_XVSSRLNI_WU_D;
                }
                break;
            case 0x1:
                /* 01110111 0100111. ........ ........ */
                /* target/loongarch/insns.decode:2208 */
                return LISA_XVSSRLNI_DU_Q;
            }
            break;
        case 0xd4:
            /* 01110111 010100.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0101000. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01010000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01010000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01010000 01...... ........ */
                            /* target/loongarch/insns.decode:2209 */
                            return LISA_XVSSRLRNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01010000 1....... ........ */
                        /* target/loongarch/insns.decode:2210 */
                        return LISA_XVSSRLRNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01010001 ........ ........ */
                    /* target/loongarch/insns.decode:2211 */
                    return LISA_XVSSRLRNI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0101001. ........ ........ */
                /* target/loongarch/insns.decode:2212 */
                return LISA_XVSSRLRNI_D_Q;
            }
            break;
        case 0xd5:
            /* 01110111 010101.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0101010. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01010100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01010100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01010100 01...... ........ */
                            /* target/loongarch/insns.decode:2213 */
                            return LISA_XVSSRLRNI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01010100 1....... ........ */
                        /* target/loongarch/insns.decode:2214 */
                        return LISA_XVSSRLRNI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01010101 ........ ........ */
                    /* target/loongarch/insns.decode:2215 */
                    return LISA_XVSSRLRNI_WU_D;
                }
                break;
            case 0x1:
                /* 01110111 0101011. ........ ........ */
                /* target/loongarch/insns.decode:2216 */
                return LISA_XVSSRLRNI_DU_Q;
            }
            break;
        case 0xd6:
            /* 01110111 010110.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0101100. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01011000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01011000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01011000 01...... ........ */
                            /* target/loongarch/insns.decode:2217 */
                            return LISA_XVSRANI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01011000 1....... ........ */
                        /* target/loongarch/insns.decode:2218 */
                        return LISA_XVSRANI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01011001 ........ ........ */
                    /* target/loongarch/insns.decode:2219 */
                    return LISA_XVSRANI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0101101. ........ ........ */
                /* target/loongarch/insns.decode:2220 */
                return LISA_XVSRANI_D_Q;
            }
            break;
        case 0xd7:
            /* 01110111 010111.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0101110. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01011100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01011100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01011100 01...... ........ */
                            /* target/loongarch/insns.decode:2221 */
                            return LISA_XVSRARNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01011100 1....... ........ */
                        /* target/loongarch/insns.decode:2222 */
                        return LISA_XVSRARNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01011101 ........ ........ */
                    /* target/loongarch/insns.decode:2223 */
                    return LISA_XVSRARNI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0101111. ........ ........ */
                /* target/loongarch/insns.decode:2224 */
                return LISA_XVSRARNI_D_Q;
            }
            break;
        case 0xd8:
            /* 01110111 011000.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0110000. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01100000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01100000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01100000 01...... ........ */
                            /* target/loongarch/insns.decode:2225 */
                            return LISA_XVSSRANI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01100000 1....... ........ */
                        /* target/loongarch/insns.decode:2226 */
                        return LISA_XVSSRANI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01100001 ........ ........ */
                    /* target/loongarch/insns.decode:2227 */
                    return LISA_XVSSRANI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0110001. ........ ........ */
                /* target/loongarch/insns.decode:2228 */
                return LISA_XVSSRANI_D_Q;
            }
            break;
        case 0xd9:
            /* 01110111 011001.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0110010. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01100100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01100100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01100100 01...... ........ */
                            /* target/loongarch/insns.decode:2229 */
                            return LISA_XVSSRANI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01100100 1....... ........ */
                        /* target/loongarch/insns.decode:2230 */
                        return LISA_XVSSRANI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01100101 ........ ........ */
                    /* target/loongarch/insns.decode:2231 */
                    return LISA_XVSSRANI_WU_D;
                }
                break;
            case 0x1:
                /* 01110111 0110011. ........ ........ */
                /* target/loongarch/insns.decode:2232 */
                return LISA_XVSSRANI_DU_Q;
            }
            break;
        case 0xda:
            /* 01110111 011010.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0110100. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01101000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01101000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01101000 01...... ........ */
                            /* target/loongarch/insns.decode:2233 */
                            return LISA_XVSSRARNI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01101000 1....... ........ */
                        /* target/loongarch/insns.decode:2234 */
                        return LISA_XVSSRARNI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01101001 ........ ........ */
                    /* target/loongarch/insns.decode:2235 */
                    return LISA_XVSSRARNI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0110101. ........ ........ */
                /* target/loongarch/insns.decode:2236 */
                return LISA_XVSSRARNI_D_Q;
            }
            break;
        case 0xdb:
            /* 01110111 011011.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0110110. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01101100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01101100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01101100 01...... ........ */
                            /* target/loongarch/insns.decode:2237 */
                            return LISA_XVSSRARNI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01101100 1....... ........ */
                        /* target/loongarch/insns.decode:2238 */
                        return LISA_XVSSRARNI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01101101 ........ ........ */
                    /* target/loongarch/insns.decode:2239 */
                    return LISA_XVSSRARNI_WU_D;
                }
                break;
            case 0x1:
                /* 01110111 0110111. ........ ........ */
                /* target/loongarch/insns.decode:2240 */
                return LISA_XVSSRARNI_DU_Q;
            }
            break;
        case 0xdc:
            /* 01110111 011100.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0111000. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01110000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01110000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01110000 01...... ........ */
                            /* target/loongarch/insns.decode:2241 */
                            return LISA_XVSSRLRNENI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01110000 1....... ........ */
                        /* target/loongarch/insns.decode:2242 */
                        return LISA_XVSSRLRNENI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01110001 ........ ........ */
                    /* target/loongarch/insns.decode:2243 */
                    return LISA_XVSSRLRNENI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0111001. ........ ........ */
                /* target/loongarch/insns.decode:2244 */
                return LISA_XVSSRLRNENI_D_Q;
            }
            break;
        case 0xdd:
            /* 01110111 011101.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0111010. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01110100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01110100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01110100 01...... ........ */
                            /* target/loongarch/insns.decode:2245 */
                            return LISA_XVSSRLRNENI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01110100 1....... ........ */
                        /* target/loongarch/insns.decode:2246 */
                        return LISA_XVSSRLRNENI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01110101 ........ ........ */
                    /* target/loongarch/insns.decode:2247 */
                    return LISA_XVSSRLRNENI_WU_D;
                }
                break;
            case 0x1:
                /* 01110111 0111011. ........ ........ */
                /* target/loongarch/insns.decode:2248 */
                return LISA_XVSSRLRNENI_DU_Q;
            }
            break;
        case 0xde:
            /* 01110111 011110.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0111100. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01111000 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01111000 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01111000 01...... ........ */
                            /* target/loongarch/insns.decode:2249 */
                            return LISA_XVSSRARNENI_B_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01111000 1....... ........ */
                        /* target/loongarch/insns.decode:2250 */
                        return LISA_XVSSRARNENI_H_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01111001 ........ ........ */
                    /* target/loongarch/insns.decode:2251 */
                    return LISA_XVSSRARNENI_W_D;
                }
                break;
            case 0x1:
                /* 01110111 0111101. ........ ........ */
                /* target/loongarch/insns.decode:2252 */
                return LISA_XVSSRARNENI_D_Q;
            }
            break;
        case 0xdf:
            /* 01110111 011111.. ........ ........ */
            switch ((insn >> 17) & 0x1) {
            case 0x0:
                /* 01110111 0111110. ........ ........ */
                switch ((insn >> 16) & 0x1) {
                case 0x0:
                    /* 01110111 01111100 ........ ........ */
                    switch ((insn >> 15) & 0x1) {
                    case 0x0:
                        /* 01110111 01111100 0....... ........ */
                        switch ((insn >> 14) & 0x1) {
                        case 0x1:
                            /* 01110111 01111100 01...... ........ */
                            /* target/loongarch/insns.decode:2253 */
                            return LISA_XVSSRARNENI_BU_H;
                        }
                        break;
                    case 0x1:
                        /* 01110111 01111100 1....... ........ */
                        /* target/loongarch/insns.decode:2254 */
                        return LISA_XVSSRARNENI_HU_W;
                    }
                    break;
                case 0x1:
                    /* 01110111 01111101 ........ ........ */
                    /* target/loongarch/insns.decode:2255 */
                    return LISA_XVSSRARNENI_WU_D;
                }
                break;
            case 0x1:
                /* 01110111 0111111. ........ ........ */
                /* target/loongarch/insns.decode:2256 */
                return LISA_XVSSRARNENI_DU_Q;
            }
            break;
        case 0xe0:
            /* 01110111 100000.. ........ ........ */
            /* target/loongarch/insns.decode:2257 */
            return LISA_XVEXTRINS_D;
        case 0xe1:
            /* 01110111 100001.. ........ ........ */
            /* target/loongarch/insns.decode:2258 */
            return LISA_XVEXTRINS_W;
        case 0xe2:
            /* 01110111 100010.. ........ ........ */
            /* target/loongarch/insns.decode:2259 */
            return LISA_XVEXTRINS_H;
        case 0xe3:
            /* 01110111 100011.. ........ ........ */
            /* target/loongarch/insns.decode:2260 */
            return LISA_XVEXTRINS_B;
        case 0xe4:
            /* 01110111 100100.. ........ ........ */
            /* target/loongarch/insns.decode:2261 */
            return LISA_XVSHUF4I_B;
        case 0xe5:
            /* 01110111 100101.. ........ ........ */
            /* target/loongarch/insns.decode:2262 */
            return LISA_XVSHUF4I_H;
        case 0xe6:
            /* 01110111 100110.. ........ ........ */
            /* target/loongarch/insns.decode:2263 */
            return LISA_XVSHUF4I_W;
        case 0xe7:
            /* 01110111 100111.. ........ ........ */
            /* target/loongarch/insns.decode:2264 */
            return LISA_XVSHUF4I_D;
        case 0xe8:
            /* 01110111 101000.. ........ ........ */
            /* target/loongarch/insns.decode:2265 */
            return LISA_XVSHUFI1_B;
        case 0xe9:
            /* 01110111 101001.. ........ ........ */
            /* target/loongarch/insns.decode:2266 */
            return LISA_XVSHUFI2_B;
        case 0xea:
            /* 01110111 101010.. ........ ........ */
            /* target/loongarch/insns.decode:2267 */
            return LISA_XVSHUFI3_B;
        case 0xeb:
            /* 01110111 101011.. ........ ........ */
            /* target/loongarch/insns.decode:2268 */
            return LISA_XVSHUFI4_B;
        case 0xec:
            /* 01110111 101100.. ........ ........ */
            /* target/loongarch/insns.decode:2269 */
            return LISA_XVSHUFI1_H;
        case 0xed:
            /* 01110111 101101.. ........ ........ */
            /* target/loongarch/insns.decode:2270 */
            return LISA_XVSHUFI2_H;
        case 0xee:
            /* 01110111 101110.. ........ ........ */
            /* target/loongarch/insns.decode:2271 */
            return LISA_XVSELI_H;
        case 0xef:
            /* 01110111 101111.. ........ ........ */
            /* target/loongarch/insns.decode:2272 */
            return LISA_XVSELI_W;
        case 0xf0:
            /* 01110111 110000.. ........ ........ */
            /* target/loongarch/insns.decode:2273 */
            return LISA_XVSELI_D;
        case 0xf1:
            /* 01110111 110001.. ........ ........ */
            /* target/loongarch/insns.decode:2274 */
            return LISA_XVBITSELI_B;
        case 0xf2:
            /* 01110111 110010.. ........ ........ */
            /* target/loongarch/insns.decode:2275 */
            return LISA_XVBITMVZI_B;
        case 0xf3:
            /* 01110111 110011.. ........ ........ */
            /* target/loongarch/insns.decode:2276 */
            return LISA_XVBITMVNZI_B;
        case 0xf4:
            /* 01110111 110100.. ........ ........ */
            /* target/loongarch/insns.decode:2277 */
            return LISA_XVANDI_B;
        case 0xf5:
            /* 01110111 110101.. ........ ........ */
            /* target/loongarch/insns.decode:2278 */
            return LISA_XVORI_B;
        case 0xf6:
            /* 01110111 110110.. ........ ........ */
            /* target/loongarch/insns.decode:2279 */
            return LISA_XVXORI_B;
        case 0xf7:
            /* 01110111 110111.. ........ ........ */
            /* target/loongarch/insns.decode:2280 */
            return LISA_XVNORI_B;
        case 0xf8:
            /* 01110111 111000.. ........ ........ */
            /* target/loongarch/insns.decode:2281 */
            return LISA_XVLDI;
        case 0xf9:
            /* 01110111 111001.. ........ ........ */
            /* target/loongarch/insns.decode:2282 */
            return LISA_XVPERMI_W;
        case 0xfa:
            /* 01110111 111010.. ........ ........ */
            /* target/loongarch/insns.decode:2283 */
            return LISA_XVPERMI_D;
        case 0xfb:
            /* 01110111 111011.. ........ ........ */
            /* target/loongarch/insns.decode:2284 */
            return LISA_XVPERMI_Q;
        }
        break;
    }
    return LISA_INVALID;
}
