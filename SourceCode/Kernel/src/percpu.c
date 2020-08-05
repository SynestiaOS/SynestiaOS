//
// Created by XingfengYang on 2020/6/30.
//

#include <kheap.h>
#include <log.h>
#include <percpu.h>
#include <thread.h>

PerCpu *perCpu = nullptr;

KernelStatus percpu_default_insert_thread(PerCpu *perCpu, Thread *thread) {
  LogWarn("[PerCpu]: insert thread '%s' to cpu '%d'.\n", thread->name, perCpu->cpuId);
  perCpu->rbTree.operations.insert(&perCpu->rbTree, &thread->rbNode);
  perCpu->priority += thread->priority;
  return OK;
}

Thread *percpu_default_remove_thread(PerCpu *perCpu, Thread *thread) {
  LogWarn("[PerCpu]: remove thread '%s' from cpu '%d'.\n", thread->name, perCpu->cpuId);
  RBNode* node = perCpu->rbTree.operations.remove(&perCpu->rbTree, &thread->rbNode);
  perCpu->priority -= thread->priority;
  return getNode(node,Thread,rbNode);
}

Thread *percpu_default_get_next_thread(PerCpu *perCpu) {
  RBNode *node = perCpu->rbTree.operations.getMin(&perCpu->rbTree);
  if (node == nullptr) {
    // todo: migration from other core.
    LogWarn("[PerCpu]: get min thread null.\n");
    return perCpu->idleThread;
  }
  Thread *thread = getNode(node, Thread, rbNode);
  if (thread == nullptr) {
    return perCpu->idleThread;
  }
  return thread;
}

KernelStatus percpu_default_init(PerCpu *perCpu, uint32_t num, Thread *idleThread) {
  perCpu->idleThread = idleThread;
  perCpu->cpuId = num;
  perCpu->priority = 0;
  perCpu->status.idleTime = 0;
  perCpu->currentThread = nullptr;
  perCpu->rbTree.root = nullptr;
  rb_tree_init(&perCpu->rbTree);
  perCpu->waitThreadQueue.next = nullptr;
  perCpu->waitThreadQueue.prev = nullptr;
  LogInfo("[PerCpu]: precpu '%d' inited.\n", num);
  return OK;
}

KernelStatus percpu_create(uint32_t cpuNum) {
  perCpu = (PerCpu *)kheap_calloc(cpuNum, sizeof(PerCpu));
  if (perCpu == nullptr) {
    return ERROR;
  }
  for (uint32_t cpuId = 0; cpuId < cpuNum; cpuId++) {
    perCpu[cpuId].operations.init = percpu_default_init;
    perCpu[cpuId].operations.insertThread = percpu_default_insert_thread;
    perCpu[cpuId].operations.removeThread = percpu_default_remove_thread;
    perCpu[cpuId].operations.getNextThread = percpu_default_get_next_thread;
  }
  return OK;
}

PerCpu *percpu_get(CpuNum cpuNum) { return &perCpu[cpuNum]; }

PerCpu *percpu_min_priority() {
  PerCpu *min = &perCpu[0];
  for (uint32_t cpuId = 0; cpuId < CPU_EXISTS_NUM; cpuId++) {
    if (perCpu[cpuId].priority < min->priority) {
      min = &perCpu[cpuId];
    }
  }
  return min;
}
