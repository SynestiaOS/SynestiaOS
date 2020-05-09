#include <../../Board/RaspberryPi3/include/uart.h>
#include <interrupt.h>
#include <stdint.h>

void clean_bss(uint8_t *start, uint8_t *end) {
  uint32_t i;
  for (i = 0; start + i < end; i++) {
    *(start + i) = '\0';
  }
}

void kernel_main(void) {
  const char str[] = "hello world\n";
  uint32_t i;
  uart_init();
  interrupt_init();
  for (i = 0; i < sizeof(str); i++) {
    uart_putc(str[i]);
  }
}