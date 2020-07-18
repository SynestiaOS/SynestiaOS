//
// Created by XingfengYang on 2020/7/17.
//

#include <mutex.h>

void mutex_create(Mutex *mutex, Atomic *atomic) { mutex->val = atomic; }

bool mutex_acquire(Mutex *mutex) {
  // todo :
}

void mutex_release(Mutex *mutex) {
  // todo :
}
