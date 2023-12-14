#ifndef _LA_BITOPTS_H_
#define _LA_BITOPTS_H_

#include <stdint.h>

/* n: 0~63 */
#define BitSet(x, n) (x | (1 << n))
#define BitUnset(x, n) (x & ~(1 << n))
#define BitIsSet(x, n) (x & (1 << n))
#define ToggleBit(x, n) (x ^ (1 << n))

/* 符号扩展到64位，wide表示原始数据位宽（1~63） */
static inline uint64_t sign_extend(uint64_t val, int wide)
{
    if (wide == 0) {
        return 0;
    }
    if (wide >= 64) {
        return val;
    }

    uint64_t sign = val & (1UL << (wide - 1));
    if (sign) {
        val = val | (-1UL << wide);
    } else {
        val = val & ((1UL << wide) - 1);
    }
    return val;
}

#endif
