//
// Created by XingfengYang on 2020/7/17.
//
#include "kernel/spinlock.h"

void spinlock_default_acquire(SpinLock *spinLock) {
    if (atomic_get(&spinLock->lock) == 0) {
        atomic_set(&spinLock->lock, 1);
        __asm__ __volatile__("cpsid i");
    } else {
        __asm__ __volatile__("WFE");
    }
}

void spinlock_default_release(SpinLock *spinLock) {
    atomic_set(&spinLock->lock, 0);
    __asm__ __volatile__("cpsie i");
    __asm__ __volatile__("SEV");
}
