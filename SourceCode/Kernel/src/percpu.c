//
// Created by XingfengYang on 2020/6/30.
//

#include <kheap.h>
#include <percpu.h>

PerCpu *preCpu = nullptr;

KernelStatus percpu_create(uint32_t cpuNum) {
  preCpu = (PerCpu *)kheap_calloc(cpuNum, sizeof(PerCpu));
  if (preCpu == nullptr) {
    return ERROR;
  }
  return OK;
}

PerCpu *percpu_get(CpuNum cpuNum) { return &preCpu[cpuNum]; }
