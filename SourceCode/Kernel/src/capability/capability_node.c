//
// Created by XingfengYang on 2021/7/2.
//

#include "kernel/kheap.h"
#include "kernel/capability/capabality_node.h"

extern Heap kernelHeap;

uint32_t* dirmap_alloc_block(){
        uint32_t* pBLock = kernelHeap.operations.alloc(&kernelHeap, (1 << 8) * sizeof(uint32_t*));
        for(uint32_t i = 0; i < (1 << 8); i++){
                pBLock[i] = 0;
        }
}

void dirmap_expand_level2(DirMap* dirmap, uint8_t l1){
        uint32_t* pBlock = dirmap_alloc_block();
        dirmap->ptrToBlock[l1] = pBlock;
}

void dirmap_expand_level3(DirMap* dirmap, uint8_t l1, uint8_t l2){
        uint32_t* l2Addr = dirmap->ptrToBlock[l1];
        uint32_t* pBlock = dirmap_alloc_block();
        l2Addr[l2] = pBlock;
}

void dirmap_expand_level4(DirMap *dirmap, uint8_t l1, uint8_t l2, uint8_t l3){
        uint32_t* l2Addr = dirmap->ptrToBlock[l1];
        uint32_t* l3Addr = l2Addr[l2];
        uint32_t* pBlock = dirmap_alloc_block();
        l3Addr[l3] = pBlock;
}

void dirmap_expand(DirMap *dirmap, uint8_t l1, uint8_t l2, uint8_t l3){
        if(dirmap->ptrToBlock == 0){
                dirmap_expand_level2(dirmap, l1);
                dirmap_expand_level3(dirmap, l1, l2);
                dirmap_expand_level4(dirmap, l1, l2, l3);
        } else {
                uint32_t* l2Addr = dirmap->ptrToBlock[l1];
                if(l2Addr[l2] == 0){
                        dirmap_expand_level3(dirmap, l1, l2);
                        dirmap_expand_level4(dirmap, l1, l2, l3);
                } else {
                        uint32_t* l3Addr = l2Addr[l2];
                        if(l3Addr[l3] == 0){
                                dirmap_expand_level4(dirmap, l1, l2, l3);
                        }
                }
        }
}

void dirmap_default_insert(DirMap* dirmap, uint32_t ref, void* data){
        uint8_t l1 = (ref >> 24) & 0xFF;
        uint8_t l2 = (ref >> 16) & 0xFF;
        uint8_t l3 = (ref >> 8) & 0xFF;
        uint8_t l4 = (ref >> 0) & 0xFF;

        dirmap_expand(dirmap, l1, l2, l3);

        uint32_t* l2Addr = dirmap->ptrToBlock[l1];
        uint32_t* l3Addr = l2Addr[l2];
        uint32_t* l4Addr = l3Addr[l3];

        l4Addr[l4] = data;
}

void* dirmap_default_get(DirMap* dirmap, uint32_t ref){
        uint8_t l1 = (ref >> 24) & 0xFF;
        uint8_t l2 = (ref >> 16) & 0xFF;
        uint8_t l3 = (ref >> 8) & 0xFF;
        uint8_t l4 = (ref >> 0) & 0xFF;
        
        if(dirmap->ptrToBlock[l1] != 0){
                uint32_t* l2Addr = dirmap->ptrToBlock[l1];
                if(l2Addr[l2] != 0){
                        uint32_t* l3Addr = l2Addr[l2];
                        if(l3Addr[l3] != 0){
                                uint32_t* l4Addr = l3Addr[l3];
                                return (void*)l4Addr[l4];
                        }        
                }
        }

        return nullptr;
}

void dirmap_default_del(DirMap *dirmap, uint32_t ref){
        dirmap_default_insert(dirmap, ref, nullptr);
}

DirMap* dimap_create(){
        DirMap* dirmap = kernelHeap.operations.alloc(&kernelHeap, sizeof(DirMap));

        dirmap->maxLevel = 4;
        for(int i = 0; i < 4; i++){
                dirmap->freelist[i] = 0;
                dirmap->slot[i] = 0;
                dirmap->used[i] = 0;
        }

        dirmap->slot[0] = 1 << 8;
        dirmap->ptrToBlock = dirmap_alloc_block();

        dirmap->operations.insert = (DirMapOperationInsert)dirmap_default_insert；
        dirmap->operations.get = (DirMapOperationGet)dirmap_default_get;
        dirmap->operations.del = (DirMapOperationDel)dirmap_default_del;

        return dirmap;
}