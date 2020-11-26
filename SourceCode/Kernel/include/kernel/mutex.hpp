//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_MUTEX_H__
#define __KERNEL_MUTEX_H__

#include "kernel/atomic.hpp"
#include "kernel/kqueue.hpp"
#include "kernel/spinlock.hpp"
#include "libc/stdint.hpp"

#define STATE_FREE 0u
#define STATE_CONTESTED 1u

#define MutexCreate()                                                                                 \
    {                                                                                                 \
        .val = {                                                                                      \
                .counter = 0,                                                                         \
        },                                                                                            \
        .spinLock = SpinLockCreate(), .waitQueue = nullptr, .operations = {                           \
                                                                    .acquire = mutex_default_acquire, \
                                                                    .release = mutex_default_release, \
                                                            },                                        \
    }

typedef void (*MutexAcquire)(struct Mutex *mutex);

typedef void (*MutexRelease)(struct Mutex *mutex);

typedef struct MutexOperations {
    MutexAcquire acquire;
    MutexRelease release;
} MutexOperations;

typedef struct Mutex {
    Atomic val;
    SpinLock spinLock;
    KQueue *waitQueue;
    MutexOperations operations;
} Mutex;

void mutex_default_acquire(Mutex *mutex);

void mutex_default_release(Mutex *mutex);

#endif// __KERNEL_MUTEX_H__
