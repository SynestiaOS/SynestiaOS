//
// Created by XingfengYang on 2021/1/4.
//
#include "kernel/cpu.h"

bool is_valid_cpu_number(CpuNum num) {
    return num < SMP_MAX_CPUS;
}

CpuMask cpu_number_to_mask(CpuNum num) {
    if (!is_valid_cpu_number(num)) {
        return 0;
    }
    return 0x1 << num;
}

CpuMask cpu_mask_but_one(CpuNum num) {
    return CPU_MASK_ALL ^ cpu_number_to_mask(num);
}
