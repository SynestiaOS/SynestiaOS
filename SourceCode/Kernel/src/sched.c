//
// Created by XingfengYang on 2020/6/29.
//

#include <interrupt.h>
#include <kqueue.h>
#include <percpu.h>
#include <sched.h>
#include <stdlib.h>

extern uint64_t ktimer_sys_runtime_tick(uint64_t tickIntreval);
#define TIMER_TICK_MS 50

Thread *currentThread = nullptr;

TimerHandler tickHandler;
Thread *tmp = nullptr;
Thread *head = nullptr;

uint32_t current_thread_stack = 0;
uint32_t switch_thread_stack = 0;
uint32_t switch_to_signal = 0;

void tick() {
  // switch to next
  ktimer_sys_runtime_tick(TIMER_TICK_MS);
  schd_switch_next();
}

KernelStatus schd_init() {
  // 1. create PreCpus
  if (percpu_create(CPU_4) != ERROR) {
    // 2. init PerCpu
    for (uint32_t i = 0; i < CPU_4; i++) {
      PerCpu *preCpu = percpu_get(i);
      preCpu->cpuNum = i;
      preCpu->status.idleTime = 0;
      Thread *idleThread = thread_create_idle_thread(i);
      preCpu->idleThread = idleThread;
      if (currentThread == nullptr) {
        currentThread = idleThread;
      } else {
        klist_append(&currentThread->threadList, &idleThread->threadList);
        printf("append\n");
      }
    }
  }
  printf("[Schd]: Schd inited.\n");

  tmp = currentThread;
  head = currentThread;

  return OK;
}

KernelStatus schd_init_thread(Thread *thread, uint32_t priority) {
  thread->priority = priority;
  klist_append(&currentThread->threadList, &thread->threadList);
  return OK;
}

KernelStatus schd_schedule(void) {
  tickHandler.node.next = nullptr;
  tickHandler.node.prev = nullptr;
  tickHandler.timer_interrupt_handler = &tick;
  register_time_interrupt(&tickHandler);
  printf("[Schd]: Schd started.\n");
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
  // push r0~r3

  if (thread == nullptr) {
    printf("[Schd]: cant switch to nullptr thread.\n");
    return ERROR;
  }
  printf("[Schd]: switch to: %s.\n", thread->name);

  // save current thread
  if (currentThread == nullptr) {
    switch_to_signal = 2;
    current_thread_stack = 0;
    switch_thread_stack = (uint32_t)(&thread->stack->top);
    currentThread = thread;
    // restore r0~r12
  } else {
    switch_to_signal = 1;
    current_thread_stack = (uint32_t)(&currentThread->stack->top);
    switch_thread_stack = (uint32_t)(&thread->stack->top);
    currentThread = thread;
  }
  // pop r0~r3
  return OK;
}

KernelStatus schd_switch_next(void) {
  if (tmp != nullptr) {
    schd_switch_to(tmp);
    if (tmp->threadList.next != nullptr) {
      tmp = getNode(tmp->threadList.next, Thread, threadList);
    } else {
      tmp = head;
    }
  } else {
    tmp = head;
  }
  return OK;
}

KernelStatus schd_add_to_schduler(Thread *thread) {
  klist_append(&currentThread->threadList, &thread->threadList);
  return OK;
}

KernelStatus schd_remove_from_schduler(Thread *thread) {
  // todo:
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
