//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_MUTEX_H__
#define __KERNEL_MUTEX_H__

#include "kernel/atomic.h"
#include "kernel/kobject.h"
#include "kernel/kqueue.h"
#include "kernel/spinlock.h"
#include "libc/stdint.h"

#define STATE_FREE 0u
#define STATE_CONTESTED 1u

#define MutexCreate()                                                                               \
    {                                                                                               \
        .val = {                                                                                    \
                .counter = 0,                                                                       \
        },                                                                                          \
        .spinLock = SpinLockCreate(), .waitQueue = {                                                \
                                              .size = 0,                                            \
                                              .head = nullptr,                                      \
                                              .tail = nullptr,                                      \
                                              .operations = {                                       \
                                                      .enqueue = kqueue_default_operation_enqueue,  \
                                                      .dequeue = kqueue_default_operation_dequeue,  \
                                                      .size = kqueue_default_operation_size,        \
                                                      .isEmpty = kqueue_default_operation_is_empty, \
                                              },                                                    \
                                      },                                                            \
        .operations = {                                                                             \
                .acquire = mutex_default_acquire,                                                   \
                .release = mutex_default_release,                                                   \
        },                                                                                          \
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
    KernelQueue waitQueue;
    KernelObject object;
    MutexOperations operations;
} Mutex;

void mutex_default_acquire(Mutex *mutex);

void mutex_default_release(Mutex *mutex);

#endif// __KERNEL_MUTEX_H__
