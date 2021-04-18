#include "kernel/module.h"
#include "kernel/log.h"
#include "libc/stdint.h"

uint32_t module_helloworld1(void* data){
    LogInfo("[Module]: module helloworld1 inited.\n");
    return 1;
}

uint32_t module_helloworld2(void* data){
    LogInfo("[Module]: module helloworld2 inited.\n");
    return 1;
}

__module_init(module_helloworld1);
__module_init(module_helloworld2);