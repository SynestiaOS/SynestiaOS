#include "kernel/module.h"
#include "kernel/log.h"
#include "libc/stdint.h"

uint32_t module_helloworld(void* data){
    LogInfo("[Module]: module helloworld inited.\n");
    return 1;
}

__module_init(module_helloworld);