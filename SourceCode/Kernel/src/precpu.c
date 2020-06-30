//
// Created by XingfengYang on 2020/6/30.
//

#include <precpu.h>
#include <kheap.h>

PreCpu *preCpu = nullptr;

KernelStatus percpu_create(uint32_t cpuNum) {
    preCpu = (PreCpu *) kheap_calloc(cpuNum, sizeof(PreCpu));
    if (preCpu == nullptr) {
        return ERROR;
    }
    return OK;
}

PreCpu *precpu_get(CpuNum cpuNum) {
    return &preCpu[cpuNum];
}
