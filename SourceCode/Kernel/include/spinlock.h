//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_SPINLOCK_H__
#define __KERNEL_SPINLOCK_H__
#include <atomic.h>

typedef void (*SpinLockAcquire)(struct SpinLock *spinLock);
typedef void (*SpinLockRelease)(struct SpinLock *spinLock);

typedef struct SpinLockOperations {
  SpinLockAcquire acquire;
  SpinLockRelease release;
} SpinLockOperations;

typedef struct SpinLock {
  Atomic lock;
  SpinLockOperations operations;
} SpinLock;

void spinlock_create(SpinLock *spinLock);
#endif // __KERNEL_SPINLOCK_H__
