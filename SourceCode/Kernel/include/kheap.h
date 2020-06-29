//
// Created by XingfengYang on 2020/6/12.
//

#ifndef __KERNEL_KHEAP_H__
#define __KERNEL_KHEAP_H__
#include <stdint.h>
#include <list.h>
#include "type.h"

#define nullptr (void*)0

typedef struct HeapArea {
    uint32_t        size;
    List            list;
} HeapArea __attribute__((packed));

extern uint32_t __heap_begin;

typedef void (*heap_alloc_func)(void *ptr, uint32_t size);
typedef void (*heap_free_func)(void *ptr);


KernelStatus kernel_heap_init();
void kernel_heap_set_alloc_callback(heap_alloc_func callback);
void kernel_heap_set_free_callback(heap_free_func callback);

void* kernel_heap_alloc(uint32_t size);
void* kernel_heap_calloc(uint32_t num, uint32_t size);
void* kernel_heap_realloc(void* ptr, uint32_t size);
KernelStatus  kernel_heap_free(void *ptr);

#endif //__KERNEL_KHEAP_H__
