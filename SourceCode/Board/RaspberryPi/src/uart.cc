#include "libc/stdint.h"
#include "raspi2/uart.h"

#include "raspi2/raspi.h"

void register_interrupt_handler(uint32_t interrupt_no, void (*interrupt_handler_func)(void),
                                void (*interrupt_clear_func)(void));

void uart_interrupt_handler(void);

void uart_init(void) {
    // disable UART0
    // 0 = UART is disabled.
    //     If the UART is disabled in the middle of transmission or reception,
    //     it completes the current character before stopping.
    // 1 = the UART is enabled.
    io_writel(0, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_CR_OFFSET));

    // clear all UART0 interrupt. The UART_ICR Register is the interrupt clear register.
    io_writel(0x7ff, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_ICR_OFFSET));

    // The UART_IBRD Register is the integer part of the baud rate divisor value.
    io_writel(1, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_IBRD_OFFSET));

    // The UART_FBRD Register is the fractional part of the baud rate divisor value.
    io_writel(40, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_FBRD_OFFSET));

    // The UART_LCRH Register is the line control register. 1<<4 means Enable FIFOs, 1<<5|1<<6 means Word length, 0b11 = 8
    // bits
    io_writel((1 << 4) | (1 << 5) | (1 << 6), (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_LCRH_OFFSET));

    // The UART_IMSC Register is the interrupt mask set/clear register.
    // TODO(shifu): not sure what these bits mean ???
    io_writel((1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10),
              (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_IMSC_OFFSET));

    // enable UART0, 1<<8=Transmit enabled, 1<<9=Receive enabled
    io_writel((1 << 0) | (1 << 8) | (1 << 9), (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_CR_OFFSET));

    // register_interrupt_handler(57, uart_interrupt_handler, (void *) 0);
    // TODO(shifu) what does 0x10 mean ???
    io_writel(0x10, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_IMSC_OFFSET));
}

static void do_uart_put_char(uint8_t character) {
    // The UART_FR Register is the flag register. 1<<5 means Transmit FIFO is full.
    while (io_readl((void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_FR_OFFSET)) & (1 << 5)) {
    }

    // The UART_DR Register is the data register.
    // if the FIFOs are enabled, data written to this location is pushed onto the transmit FIFO.
    io_writel(character, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_DR_OFFSET));
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
    // The UART_FR Register is the flag register. 1<<4 means Receive FIFO empty.
    while (io_readl((void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_FR_OFFSET)) & (1 << 4)) {
    }

    return ((uint8_t)(io_readl((void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_DR_OFFSET)) & 0xff));
}

void uart_print(const char *str) {
    while (*str) {
        uart_put_char(*str);
        str++;
    }
}

void uart_interrupt_handler(void) { uart_put_char(do_uart_get_char()); }
