#include <stdlib.h>
#include <synestia_os_hal.h>
#include <timer.h>
#include <uart.h>

void init_bsp(void) {
  print("[Device] uart_init...\n");
  uart_init();
  print("[Device] uart_init complete.\n");

  print("[Device] timer_init...\n");
  timer_init();
  print("[Device] timer_init complete.\n");
}
