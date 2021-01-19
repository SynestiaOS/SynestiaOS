//
// Created by XingfengYang on 2020/6/29.
//

#ifndef __KERNEL_SCHEDULER_H__
#define __KERNEL_SCHEDULER_H__

#include "kernel/thread.h"
#include "libc/stdint.h"
#include "interrupt.h"

typedef KernelStatus (*SchedulerOperationInit)(struct Scheduler *scheduler);

typedef KernelStatus (*SchedulerOperationAddThread)(struct Scheduler *scheduler,Thread *thread, uint32_t priority);

typedef KernelStatus (*SchedulerOperationSchedule)(struct Scheduler *scheduler);

typedef KernelStatus (*SchedulerOperationBlock)(struct Scheduler *scheduler);

typedef KernelStatus (*SchedulerOperationYield)(struct Scheduler *scheduler);

typedef KernelStatus (*SchedulerOperationPreempt)(struct Scheduler *scheduler);

typedef KernelStatus (*SchedulerOperationSwitchTo)(struct Scheduler *scheduler,Thread *thread);

typedef KernelStatus (*SchedulerOperationSwitchNext)(struct Scheduler *scheduler);

typedef uint32_t (*SchedulerOperationGetCurrentPid)(struct Scheduler *scheduler);

typedef Thread *(*SchedulerOperationGetCurrentThread)(struct Scheduler *scheduler);

typedef struct SchedulerOperation {
    SchedulerOperationInit init;
    SchedulerOperationAddThread addThread;
    SchedulerOperationSchedule schedule;
    SchedulerOperationBlock block;
    SchedulerOperationYield yield;
    SchedulerOperationPreempt preempt;
    SchedulerOperationSwitchTo switchTo;
    SchedulerOperationSwitchNext switchNext;
    SchedulerOperationGetCurrentPid getCurrentPid;
    SchedulerOperationGetCurrentThread getCurrentThread;
} SchedulerOperation;

typedef struct Scheduler {
    Thread *prevThread;
    Thread *currentThread;
    Tick schedulerTick;
    SchedulerOperation operation;
} Scheduler;

Scheduler *scheduler_create(Scheduler *scheduler);

KernelStatus schd_init(void);

KernelStatus schd_add_thread(Thread *thread, uint32_t priority);

KernelStatus schd_schedule(void);

KernelStatus schd_block(void);

KernelStatus schd_yield(void);

KernelStatus schd_preempt(void);

KernelStatus schd_switch_to(Thread *thread);

KernelStatus schd_switch_next(void);

uint32_t schd_getpid();

Thread *schd_get_current_thread(void);

#endif//__KERNEL_SCHEDULER_H__
