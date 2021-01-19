#ifndef __BOARD_RASP_UART_H__
#define __BOARD_RASP_UART_H__

#include "libc/stdint.h"

#define UART_DR_OFFSET 0x00
#define UART_FR_OFFSET 0x18
#define UART_IBRD_OFFSET 0x24
#define UART_FBRD_OFFSET 0x28
#define UART_LCRH_OFFSET 0x2C
#define UART_CR_OFFSET 0x30
#define UART_IMSC_OFFSET 0x38
#define UART_ICR_OFFSET 0x44

extern void io_writeb(uint8_t val, void *addr);

extern void io_writew(uint16_t val, void *addr);

extern void io_writel(uint32_t val, void *addr);

extern uint8_t io_readb(void *addr);

extern uint16_t io_readw(void *addr);

extern uint32_t io_readl(void *addr);

void uart_init(void);
void uart_put_char(uint8_t ch);
void uart_print(const char *str);

#endif// __BOARD_RASP_UART_H__
