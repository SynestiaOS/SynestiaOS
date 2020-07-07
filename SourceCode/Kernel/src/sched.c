//
// Created by XingfengYang on 2020/6/29.
//

#include <sched.h>
#include <kqueue.h>
#include <percpu.h>
#include <stdlib.h>
#include <interrupt.h>

Thread *currentThread = nullptr;

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

    printf("[Schd] Schd inited.\n");
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

KernelStatus schd_switch_to(Thread *thread) {
    if (thread == nullptr) {
        printf("[SC] cant switch to nullptr thread.\n");
        return ERROR;
    }
    printf("[SC] switch to: %s.\n", thread->name);

//    void *sp;
    disable_interrupt();

//    cpu_switch_to(currentThread, thread);

//    if (currentThread != nullptr) {
//        currentThread->stack = sp;
//    }
//    sp = thread->stack;
//
//
//    currentThread = thread;
//    currentThread->threadStatus = THREAD_READY;
//    currentThread->threadStatus = THREAD_RUNNING;

    enable_interrupt();

    return OK;
}

KernelStatus schd_reschedule(void) {
    // todo:
    return OK;
}

KernelStatus sche_insert_into_percpu_rq(CpuNum cpuNum, Thread *thread) {
    PerCpu *preCpu = percpu_get(cpuNum);
    kqueue_enqueue(&preCpu->readyThreadQueue, &thread->threadReadyQueue);
    return OK;
}
