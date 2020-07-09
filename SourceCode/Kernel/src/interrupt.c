#include <interrupt.h>
#include <stdlib.h>
#include <timer.h>

static rpi_irq_controller_t *rpiIRQController = (rpi_irq_controller_t *) RPI_INTERRUPT_CONTROLLER_BASE;

rpi_irq_controller_t *getIRQController(void) { return rpiIRQController; }

void init_interrupt() {
    getIRQController()->Disable_Basic_IRQs = 0xffffffff;
    getIRQController()->Disable_IRQs_1 = 0xffffffff;
    getIRQController()->Disable_IRQs_2 = 0xffffffff;

    enable_interrupt();
    printf("[Interrupt]: interrupt init\n");
}

uint32_t is_interrupt_enabled() {
    uint32_t cpsr;
    __asm__ __volatile__("mrs %0, cpsr" : "=r"(cpsr) :);
    return ((cpsr >> 7) & 1) == 0;
}

void enable_interrupt() {
    if (!is_interrupt_enabled()) {
        __asm__ __volatile__("cpsie i");
        printf("[Interrupt]: enable\n");
    }
}

void disable_interrupt() {
    if (is_interrupt_enabled()) {
        __asm__ __volatile__("cpsid i");
        printf("[Interrupt]: disable\n");
    }
}

void swi(uint32_t num) {
    __asm__ __volatile__("push {lr}\n\t"
                         "mov r0, %0\n\t"
                         "swi 0x0\n\t"
                         "pop {pc}\n\t"::"r"(num));
}

void hello_from_swi() {
    disable_interrupt();
    const char str[] = "hello from swi\n";
    print(str);
    enable_interrupt();
}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_handler(void) {}

void __attribute__((interrupt("SWI"))) software_interrupt_handler(void) { hello_from_swi(); }

void __attribute__((interrupt("ABORT"))) prefetch_abort_handler(void) {}

void __attribute__((interrupt("ABORT"))) data_abort_handler(void) {}

void unused_handler(void) {}

#define IRQ_IS_BASIC(x) ((x >= 64))
#define IRQ_IS_GPU2(x) ((x >= 32 && x < 64))
#define IRQ_IS_GPU1(x) ((x < 32))
#define IRQ_IS_PENDING(regs, num)                                                                                      \
  ((IRQ_IS_BASIC(num) && ((1 << (num - 64)) & regs->IRQ_basic_pending)) ||                                             \
   (IRQ_IS_GPU2(num) && ((1 << (num - 32)) & regs->IRQ_pending_2)) ||                                                  \
   (IRQ_IS_GPU1(num) && ((1 << (num)) & regs->IRQ_pending_1)))

typedef struct irq_handler {
    void (*interrupt_handler_func)(void);

    void (*interrupt_clear_func)(void);

    uint32_t registered;
} irq_handler_t;

/**
 * map for interrupt number and it's handler func and clear func
 */
#define IRQ_NUMS 96
irq_handler_t irq_handlers[IRQ_NUMS];

void register_interrupt_handler(uint32_t interrupt_no, void (*interrupt_handler_func)(void),
                                void (*interrupt_clear_func)(void)) {
    irq_handlers[interrupt_no].interrupt_handler_func = interrupt_handler_func;
    irq_handlers[interrupt_no].interrupt_clear_func = interrupt_clear_func;
    irq_handlers[interrupt_no].registered = 1;

    if (IRQ_IS_BASIC(interrupt_no)) {
        getIRQController()->Enable_Basic_IRQs |= (1 << (interrupt_no - 64));
    } else if (IRQ_IS_GPU2(interrupt_no)) {
        getIRQController()->Enable_IRQs_2 |= (1 << (interrupt_no - 32));
    } else if (IRQ_IS_GPU1(interrupt_no)) {
        getIRQController()->Enable_IRQs_1 |= (1 << (interrupt_no));
    }
}

void __attribute__((interrupt("IRQ"))) interrupt_handler(void) {
    printf("[IRQ]: triggered\n");
    for (uint32_t interrupt_no = 0; interrupt_no < IRQ_NUMS; interrupt_no++) {
        if (irq_handlers[interrupt_no].registered == 1) {
            if (irq_handlers[interrupt_no].interrupt_clear_func) {
                irq_handlers[interrupt_no].interrupt_clear_func();
            }

            disable_interrupt();
            irq_handlers[interrupt_no].interrupt_handler_func();
            enable_interrupt();
        }
    }
}

void __attribute__((interrupt("FIQ"))) fast_interrupt_handler(void) {}

timer_handler_t *timerHandler = nullptr;

void register_time_interrupt(timer_handler_t *handler) {
    if (timerHandler == nullptr) {
        timerHandler = handler;
    } else {
        klist_append(&timerHandler->node, &handler->node);
    }
}
