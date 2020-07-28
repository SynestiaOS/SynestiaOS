//
// Created by XingfengYang on 2020/7/13.
//

#include <log.h>
#include <sched.h>
#include <sys_call.h>

uint32_t sys_getpid(void) { return schd_getpid(); }