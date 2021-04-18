//
// Created by XingfengYang on 2021/4/17.
//

#include "kernel/module.h"
#include "kernel/type.h"
#include "kernel/log.h"

extern uint32_t __module_init_start;
extern uint32_t __module_init_end;

void kernel_module_init(){
    ModuleInitFunction function = nullptr;
    LogInfo("[Module]: init.\n");
    for(function = __module_init_start; function < __module_init_end; function++){
        if((*function)(nullptr) < 0){
            LogError("[Module]: failed to init module.\n");
        }
    }
    LogInfo("[Module]: inited.\n");
}