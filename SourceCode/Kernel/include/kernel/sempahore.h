//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_SEMAPHORE_H__
#define __KERNEL_SEMAPHORE_H__

#include <kernel/atomic.h>
#include <kernel/kqueue.h>
#include <kernel/spinlock.h>
#include <libc/stdint.h>

#define SemaphoreCreate()                                    \
    {                                                        \
        .count = {                                           \
                .counter = 0,                                \
        },                                                   \
        .operations = {                                      \
                .post = semaphore_default_post,              \
                .wait = semaphore_default_wait,              \
        },                                                   \
        .spinLock = SpinLockCreate(), .waitQueue = nunllptr, \
    }

typedef void (*SemaphorePost)(struct Semaphore *semaphore);

typedef void (*SemaphoreWait)(struct Semaphore *semaphore);

typedef struct SemaphoreOperations {
    SemaphorePost post;
    SemaphoreWait wait;
} SemaphoreOperations;

typedef struct Semaphore {
    Atomic count;
    SpinLock spinLock;
    KQueue waitQueue;
    SemaphoreOperations operations;
} Semaphore;

#endif// __KERNEL_SEMAPHORE_H__
