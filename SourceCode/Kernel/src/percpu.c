//
// Created by XingfengYang on 2020/6/30.
//

#include <kheap.h>
#include <percpu.h>
#include <thread.h>

PerCpu *perCpu = nullptr;

KernelStatus percpu_default_insert_thread(PerCpu* perCpu, Thread *thread){
  perCpu->rbTree.operations.insert(&perCpu->rbTree, &thread->rbNode);
  // todo: insert into rbtree
  return ERROR;
}

Thread* percpu_default_remove_thread(PerCpu* perCpu, Thread *thread){
  RBNode* node = perCpu->rbTree.operations.remove(&perCpu->rbTree,&thread->rbNode);
  return node;
}

Thread* percpu_default_get_next_thread(PerCpu* perCpu){
  PerCpu *min =percpu_min_priority();
  RBNode* node = min->rbTree.operations.getMin(&min->rbTree);
  if(node==nullptr){
    // todo: migration from other core.
    return perCpu->idleThread;
  }else{
    Thread* thread = getNode(node,Thread,rbNode);
    if(thread==nullptr){
      return perCpu->idleThread;
    }
    return thread;
  }
}

KernelStatus percpu_default_init(PerCpu* perCpu, uint32_t num,Thread *idleThread){
  perCpu->idleThread = idleThread;
  perCpu->cpuNum = num;
  perCpu->priority = 0;
  perCpu->status.idleTime = 0;
  perCpu->currentThread = nullptr;
  perCpu->rbTree.root = nullptr;

  perCpu->waitThreadQueue.next = nullptr;
  perCpu->waitThreadQueue.prev = nullptr;
  return OK;
}

KernelStatus percpu_create(uint32_t cpuNum) {
  perCpu = (PerCpu *)kheap_calloc(cpuNum, sizeof(PerCpu));
  if (perCpu == nullptr) {
    return ERROR;
  }
  for(uint32_t cpuId = 0;cpuId<cpuNum;cpuId++){
    perCpu[cpuId].operations.init = percpu_default_init;
    perCpu[cpuId].operations.insertThread = percpu_default_insert_thread;
    perCpu[cpuId].operations.insertThread = percpu_default_remove_thread;
    perCpu[cpuId].operations.getNextThread = percpu_default_get_next_thread;
  }
  return OK;
}

PerCpu *percpu_get(CpuNum cpuNum) { return &perCpu[cpuNum]; }

PerCpu *percpu_min_priority(){
  PerCpu *min = &perCpu[0];
  for(uint32_t cpuId = 0;cpuId<CPU_EXISTS_NUM;cpuId++){
    if(perCpu[cpuId].priority < min->priority){
      min = &perCpu[cpuId];
    }
  }
  return min;
}