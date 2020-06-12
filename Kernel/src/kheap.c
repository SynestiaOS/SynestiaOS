//
// Created by XingfengYang on 2020/6/12.
//

#include <kheap.h>

static heap_alloc_func heapAllocFunc;
static heap_free_func  heapFreeFunc;


void heap_set_alloc_callback(heap_alloc_func callback){
    heapAllocFunc = callback;
}
void heap_set_free_callback(heap_free_func callback){
    heapFreeFunc = callback;
}

void* heap_alloc(uint32_t size){
    HeapArea *a = nullptr;

}

void* heap_calloc(uint32_t num, uint32_t size){

}

void* heap_realloc(void* ptr, uint32_t size){

}

void  heap_free(void *ptr){

}
