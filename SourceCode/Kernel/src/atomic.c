//
// Created by XingfengYang on 2020/7/17. 
//
#include <atomic.h>

void atomic_set(Atomic *atomic,uint32_t val){
    // todo : STREX
}

uint32_t atomic_get(Atomic *atomic){
    // todo : LDREX
}