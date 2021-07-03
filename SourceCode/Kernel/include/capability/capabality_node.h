#ifndef SYNESTIAOS_CAPABILITY_NODE_H
#define SYNESTIAOS_CAPABILITY_NODE_H

#include "libc/stdint.h"

typedef uint32_t (*DirMapOperationInsert)(DirMap *dirmap, void *data);
typedef void* (*DirMapOperationGet)(DirMap* dirmap, uint32_t ref);
typedef void (*DirMapOperationDel)(DirMap* dirmap, uint32_t ref);

typedef struct DirMapOperation{
    DirMapOperationInsert insert;
    DirMapOperationGet get;
    DirMapOperationDel del;
} DirMapOperation;

// 2-8-8-12
typedef struct DirMap {
    uint32_t maxLevel;
    uint32_t used[4];
    uint32_t slot[4];
    uint32_t freelist[4];

    DirMapOperation operation;

    uint32_t* ptrToBlock;
} DirMap;

DirMap* dirmap_create();

typedef struct CapabilityNode {
    DirMap ownTable; // Own ability and authority
    DirMap conferTable; // Capabilities and permissions granted to other threads
    DirMap acquireTable; // Ability and authority acquired
} CapabilityNode;

#endif // SYNESTIAOS_CAPABILITY_H