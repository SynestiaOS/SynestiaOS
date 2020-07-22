//
// Created by XingfengYang on 2020/6/29.
//

#include <interrupt.h>
#include <kqueue.h>
#include <log.h>
#include <percpu.h>
#include <sched.h>
#include <stdlib.h>

extern uint64_t ktimer_sys_runtime_tick(uint64_t tickIntreval);
#define TIMER_TICK_MS 50

Thread *currentThread = nullptr;
Thread *headThread = nullptr;
Thread *tmpThread = nullptr;

TimerHandler tickHandler;

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
      if (idleThread == nullptr) {
        return ERROR;
      }
      preCpu->idleThread = idleThread;

      if (currentThread == nullptr) {
        currentThread = idleThread;
      } else {
        KernelStatus threadAddStatus = schd_add_to_schduler(idleThread);
        if (threadAddStatus != OK) {
          return ERROR;
        }
      }
    }
  }
  LogInfo("[Schd]: Schd inited.\n");
  headThread = currentThread;
  tmpThread = currentThread;
  return OK;
}

KernelStatus schd_init_thread(Thread *thread, uint32_t priority) {
  thread->priority = priority;
  KernelStatus threadAddStatus = schd_add_to_schduler(thread);
  if (threadAddStatus != OK) {
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
    LogWarnning("[Schd]: cant switch to nullptr thread.\n");
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

KernelStatus schd_switch_next(void) {
  if (tmpThread != nullptr) {
    schd_switch_to(tmpThread);
    if (tmpThread->threadList.next != nullptr) {
      tmpThread = getNode(tmpThread->threadList.next, Thread, threadList);
    } else {
      tmpThread = headThread;
    }
  } else {
    tmpThread = headThread;
  }
  return OK;
}

KernelStatus schd_add_to_cfs_schduler(Thread *root, Thread *node) {
  KernelStatus ret = OK;
  RBNode *nd = nullptr;

  /* Case 1: Simplest case -- tree is empty */
  if (&root->rbTree == nullptr) {
    root->rbTree = node->rbTree;
    node->rbTree.color = NODE_BLACK;
    return ret;
  }

  /* Otherwise, insert the node as you would typically in a BST */
  nd = &root->rbTree;
  node->rbTree.color = NODE_RED;

  /* Insert a node into the tree as you normally would */
  while (nd != nullptr) {
    uint32_t parentValue = root->runtimVirtualNs;
    uint32_t nodeValue = node->runtimVirtualNs;

    int compare = parentValue - nodeValue;

    if (compare == 0) {
      LogError("[RBTree]: dup thread virtual time.\n");
      return OK;
    }

    if (compare < 0) {
      if (nd->left == nullptr) {
        nd->left = &node->rbTree;
        break;
      } else {
        nd = nd->left;
      }
    } else {
      if (nd->right == nullptr) {
        nd->right = &node->rbTree;
        break;
      } else {
        nd = nd->right;
      }
    }
  }

  node->rbTree.parent = nd;

  rbtree_rebalance(&root->rbTree, &node->rbTree);
}

KernelStatus schd_add_to_schduler(Thread *thread) {
  // Add thread to global list for track or for other usage
  KernelStatus threadAddStatus = klist_append(&currentThread->threadList, &thread->threadList);
  if (threadAddStatus != OK) {
    LogError("[Schd]: thread '%s' add to schduler failed.\n", thread->name);
    return ERROR;
  }
  LogInfo("[Schd]: thread '%s' add to schduler.\n", thread->name);

  // Add thread to CFS scheduler tree
  headThread->rbTree.color = NODE_BLACK;
  schd_add_to_cfs_schduler(headThread, thread);

  return OK;
}

KernelStatus schd_remove_from_schduler(Thread *thread) {
  klist_remove_node(&thread->threadList);
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
