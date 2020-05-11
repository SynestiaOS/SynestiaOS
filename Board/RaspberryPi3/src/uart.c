#include <uart.h>

#if defined(RASPI2) || defined(RASPI3)
#include <raspi3.h>
#endif

void uart_init(void) {
    io_writel(0, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_CR_OFFSET));
    io_writel(0x7ff, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_ICR_OFFSET));
    io_writel(1, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_IBRD_OFFSET));
    io_writel(40, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_FBRD_OFFSET));
    io_writel((1 << 4) | (1 << 5) | (1 << 6), (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_LCRH_OFFSET));
    io_writel((1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10),
              (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_IMSC_OFFSET));
    io_writel((1 << 0) | (1 << 8) | (1 << 9), (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_CR_OFFSET));
}

void uart_putc(uint8_t ch) {
    while (io_readl((void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_FR_OFFSET)) & (1 << 5));
    io_writel(ch, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_DR_OFFSET));
}

void uart_print(const char *str) {
    while (*str) {
        uart_putc(*str);
        str++;
    }
}

