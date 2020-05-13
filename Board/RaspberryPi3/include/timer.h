#ifndef __BOARD_RASP3_TIMER_H__
#define __BOARD_RASP3_TIMER_H__

#include <raspi3.h>
#include <stdint.h>

#define SYSTEM_TIMER_BASE (SYSTEM_TIMER_OFFSET + PERIPHERAL_BASE)

/**
 * timer init
 */
void timer_init(void);

void timer_set(uint32_t usecs);

void block_delay(uint32_t usecs);

typedef struct {
  uint8_t timer0_matched : 1;
  uint8_t timer1_matched : 1;
  uint8_t timer2_matched : 1;
  uint8_t timer3_matched : 1;
  uint32_t reserved : 28;
} timer_control_reg_t;

typedef struct {
  timer_control_reg_t control;
  uint32_t counter_low;
  uint32_t counter_high;
  uint32_t timer0;
  uint32_t timer1;
  uint32_t timer2;
  uint32_t timer3;
} timer_registers_t;

#endif // __BOARD_RASP3_TIMER_H__
