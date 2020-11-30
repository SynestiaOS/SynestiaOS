//
// Created by XingfengYang on 2020/7/17.
//

#include "arm/cpu.h"
#include "kernel/kqueue.h"
#include "kernel/log.h"
#include "kernel/mutex.h"
#include "kernel/percpu.h"
#include "kernel/sched.h"
#include "kernel/thread.h"

void mutex_default_acquire(Mutex *mutex) {
    if (atomic_get(&mutex->val) == 0) {
        atomic_set(&mutex->val, 1);
    } else {
        uint32_t cpuid = read_cpuid();
        PerCpu *perCpu = percpu_get(cpuid);
        Thread *currentThread = perCpu->currentThread;
        // can not get the lock, just add to lock wait list
        kqueue_enqueue(&mutex->waitQueue, &currentThread->threadReadyQueue);
        currentThread->threadStatus = THREAD_BLOCKED;
        // remove from schd list
        perCpu->rbTree.operations.remove(&perCpu->rbTree, &currentThread->rbNode);
        // 2. switch to the next thread in scheduler
        schd_switch_next();
    }
}

void mutex_default_release(Mutex *mutex) {
    if (atomic_get(&mutex->val) == 0) {
        return;
    } else {
        KQueue *node = kqueue_dequeue(&mutex->waitQueue);

        uint32_t cpuid = read_cpuid();
        PerCpu *perCpu = percpu_get(cpuid);
        Thread *th = getNode(node, Thread, threadReadyQueue);
        perCpu->rbTree.operations.insert(&perCpu->rbTree, &th->rbNode);
        th->threadStatus = THREAD_READY;
        atomic_set(&mutex->val, 0);

        // TODO: maybe should consider virtual runtime.
    }
}
