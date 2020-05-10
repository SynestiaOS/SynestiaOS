#pragma once
#include <../../Board/RaspberryPi3/include/raspi3.h>
#include <stdint.h>

#define ARM_INTERRUPT_REGISTER_BASE 0x7E00B000
#define RPI_INTERRUPT_CONTROLLER_BASE   (ARM_INTERRUPT_REGISTER_BASE+0x0200)

typedef struct {
    volatile  uint32_t IRQ_basic_pending;
    volatile  uint32_t IRQ_pending_1;
    volatile  uint32_t IRQ_pending_2;
    volatile  uint32_t FIQ_control;
    volatile  uint32_t Enable_IRQs_1;
    volatile  uint32_t Enable_IRQs_2;
    volatile  uint32_t Enable_Basic_IRQs;
    volatile  uint32_t Disable_IRQs_1;
    volatile  uint32_t Disable_IRQs_2;
    volatile  uint32_t Disable_Basic_IRQs;
} rpi_irq_controller_t;

rpi_irq_controller_t* getIRQController(void);

#define INTERRUPTS_BASE (PERIPHERAL_BASE + INTERRUPTS_OFFSET)
#define INTERRUPTS_PENDING (INTERRUPTS_BASE + 0x200)

#define IRQ_IS_BASIC(x) ((x >= 64 ))
#define IRQ_IS_GPU2(x) ((x >= 32 && x < 64 ))
#define IRQ_IS_GPU1(x) ((x < 32 ))
#define IRQ_IS_PENDING(regs, num) ((IRQ_IS_BASIC(num) && ((1 << (num-64)) & regs->IRQ_basic_pending)) || (IRQ_IS_GPU2(num) && ((1 << (num-32)) & regs->IRQ_pending_2)) || (IRQ_IS_GPU1(num) && ((1 << (num)) & regs->IRQ_pending_1)))
#define NUM_IRQS 72

__inline__ int INTERRUPTS_ENABLED(void) {
    int res;
    __asm__ __volatile__("mrs %[res], CPSR": [res] "=r" (res)::);
    return ((res >> 7) & 1) == 0;
}

__inline__ void ENABLE_INTERRUPTS(void) {
    if (!INTERRUPTS_ENABLED()) {
        __asm__ __volatile__("cpsie i");
    }
}

__inline__ void DISABLE_INTERRUPTS(void) {
    if (INTERRUPTS_ENABLED()) {
        __asm__ __volatile__("cpsid i");
    }
}

typedef void (*interrupt_handler_f)(void);
typedef void (*interrupt_clearer_f)(void);

typedef enum {
    SYSTEM_TIMER_1 = 1,
    USB_CONTROLER = 9,
    ARM_TIMER = 64
} irq_number_t;

void interrupt_init();
void enable_interrupt();
void disable_interrupt();

void register_irq_handler(irq_number_t irq_num, interrupt_handler_f handler, interrupt_clearer_f clearer);
void unregister_irq_handler(irq_number_t irq_num);
