//
// Created by tcz001 on 2020/8/7.
//

#ifndef __BOARD_RASP_GPIO_H__
#define __BOARD_RASP_GPIO_H__

#include "raspi2/raspi.h"

#define GPIO_BASE (PERIPHERAL_BASE | GPIO_OFFSET)
/*
 * GPIO SELECT, SET and CLEAR register addresses
 */

// GPIO function select (GFSEL) registers have 3 bits per GPIO
#define GPFSEL0 (GPIO_BASE | 0x0) // GPIO select 0
#define GPFSEL1 (GPIO_BASE | 0x4) // GPIO select 1
#define GPFSEL2 (GPIO_BASE | 0x8) // GPIO select 2
#define GPFSEL3 (GPIO_BASE | 0xC) // GPIO select 3
#define GPFSEL4 (GPIO_BASE | 0x10)// GPIO select 4
#define GPIO_INPUT (0 << 0)       // GPIO is input      (000)
#define GPIO_OUTPUT (1 << 0)      // GPIO is output     (001)
#define GPIO_ALT0 (4)             // GPIO is Alternate0 (100)
#define GPIO_ALT1 (5)             // GPIO is Alternate1 (101)
#define GPIO_ALT2 (6)             // GPIO is Alternate2 (110)
#define GPIO_ALT3 (7)             // GPIO is Alternate3 (111)
#define GPIO_ALT4 (3)             // GPIO is Alternate4 (011)
#define GPIO_ALT5 (2)             // GPIO is Alternate5 (010)

// GPIO SET/CLEAR registers have 1 bit per GPIO
#define GPSET0 (GPIO_BASE | 0x1C)// set0 (GPIO 0 - 31)
#define GPSET1 (GPIO_BASE | 0x20)// set1 (GPIO 32 - 63)
#define GPCLR0 (GPIO_BASE | 0x28)// clear0 (GPIO 0 - 31)
#define GPCLR1 (GPIO_BASE | 0x2C)// clear1 (GPIO 32 - 63)

// GPIO Pull Up and Down Configuration registers
#define GPPUD (GPIO_BASE | 0x94)
#define GPPUD_OFF (0 << 0)
#define GPPUD_PULL_DOWN (1 << 0)
#define GPPUD_PULL_UP (1 << 1)
#define GPPUDCLK0 (GPIO_BASE | 0x98)
#define GPPUDCLK1 (GPIO_BASE | 0x9C)

#endif// __BOARD_RASP_GPIO_H__