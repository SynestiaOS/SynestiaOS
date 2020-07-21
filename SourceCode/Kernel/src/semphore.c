//
// Created by XingfengYang on 2020/7/17.
//

#include <semphore.h>
#include <stdbool.h>
#include <thread.h>

extern Thread *currentThread;
extern KernelStatus schd_switch_next();
extern KernelStatus schd_add_to_schduler(Thread *thread);
extern KernelStatus schd_remove_from_schduler(Thread *thread);

void semphore_create(Semphore *semphore, Atomic *atomic, uint32_t count) {
  semphore->count = atomic;
  semphore->waitQueue = nullptr;
  atomic_set(atomic, count);
}

uint32_t semphore_post(Semphore *semphore) {
  atomic_inc(semphore->count);
  KQueue *queueNode = kqueue_dequeue(semphore->waitQueue);
  Thread *releasedThread = getNode(queueNode, Thread, threadReadyQueue);
  KernelStatus addToSchduler = schd_add_to_schduler(releasedThread);
  if (addToSchduler != OK) {
    printf("[Semphore]: thread add to schduler failed. \n");
  }
  return atomic_get(semphore->count);
}

KernelStatus semphore_wait(Semphore *semphore) {
  if (atomic_get(semphore->count) > 0) {
    atomic_dec(semphore->count);
    return OK;
  } else {
    // can not get the lock, just add to lock wait list
    KernelStatus enQueueStatus = kqueue_enqueue(semphore->waitQueue, &currentThread->threadReadyQueue);
    if (enQueueStatus != OK) {
      printf("[Semphore]: thread add to wait list failed. \n");
      return ERROR;
    }
    // reomve from schd list
    KernelStatus removeStatus = schd_remove_from_schduler(currentThread);
    if (removeStatus != OK) {
      printf("[Mutex]: thread remove from schd list failed. \n");
      return ERROR;
    }

    // 2. switch to the next thread in scheduler
    KernelStatus thradSwitchNextStatus = schd_switch_next();
    if (thradSwitchNextStatus != OK) {
      printf("[Semphore]: thread switch to next failed. \n");
      return ERROR;
    }
    return OK;
  }
}