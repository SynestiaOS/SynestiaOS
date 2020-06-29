//
// Created by XingfengYang on 2020/6/26.
//

#include <thread.h>
#include <kstack.h>
#include <kheap.h>


Thread *thread_create(const char *name, ThreadStartRoutine entry, void *arg, uint32_t priority) {

}

Thread *thread_create_idle_thread(uint32_t cpuNum) {
    KernelStack *kernelStack = nullptr;
    KernelStatus kernelStackAllocateState = vmm_allocate_kernel_stack(kernelStack);
    if (kernelStack != nullptr && kernelStackAllocateState != ERROR) {
        // todo: init kernel stack
    }
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
