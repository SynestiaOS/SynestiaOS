//
// Created by XingfengYang on 2020/7/17.
//

#include "kernel/mutex.h"
#include "arm/register.h"
#include "kernel/assert.h"
#include "kernel/kqueue.h"
#include "kernel/percpu.h"
#include "kernel/scheduler.h"
#include "kernel/thread.h"

void mutex_default_acquire(Mutex *mutex) {
    mutex->spinLock.operations.acquire(&mutex->spinLock);

    if (atomic_get(&mutex->val) == 0) {
        atomic_set(&mutex->val, 1);
    } else {
        uint32_t cpuid = read_cpuid();
        PerCpu *perCpu = percpu_get(cpuid);
        Thread *currentThread = perCpu->currentThread;

        DEBUG_ASSERT(currentThread != nullptr);

        // can not get the lock, just add to lock wait list
        mutex->waitQueue.operations.enqueue(&mutex->waitQueue, &currentThread->threadReadyQueue);
        currentThread->threadStatus = THREAD_BLOCKED;
        // remove from schd list
        perCpu->rbTree.operations.remove(&perCpu->rbTree, &currentThread->rbNode);
        // 2. switch to the next thread in scheduler
        schd_switch_next();
    }

    mutex->spinLock.operations.release(&mutex->spinLock);
}

void mutex_default_release(Mutex *mutex) {
    mutex->spinLock.operations.acquire(&mutex->spinLock);

    if (atomic_get(&mutex->val) == 0) {
        return;
    } else {
        KQueueNode *node = mutex->waitQueue.operations.dequeue(&mutex->waitQueue);

        uint32_t cpuid = read_cpuid();
        PerCpu *perCpu = percpu_get(cpuid);
        Thread *currentThread = getNode(node, Thread, threadReadyQueue);

        DEBUG_ASSERT(currentThread != nullptr);

        perCpu->rbTree.operations.insert(&perCpu->rbTree, &currentThread->rbNode);
        currentThread->threadStatus = THREAD_READY;
        atomic_set(&mutex->val, 0);

        // TODO: maybe should consider virtual runtime.
    }

    mutex->spinLock.operations.release(&mutex->spinLock);
}
