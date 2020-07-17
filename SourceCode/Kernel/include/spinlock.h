//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_SPINLOCK_H__
#define __KERNEL_SPINLOCK_H__
#include <stdbool.h>

typedef struct SpinLock{
    bool lock;
} SpinLock;

void spinlock_create(SpinLock *spinLock);
void spinlock_acquire(SpinLock *spinLock);
void spinlock_release(SpinLock *spinLock);
bool spinlock_try_acquire(SpinLock *spinLock);
bool spinlock_try_held(SpinLock *spinLock);
#endif // __KERNEL_SPINLOCK_H__

