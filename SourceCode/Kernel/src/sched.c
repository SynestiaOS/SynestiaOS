//
// Created by XingfengYang on 2020/6/29.
//

#include <sched.h>
#include <kqueue.h>
#include <percpu.h>
#include <rbtree.h>

RBNode *cfsTreeRoot;

KernelStatus schd_init() {

    // 1. create PreCpus
    if (percpu_create(CPU_4) != ERROR) {
        // 2. init PerCpu
        for (uint32_t i = 0; i < CPU_4; i++) {
            PerCpu *preCpu = percpu_get(i);
            preCpu->cpuNum = i;
            preCpu->status.idleTime = 0;
            preCpu->idleThread = thread_create_idle_thread(i);
        }
    }
    return OK;
}

KernelStatus schd_init_thread(Thread *thread, uint32_t priority) {
    thread->priority = priority;
    // todo:
    return OK;
}

KernelStatus schd_block(void) {
    // todo:
    return OK;
}

KernelStatus schd_yield(void) {
    // todo:
    return OK;
}

KernelStatus schd_preempt(void) {
    // todo:
    return OK;
}

KernelStatus sche_insert_into_percpu_rq(CpuNum cpuNum, Thread *thread) {
    // todo:
    return OK;
}
