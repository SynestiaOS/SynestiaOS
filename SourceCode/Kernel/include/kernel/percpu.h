//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_PRECPU_H__
#define __KERNEL_PRECPU_H__

#include "kernel/kqueue.h"
#include "kernel/rbtree.h"
#include "kernel/thread.h"

#define CPU_EXISTS_NUM 4

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

typedef enum CPUMask {
    CPU_0_MASK = 0x1,
    CPU_1_MASK = 0x1 << 1,
    CPU_2_MASK = 0x1 << 2,
    CPU_3_MASK = 0x1 << 3,
    CPU_4_MASK = 0x1 << 4,
    CPU_5_MASK = 0x1 << 5,
    CPU_6_MASK = 0x1 << 6,
    CPU_7_MASK = 0x1 << 7,
    CPU_8_MASK = 0x1 << 8,
    CPU_9_MASK = 0x1 << 9,
    CPU_10_MASK = 0x1 << 10,
    CPU_11_MASK = 0x1 << 11,
    CPU_12_MASK = 0x1 << 12,
    CPU_13_MASK = 0x1 << 13,
    CPU_14_MASK = 0x1 << 14,
    CPU_15_MASK = 0x1 << 15,
} CPUMask;

#define CPU_MASK_ALL  CPU_0_MASK | CPU_1_MASK | CPU_2_MASK | CPU_3_MASK | CPU_4_MASK | CPU_5_MASK | CPU_6_MASK | CPU_7_MASK | CPU_8_MASK | CPU_9_MASK | CPU_10_MASK | CPU_11_MASK | CPU_12_MASK | CPU_13_MASK | CPU_14_MASK | CPU_15_MASK

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
    KQueueNode waitThreadQueue;

    Thread *idleThread;
    Thread *currentThread;
    CpuStatus status;

    struct ListNode node;

    PerCpuOperations operations;
} PerCpu;

KernelStatus percpu_create(uint32_t cpuNum);

PerCpu *percpu_get(CpuNum cpuNum);

PerCpu *percpu_min_priority(uint32_t cpuMask);

#endif//__KERNEL_PRECPU_H__
