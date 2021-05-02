//
// Created by XingfengYang on 2021/4/17.
//

#ifndef __KERNEL_MODULE_H__
#define __KERNEL_MODULE_H__

#include <libc/stdint.h> 

typedef uint32_t (*ModuleInitFunction)(void *);

#define __module_init(func) static ModuleInitFunction __module_init_##func __attribute__((section(".moduleinit"))) = func;

void kernel_module_init();

#endif // __KERNEL_MODULE_H__