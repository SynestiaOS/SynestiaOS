#ifndef _URT_H_
#define _URT_H_

#include <common.h>

#define DEFAULT_UART_CLK            (3 * 1000000)
#define DEFAULT_BAUD    115200

#define UART_DR_OFFSET      0x00
#define UART_RSRECR_OFFSET  0x04
#define UART_FR_OFFSET      0x18
#define UART_ILPR_OFFSET    0x20
#define UART_IBRD_OFFSET    0x24
#define UART_FBRD_OFFSET    0x28
#define UART_LCRH_OFFSET    0x2C
#define UART_CR_OFFSET      0x30
#define UART_IFLS_OFFSE     0x34
#define UART_IMSC_OFFSET    0x38
#define UART_RIS_OFFSET     0x3C
#define UART_MIS_OFFSET     0x40
#define UART_ICR_OFFSET     0x44
#define UART_DMACR_OFFSET   0x48
#define UART_ITCR_OFFSET    0x80
#define UART_ITIP_OFFSET    0x84
#define UART_ITOP_OFFSET    0x88
#define UART_TDR_OFFSET     0x8C

extern void uart_init(void);
extern void uart_putc(uint8_t ch);

#endif