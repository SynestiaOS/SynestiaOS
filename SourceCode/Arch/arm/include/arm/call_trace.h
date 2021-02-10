//
// Created by XingfengYang on 2021/1/8.
//

#include "libc/stdbool.h"

#ifndef SYNESTIAOS_CALL_TRACE_H
#define SYNESTIAOS_CALL_TRACE_H

/* dump call trace based on current stack (e.g., xxx thread). */
void dump_calltrace(void);

/* judge whether a function is leaf or not.
   true means leaf function;
   false means non-leaf function. */
bool func_is_leaf(unsigned int *instr);

/* NOTE: please put this macro at the beginning of exception handler for call trace */
#define prepare_calltrace_in_exception() \
    do { \
        unsigned int *epc; \
        unsigned int fp; \
        \
        /* first thing is to get exception address */ \
        __asm__ __volatile__("str lr, %0\n\t" : "=m"(epc)); \
        LogError("undefined instruction!!!\n"); \
        LogError("exception pc: 0x%x\n", --epc); \
        \
        /* last frame pointer is not in system mode stack */ \
        __asm__ __volatile__("str r11, %0\n\t" : "=m"(fp)); \
        /* r12 is pushed because of __attribute__((interrupt("UNDEF"))), \
           so the offset is -2. */ \
        fp = ((unsigned int *) fp)[-2]; \
        \
        if (func_is_leaf(epc)) { \
            unsigned int lr; \
            lr = 0; \
            /* get lr of leaf function */ \
            __asm__ __volatile__("mrs r0, spsr\n\t" \
                                "nop\n\t" \
                                "msr cpsr, #0b11011111\n\t" \
                                "nop\n\t" \
                                "mov r1, lr\n\t" \
                                "sub sp, sp, #4\n\t" /* create extra stack space */ \
                                "msr cpsr, r0\n\t" \
                                "nop\n\t" \
                                "str r1, %0\n\t" \
                                : \
                                : "m"(lr)); \
            /* construct universal function stack along low address */ \
            ((unsigned int *) fp)[1] = lr; \
            /* update fp */ \
            fp += 4; \
        } \
        \
        /* recover r11 to system mode */ \
        __asm__ __volatile__("ldr r0, %0\n\t" /* r11 cannot be modified directly, local vars use r11 */ \
                            "ldr r1, %1\n\t" \
                            "msr cpsr, #0b11011111\n\t" \
                            "nop\n\t" \
                            /* construct c function info on sys stack */ \
                            "push {r1}\n\t" /* lr */ \
                            "push {r0}\n\t" /* r11 */ \
                            "add r11, sp, #4\n\t" /* only 2 registers, so it is 4 */ \
                            : \
                            : "m"(fp), "m"(epc)); \
    } while (0)

#endif //SYNESTIAOS_CALL_TRACE_H
