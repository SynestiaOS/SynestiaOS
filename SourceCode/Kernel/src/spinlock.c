//
// Created by XingfengYang on 2020/7/17.
//
#include <spinlock.h>

void spinlock_default_acquire(SpinLock *spinLock) {
  if (atomic_get(&spinLock->lock) == 0) {
    atomic_set(&spinLock->lock, 1);
  } else {
    asm volatile("WFE");
  }
}

void spinlock_default_release(SpinLock *spinLock) {
  atomic_set(&spinLock->lock, 0);
  asm volatile("SEV");
}

void spinlock_create(SpinLock *spinLock) {
  atomic_create(&spinLock->lock);
  spinLock->operations.acquire = spinlock_default_acquire;
  spinLock->operations.release = spinlock_default_release;
}
