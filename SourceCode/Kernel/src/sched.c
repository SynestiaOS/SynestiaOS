//
// Created by XingfengYang on 2020/6/29.
//

#include <sched.h>
#include <kqueue.h>
#include <percpu.h>
#include <stdlib.h>
#include <interrupt.h>

Thread *currentThread = nullptr;


TimerHandler t;
int i = 0;
void xx() {
    //Switch To thread
    PerCpu *preCpu = percpu_get(i);
    schd_switch_to(preCpu->idleThread);
    i++;
    if(i==4){
        i = 0;
    }
}

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

    t.node.next = nullptr;
    t.node.prev = nullptr;
    t.timer_interrupt_handler = &xx;
    register_time_interrupt(&t);

    printf("[Schd]: Schd inited.\n");
    return OK;
}

KernelStatus schd_init_thread(Thread *thread, uint32_t priority) {
    thread->priority = priority;
    // todo : it's just a test
    PerCpu *preCpu = percpu_get(0);
    preCpu->idleThread = thread;
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

extern void cpu_context_switch_to(uint32_t current_stack, uint32_t switch_stack);


uint32_t  current_thread_stack = 0;
uint32_t  switch_thread_stack = 0;
uint32_t  switch_to_signal = 0;


KernelStatus schd_switch_to(Thread *thread) {

  //push r0~r3

    if (thread == nullptr) {
        printf("[Schd]: cant switch to nullptr thread.\n");
        return ERROR;
    }
    printf("[Schd]: switch to: %s.\n", thread->name);

    //disable_interrupt();

    //save current thread


    if (currentThread == nullptr) {
        switch_to_signal = 2;
        current_thread_stack = 0;
        switch_thread_stack = (uint32_t)(&thread->stack->top);
        currentThread = thread;
        //cpu_context_switch_to(0, thread->stack->top);
        //restore r0~r12
    } else {
        switch_to_signal = 1;
        current_thread_stack = (uint32_t)(&currentThread->stack->top);
        switch_thread_stack = (uint32_t)(&thread->stack->top);
        currentThread = thread;
      //cpu_context_switch_to(currentThread->stack->top, thread->stack->top);
    }


    //restore new thread
    //enable_interrupt();

      //pop r0~r3
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
