//
// Created by XingfengYang on 2021/1/8.
//

#ifndef SYNESTIAOS_INTERRUPT_CONTROLLER_H
#define SYNESTIAOS_INTERRUPT_CONTROLLER_H

#include "libc/stdbool.h"
#include "libc/stdint.h"
#include "raspi2/raspi.h"

#define RPI_INTERRUPT_CONTROLLER_BASE (PERIPHERAL_BASE + INTERRUPTS_OFFSET + 0x200)


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

void interrupt_controller_enable(uint32_t no);
void interrupt_controller_disable(uint32_t no);
void interrupt_controller_clear(uint32_t no);
bool interrupt_controller_pending(uint32_t no);



#endif //SYNESTIAOS_INTERRUPT_CONTROLLER_H
