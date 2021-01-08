#ifndef __OS_HAL_H__
#define __OS_HAL_H__

/**
 * bsp
 * do some bsp configuration stuff.
 * e.g. uart init
 **/

void synestia_init_bsp(void);

void synestia_init_timer(void);

void synestia_interrupt_register(uint32_t no);

void synestia_init_interrupt(void);

#endif// __OS_HAL_H__
