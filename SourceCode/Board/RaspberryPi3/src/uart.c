#include <stdint.h>
#include <uart.h>

#if defined(RASPI2) || defined(RASPI3)

#include <raspi3.h>

#endif

void register_interrupt_handler(uint32_t interrupt_no, void (*interrupt_handler_func)(void),
                                void (*interrupt_clear_func)(void));

void uart_interrupt_handler(void);

void uart_init(void) {
    io_writel(0, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_CR_OFFSET));
    io_writel(0x7ff, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_ICR_OFFSET));
    io_writel(1, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_IBRD_OFFSET));
    io_writel(40, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_FBRD_OFFSET));
    io_writel((1 << 4) | (1 << 5) | (1 << 6), (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_LCRH_OFFSET));
    io_writel((1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10),
              (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_IMSC_OFFSET));
    io_writel((1 << 0) | (1 << 8) | (1 << 9), (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_CR_OFFSET));

    //register_interrupt_handler(57, uart_interrupt_handler, (void *) 0);
    io_writel(0x10, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_IMSC_OFFSET));
}

static void do_uart_put_char(uint8_t ch) {
    while (io_readl((void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_FR_OFFSET)) & (1 << 5));
    io_writel(ch, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_DR_OFFSET));
}

void uart_put_char(uint8_t ch) {
    if (ch == '\r') {
        do_uart_put_char('\n');
    }
    if (ch == '\n') {
        do_uart_put_char('\r');
    }
    do_uart_put_char(ch);
}

uint8_t do_uart_get_char(void) {
    while (io_readl((void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_FR_OFFSET)) & (1 << 4));
    return ((uint8_t) (io_readl((void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_DR_OFFSET)) & 0xff));
}

void uart_interrupt_handler(void) {
    uart_put_char(do_uart_get_char());
}
