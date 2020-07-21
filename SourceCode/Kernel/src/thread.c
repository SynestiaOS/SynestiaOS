//
// Created by XingfengYang on 2020/6/26.
//

#include <kheap.h>
#include <kstack.h>
#include <stdlib.h>
#include <thread.h>

extern uint64_t ktimer_sys_runtime();

void thread_insert_to_rb_tree(RBNode *root, RBNode *node) {
  uint32_t parentValue = getNode(root, Thread, rbTree)->runtimVirtualNs;
  uint32_t nodeValue = getNode(node, Thread, rbTree)->runtimVirtualNs;
  if (nodeValue >= parentValue) {
    if (root->right != nullptr) {
      thread_insert_to_rb_tree(root->right, node);
    } else {
      root->right = node;
      rbtree_balance(root, node);
    }
  } else {
    if (root->left != nullptr) {
      thread_insert_to_rb_tree(root->left, node);
    } else {
      root->left = node;
      rbtree_balance(root, node);
    }
  }
}

Thread *thread_create(const char *name, ThreadStartRoutine entry, void *arg, uint32_t priority) {
  // 1. allocate stack memory from kernel heap for idle task
  KernelStack *kernelStack = kstack_allocate(kernelStack);
  if (kernelStack != nullptr && kernelStack != nullptr) {
    // 1. init kernel stack
    kstack_clear(kernelStack);

    kstack_push(kernelStack, entry);      // R15 PC
    kstack_push(kernelStack, entry);      // R14 LR
    kstack_push(kernelStack, 0x12121212); // R12
    kstack_push(kernelStack, 0x11111111); // R11
    kstack_push(kernelStack, 0x10101010); // R10
    kstack_push(kernelStack, 0x09090909); // R09
    kstack_push(kernelStack, 0x08080808); // R08
    kstack_push(kernelStack, 0x07070707); // R07
    kstack_push(kernelStack, 0x06060606); // R06
    kstack_push(kernelStack, 0x05050505); // R05
    kstack_push(kernelStack, 0x04040404); // R04
    kstack_push(kernelStack, 0x03030303); // R03
    kstack_push(kernelStack, 0x02020202); // R02
    kstack_push(kernelStack, 0x01010101); // R01
    kstack_push(kernelStack, arg);        // R00
    kstack_push(kernelStack, 0x600001d3); // cpsr

    Thread *thread = (Thread *)kheap_alloc(sizeof(Thread));
    thread->magic = THREAD_MAGIC;
    thread->threadStatus = THREAD_INITIAL;
    thread->stack = kernelStack;
    thread->priority = priority;
    thread->currCpu = INVALID_CPU;
    thread->lastCpu = INVALID_CPU;
    thread->entry = (ThreadStartRoutine)entry;
    thread->runtimeNs = 0;
    thread->runtimVirtualNs = 0;
    thread->startTime = ktimer_sys_runtime();
    thread->pid = 0;
    strcpy(thread->name, name);
    thread->arg = arg;

    thread->threadList.prev = nullptr;
    thread->threadList.next = nullptr;

    thread->threadReadyQueue.prev = nullptr;
    thread->threadReadyQueue.next = nullptr;
    // todo : other properties, like list

    printf("[Thread]: thread '%s' created.\n", name);
    return thread;
  }
  printf("[Thread]: thread '%s' created failed.\n", name);
  return nullptr;
}

uint32_t *idle_thread_routine(int arg) {
  while (1) {
    printf("[Thread]: IDLE: %d \n", arg);
    asm volatile("wfi");
  }
}

Thread *thread_create_idle_thread(uint32_t cpuNum) {
  Thread *idleThread = thread_create("IDLE", idle_thread_routine, cpuNum, IDLE_PRIORITY);
  idleThread->cpuAffinity = cpuNum;
  // 2. idle thread
  idleThread->pid = 0;

  char idleNameStr[10] = {'\0'};
  strcpy(idleThread->name, itoa(cpuNum, &idleNameStr, 10));
  // todo : other properties, like list
  printf("[Thread]: Idle thread for CPU '%d' created.\n", cpuNum);
  return idleThread;
}

KernelStatus thread_reschedule(void) {
  // todo
  return OK;
}

KernelStatus thread_sleep(uint32_t deadline) {
  // todo
  return OK;
}

KernelStatus thread_detach(Thread *thread) {
  // todo
  return OK;
}

KernelStatus thread_join(Thread *thread, int *retcode, uint32_t deadline) {
  // todo
  return OK;
}

KernelStatus init_thread_struct(Thread *thread, const char *name) {
  strcpy(thread->name, name);
  thread->threadStatus = THREAD_INITIAL;
  // todo : other properties, like list
  printf("[Thread]: thread: '%s' initialed.\n", name);
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
