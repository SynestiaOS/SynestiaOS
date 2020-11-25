//
// Created by XingfengYang on 2020/7/20.
//

#ifndef __KERNEL_KTIMER_H__
#define __KERNEL_KTIMER_H__

#include "libc/stdint.h"

uint64_t ktimer_sys_runtime_tick(uint64_t tickIntreval);

uint64_t ktimer_sys_runtime();

#endif// __KERNEL_KTIMER_H__
