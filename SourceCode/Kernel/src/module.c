//
// Created by XingfengYang on 2021/4/17.
//

#include "kernel/module.h"
#include "kernel/type.h"
#include "kernel/log.h"

extern uint32_t __module_init_start;
extern uint32_t __module_init_end;

void kernel_module_init(){
    LogInfo("[Module]: init.\n");
    ModuleInitFunction function = nullptr;
    for(function = &__module_init_start; function < &__module_init_end; function += sizeof(ModuleInitFunction)){
        uint32_t funcAddr = *(uint32_t*)(function);
        if(((ModuleInitFunction)funcAddr)(nullptr) < 0){
            LogError("[Module]: failed to init module.\n");
        }
    }
    LogInfo("[Module]: inited.\n");
}