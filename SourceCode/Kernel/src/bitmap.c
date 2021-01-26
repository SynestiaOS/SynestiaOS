//
// Created by XingfengYang on 2021/1/21.
//

#include "kernel/log.h"
#include "kernel/bitmap.h"


void bitmap_default_set_true(struct BitMap *bitMap, uint32_t pos) {
    uint32_t index = pos / BITS_IN_UINT32;
    uint8_t bitIndex = pos % BITS_IN_UINT32;

    bitMap->data[index] |= (uint32_t) 0x1 << bitIndex;
}

void bitmap_default_set_false(struct BitMap *bitMap, uint32_t pos) {
    uint32_t index = pos / BITS_IN_UINT32;
    uint8_t bitIndex = pos % BITS_IN_UINT32;

    bitMap->data[index] ^= (uint32_t) 0x1 << bitIndex;
}

uint32_t bitmap_default_get_first_true(struct BitMap *bitMap) {
    for (uint32_t i = 0; i < bitMap->size / BITS_IN_UINT32; i++) {
        if (bitMap->data[i] != 0x0) {
            for (uint8_t j = 0; j < BITS_IN_UINT32; j++) {
                if ((bitMap->data[i] & ((uint32_t) 0x1 << j)) == 1) {
                    return i * BITS_IN_UINT32 + j;
                }
            }
        }
    }
}

uint32_t bitmap_default_get_first_false(struct BitMap *bitMap) {
    for (uint32_t i = 0; i < bitMap->size / BITS_IN_UINT32; i++) {
        if (bitMap->data[i] != MAX_UINT_32) {
            for (uint8_t j = 0; j < BITS_IN_UINT32; j++) {
                if ((bitMap->data[i] & ((uint32_t) 0x1 << j)) == 0) {
                    return i * BITS_IN_UINT32 + j;
                }
            }
        }
    }
}

void bitmap_default_free(struct BitMap *bitMap) {
    bitMap->heap->operations.free(bitMap->heap, bitMap->data);
}

BitMap *bitmap_create(struct BitMap *bitMap, struct Heap *heap, uint32_t size) {
    bitMap->operation.getFirstFalse = (BitMapOperationGetFirstFalse) bitmap_default_get_first_false;
    bitMap->operation.getFirstTrue = (BitMapOperationGetFirstTrue) bitmap_default_get_first_true;
    bitMap->operation.setTrue = (BitMapOperationSetTrue) bitmap_default_set_true;
    bitMap->operation.setFalse = (BitMapOperationSetFalse) bitmap_default_set_false;
    bitMap->operation.free = (BitMapOperationFree) bitmap_default_free;

    bitMap->size = size;
    bitMap->heap = heap;

    uint32_t i32Nums = (size / BITS_IN_UINT32) + (size % BITS_IN_UINT32 > 0 ? 1 : 0);

    bitMap->data = heap->operations.calloc(heap, i32Nums, sizeof(uint32_t));
    if (bitMap->data == nullptr) {
        LogError("[BitMap] data allocate failed.\n");
    }

    return bitMap;
}
