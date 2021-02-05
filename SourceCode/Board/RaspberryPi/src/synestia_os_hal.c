#include "raspi2/interrupt_controller.h"
#include "raspi2/synestia_os_hal.h"
#include "kernel/log.h"
#include "libc/stdlib.h"
#include "raspi2/timer.h"
#include "raspi2/uart.h"
#include "raspi2/gic400.h"
#include "raspi2/armtimer.h"


void synestia_init_bsp(void) {
    //uart_init();
    RPI_AuxMiniUartInit( 115200, 8 );
    int mmioBase = PERIPHERAL_BASE;
    LogInfo("[MMIO]: %d \n", mmioBase);
    LogInfo("[HAL]: uart_init complete.\n");
    RPI_ArmTimerInit();
    RPI_EnableARMTimerInterrupt();
}

void synestia_init_timer(void) {
#ifndef RASPI4
    LogInfo("[HAL]： timer_init...\n");
    LogInfo("[HAL]: generic_timer_init...\n");
    generic_timer_init();
    LogInfo("[HAL]: generic_timer_init complete.\n");
#else
    LogInfo("[HAL]： timer_init...\n");
    LogInfo("[HAL]: arm_timer_init...\n");
    arm_timer_init();
    LogInfo("[HAL]: armc_timer_init complete.\n");
#endif
}


void synestia_interrupt_enable(uint32_t no) {
    interrupt_controller_enable(no);
}

bool synestia_interrupt_pending(uint32_t no) {
    return interrupt_controller_pending(no);
}

bool synestia_interrupt_clear(uint32_t no) {
    interrupt_controller_clear(no);
}

void synestia_interrupt_disable(uint32_t no) {
    interrupt_controller_disable(no);
}

void synestia_init_interrupt(void) {
    LogInfo("[HAL] interrupt init\n")
#if defined(RASPI4)
    gic400_init(0xFF840000);
#else
    interrupt_controller_init();
#endif
}
