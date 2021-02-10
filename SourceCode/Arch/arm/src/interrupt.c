//
// Created by XingfengYang on 2021/1/8.
//

#include "arm/interrupt.h"
#include "kernel/interrupt.h"
#include "kernel/log.h"
#include "arm/vmm.h"
#include "arm/call_trace.h"

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

void __attribute__((interrupt("UNDEF"))) undefined_instruction_handler(void) {
    prepare_calltrace_in_exception();
    LogError("[%s]: exception\n", __FUNCTION__);
    dump_calltrace();
    dead();
}

extern SysCall sys_call_table[];

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

    SysCall sysCall = sys_call_table[sysCallNo];
    return sysCall(r0, r1, r2, r3, r4);
}

void __attribute__((interrupt("ABORT"))) prefetch_abort_handler(void) {
    prepare_calltrace_in_exception();
    LogError("[%s]: exception\n", __FUNCTION__);
    dump_calltrace();
    dead();
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
    prepare_calltrace_in_exception();
    LogError("[%s]: exception\n", __FUNCTION__);
    dump_calltrace();
    dead();
}

void fast_interrupt_handler(void) {
    LogError("[Interrupt]: fast irq\n");
}

void interrupt_handler(void) {
    genericInterruptManager.operation.interrupt(&genericInterruptManager);
}
