//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_PRECPU_H__
#define __KERNEL_PRECPU_H__

#include "kqueue.h"
#include "thread.h"

typedef struct CpuStatus {
    uint32_t idleTime;
} CpuStatus;


typedef struct PreCpu {
    CpuNum cpuNum;

    KQueue *readyQueue;
    KQueue *waitQueue;

    Thread *idleThread;

    CpuStatus status;
} __attribute__((packed)) PreCpu;


KernelStatus percpu_create(uint32_t cpuNum);

PreCpu *precpu_get(CpuNum cpuNum);

#endif //__KERNEL_PRECPU_H__
