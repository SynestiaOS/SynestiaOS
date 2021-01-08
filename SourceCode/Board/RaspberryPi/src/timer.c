#include "raspi2/timer.h"
#include "kernel/interrupt.h"
#include "kernel/log.h"
#include "libc/stdlib.h"


extern InterruptManager genericInterruptManager;

static timer_registers_t *timer_regs = (timer_registers_t *) SYSTEM_TIMER_BASE;

void system_timer_irq_handler(void) {
    LogInfo("[Timer]: system timer interrupt triggered\n");
    timer_set(300);
}

void system_timer_irq_clear(void) { timer_regs->control.timer1_matched = 1; }

void timer_set(uint32_t usecs) { timer_regs->timer1 = timer_regs->counter_low + usecs; }

void system_timer_init(void) {
    Interrupt timerInterrupt;
    timerInterrupt.interruptNumber = 1;
    timerInterrupt.handler = system_timer_irq_handler;
    timerInterrupt.clearHandler = system_timer_irq_clear;
    genericInterruptManager.operation.registerInterrupt(&genericInterruptManager, timerInterrupt);
}

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
    genericInterruptManager.operation.registerInterrupt(&genericInterruptManager, timerInterrupt);
}
