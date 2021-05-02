//
// Created by XingfengYang on 2021/4/17.
//

#ifndef __KERNEL_MODULE_H__
#define __KERNEL_MODULE_H__

#include <libc/stdint.h> 

typedef uint32_t (*ModuleInitFunction)(void *);

#define __module_init(func, level) static ModuleInitFunction __module_init_lv##lv##_##func __attribute__((section(".module_lv"#level ".init"))) = func;

#define module_init(func) static ModuleInitFunction __module_init_lv5_##func __attribute__((section(".module_lv5.init"))) = func;

#define modules_init(level) \
extern uint32_t __module_init_lv##level##_start;    \
extern uint32_t __module_init_lv##level##_end;  \
void kernel_module_level_##level##_init(){  \
    LogInfo("[Module]: level "#level " init.\n");   \
    if(&__module_init_lv##level##_start == &__module_init_lv##level##_end){ \
        LogError("[Module]: no module found in level "#level ".\n"); \
        return; \
    }   \
    ModuleInitFunction function = nullptr;  \
    for(function = &__module_init_lv##level##_start; function < &__module_init_lv##level##_end; function += sizeof(ModuleInitFunction)){    \
        uint32_t funcAddr = *(uint32_t*)(function);     \
        if(((ModuleInitFunction)funcAddr)(nullptr) < 0){    \
            LogError("[Module]: failed to init module.\n"); \
        }   \
    }   \
    LogInfo("[Module]: level "#level " inited.\n"); \
}

void kernel_module_level_0_init();
void kernel_module_level_1_init();
void kernel_module_level_2_init();
void kernel_module_level_3_init();
void kernel_module_level_4_init();
void kernel_module_level_5_init();
void kernel_module_init();

#endif // __KERNEL_MODULE_H__