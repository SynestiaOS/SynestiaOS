#ifndef __BOARD_RASP_UART_H__
#define __BOARD_RASP_UART_H__

#include "libc/stdint.hpp"

#define DEFAULT_UART_CLK (3 * 1000000)
#define DEFAULT_BAUD 115200

#define UART_DR_OFFSET 0x00
#define UART_RSRECR_OFFSET 0x04
#define UART_FR_OFFSET 0x18
#define UART_ILPR_OFFSET 0x20
#define UART_IBRD_OFFSET 0x24
#define UART_FBRD_OFFSET 0x28
#define UART_LCRH_OFFSET 0x2C
#define UART_CR_OFFSET 0x30
#define UART_IFLS_OFFSE 0x34
#define UART_IMSC_OFFSET 0x38
#define UART_RIS_OFFSET 0x3C
#define UART_MIS_OFFSET 0x40
#define UART_ICR_OFFSET 0x44
#define UART_DMACR_OFFSET 0x48
#define UART_ITCR_OFFSET 0x80
#define UART_ITIP_OFFSET 0x84
#define UART_ITOP_OFFSET 0x88
#define UART_TDR_OFFSET 0x8C

extern void io_writeb(uint8_t val, void *addr);

extern void io_writew(uint16_t val, void *addr);

extern void io_writel(uint32_t val, void *addr);

extern uint8_t io_readb(void *addr);

extern uint16_t io_readw(void *addr);

extern uint32_t io_readl(void *addr);

void uart_init(void);
void uart_print(const char *str);

#endif// __BOARD_RASP_UART_H__
