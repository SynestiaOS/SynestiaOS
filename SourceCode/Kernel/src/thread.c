//
// Created by XingfengYang on 2020/6/26.
//

#include <thread.h>
#include <kstack.h>
#include <kheap.h>
#include <stdlib.h>

Thread *thread_create(const char *name, ThreadStartRoutine entry, void *arg, uint32_t priority) {

}


uint32_t *idle_thread_routine(void *arg) {
    asm volatile("wfi");
}

Thread *thread_create_idle_thread(uint32_t cpuNum) {
    KernelStack *kernelStack = nullptr;
    // 1. allocate stack memory from kernel heap for idle task
    KernelStatus kernelStackAllocateState = vmm_allocate_kernel_stack(kernelStack);
    if (kernelStack != nullptr && kernelStackAllocateState != ERROR) {
        // 1. init kernel stack

        // 2. idle thread
        Thread *idleThread = (Thread *) kernel_heap_alloc(sizeof(Thread));
        idleThread->magic = THREAD_MAGIC;
        idleThread->threadStatus = THREAD_READY;
        idleThread->stack = kernelStack;
        idleThread->priority = IDLE_PRIORITY;
        idleThread->currCpu = INVALID_CPU;
        idleThread->lastCpu = INVALID_CPU;
        idleThread->entry = idle_thread_routine;
        idleThread->pid = 0;
        strcpy(idleThread->name, "idle");

        // todo : other properties

        return idleThread;
    }
    return nullptr;
}

KernelStatus init_thread_struct(Thread *thread, const char *name) {
    // todo
    return OK;
}

KernelStatus thread_exit(uint32_t returnCode) {
    // todo
    return OK;
}

KernelStatus thread_kill(Thread *thread) {
    // todo
    return OK;
}
