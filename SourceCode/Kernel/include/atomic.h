//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_ATOMIC_H__
#define __KERNEL_ATOMIC_H__
#include <stdint.h>
typedef uint32_t Atomic;

void atomic_set(Atomic *atomic,uint32_t val);
uint32_t atomic_get(Atomic *atomic);

#endif // __KERNEL_ATOMIC_H__

