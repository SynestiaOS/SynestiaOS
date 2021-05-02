//
// Created by XingfengYang on 2021/4/17.
//

#include "kernel/module.h"
#include "kernel/type.h"
#include "kernel/log.h"

modules_init(0);
modules_init(1);
modules_init(2);

void kernel_module_init(){
    LogInfo("[Module]: init.\n");
    kernel_module_level_0_init();
    kernel_module_level_1_init();
    LogInfo("[Module]: inited.\n");
}