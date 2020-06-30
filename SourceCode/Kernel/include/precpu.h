//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_PRECPU_H__
#define __KERNEL_PRECPU_H__

#include "kqueue.h"
#include "thread.h"

typedef enum CpuStatus {
    HALT
} CpuStatus;


typedef struct PreCpu {
    CpuNum cpuNum;

    KQueue *readyQueue;
    KQueue *waitQueue;

    Thread *idleThread;

    CpuStatus status;
} __attribute__((packed)) PreCpu;

#endif //__KERNEL_PRECPU_H__
