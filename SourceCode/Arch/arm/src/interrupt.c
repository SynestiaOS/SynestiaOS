//
// Created by XingfengYang on 2021/1/8.
//

#include "arm/interrupt.h"
#include "kernel/interrupt.h"
#include "kernel/log.h"

extern InterruptManager genericInterruptManager;

uint32_t arch_is_interrupt_enabled() {
    uint32_t cpsr;
    __asm__ __volatile__("mrs %0, cpsr"
    : "=r"(cpsr)
    :);
    return ((cpsr >> 7) & 1) == 0;
}

void arch_enable_interrupt() {
    if (!arch_is_interrupt_enabled()) {
        __asm__ __volatile__("cpsie i");
        LogInfo("[Interrupt]: enable\n");
    }
}

void arch_disable_interrupt() {
    if (arch_is_interrupt_enabled()) {
        __asm__ __volatile__("cpsid i");
        LogInfo("[Interrupt]: disable\n");
    }
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
    for (uint32_t interrupt_no = 0; interrupt_no < IRQ_NUMS; interrupt_no++) {
        if (genericInterruptManager.registed[interrupt_no]) {
            LogInfo("[Interrupt]: interrupt '%d' triggered.\n", interrupt_no);
            if (genericInterruptManager.interrupts[interrupt_no].clearHandler) {
                genericInterruptManager.interrupts[interrupt_no].clearHandler();
            }
            genericInterruptManager.interrupts[interrupt_no].handler();
        }
    }
}
