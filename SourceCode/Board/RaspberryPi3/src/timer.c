#include <stdlib.h>
#include <timer.h>
#include <interrupt.h>

static timer_registers_t *timer_regs = (timer_registers_t *) SYSTEM_TIMER_BASE;

extern void register_interrupt_handler(uint32_t interrupt_no, void (*interrupt_handler_func)(void),
                                       void (*interrupt_clear_func)(void));


void system_timer_irq_handler(void) {
    print("timer interrupt triggered\n");
    timer_set(300);
}

void system_timer_irq_clear(void) { timer_regs->control.timer1_matched = 1; }

void system_timer_init(void) {
    register_interrupt_handler(1, system_timer_irq_handler, system_timer_irq_clear);
}

void timer_set(uint32_t usecs) { timer_regs->timer1 = timer_regs->counter_low + usecs; }

__attribute__((optimize(0))) void block_delay(uint32_t usecs) {
    volatile uint32_t curr = timer_regs->counter_low;
    volatile uint32_t x = timer_regs->counter_low - curr;
    while (x < usecs) {
        x = timer_regs->counter_low - curr;
    }
}

void enable_core0_irq(void) {
    io_writel(0x8, 0x40000040);
}

uint32_t read_cntfrq(void) {
    uint32_t value;
    asm volatile ("mrc p15, 0, %0, c14, c0, 0" : "=r"(value));
    return value;
}

void write_cntvtval(uint32_t value) {
    asm volatile ("mcr p15, 0, %0, c14, c3, 0"::"r"(value));
}

void enable_cntv(void) {
    uint32_t value = 1;
    asm volatile ("mcr p15, 0, %0, c14, c3, 1"::"r"(value));
}


void generic_timer_irq_clear(void) {
    //DO Nothing
}

void generic_timer_irq_handler(void) {
    printf("[Timer]: generic timer interrupted\n");
    write_cntvtval(read_cntfrq() / 5);
    TimerHandler *timerHandler = timer_get_handler();
    if (timerHandler != nullptr) {
        void (*timer_interrupt_handler)(void) = timerHandler->timer_interrupt_handler;
        (*timer_interrupt_handler)();
        while (timerHandler->node.next != nullptr) {
            TimerHandler *pHandler = getNode(timerHandler->node.next, TimerHandler, node);
            pHandler->timer_interrupt_handler();
            timerHandler = pHandler;
        }
    }
}


void generic_timer_init(void) {
    write_cntvtval(read_cntfrq() / 5);
    enable_cntv();
    enable_core0_irq();
    register_interrupt_handler(1, generic_timer_irq_handler, generic_timer_irq_clear);
}
