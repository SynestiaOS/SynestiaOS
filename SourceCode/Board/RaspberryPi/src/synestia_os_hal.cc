#include "kernel/log.hpp"
#include "libc/stdlib.hpp"
#include "raspi2/synestia_os_hal.hpp"
#include "raspi2/timer.hpp"
#include "raspi2/uart.hpp"

void init_bsp(void) {
    LogInfo("[Device]: uart_init...\n");
    uart_init();
    LogInfo("[Device]: uart_init complete.\n");

    // print("[Device]： timer_init...\n");
    // system_timer_init();
    // print("[Device]： timer_init complete.\n");

    LogInfo("[Device]: generic_timer_init...\n");
    generic_timer_init();
    LogInfo("[Device]: generic_timer_init complete.\n");
}
