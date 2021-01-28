//
// Created by XingfengYang on 2020/7/20.
//

#include "kernel/log.h"
#include "kernel/scheduler.h"
#include "kernel/interrupt.h"
#include "kernel/ktimer.h"
#include "kernel/list.h"
#include "kernel/kheap.h"
#include "kernel/assert.h"
#include "kernel/thread.h"

// TODO: this value should read from global config
#define TICK_INTERVAL 50

extern InterruptManager genericInterruptManager;
extern Heap kernelHeap;
extern Scheduler cfsScheduler;
extern KernelTimerManager kernelTimerManager;

KernelTimer kernel_timer_manger_default_init(struct KernelTimerManager *kernelTimerManager) {
    tick_init(&kernelTimerManager->timerManagerTick, kernelTimerManager->operation.onTick, "timer manager tick");
    genericInterruptManager.operation.registerTick(&genericInterruptManager, &kernelTimerManager->timerManagerTick);
}


KernelStatus kernel_timer_default_set(struct KernelTimer *timer, uint32_t timeout) {
    timer->deadline = timeout;
    timer->remainTime = timeout;
}

KernelStatus kernel_timer_default_cancel(struct KernelTimer *timer) {
    timer->deadline = 0;
    timer->remainTime = 0;
}


KernelTimer *kernel_timer_manger_default_create_timer(KernelTimerManager *kernelTimerManager, uint32_t deadline) {
    KernelTimer *timer = kernelHeap.operations.alloc(&kernelHeap, sizeof(struct KernelTimer));
    DEBUG_ASSERT(timer != nullptr);
    if (timer == nullptr) {
        return nullptr;
    }
    kqueue_create(&timer->waitQueue);
    timer->list.prev = nullptr;
    timer->list.next = nullptr;
    timer->deadline = deadline;
    timer->remainTime = 0;
    timer->operation.set = (KernelTimerOperationSet) kernel_timer_default_set;
    timer->operation.cancel = (KernelTimerOperationCancel) kernel_timer_default_cancel;

    if (kernelTimerManager->timerNodes == nullptr) {
        kernelTimerManager->timerNodes = &timer->list;
    } else {
        KernelStatus addToManager = klist_append(kernelTimerManager->timerNodes, &timer->list);
        if (addToManager == ERROR) {
            kernelHeap.operations.free(&kernelHeap, timer);
            return nullptr;
        }
    }
    return timer;
}

KernelStatus
kernel_timer_manger_default_release_timer(KernelTimerManager *kernelTimerManager, KernelTimer *timer) {
    LogInfo("[TimerManager] release timer\n");
    if (timer->waitQueue.operations.size == 0) {
        klist_remove_node(&timer->list);
    } else {
        while (timer->waitQueue.size != 0) {
            KQueueNode *node = timer->waitQueue.operations.dequeue(&timer->waitQueue);
            Thread *thread = getNode(node, Thread, threadReadyQueue);
            KernelStatus status = cfsScheduler.operation.addThread(&cfsScheduler, thread, thread->priority);
            DEBUG_ASSERT(status == OK);
            if (status != OK) {
                LogError("[KernelTimer] add thread to scheduler failed.\n");
                timer->waitQueue.operations.enqueue(&timer->waitQueue, &thread->threadReadyQueue);
                return ERROR;
            }
        }
        klist_remove_node(&timer->list);
    }
    return OK;
}

KernelStatus
kernel_timer_manger_default_free_timer(KernelTimerManager *kernelTimerManager, KernelTimer *timer) {
    KernelStatus releaseStatus = kernelTimerManager->operation.releaseTimer(kernelTimerManager, timer);
    DEBUG_ASSERT(releaseStatus != ERROR);
    if (releaseStatus != OK) {
        return ERROR;
    }
    kernelHeap.operations.free(&kernelHeap, timer);
    return OK;
}


KernelStatus kernel_timer_manger_default_get_sys_runtime_ms(KernelTimerManager *kernelTimerManager) {
    return kernelTimerManager->sysRuntimeMs;
}

void kernel_timer_manger_tick_on_each_timer(struct ListNode *node) {
    struct KernelTimer *timer = getNode(node, struct KernelTimer, list);
    LogInfo("[TimerManager] timer tick, remainTime: %d\n", timer->remainTime);
    if (timer->remainTime >= TICK_INTERVAL) {
        timer->remainTime -= TICK_INTERVAL;
    }
    if (timer->remainTime <= 0) {
        kernelTimerManager.operation.releaseTimer(&kernelTimerManager, timer);
    }
}

KernelStatus kernel_timer_manger_default_on_tick() {
    kernelTimerManager.sysRuntimeMs += TICK_INTERVAL;
    LogInfo("[TimerManager] tick\n");
    if (kernelTimerManager.timerNodes != nullptr && klist_size(kernelTimerManager.timerNodes) != 0) {
        klist_iter(kernelTimerManager.timerNodes, kernel_timer_manger_tick_on_each_timer);
    }
}

KernelTimerManager *kernel_timer_manager_create(KernelTimerManager *kernelTimerManager) {
    kernelTimerManager->sysRuntimeMs = 0;
    kernelTimerManager->timerNodes = nullptr;
    kernelTimerManager->operation.init = (KernelTimerManagerOperationInit) kernel_timer_manger_default_init;
    kernelTimerManager->operation.getSysRuntimeMs = (KernelTimerManagerOperationGetSysRuntimeMs) kernel_timer_manger_default_get_sys_runtime_ms;
    kernelTimerManager->operation.createTimer = (KernelTimerManagerOperationCreateTimer) kernel_timer_manger_default_create_timer;
    kernelTimerManager->operation.releaseTimer = (KernelTimerManagerOperationReleaseTimer) kernel_timer_manger_default_release_timer;
    kernelTimerManager->operation.freeTimer = (KernelTimerManagerOperationFreeTimer) kernel_timer_manger_default_free_timer;
    kernelTimerManager->operation.onTick = (KernelTimerManagerOperationOnTick) kernel_timer_manger_default_on_tick;

    return kernelTimerManager;
}
