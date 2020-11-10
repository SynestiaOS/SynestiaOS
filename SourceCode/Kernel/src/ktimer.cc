//
// Created by XingfengYang on 2020/7/20.
//

#include <ktimer.h>
#include <list.h>
#include <mutex.h>

uint64_t sys_runtime_ms = 0;

uint64_t ktimer_sys_runtime_tick(uint64_t tickIntreval) { sys_runtime_ms += tickIntreval; }

uint64_t ktimer_sys_runtime() { return sys_runtime_ms; }

typedef struct KernelTimer {
    long time;
    ListNode listNode;
    Mutex *mutex;
} KernelTimer;
