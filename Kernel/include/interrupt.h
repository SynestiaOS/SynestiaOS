#pragma once
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

void interrupt_init();

void enable_interrupt();

void disable_interrupt();