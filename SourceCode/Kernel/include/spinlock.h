//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_SPINLOCK_H__
#define __KERNEL_SPINLOCK_H__
#include <atomic.h>

#define SpinLockCreate(x)                                                                                              \
  SpinLock x = {                                                                                                       \
      .lock =                                                                                                          \
          {                                                                                                            \
              .counter = 0,                                                                                            \
          },                                                                                                           \
      .operations =                                                                                                    \
          {                                                                                                            \
              .acquire = spinlock_default_acquire,                                                                     \
              .release = spinlock_default_release,                                                                     \
          },                                                                                                           \
  }

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

void spinlock_default_acquire(SpinLock *spinLock);
void spinlock_default_release(SpinLock *spinLock);

void spinlock_init(SpinLock *spinLock);
#endif // __KERNEL_SPINLOCK_H__
