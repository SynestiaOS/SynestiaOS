//
// Created by XingfengYang on 2020/7/17.
//
#include <spinlock.h>

void spinlock_create(SpinLock *spinLock, Atomic *atomic) { atomic_create(atomic); }

void spinlock_acquire(SpinLock *spinLock) {
  if (atomic_get(spinLock->lock) == 0) {
    atomic_set(spinLock->lock, 1);
  } else {
    asm volatile("WFE");
  }
}

void spinlock_release(SpinLock *spinLock) {
  atomic_set(spinLock->lock, 0);
  asm volatile("SEV");
}