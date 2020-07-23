//
// Created by XingfengYang on 2020/6/29.
//

#include <interrupt.h>
#include <kqueue.h>
#include <kvector.h>
#include <log.h>
#include <percpu.h>
#include <sched.h>
#include <stdlib.h>

extern uint64_t ktimer_sys_runtime_tick(uint64_t tickIntreval);
#define TIMER_TICK_MS 50

Thread *currentThread = nullptr;
Thread *headThread = nullptr;

TimerHandler tickHandler;

uint32_t current_thread_stack = 0;
uint32_t switch_thread_stack = 0;
uint32_t switch_to_signal = 0;

void tick() {
  // switch to next
  ktimer_sys_runtime_tick(TIMER_TICK_MS);
  schd_switch_next();
}

KernelStatus schd_switch_next(void) {
  // switch to virtualRuntime mix Thread in cfs tree
  RBNode *minvirtualRuntimeNode = rbtree_get_min(&headThread->rbTree);

  if (minvirtualRuntimeNode == nullptr) {
    LogError("[CFS]: The smallest node from csf tree is null. \n");
  }

  Thread *thread = getNode(minvirtualRuntimeNode, Thread, rbTree);
  LogInfo("[CFS]: smallet thread '%s'. \n", thread->name);
  schd_switch_to(thread);
  thread->runtimVirtualNs += TIMER_TICK_MS;
  schd_reschedule();
  return OK;
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
        KernelStatus threadAddGlobalStatus = schd_add_to_global_list(idleThread);
        if (threadAddGlobalStatus != OK) {
          return ERROR;
        }

        KernelStatus threadAddStatus = schd_add_to_schduler(idleThread);
        if (threadAddStatus != OK) {
          return ERROR;
        }
      }
    }
  }
  LogInfo("[Schd]: Schd inited.\n");
  headThread = currentThread;
  return OK;
}

KernelStatus schd_init_thread(Thread *thread, uint32_t priority) {
  thread->priority = priority;
  KernelStatus threadAddGlobalStatus = schd_add_to_global_list(thread);
  if (threadAddGlobalStatus != OK) {
    return ERROR;
  }

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
    int compare = nodeValue - parentValue;
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

  return OK;
}

KernelStatus schd_add_to_global_list(Thread *thread) {
  // Add thread to global list for track or for other usage
  KernelStatus threadAddStatus = klist_append(&currentThread->threadList, &thread->threadList);
  if (threadAddStatus != OK) {
    LogError("[Schd]: thread '%s' add to global list failed.\n", thread->name);
    return ERROR;
  }
  LogInfo("[Schd]: thread '%s' add to global list.\n", thread->name);
  return OK;
}

KernelStatus schd_add_to_schduler(Thread *thread) {
  // Add thread to CFS scheduler tree
  headThread->rbTree.color = NODE_BLACK;
  KernelStatus threadAddCSFStatus = schd_add_to_cfs_schduler(headThread, thread);
  if (threadAddCSFStatus != OK) {
    LogError("[CFS]: thread '%s' add to CFS schduler failed.\n", thread->name);
    return ERROR;
  }
  LogInfo("[CFS]: thread '%s' add to CFS schduler.\n", thread->name);

  return OK;
}

KernelStatus schd_remove_from_schduler(Thread *thread) {
  // remove thread from cfs schedule tree.
  if (thread->rbTree.parent != nullptr && thread->rbTree.parent->color != NODE_BLACK &&
      thread->rbTree.left == nullptr && thread->rbTree.right == nullptr) {
    if (thread->rbTree.parent->left == &thread->rbTree) {
      thread->rbTree.parent->left = nullptr;
    }
    if (thread->rbTree.parent->right == &thread->rbTree) {
      thread->rbTree.parent->right = nullptr;
    }
    rbtree_rebalance(&headThread->rbTree, thread->rbTree.parent);
    thread->rbTree.parent = nullptr;
    thread->rbTree.left = nullptr;
    thread->rbTree.right = nullptr;
  } else {
    LogError("[CFS] can not remove root node from cfs tree. \n");
    return ERROR;
  }
  return OK;
}

KernelStatus schd_reschedule(void) {
  KernelVector *vector = kvector_allocate();
  rbtree_reconstruct_to_list(vector, &headThread->rbTree);
  LogInfo("[CSF]: %d thread in cfs.\n", vector->index);

  headThread->rbTree.parent = nullptr;
  headThread->rbTree.left = nullptr;
  headThread->rbTree.right = nullptr;

  // re construct a new rb tree with list above
  LogInfo("[CFS]: reconstruct csf schdule tree. \n");
  for (uint32_t i = 0; i < vector->index; i++) {
    Thread *thread = getNode(kvector_get(vector, i), Thread, threadList);
    thread->rbTree.parent = nullptr;
    thread->rbTree.left = nullptr;
    thread->rbTree.right = nullptr;
    thread->rbTree.color = NODE_RED;
    schd_add_to_cfs_schduler(headThread, thread);
  }

  kvector_free(vector);
  return OK;
}

KernelStatus sche_insert_into_percpu_rq(CpuNum cpuNum, Thread *thread) {
  PerCpu *preCpu = percpu_get(cpuNum);
  kqueue_enqueue(&preCpu->readyThreadQueue, &thread->threadReadyQueue);
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
