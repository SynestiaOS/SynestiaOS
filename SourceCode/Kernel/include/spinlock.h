//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_SPINLOCK_H__
#define __KERNEL_SPINLOCK_H__
#include <atomic.h>

typedef struct SpinLock {
  Atomic *lock;
} SpinLock;

void spinlock_create(SpinLock *spinLock, Atomic *atomic);
void spinlock_acquire(SpinLock *spinLock);
void spinlock_release(SpinLock *spinLock);
#endif // __KERNEL_SPINLOCK_H__
