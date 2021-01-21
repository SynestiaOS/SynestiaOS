//
// Created by XingfengYang on 2021/1/21.
//

#include "kernel/bitmap.h"


void bitmap_default_set_true(struct BitMap *bitMap, uint32_t pos) {

}

void bitmap_default_set_false(struct BitMap *bitMap, uint32_t pos) {

}

uint32_t bitmap_default_get_first_true(struct BitMap *bitMap) {

}

uint32_t bitmap_default_get_first_false(struct BitMap *bitMap) {

}

void bitmap_default_free(struct BitMap *bitMap) {

}

BitMap *bitmap_create(struct BitMap *bitMap, uint32_t size) {
    bitMap->operation.getFirstFalse = (BitMapOperationGetFirstFalse) bitmap_default_get_first_false;
    bitMap->operation.getFirstTrue = (BitMapOperationGetFirstTrue) bitmap_default_get_first_true;
    bitMap->operation.setTrue = (BitMapOperationSetTrue) bitmap_default_set_true;
    bitMap->operation.setFalse = (BitMapOperationSetFalse) bitmap_default_set_false;
    bitMap->operation.free = (BitMapOperationFree) bitmap_default_free;

    return bitMap;
}
