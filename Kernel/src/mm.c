//
// Created by XingfengYang on 2020/6/12.
//

#include <mm.h>

uint32_t *mask;

void  mm_init(){
    int maxMemory = 0xFFFFFFFF;

}

void* kmalloc(uint32_t size);

void* krealloc(void *mem, uint32_t size);


void kfree(void *);
