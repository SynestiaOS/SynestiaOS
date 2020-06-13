//
// Created by XingfengYang on 2020/6/12.
//

#ifndef __KERNEL_KHEAP_H__
#define __KERNEL_KHEAP_H__
#include <stdint.h>
#include <list.h>

#define nullptr (void*)0

typedef struct HeapArea {
    uint32_t        size;
    List            list;
} HeapArea __attribute__((packed));

extern struct HeapArea *heap_begin;
extern struct HeapArea *heap_end;


typedef void (*heap_alloc_func)(void *ptr, uint32_t size);
typedef void (*heap_free_func)(void *ptr);


void heap_init();
void heap_set_alloc_callback(heap_alloc_func callback);
void heap_set_free_callback(heap_free_func callback);

void* heap_alloc(uint32_t size);
void* heap_calloc(uint32_t num, uint32_t size);
void* heap_realloc(void* ptr, uint32_t size);
void  heap_free(void *ptr);

#endif //__KERNEL_KHEAP_H__
