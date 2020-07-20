//
// Created by XingfengYang on 2020/7/20.
//

#include <ktimer.h>

uint64_t sys_runtime_ms = 0;

uint64_t ktimer_sys_runtime_tick(uint64_t tickIntreval) { sys_runtime_ms += tickIntreval; }

uint64_t ktimer_sys_runtime() { return sys_runtime_ms; }