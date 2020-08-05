//
// Created by XingfengYang on 2020/6/29.
//

#include <cache.h>
#include <interrupt.h>
#include <log.h>
#include <percpu.h>
#include <sched.h>
#include <spinlock.h>
#include <stdlib.h>

extern uint64_t ktimer_sys_runtime_tick(uint64_t tickIntreval);

#define TIMER_TICK_MS 50

TimerHandler tickHandler;

uint32_t current_thread_stack = 0;
uint32_t switch_thread_stack = 0;
uint32_t switch_to_signal = 0;

Thread *currentThread = nullptr;

void tick() {
  ktimer_sys_runtime_tick(TIMER_TICK_MS);
  schd_switch_next();
}

SpinLockCreate(spinlock);

KernelStatus schd_switch_next(void) {
  uint32_t cpuid = read_cpuid();
  LogWarn("[Schd]: cpuId %d .\n", cpuid);
  PerCpu *perCpu = percpu_get(cpuid);
  Thread *thread = perCpu->operations.getNextThread(perCpu);

  spinlock.operations.acquire(&spinlock);
  schd_switch_to(thread);
  spinlock.operations.release(&spinlock);

  if(thread!=perCpu->idleThread) {
      Thread *removedThread = perCpu->operations.removeThread(perCpu, thread);
      if (removedThread != perCpu->idleThread) {
          schd_add_thread(removedThread, removedThread->priority);
      }
  }
  return OK;
}

KernelStatus schd_init() {
  if (percpu_create(CPU_EXISTS_NUM) != ERROR) {
    for (uint32_t cpuId = 0; cpuId < CPU_EXISTS_NUM; cpuId++) {
      Thread *idleThread = thread_create_idle_thread(cpuId);
      if (idleThread == nullptr) {
        return ERROR;
      }
      PerCpu *perCpu = percpu_get(cpuId);
      perCpu->operations.init(perCpu, cpuId, idleThread);
    }
  }

  LogInfo("[Schd]: Schd inited.\n");
  return OK;
}

KernelStatus schd_add_thread(Thread *thread, uint32_t priority) {
  thread->priority = priority;
  PerCpu *perCpu = percpu_min_priority();
  KernelStatus threadAddStatus = perCpu->operations.insertThread(perCpu, thread);
  if (threadAddStatus != OK) {
    LogError("[Schd] thread %s add to schduler failed.\n", thread->name);
    return ERROR;
  }
  return OK;
}

KernelStatus schd_schedule(void) {
  tickHandler.node.next = nullptr;
  tickHandler.node.prev = nullptr;
  tickHandler.timer_interrupt_handler = &tick;
  register_time_interrupt(&tickHandler);
  LogInfo("[Schd]: Schd started.\n");
  return OK;
}

KernelStatus schd_switch_to(Thread *thread) {
  // push r0~r3
  if (thread == nullptr) {
    LogWarn("[Schd]: cant switch to nullptr thread.\n");
    return ERROR;
  }
  LogInfo("[Schd]: switch to: %s.\n", thread->name);

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

uint32_t schd_getpid() { return currentThread->pid; }
