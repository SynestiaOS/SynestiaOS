#ifndef __OS_HAL_H__
#define __OS_HAL_H__

#include "libc/stdbool.h"

/**
 * bsp
 * do some bsp configuration stuff.
 * e.g. uart init
 **/

void synestia_init_bsp(void);

void synestia_init_timer(void);

void synestia_interrupt_enable(uint32_t no);
bool synestia_interrupt_pending(uint32_t no);
bool synestia_interrupt_clear(uint32_t no);
void synestia_interrupt_disable(uint32_t no);

void synestia_init_interrupt(void);



#endif// __OS_HAL_H__
