//
// Created by XingfengYang on 2020/7/20.
//

#include "kernel/interrupt.h"
#include "kernel/ktimer.h"
#include "kernel/list.h"
#include "kernel/kheap.h"
#include "kernel/assert.h"

extern InterruptManager genericInterruptManager;
extern Heap kernelHeap;

KernelTimer kernel_timer_manger_default_init(struct KernelTimerManager *kernelTimerManager) {
    tick_init(&kernelTimerManager->timerManagerTick, kernelTimerManager->operation.onTick, "timer manager tick");
    genericInterruptManager.operation.registerTick(&genericInterruptManager, &kernelTimerManager->timerManagerTick);
}


KernelStatus kernel_timer_default_set(struct KernelTimer *timer, uint32_t timeout) {
    timer->deadline = timeout;
    timer->remainTime = timeout;
}

KernelStatus kernel_timer_default_cancel(struct KernelTimer *timer) {

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
    timer->deadline = 0;
    timer->remainTime = 0;
    timer->operation.set = (KernelTimerOperationSet) kernel_timer_default_set;
    timer->operation.cancel = (KernelTimerOperationCancel) kernel_timer_default_cancel;

    KernelStatus addToManager = klist_append(kernelTimerManager->timerNodes, &timer->list);
    if (addToManager == ERROR) {
        kernelHeap.operations.free(&kernelHeap, timer);
        return nullptr;
    }
    return timer;
}

KernelStatus
kernel_timer_manger_default_release_timer(KernelTimerManager *kernelTimerManager, KernelTimer *timer) {

}

KernelStatus kernel_timer_manger_default_get_sys_runtime_ms(KernelTimerManager *kernelTimerManager) {
    return kernelTimerManager->sysRuntimeMs;
}

KernelStatus kernel_timer_manger_default_on_tick(KernelTimerManager *kernelTimerManager) {

}

KernelTimerManager *kernel_timer_manager_create(KernelTimerManager *kernelTimerManager) {
    kernelTimerManager->sysRuntimeMs = 0;
    kernelTimerManager->timerNodes = nullptr;
    kernelTimerManager->operation.init = (KernelTimerManagerOperationInit) kernel_timer_manger_default_init;
    kernelTimerManager->operation.getSysRuntimeMs = (KernelTimerManagerOperationGetSysRuntimeMs) kernel_timer_manger_default_get_sys_runtime_ms;
    kernelTimerManager->operation.createTimer = (KernelTimerManagerOperationCreateTimer) kernel_timer_manager_create;
    kernelTimerManager->operation.releaseTimer = (KernelTimerManagerOperationReleaseTimer) kernel_timer_manger_default_release_timer;
    kernelTimerManager->operation.onTick = (KernelTimerManagerOperationOnTick) kernel_timer_manger_default_on_tick;

    return kernelTimerManager;
}
