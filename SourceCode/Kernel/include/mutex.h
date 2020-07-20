//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_MUTEX_H__
#define __KERNEL_MUTEX_H__
#include <atomic.h>
#include <kqueue.h>
#include <stdint.h>

#define STATE_FREE 0u
#define STATE_CONTESTED 1u

typedef struct Mutex {
  Atomic *val;
  KQueue *waitList;
} Mutex;

void mutex_create(Mutex *mutex, Atomic *atmoic);
bool mutex_acquire(Mutex *mutex);
void mutex_release(Mutex *mutex);
#endif // __KERNEL_MUTEX_H__
