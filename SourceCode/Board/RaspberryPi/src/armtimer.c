/*
    Part of the Raspberry-Pi Bare Metal Tutorials
    https://www.valvers.com/rpi/bare-metal/
    Copyright (c) 2013-2018, Brian Sidebotham

    This software is licensed under the MIT License.
    Please see the LICENSE file included with this software.

*/

//#include <stdint.h>
#include "raspi2/armtimer.h"

static rpi_arm_timer_t* rpiArmTimer = (rpi_arm_timer_t*)RPI_ARMTIMER_BASE;


rpi_arm_timer_t* RPI_GetArmTimer(void)
{
    return rpiArmTimer;
}

void RPI_ArmTimerInit(void)
{
    /* Setup the system timer interrupt
    Timer frequency = Clk/256 * 0x400

    NOTE: If the system decides to alter the clock, the frequency of these
             interrupts will also change. The system timer remains consistent.
    */
    RPI_GetArmTimer()->Load = 0x4000;

    /* Setup the ARM Timer */
    RPI_GetArmTimer()->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256;

}
