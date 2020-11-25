//
// Created by tcz001 on 2020/8/7.
//

#ifndef __BOARD_RASP_LED_H__
#define __BOARD_RASP_LED_H__

#include "libc/stdint.h"

#define REG8(address) (*(volatile uint8_t *) (address))
#define REG16(address) (*(volatile uint16_t *) (address))
#define REG32(address) (*(volatile uint32_t *) (address))

int led_init(void);

#endif// __BOARD_RASP_LED_H__
