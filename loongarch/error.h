#ifndef _LA_ERROR_H_
#define _LA_ERROR_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int lmj_debug_log;

#define CONFIG_LMJ_DEBUG

#ifdef CONFIG_LMJ_DEBUG
#define lsassert(cond)                                                  \
    do {                                                                \
        if (!(cond)) {                                                  \
            fprintf(stderr,                                             \
                    "\033[31m assertion failed in <%s> %s:%d \033[m\n", \
                    __FUNCTION__, __FILE__, __LINE__);                  \
            abort();                                                    \
        }                                                               \
    } while (0)

#define lsassertm(cond, ...)                                                  \
    do {                                                                      \
        if (!(cond)) {                                                        \
            fprintf(stderr, "\033[31m assertion failed in <%s> %s:%d \033[m", \
                    __FUNCTION__, __FILE__, __LINE__);                        \
            fprintf(stderr, __VA_ARGS__);                                     \
            abort();                                                          \
        }                                                                     \
    } while (0)

#define lslog(...)                          \
    do {                                    \
        if (lmj_debug_log) {                \
            fprintf(stderr, __VA_ARGS__);   \
        }                                   \
    } while (0)

#define lsdebug(...)                        \
    do {                                    \
        if (lmj_debug_log) {                \
            fprintf(stderr, "[LS debug] "); \
            fprintf(stderr, __VA_ARGS__);   \
        }                                   \
    } while (0)

#define lswarn(...)                                     \
    do {                                                \
        if (lmj_debug_log) {                            \
            fprintf(stderr, "[LS warn] <%s> %s:%d ",    \
                    __FUNCTION__, __FILE__, __LINE__);  \
            fprintf(stderr, __VA_ARGS__);               \
        }                                               \
    } while (0)

#else
#define lsassert(cond)          ((void)0)
#define lsassertm(cond, ...)    ((void)0)
#define lslog(...)              ((void)0)
#define lsdebug(...)            ((void)0)
#define lswarn(...)             ((void)0)
#endif

#endif

