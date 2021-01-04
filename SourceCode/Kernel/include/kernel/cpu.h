//
// Created by XingfengYang on 2021/1/4.
//

#ifndef SYNESTIAOS_CPU_H
#define SYNESTIAOS_CPU_H

#include "libc/stdint.h"
#include "libc/stdbool.h"

typedef uint32_t CpuNum;
typedef uint32_t CpuMask;

#define CPU_MASK_ALL 0xFFFFFFFF

#define SMP_MAX_CPUS 4

bool is_valid_cpu_number(CpuNum num);

CpuMask cpu_number_to_mask(CpuNum num);

CpuMask cpu_mask_but_one(CpuNum num);

#endif //SYNESTIAOS_CPU_H
