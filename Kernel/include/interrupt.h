#pragma once
#include <stdint.h>

extern uint32_t __stack;

void interrupt_init();

void enable_interrupt();

void disable_interrupt();

void Reset_Handler(void);
void undefined_instruction(void);
void software_interrupt(void);
void prefetch_abort(void);
void data_abort(void);
void irq(void);
void fiq(void);
