#include "raspi2/uart.h"
#include "libc/stdint.h"
#include "raspi2/gpio.h"
#include "raspi2/raspi.h"

#define TX_FIFO_FULL     (1 << 5)
#define RX_FIFO_FULL     (1 << 6)

#define BAUD_RATE 115200
#if defined(RASPI3) || defined(RASPI4)
  // RPI 3/4 has a 48MHz clock as it was intended to work with BT
  #define CLOCK_RATE 48000000
#else
  // RPI 1/2 has a 3MHz clock by default
  #define CLOCK_RATE 3000000
#endif

void uart_init(void) {
    // disable UART0
    // 0 = UART is disabled.
    //     If the UART is disabled in the middle of transmission or reception,
    //     it completes the current character before stopping.
    // 1 = the UART is enabled.
  io_writel(0, (void *)(PERIPHERAL_BASE + UART0_OFFSET + UART_LCRH_OFFSET));
    io_writel(0, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_CR_OFFSET));

    // clear all UART0 interrupt. The UART_ICR Register is the interrupt clear register.
    io_writel(0x7ff, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_ICR_OFFSET));

  /* Select Alternate 0 for UART over GPIO pins 14 Tx and 15 Rx.*/
  uint32_t gpio;
  gpio = io_readl((void *)(GPFSEL1));
  gpio &= ~(7 << 12); /* clear GPIO 14 */
  gpio |= GPIO_ALT0 << 12; /* set GPIO 14 to Alt 0 */
  gpio &= ~(7 << 15); /* clear GPIO 15 */
  gpio |= GPIO_ALT0 << 15; /* set GPIO 15 to Alt 0 */
  io_writel(gpio, (void *)(GPFSEL1));

  /*
  ** GPPUD can be 0 (disable pull up/down)
  ** (0) disable pull up and pull down to float the GPIO
  ** (1 << 0) enable pull down (low)
  ** (1 << 1) enable pull up (high)
  */

  ///* Disable pull up/down for next configured GPIOs so they float. */
  io_writel(GPPUD_OFF, (void *)(GPPUD));
  //usleep(MICROS_PER_MILLISECOND); /* hold time */

  ///* Apply above configuration (floating) to UART Rx and Tx GPIOs. */
  io_writel((1 << 14) | (1 << 15), (void *)(GPPUDCLK0));/* GPIO 14 and 15 */
  //usleep(MICROS_PER_MILLISECOND); /* hold time */

  unsigned nClockRate = CLOCK_RATE;
  unsigned nBaudrate = BAUD_RATE;

  unsigned nBaud16 = nBaudrate * 16;
  unsigned nIntDiv = nClockRate / nBaud16;
  unsigned nFractDiv2 = (nClockRate % nBaud16) * 8 / nBaudrate;
  unsigned nFractDiv = nFractDiv2 / 2 + nFractDiv2 % 2;

    // The UART_IBRD Register is the integer part of the baud rate divisor value.
  io_writel(nIntDiv, (void *)(PERIPHERAL_BASE + UART0_OFFSET + UART_IBRD_OFFSET));

    // The UART_FBRD Register is the fractional part of the baud rate divisor value.
  io_writel(nFractDiv, (void *)(PERIPHERAL_BASE + UART0_OFFSET + UART_FBRD_OFFSET));

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
  // 0x10 == 1<<1 as the GPPUD_PULL_UP
    io_writel(0x10, (void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_IMSC_OFFSET));
}

static void do_uart_put_char(uint8_t character) {
    // The UART_FR Register is the flag register. 1<<5 means Transmit FIFO is full.
  while (io_readl((void *)(PERIPHERAL_BASE + UART0_OFFSET + UART_FR_OFFSET)) & TX_FIFO_FULL) {
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
  while (io_readl((void *)(PERIPHERAL_BASE + UART0_OFFSET + UART_FR_OFFSET)) & RX_FIFO_FULL) {
    }

    return ((uint8_t)(io_readl((void *) (PERIPHERAL_BASE + UART0_OFFSET + UART_DR_OFFSET)) & 0xff));
}

void uart_print(const char *str) {
    while (*str) {
        RPI_AuxMiniUartWrite(*str);
        //uart_put_char(*str);
        str++;
    }
}
