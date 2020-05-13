#include <stdlib.h>
#include <timer.h>

static timer_registers_t *timer_regs = (timer_registers_t *)SYSTEM_TIMER_BASE;

void timer_irq_handler(void) {
  print("timer interrupt triggered\n");
  timer_set(300);
}

void timer_irq_clear(void) { timer_regs->control.timer1_matched = 1; }

extern void register_interrupt_handler(uint32_t interrupt_no, void (*interrupt_handler_func)(void),
                                       void (*interrupt_clear_func)(void));

void timer_init(void) { register_interrupt_handler(1, timer_irq_handler, timer_irq_clear); }

void timer_set(uint32_t usecs) { timer_regs->timer1 = timer_regs->counter_low + usecs; }

__attribute__((optimize(0))) void block_delay(uint32_t usecs) {
  volatile uint32_t curr = timer_regs->counter_low;
  volatile uint32_t x = timer_regs->counter_low - curr;
  while (x < usecs) {
    x = timer_regs->counter_low - curr;
  }
}
