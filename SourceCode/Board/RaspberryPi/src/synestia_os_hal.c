#include "raspi2/synestia_os_hal.h"
#include "kernel/log.h"
#include "libc/stdlib.h"
#include "raspi2/timer.h"
#include "raspi2/uart.h"

void init_bsp(void) {
    // logger is based on uart now
    // LogInfo("[Device]: uart_init...\n");
    uart_init();
    LogInfo("[Device]: uart_init complete.\n");

    print("[Device]： timer_init...\n");
    system_timer_init();
    print("[Device]： timer_init complete.\n");

    LogInfo("[Device]: generic_timer_init...\n");
    generic_timer_init();
    LogInfo("[Device]: generic_timer_init complete.\n");
}
