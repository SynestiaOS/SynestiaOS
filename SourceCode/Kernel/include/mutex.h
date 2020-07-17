//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_MUTEX_H__
#define __KERNEL_MUTEX_H__
#include <stdint.h>
#include <atmoic.h>
#include <stdbool.h>

Atmoic STATE_FREE = 0u;
Atmoic STATE_CONTESTED = 1u;

typedef struct Mutex{
    Atmoic val;
} Mutex;

void mutex_create(Mutex *mutex);
bool mutex_acquire(Mutex *mutex);
void mutex_release(Mutex *mutex);
#endif // __KERNEL_MUTEX_H__

