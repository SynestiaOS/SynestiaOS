#ifndef __BOARD_RASP_TIMER_H__
#define __BOARD_RASP_TIMER_H__

#include "libc/stdint.h"
#include "raspi2/raspi.h"

extern void io_writel(uint32_t val, void *addr);

void generic_timer_init(void);

#endif// __BOARD_RASP_TIMER_H__
