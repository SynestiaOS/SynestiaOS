//
// Created by XingfengYang on 2021/1/21.
//

#ifndef SYNESTIAOS_BITMAP_H
#define SYNESTIAOS_BITMAP_H

#include "kernel/type.h"
#include "libc/stdint.h"
#include "kernel/kheap.h"

typedef void (*BitMapOperationSetTrue)(struct BitMap *bitMap, uint32_t pos);

typedef void (*BitMapOperationSetFalse)(struct BitMap *bitMap, uint32_t pos);

typedef uint32_t (*BitMapOperationGetFirstTrue)(struct BitMap *bitMap);

typedef uint32_t (*BitMapOperationGetFirstFalse)(struct BitMap *bitMap);

typedef void (*BitMapOperationFree)(struct BitMap *bitMap);

typedef struct BitMapOperation {
    BitMapOperationSetTrue setTrue;
    BitMapOperationSetFalse setFalse;
    BitMapOperationGetFirstTrue getFirstTrue;
    BitMapOperationGetFirstFalse getFirstFalse;
    BitMapOperationFree free;
} BitMapOperation;

typedef struct BitMap {
    uint32_t size;
    uint32_t *data;
    Heap *heap;
    BitMapOperation operation;
} BitMap;

BitMap *bitmap_create(struct BitMap *bitMap, struct Heap *heap, uint32_t size);

#endif //SYNESTIAOS_BITMAP_H
