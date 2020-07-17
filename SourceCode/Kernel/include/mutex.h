//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_MUTEX_H__
#define __KERNEL_MUTEX_H__
#include <stdint.h>
#include <atomic.h>

Atomic STATE_FREE = 0u;
Atomic STATE_CONTESTED = 1u;

typedef struct Mutex{
    Atomic val;
} Mutex;

void mutex_create(Mutex *mutex);
bool mutex_acquire(Mutex *mutex);
void mutex_release(Mutex *mutex);
#endif // __KERNEL_MUTEX_H__

