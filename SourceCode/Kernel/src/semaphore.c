//
// Created by XingfengYang on 2020/7/17.
//

#include "kernel/log.h"
#include "kernel/sempahore.h"
#include "kernel/thread.h"

extern Thread *currentThread;

void semaphore_default_post(Semaphore *semaphore) {}

void semaphore_default_wait(Semaphore *semaphore) {}
