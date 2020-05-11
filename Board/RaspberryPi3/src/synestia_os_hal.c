#include <synestia_os_hal.h>
#include <uart.h>
#include <timer.h>

void init_bsp(void){
    uart_print("[Device] uart_init...\n");
    uart_init();
    uart_print("[Device] uart_init complete.\n");

    uart_print("[Device] timer_init...\n");
    timer_init();
    uart_print("[Device] timer_init complete.\n");
}
