#include "libc/string.h"
#include "raspi2/timer.h"
#include "kernel/interrupt.h"
#include "kernel/log.h"
#include "libc/stdlib.h"

extern InterruptManager genericInterruptManager;

void enable_core0_irq(void) { io_writel(0x8, 0x40000040); }

uint32_t read_cntfrq(void) {
    uint32_t value;
    asm volatile("mrc p15, 0, %0, c14, c0, 0"
    : "=r"(value));
    return value;
}

void write_cntvtval(uint32_t value) { asm volatile("mcr p15, 0, %0, c14, c3, 0"::"r"(value)); }

void enable_cntv(void) {
    uint32_t value = 1;
    asm volatile("mcr p15, 0, %0, c14, c3, 1"::"r"(value));
}

void generic_timer_irq_clear(void) {
    // DO Nothing
}

void generic_timer_irq_handler(void) {
    LogInfo("[Timer]: generic timer interrupted\n");
    write_cntvtval(read_cntfrq() / 10);

    genericInterruptManager.operation.tick(&genericInterruptManager);
}

void generic_timer_init(void) {
    write_cntvtval(read_cntfrq() / 10);
    enable_cntv();
    enable_core0_irq();

    Interrupt timerInterrupt;
    timerInterrupt.interruptNumber = 1;
    timerInterrupt.handler = generic_timer_irq_handler;
    timerInterrupt.clearHandler = generic_timer_irq_clear;
    memset(timerInterrupt.name, 0, sizeof(timerInterrupt.name));
    strcpy(timerInterrupt.name, "generic timer");
    genericInterruptManager.operation.registerInterrupt(&genericInterruptManager, timerInterrupt);
}
