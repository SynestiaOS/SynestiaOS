/*
    Part of the Raspberry-Pi Bare Metal Tutorials
    https://www.valvers.com/rpi/bare-metal/
    Copyright (c) 2013-2018, Brian Sidebotham

    This software is licensed under the MIT License.
    Please see the LICENSE file included with this software.

*/

//#include <stdint.h>
#include "raspi2/armtimer.h"
#include "libc/string.h"
#include "raspi2/timer.h"
#include "kernel/interrupt.h"
#include "kernel/log.h"
#include "libc/stdlib.h"


static rpi_arm_timer_t* rpiArmTimer = (rpi_arm_timer_t*)RPI_ARMTIMER_BASE;

extern InterruptManager genericInterruptManager;

rpi_arm_timer_t* RPI_GetArmTimer(void)
{
    return rpiArmTimer;
}

void RPI_ArmTimerInit(void)
{
    RPI_GetArmTimer()->Load = 0x400000;

    RPI_GetArmTimer()->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256;

}


void arm_timer_irq_clear(void) {
    LogInfo("Arm Timer Clear\n");
    if( RPI_GetArmTimer()->MaskedIRQ ) {
        RPI_GetArmTimer()->IRQClear = 1;
    }
}

void arm_timer_irq_handler(void) {

    LogInfo("Arm Timer Handler\n");
    genericInterruptManager.operation.tick(&genericInterruptManager);
}

void arm_timer_init(void) {
    Interrupt timerInterrupt;
    timerInterrupt.interruptNumber = 2;
    timerInterrupt.handler = arm_timer_irq_handler;
    timerInterrupt.clearHandler = arm_timer_irq_clear;
    memset(timerInterrupt.name, 0, sizeof(timerInterrupt.name));
    strcpy(timerInterrupt.name, "Arm Timer");
    genericInterruptManager.operation.registerInterrupt(&genericInterruptManager, timerInterrupt);
}
