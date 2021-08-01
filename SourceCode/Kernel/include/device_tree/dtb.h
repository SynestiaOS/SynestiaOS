#ifndef SYNESTIAOS_DEVICE_TREE_DTB_H
#define SYNESTIAOS_DEVICE_TREE_DTB_H

#include "libc/stdint.h"

#define FDT_BEGIN_NODE  0x00000001
#define FDT_END_NODE    0x00000002
#define FDT_PROP        0x00000003
#define FDT_NOP         0x00000004
#define FDT_END         0x00000009

typedef struct FtdHeader{
    uint32_t magic;
    uint32_t totalsize;
    uint32_t offsetOfStructureBlock;
    uint32_t offsetOfStringsBlock;
    uint32_t offsetOfMemReservationBlock;
    uint32_t version;
    uint32_t lastCompatibleVersion;
    uint32_t bootPhysicalCpuID;
    uint32_t sizeOfStringsBlock;
    uint32_t sizeOfStructureBlock;
} FtdHeader;

typedef struct FdtReserveEntry {
    uint64_t address;
    uint64_t size;
} FdtReserveEntry;


typedef struct FdtProprty {
    uint32_t len;
    uint32_t nameoff;
} FdtProperty;

typedef struct DeviceTreeNode {
    // TODO: fill me 
} DeviceTreeNode;


typedef uint32_t (*DeviceTreeOperationGetNodeOffsetByCompatible)(const char* compatible);
typedef struct DeviceTreeOperations{
    DeviceTreeOperationGetNodeByCompatible getNodeOffsetByCompatible;
} DeviceTreeOperations;
typedef struct DeviceTree {
    DeviceTreeNode *rootNode;
    DeviceTreeOperations ops;
} DeviceTree;

#endif //SYNESTIAOS_DEVICE_TREE_DTB_H
