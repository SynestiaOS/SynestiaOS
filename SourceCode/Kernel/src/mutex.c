//
// Created by XingfengYang on 2020/7/17.
//

#include <mutex.h>
#include <stdbool.h>
#include <thread.h>
#include <log.h>

extern Thread *currentThread;
extern KernelStatus schd_switch_next();
extern KernelStatus schd_add_to_schduler(Thread *thread);
extern KernelStatus schd_remove_from_schduler(Thread *thread);

void mutex_create(Mutex *mutex, Atomic *atomic) {
  mutex->val = atomic;
  mutex->waitQueue = nullptr;
  atomic_create(atomic);
}

bool mutex_acquire(Mutex *mutex) {
  if (atomic_get(mutex->val) == 0) {
    atomic_set(mutex->val, 1);
    return true;
  } else {
    // can not get the lock, just add to lock wait list
    KernelStatus enQueueStatus = kqueue_enqueue(mutex->waitQueue, &currentThread->threadReadyQueue);
    if (enQueueStatus != OK) {
      LogError("[Mutex]: thread add to wait list failed. \n");
      return false;
    }

    // reomve from schd list
    KernelStatus removeStatus = schd_remove_from_schduler(currentThread);
    if (removeStatus != OK) {
      LogError("[Mutex]: thread remove from schd list failed. \n");
      return false;
    }

    // 2. switch to the next thread in scheduler
    KernelStatus thradSwitchNextStatus = schd_switch_next();
    if (thradSwitchNextStatus != OK) {
      LogError("[Mutex]: thread switch to next failed. \n");
    }
    return false;
  }
}

void mutex_release(Mutex *mutex) {
  atomic_set(mutex->val, 0);
  KQueue *queueNode = kqueue_dequeue(mutex->waitQueue);
  Thread *releasedThread = getNode(queueNode, Thread, threadReadyQueue);
  KernelStatus addToSchduler = schd_add_to_schduler(releasedThread);
  if (addToSchduler != OK) {
    LogError("[Mutex]: thread add to schduler failed. \n");
  }
}
