//
// Created by XingfengYang on 2020/6/29.
//

#ifndef __KERNEL_SCHED_H__
#define __KERNEL_SCHED_H__

#include <stdint.h>
#include <thread.h>

KernelStatus schd_init(void);

KernelStatus schd_add_thread(Thread *thread, uint32_t priority);

KernelStatus schd_schedule(void);

KernelStatus schd_block(void);

KernelStatus schd_yield(void);

KernelStatus schd_preempt(void);

KernelStatus schd_switch_to(Thread *thread);

KernelStatus schd_switch_next(void);

uint32_t schd_getpid();

#endif //__KERNEL_SCHED_H__
