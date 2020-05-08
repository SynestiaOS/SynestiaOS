#pragma once
#include <stdint.h>

extern uint32_t __stack;

void Reset_Handler(void);
void SysTick_Handler(void);
void PendSV_Handler(void);
void NMI_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);

void interrupt_init();

void enable_interrupt();

void disable_interrupt();

