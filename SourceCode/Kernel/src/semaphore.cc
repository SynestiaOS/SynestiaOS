//
// Created by XingfengYang on 2020/7/17.
//

#include "kernel/log.hpp"
#include "kernel/sempahore.hpp"
#include "kernel/thread.hpp"

extern Thread *currentThread;

void semaphore_default_post(Semaphore *semaphore) {}

void semaphore_default_wait(Semaphore *semaphore) {}
