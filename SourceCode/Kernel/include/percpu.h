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

typedef struct PerCpu {
  CpuNum cpuNum;

  KQueue readyThreadQueue;
  KQueue waitThreadQueue;

  Thread *idleThread;

  CpuStatus status;
} __attribute__((packed)) PerCpu;

KernelStatus percpu_create(uint32_t cpuNum);

PerCpu *percpu_get(CpuNum cpuNum);

#endif //__KERNEL_PRECPU_H__
