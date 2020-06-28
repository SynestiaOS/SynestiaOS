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
    uint32_t kernelStackAllocateState = vmm_allocate_kernel_stack(kernelStack);
    if (kernelStack != nullptr && kernelStackAllocateState > 0) {
        // todo: init kernel stack
    }
}

void init_thread_struct(Thread *thread, const char *name) {

}

void thread_exit(uint32_t returnCode) {

}

void thread_kill(Thread *thread) {

}
