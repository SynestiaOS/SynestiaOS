//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_PRECPU_H__
#define __KERNEL_PRECPU_H__

#include <kqueue.h>
#include <rbtree.h>
#include <thread.h>

#define CPU_EXISTS_NUM 4

typedef struct CpuStatus {
    uint32_t idleTime;
} CpuStatus;

typedef KernelStatus (*PerCpuInit)(struct PerCpu *perCpu, uint32_t num, Thread *idleThread);

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
    KQueue waitThreadQueue;

    Thread *idleThread;
    Thread *currentThread;
    CpuStatus status;

    PerCpuOperations operations;
} __attribute__((packed)) PerCpu;

KernelStatus percpu_create(uint32_t cpuNum);

PerCpu *percpu_get(CpuNum cpuNum);

PerCpu *percpu_min_priority();

#endif //__KERNEL_PRECPU_H__
