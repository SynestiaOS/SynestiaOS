#include "raspi2/interrupt_controller.h"
#include "raspi2/synestia_os_hal.h"
#include "kernel/log.h"
#include "libc/stdlib.h"
#include "raspi2/timer.h"
#include "raspi2/uart.h"
#include "raspi2/gic400.h"

void synestia_init_bsp(void) {
    uart_init();
    int mmioBase = PERIPHERAL_BASE;
    LogInfo("[MMIO]: %d \n", mmioBase);
    LogInfo("[HAL]: uart_init complete.\n");

}

void synestia_init_timer(void) {
    LogInfo("[HAL]： timer_init...\n");
    LogInfo("[HAL]: generic_timer_init...\n");
    generic_timer_init();
    LogInfo("[HAL]: generic_timer_init complete.\n");
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
