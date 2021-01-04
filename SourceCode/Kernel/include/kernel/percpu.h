//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_PRECPU_H__
#define __KERNEL_PRECPU_H__

#include "kernel/kqueue.h"
#include "kernel/rbtree.h"
#include "kernel/thread.h"
#include "kernel/cpu.h"

typedef enum CPU {
    CPU_0 = 0,
    CPU_1,
    CPU_2,
    CPU_3,
    CPU_4,
    CPU_5,
    CPU_6,
    CPU_7,
    CPU_8,
    CPU_9,
    CPU_10,
    CPU_11,
    CPU_12,
    CPU_13,
    CPU_14,
    CPU_15,
    INVALID_CPU = 255,
} CPU;

typedef struct CpuStatus {
    uint32_t idleTime;
} CpuStatus;

typedef KernelStatus (*PerCpuInit)(struct PerCpu *perCpu, CpuNum num, Thread *idleThread);

typedef KernelStatus (*PerCpuInsertThread)(struct PerCpu *perCpu, Thread *thread);

typedef Thread *(*PerCpuRemoveThread)(struct PerCpu *perCpu, Thread *thread);

typedef Thread *(*PerCpuGetNextThread)(struct PerCpu *perCpu);

typedef struct PerCpuOperations {
    PerCpuInit init;
    PerCpuInsertThread insertThread;
    PerCpuRemoveThread removeThread;
    PerCpuGetNextThread getNextThread;
} PerCpuOperations;

typedef struct PerCpu {
    CpuNum cpuId;
    uint32_t priority;

    RBTree rbTree;
    KQueueNode waitThreadQueue;

    Thread *idleThread;
    Thread *currentThread;
    CpuStatus status;

    struct ListNode node;

    PerCpuOperations operations;
} PerCpu;

KernelStatus percpu_create(CpuNum cpuNum);

PerCpu *percpu_get(CpuNum cpuNum);

PerCpu *percpu_min_priority(CpuNum cpuMask);

#endif//__KERNEL_PRECPU_H__
