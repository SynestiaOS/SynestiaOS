#include <uart.h>

#if defined(RASPI2) || defined(RASPI3)
#include <raspi3.h>
#endif

void uart_init(void) {
  io_writel(0, (void *)(UART0_BASE + UART_CR_OFFSET));
  io_writel(0x7ff, (void *)(UART0_BASE + UART_ICR_OFFSET));
  io_writel(1, (void *)(UART0_BASE + UART_IBRD_OFFSET));
  io_writel(40, (void *)(UART0_BASE + UART_FBRD_OFFSET));
  io_writel((1 << 4) | (1 << 5) | (1 << 6), (void *)(UART0_BASE + UART_LCRH_OFFSET));
  io_writel((1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10),
            (void *)(UART0_BASE + UART_IMSC_OFFSET));
  io_writel((1 << 0) | (1 << 8) | (1 << 9), (void *)(UART0_BASE + UART_CR_OFFSET));
}

void uart_putc(uint8_t ch) {
  while (io_readl((void *)(UART0_BASE + UART_FR_OFFSET)) & (1 << 5))
    ;
  io_writel(ch, (void *)(UART0_BASE + UART_DR_OFFSET));
}

