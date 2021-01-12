//
// Created by XingfengYang on 2020/7/20.
//

#ifndef __KERNEL_KTIMER_H__
#define __KERNEL_KTIMER_H__

#include "libc/stdint.h"
#include "kernel/list.h"
#include "kernel/kqueue.h"
#include "kernel/interrupt.h"

typedef KernelStatus (*KernelTimerOperationSet)(struct KernelTimer *timer, uint32_t timeout);

typedef KernelStatus (*KernelTimerOperationCancel)(struct KernelTimer *timer);

typedef struct KernelTimerOperation {
    KernelTimerOperationSet set;
    KernelTimerOperationCancel cancel;
} KernelTimerOperation;

typedef struct KernelTimer {
    uint32_t deadline;
    uint32_t remainTime;
    ListNode list;
    KernelQueue waitQueue;
    KernelTimerOperation operation;
} KernelTimer;


typedef KernelTimer (*KernelTimerManagerOperationInit)(struct KernelTimerManager *kernelTimerManager);

typedef KernelTimer *(*KernelTimerManagerOperationCreateTimer)(struct KernelTimerManager *kernelTimerManager,
                                                               uint32_t deadline);

typedef KernelStatus (*KernelTimerManagerOperationReleaseTimer)(struct KernelTimerManager *kernelTimerManager,
                                                                KernelTimer *timer);

typedef KernelStatus (*KernelTimerManagerOperationGetSysRuntimeMs)(struct KernelTimerManager *kernelTimerManager);

typedef void (*KernelTimerManagerOperationOnTick)();

typedef struct KernelTimerMangerOperation {
    KernelTimerManagerOperationInit init;
    KernelTimerManagerOperationOnTick onTick;
    KernelTimerManagerOperationGetSysRuntimeMs getSysRuntimeMs;
    KernelTimerManagerOperationCreateTimer createTimer;
    KernelTimerManagerOperationReleaseTimer releaseTimer;
} KernelTimerMangerOperation;

typedef struct KernelTimerManager {
    uint32_t sysRuntimeMs;
    ListNode *timerNodes;
    Tick timerManagerTick;
    KernelTimerMangerOperation operation;
} KernelTimerManager;

KernelTimerManager *kernel_timer_manager_create(KernelTimerManager *kernelTimerManager);

#endif// __KERNEL_KTIMER_H__
