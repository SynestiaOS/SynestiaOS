#include "kernel/interrupt.h"
#include "arm/vmm.h"
#include "kernel/log.h"
#include "libc/stdlib.h"
#include "raspi2/timer.h"

static rpi_irq_controller_t *rpiIRQController = (rpi_irq_controller_t *) RPI_INTERRUPT_CONTROLLER_BASE;

rpi_irq_controller_t *getIRQController(void) { return rpiIRQController; }

void init_interrupt() {
    getIRQController()->Disable_Basic_IRQs = 0xffffffff;
    getIRQController()->Disable_IRQs_1 = 0xffffffff;
    getIRQController()->Disable_IRQs_2 = 0xffffffff;
    LogInfo("[Interrupt]: interrupt init\n");
    disable_interrupt();
}

uint32_t is_interrupt_enabled() {
    uint32_t cpsr;
    __asm__ __volatile__("mrs %0, cpsr"
    : "=r"(cpsr)
    :);
    return ((cpsr >> 7) & 1) == 0;
}

void enable_interrupt() {
    if (!is_interrupt_enabled()) {
        __asm__ __volatile__("cpsie i");
        LogInfo("[Interrupt]: enable\n");
    }
}

void disable_interrupt() {
    if (is_interrupt_enabled()) {
        __asm__ __volatile__("cpsid i");
        LogInfo("[Interrupt]: disable\n");
    }
}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_handler(void) {}

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

#define IRQ_IS_BASIC(x) ((x >= 64))
#define IRQ_IS_GPU2(x) ((x >= 32 && x < 64))
#define IRQ_IS_GPU1(x) ((x < 32))

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

void interrupt_handler(void) {
    for (uint32_t interrupt_no = 0; interrupt_no < IRQ_NUMS; interrupt_no++) {
        if (irq_handlers[interrupt_no].registered == 1) {
            LogInfo("[Interrupt]: interrupt '%d' triggered.\n", interrupt_no);
            if (irq_handlers[interrupt_no].interrupt_clear_func) {
                irq_handlers[interrupt_no].interrupt_clear_func();
            }

            disable_interrupt();
            irq_handlers[interrupt_no].interrupt_handler_func();
            enable_interrupt();
        }
    }
}

void fast_interrupt_handler(void) {
    LogError("[Interrupt]: fast irq\n");
}

TimerHandler *timerHandler = nullptr;

void register_time_interrupt(TimerHandler *handler) {
    if (timerHandler == nullptr) {
        timerHandler = handler;
    } else {
        klist_append(&timerHandler->node, &handler->node);
    }
}

TimerHandler *timer_get_handler(void) { return timerHandler; }


void interrupt_manager_default_register(InterruptManager *manager, Interrupt interrupt) {
    manager->interrupts[interrupt.interruptNumber].handler = interrupt.handler;
    manager->interrupts[interrupt.interruptNumber].clearHandler = interrupt.clearHandler;
    manager->registed[interrupt.interruptNumber] = 1;

    uint32_t interrupt_no = interrupt.interruptNumber;
    if (IRQ_IS_BASIC(interrupt_no)) {
        getIRQController()->Enable_Basic_IRQs |= (1 << (interrupt_no - 64));
    } else if (IRQ_IS_GPU2(interrupt_no)) {
        getIRQController()->Enable_IRQs_2 |= (1 << (interrupt_no - 32));
    } else if (IRQ_IS_GPU1(interrupt_no)) {
        getIRQController()->Enable_IRQs_1 |= (1 << (interrupt_no));
    }
}

void interrupt_manager_default_unregister(InterruptManager *manager, Interrupt interrupt) {
    manager->interrupts[interrupt.interruptNumber].handler = nullptr;
    manager->interrupts[interrupt.interruptNumber].clearHandler = nullptr;
    manager->registed[interrupt.interruptNumber] = 0;
}

void interrupt_manager_default_enable(InterruptManager *manager) {
    if (!is_interrupt_enabled()) {
        __asm__ __volatile__("cpsie i");
        LogInfo("[Interrupt]: enable\n");
    }
}

void interrupt_manager_default_disable(InterruptManager *manager) {
    if (is_interrupt_enabled()) {
        __asm__ __volatile__("cpsid i");
        LogInfo("[Interrupt]: disable\n");
    }
}

void interrupt_manager_default_init(InterruptManager *manager) {
    getIRQController()->Disable_Basic_IRQs = 0xffffffff;
    getIRQController()->Disable_IRQs_1 = 0xffffffff;
    getIRQController()->Disable_IRQs_2 = 0xffffffff;
    LogInfo("[Interrupt]: interrupt init\n");
    disable_interrupt();
}

InterruptManager *interrupt_manager_create(InterruptManager *manger) {
    manger->operation.init = (InterruptManagerOperationInit) interrupt_manager_default_init;
    manger->operation.registerInterrupt = (InterruptManagerOperationRegister) interrupt_manager_default_register;
    manger->operation.unRegisterInterrupt = (InterruptManagerOperationUnRegister) interrupt_manager_default_register;
    manger->operation.enableInterrupt = (InterruptManagerOperationEnableInterrupt) interrupt_manager_default_enable;
    manger->operation.disableInterrupt = (InterruptManagerOperationDisableInterrupt) interrupt_manager_default_disable;


    return manger;
}
