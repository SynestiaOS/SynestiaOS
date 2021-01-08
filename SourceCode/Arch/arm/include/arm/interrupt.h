//
// Created by XingfengYang on 2021/1/8.
//

#ifndef SYNESTIAOS_INTERRUPT_H
#define SYNESTIAOS_INTERRUPT_H

#include "libc/stdint.h"

/**
 * check interrupt status form cpsr register
 * @return
 */
uint32_t arch_is_interrupt_enabled();

/**
 * enable interrupt with cpsie
 */
void arch_enable_interrupt();

/**
 * disable instrrupt with cpsid
 */
void arch_disable_interrupt();

#endif //SYNESTIAOS_INTERRUPT_H
