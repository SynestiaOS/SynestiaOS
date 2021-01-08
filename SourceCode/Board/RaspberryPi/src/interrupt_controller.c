//
// Created by XingfengYang on 2021/1/8.
//
#include "raspi2/interrupt_controller.h"
#include "kernel/log.h"


#define IRQ_IS_BASIC(x) ((x >= 64))
#define IRQ_IS_GPU2(x) ((x >= 32 && x < 64))
#define IRQ_IS_GPU1(x) ((x < 32))

static rpi_irq_controller_t *rpiIRQController = (rpi_irq_controller_t *) RPI_INTERRUPT_CONTROLLER_BASE;

rpi_irq_controller_t *getIRQController(void) { return rpiIRQController; }

void interrupt_controller_init(void) {
    getIRQController()->Disable_Basic_IRQs = 0xffffffff;
    getIRQController()->Disable_IRQs_1 = 0xffffffff;
    getIRQController()->Disable_IRQs_2 = 0xffffffff;
    LogInfo("[Interrupt]: interrupt init\n");
}

void interrupt_controller_register(uint32_t interrupt_no){
    if (IRQ_IS_BASIC(interrupt_no)) {
        getIRQController()->Enable_Basic_IRQs |= (1 << (interrupt_no - 64));
    } else if (IRQ_IS_GPU2(interrupt_no)) {
        getIRQController()->Enable_IRQs_2 |= (1 << (interrupt_no - 32));
    } else if (IRQ_IS_GPU1(interrupt_no)) {
        getIRQController()->Enable_IRQs_1 |= (1 << (interrupt_no));
    }
}
