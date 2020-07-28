//
// Created by XingfengYang on 2020/6/29.
//

#ifndef __KERNEL_SCHED_H__
#define __KERNEL_SCHED_H__

#include <stdint.h>
#include <thread.h>

KernelStatus schd_init(void);

KernelStatus schd_init_thread(Thread *thread, uint32_t priority);

KernelStatus schd_schedule(void);

KernelStatus schd_block(void);

KernelStatus schd_yield(void);

KernelStatus schd_preempt(void);

KernelStatus schd_switch_to(Thread *thread);

KernelStatus schd_add_to_global_list(Thread *thread);

KernelStatus schd_add_to_cfs_schduler(Thread *root, Thread *node);

KernelStatus schd_add_to_schduler(Thread *thread);

KernelStatus schd_remove_from_schduler(Thread *thread);

KernelStatus schd_switch_next(void);

KernelStatus schd_reschedule(void);

KernelStatus sche_insert_into_percpu_rq(CpuNum cpuNum, Thread *thread);


uint32_t schd_getpid();

#endif //__KERNEL_SCHED_H__
