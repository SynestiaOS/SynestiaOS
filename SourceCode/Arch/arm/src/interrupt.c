//
// Created by XingfengYang on 2021/1/8.
//

#include "arm/interrupt.h"
#include "kernel/interrupt.h"
#include "kernel/log.h"
#include "arm/vmm.h"
#include "libc/string.h"

extern InterruptManager genericInterruptManager;

uint32_t arch_is_interrupt_enabled() {
    uint32_t cpsr;
    __asm__ __volatile__("mrs %0, cpsr"
    : "=r"(cpsr)
    :);
    return ((cpsr >> 7) & 1) == 0;
}

void arch_enable_interrupt() {
    __asm__ __volatile__("cpsie i");
}

void arch_disable_interrupt() {
    __asm__ __volatile__("cpsid i");
}

static void find_func_header(unsigned int *instr)
{
    static const unsigned int prologue[2] = { 0xe92d4800, 0xe28db000 }; // todo: add more....
    unsigned int i;

#define MAX_FUNC_LEN 0x1000
    for (i = 0; (i < MAX_FUNC_LEN) && (0 != instr); i++, instr--) {
        if (((0xffff4800 & *(instr - 1)) == prologue[0]) // if only {r11, lr} are pushed
         && ((0xffffff00 & *instr) == prologue[1])) {
            LogError("func: %x\n", instr - 1);
            return;
        }
    }
    LogError("can not find function!!!\n");
}

void dump_callstack(void)
{
    unsigned int *lr, *fp;
    unsigned int *func;

    __asm__ __volatile__("push {r0, r2, r4, r6, r8, r12, r14}\n\t" : "=m"(lr));
    __asm__ __volatile__("push {r0, r2, r4, r6, r8}\n\t" : "=m"(lr));
    __asm__ __volatile__("push {r8}\n\t" : "=m"(lr));
    __asm__ __volatile__("push {r8, r9, r10, r11, r12, r13, r14}\n\t" : "=m"(lr));

    __asm__ __volatile__("str lr, %0\n\t" : "=m"(lr));
    __asm__ __volatile__("str r11, %0\n\t" : "=m"(fp));

    LogError("callstack info:\n");
    while (fp) {
        lr = (unsigned int *) fp[0];
        fp = (unsigned int *) fp[-1];
        find_func_header(lr);
    }
    LogError("callstack end\n");
}

extern SysCall sys_call_table[];

void __attribute__((interrupt("UNDEF"))) undefined_instruction_handler(void) {}

int software_interrupt_handler() {
    volatile int r0, r1, r2, r3, r4, sysCallNo;
    __asm__ volatile("mov %0,r1\n\t"
                     "mov %1,r2\n\t"
                     "mov %2,r4\n\t"
                     "mov %3,r5\n\t"
                     "mov %4,r6\n\t"
                     "mov %5,r7\n\t"
    : "=r"(r0), "=r"(r1), "=r"(r2), "=r"(r3), "=r"(r4), "=r"(sysCallNo)
    :
    : "r1", "r2", "r4", "r5", "r6", "r7");

    return sys_call_table[sysCallNo](r0, r1, r2, r3, r4);
}

void __attribute__((interrupt("ABORT"))) prefetch_abort_handler(void) {
    LogError("[Interrupt]: abort panic\n");
}

void data_abort_handler() {
    volatile uint32_t r0, r1, r2, r3, r4, r5;
    __asm__ volatile("mov %0,r0\n\t"
                     "mov %1,r1\n\t"
                     "mov %2,r2\n\t"
                     "mov %3,r3\n\t"
                     "mov %4,r4\n\t"
                     "mov %5,r5\n\t"
    : "=r"(r0), "=r"(r1), "=r"(r2), "=r"(r3), "=r"(r4), "=r"(r5)
    :
    : "r0", "r1", "r2", "r3", "r4", "r5");
    // TODO: get page fault info from cp15
    LogError("[Interrupt]: data abort\n");
    do_page_fault(r3);
}

void unused_handler(void) {
    LogError("[Interrupt]: unused panic\n");
}

void fast_interrupt_handler(void) {
    LogError("[Interrupt]: fast irq\n");
}

void interrupt_handler(void) {
    genericInterruptManager.operation.interrupt(&genericInterruptManager);
}
