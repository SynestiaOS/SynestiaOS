#include "raspi2/interrupt_controller.h"
#include "raspi2/synestia_os_hal.h"
#include "kernel/log.h"
#include "libc/stdlib.h"
#include "raspi2/timer.h"
#include "raspi2/uart.h"

void synestia_init_bsp(void) {
    uart_init();
    LogInfo("[Device]: uart_init complete.\n");
}

void synestia_init_timer(void) {
    LogInfo("[Device]： timer_init...\n");

    LogInfo("[Device]: generic_timer_init...\n");
    generic_timer_init();
    LogInfo("[Device]: generic_timer_init complete.\n");
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
    interrupt_controller_init();
}
