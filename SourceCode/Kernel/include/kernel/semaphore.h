//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_SEMAPHORE_H__
#define __KERNEL_SEMAPHORE_H__

#include "kernel/atomic.h"
#include "kernel/kqueue.h"
#include "kernel/spinlock.h"
#include "libc/stdint.h"
#include "kernel/kobject.h"

#define SemaphoreCreate(cc)                                  \
    {                                                        \
        .count = {                                           \
                .counter = cc,                               \
        },                                                   \
        .operations = {                                      \
                .post = semaphore_default_post,              \
                .wait = semaphore_default_wait,              \
        },                                                   \
        .waitQueue = {                                       \
                .size = 0,                                      \
                .head = nullptr,                                \
                .tail = nullptr,                                    \
                 .operations = {                                                                       \
                        .enqueue = kqueue_default_operation_enqueue, \
                        .dequeue = kqueue_default_operation_dequeue, \
                        .size = kqueue_default_operation_size,          \
                        .isEmpty = kqueue_default_operation_is_empty,                                         \
                        }\
        }                                                           \
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
    KernelQueue waitQueue;
    KernelObject object;
    SemaphoreOperations operations;
} Semaphore;

#endif// __KERNEL_SEMAPHORE_H__
