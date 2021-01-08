//
// Created by XingfengYang on 2021/1/8.
//

#ifndef SYNESTIAOS_INTERRUPT_CONTROLLER_H
#define SYNESTIAOS_INTERRUPT_CONTROLLER_H

#include "libc/stdint.h"

#define ARM_INTERRUPT_REGISTER_BASE 0x3F00B000
#define RPI_INTERRUPT_CONTROLLER_BASE (ARM_INTERRUPT_REGISTER_BASE + 0x0200)


typedef struct {
    volatile uint32_t IRQ_basic_pending;
    volatile uint32_t IRQ_pending_1;
    volatile uint32_t IRQ_pending_2;
    volatile uint32_t FIQ_control;
    volatile uint32_t Enable_IRQs_1;
    volatile uint32_t Enable_IRQs_2;
    volatile uint32_t Enable_Basic_IRQs;
    volatile uint32_t Disable_IRQs_1;
    volatile uint32_t Disable_IRQs_2;
    volatile uint32_t Disable_Basic_IRQs;
} rpi_irq_controller_t;

rpi_irq_controller_t *getIRQController(void);

void interrupt_controller_init(void);

void interrupt_controller_register(uint32_t no);


#endif //SYNESTIAOS_INTERRUPT_CONTROLLER_H
