#include <../../Board/RaspberryPi3/include/timer.h>
#include <../../Board/RaspberryPi3/include/uart.h>
#include <interrupt.h>
#include <stdint.h>
#include <stdlib.h>

void clean_bss(uint8_t *start, uint8_t *end) {
  uint32_t i;
  for (i = 0; start + i < end; i++) {
    *(start + i) = '\0';
  }
}

void kernel_main(void) {
  uart_init();
  interrupt_init();
  timer_init();
}
