//
// Created by XingfengYang on 2020/8/7.
//

#include <kernel/ext2.h>
#include <kernel/kheap.h>
#include <kernel/list.h>
#include <kernel/log.h>
#include <kernel/vfs_dentry.h>
#include <kernel/vfs_inode.h>
#include <libc/stdint.h>
#include <libc/string.h>

extern Heap kernelHeap;

#define EXT2_SIGNATURE 0xef53
#define EXT2_BLOCK_GROUP_DESCRIPTOR_SIZE 32
#define EXT2_INDEX_NODE_STRUCTURE_SIZE 128
#define EXT2_SUPER_BLOCK_OFFSET 1024

void ext2_recursively_fill_superblock(Ext2FileSystem *ext2FileSystem, Ext2IndexNode *ext2IndexNode,
                                      DirectoryEntry *vfsDirectoryEntry, char *name) {
    if ((ext2IndexNode->typeAndPermissions & 0xF000) == EXT2_INDEX_NODE_TYPE_DIRECTORY) {
        // create directory vfs inode, and dentry, and fill them
        DirectoryEntry *directoryEntry = ext2FileSystem->superblock.operations.createDirectoryEntry(
                &ext2FileSystem->superblock, name);
        IndexNode *indexNode = ext2FileSystem->superblock.operations.createIndexNode(&ext2FileSystem->superblock,
                                                                                     directoryEntry);

        if (vfsDirectoryEntry->children != nullptr) {
            // connect this dentry to parent's children 's node
            klist_append(&vfsDirectoryEntry->children->list, &directoryEntry->list);
        }

        directoryEntry->operations.initOperation(directoryEntry, vfsDirectoryEntry, indexNode);

        // atomic_set(&directoryEntry->refCount,1);
        directoryEntry->operations.hashOperation(directoryEntry);
        directoryEntry->indexNode->type = INDEX_NODE_DIRECTORY;

        Ext2DirectoryEntry *dEntry = (Ext2DirectoryEntry *) ((uint32_t) ext2FileSystem->data +
                                                             ext2IndexNode->directBlockPointer0 *
                                                                     ext2FileSystem->blockSize);

        while (*(uint32_t *) ((uint32_t) dEntry) != 0) {
            if (strcmp(dEntry->nameCharacters, "..") || strcmp(dEntry->nameCharacters, ".") ||
                strcmp(dEntry->nameCharacters, "lost+found")) {
                // TODO: lost+found
                // ignore

                uint32_t dEntryNameAlignment = dEntry->nameLength / 4;
                dEntryNameAlignment = dEntryNameAlignment * 4 + (dEntry->nameLength % 4 > 0 ? 4 : 0);
                uint32_t nextDEntryAddr = dEntry->nameCharacters + dEntryNameAlignment;
                dEntry = (Ext2DirectoryEntry *) (nextDEntryAddr);
                continue;
            }
            // inode is directory , it's means should recursion
            uint32_t blockGroup = (dEntry->indexNode - 1) / ext2FileSystem->ext2SuperBlock->eachBlockGroupIndexNodeNums;

            Ext2IndexNode *nextNode = (Ext2IndexNode *) ((uint32_t) ext2FileSystem->blockGroups[blockGroup].indexNode +
                                                         (((uint32_t) dEntry->indexNode - 1) %
                                                          ext2FileSystem->ext2SuperBlock->eachBlockGroupIndexNodeNums) *
                                                                 EXT2_INDEX_NODE_STRUCTURE_SIZE);
            char name[0xFF] = {'\0'};
            for (uint32_t i = 0; i < dEntry->nameLength; i++) {
                name[i] = dEntry->nameCharacters[i];
            }
            ext2_recursively_fill_superblock(ext2FileSystem, nextNode, directoryEntry, name);

            uint32_t dEntryNameAlignment = dEntry->nameLength / 4;
            dEntryNameAlignment = dEntryNameAlignment * 4 + (dEntry->nameLength % 4 > 0 ? 4 : 0);
            uint32_t nextDEntryAddr = dEntry->nameCharacters + dEntryNameAlignment;

            dEntry = (Ext2DirectoryEntry *) (nextDEntryAddr);
        }
    } else if ((ext2IndexNode->typeAndPermissions & 0xF000) == EXT2_INDEX_NODE_TYPE_REGULAR_FILE) {
        // create vfs inode, create vfs dentry , and fill them
        DirectoryEntry *directoryEntry = ext2FileSystem->superblock.operations.createDirectoryEntry(
                &ext2FileSystem->superblock, name);
        IndexNode *indexNode = ext2FileSystem->superblock.operations.createIndexNode(&ext2FileSystem->superblock,
                                                                                     directoryEntry);

        if (vfsDirectoryEntry->children != nullptr) {
            // connect this dentry to parent's children 's node
            klist_append(&vfsDirectoryEntry->children->list, &directoryEntry->list);
        }

        directoryEntry->operations.initOperation(directoryEntry, vfsDirectoryEntry, indexNode);

        indexNode->type = INDEX_NODE_FILE;
        indexNode->id =
                (uint32_t)(ext2IndexNode - ext2FileSystem->blockGroups->indexNode) / EXT2_INDEX_NODE_STRUCTURE_SIZE;
        indexNode->mode = ext2IndexNode->typeAndPermissions & 0xFFF;
        indexNode->fileSize = ext2IndexNode->sizeUpper32Bits << 32 | ext2IndexNode->sizeLower32Bits;
        // atomic_set(&indexNode->linkCount,1);
        indexNode->createTimestamp = ext2IndexNode->createTime;
        indexNode->lastAccessTimestamp = ext2IndexNode->lastAccessTime;
        indexNode->lastUpdateTimestamp = ext2IndexNode->lastModficationTime;

        indexNode->indexNodePrivate = (uint32_t) ext2IndexNode;
        return;
    }
}

KernelStatus ext2_fs_default_mount(Ext2FileSystem *ext2FileSystem, char *mountName, void *data) {
    Ext2SuperBlock *ext2SuperBlock = (Ext2SuperBlock *) ((uint32_t) data + EXT2_SUPER_BLOCK_OFFSET);

    if (ext2SuperBlock->signature != EXT2_SIGNATURE) {
        LogError("[Ext2]: not a ext2 file system.\n");
        return ERROR;
    }

    // make root
    DirectoryEntry *rootDirectoryEntry = ext2FileSystem->superblock.operations.createDirectoryEntry(
            &ext2FileSystem->superblock, mountName);
    IndexNode *rootIndexNode = ext2FileSystem->superblock.operations.createIndexNode(&ext2FileSystem->superblock,
                                                                                     rootDirectoryEntry);
    rootDirectoryEntry->operations.initOperation(rootDirectoryEntry, nullptr, rootIndexNode);
    ext2FileSystem->superblock.rootDirectoryEntry = rootDirectoryEntry;

    ext2FileSystem->ext2SuperBlock = ext2SuperBlock;

    LogInfo("[Ext2]: %d inodes in file system.\n", ext2SuperBlock->indexNodeNums);
    LogInfo("[Ext2]: %d blocks in file system.\n", ext2SuperBlock->blockNums);
    LogInfo("[Ext2]: %d blocks reserved for superuser.\n", ext2SuperBlock->blockReservedForSuperuserNums);
    LogInfo("[Ext2]: %d unallocated blocks.\n", ext2SuperBlock->unallocatedBlockNums);
    LogInfo("[Ext2]: %d unallocated inodes.\n", ext2SuperBlock->unallocatedIndexNodeNums);
    LogInfo("[Ext2]: %d block containing the superblock.\n", ext2SuperBlock->blockContainingSuperblockNums);
    LogInfo("[Ext2]: BlockSize: %d .\n", 1 << (ext2SuperBlock->log2BlockSizeSub10 + 10));
    LogInfo("[Ext2]: FragmentSize: %d .\n", 1 << (ext2SuperBlock->log2FragmentSizeSub10 + 10));
    LogInfo("[Ext2]: %d blocks in each block group.\n", ext2SuperBlock->eachBlockGroupBlockNums);
    LogInfo("[Ext2]: %d fragments in each block group.\n", ext2SuperBlock->eachBlockGroupFragmentNums);
    LogInfo("[Ext2]: %d inodes in each block group.\n", ext2SuperBlock->eachBlockGroupIndexNodeNums);
    LogInfo("[Ext2]: superblock in %d block group.\n", ext2SuperBlock->blockGroups);

    // Block size
    uint32_t blockSize = 1 << (ext2SuperBlock->log2BlockSizeSub10 + 10);

    // Block Group Descriptor numbers , other words, this is super block numbers or block group number
    uint32_t blockGroupNums = ext2SuperBlock->indexNodeNums / ext2SuperBlock->eachBlockGroupIndexNodeNums;
    if (ext2SuperBlock->indexNodeNums % ext2SuperBlock->eachBlockGroupIndexNodeNums > 0) {
        blockGroupNums++;
    }
    LogInfo("[Ext2]: block groups: %d .\n", blockGroupNums);

    uint32_t indexNodeNumsInEachBlock = blockSize / EXT2_INDEX_NODE_STRUCTURE_SIZE;
    uint32_t blockForIndexNodeTable = ext2SuperBlock->indexNodeNums / indexNodeNumsInEachBlock;
    uint32_t blockForIndexNodeTableMod = ((ext2SuperBlock->indexNodeNums % indexNodeNumsInEachBlock) > 0) ? 1 : 0;
    blockForIndexNodeTable += blockForIndexNodeTableMod;
    LogInfo("[Ext2]: index node table  blocks: %d .\n", blockForIndexNodeTable);

    Ext2BlockGroup *blockGroup = (Ext2BlockGroup *) kernelHeap.operations.alloc(&kernelHeap, blockGroupNums *
                                                                                                     sizeof(Ext2BlockGroup));

    for (uint32_t blockGroupDescriptorIndex = 0; blockGroupDescriptorIndex < blockGroupNums;
         blockGroupDescriptorIndex++) {
        blockGroup[blockGroupDescriptorIndex].superBlock = (Ext2SuperBlock *) ((uint32_t) data +
                                                                               EXT2_SUPER_BLOCK_OFFSET);

        blockGroup[blockGroupDescriptorIndex].blockGroupDescriptor = (Ext2BlockGroupDescriptor *) ((uint32_t) blockGroup[blockGroupDescriptorIndex].superBlock + blockSize +
                                                                                                   blockGroupDescriptorIndex * EXT2_BLOCK_GROUP_DESCRIPTOR_SIZE);

        blockGroup[blockGroupDescriptorIndex].dataBlockBitmap = (Ext2DataBlockBitmap *) ((uint32_t) data +
                                                                                         blockGroup[blockGroupDescriptorIndex].blockGroupDescriptor->blockUsageBitMapBlock *
                                                                                                 blockSize);

        blockGroup[blockGroupDescriptorIndex].indexNodeBitmap = (Ext2IndexNodeBlockBitmap *) ((uint32_t) data +
                                                                                              blockGroup[blockGroupDescriptorIndex].blockGroupDescriptor->indexNodeUsageBitMapBlock *
                                                                                                      blockSize);

        blockGroup[blockGroupDescriptorIndex].indexNode = (Ext2IndexNode *) ((uint32_t) data +
                                                                             blockGroup[blockGroupDescriptorIndex].blockGroupDescriptor->indexNodeTableBlockBlock *
                                                                                     blockSize);

        blockGroup[blockGroupDescriptorIndex].dataBlock = (Ext2DataBlock *) ((uint32_t) blockGroup[blockGroupDescriptorIndex].indexNode + blockForIndexNodeTable * blockSize);
    }

    ext2FileSystem->blockGroups = blockGroup;
    ext2FileSystem->blockGroupNums = blockGroupNums;

    // assume that the root directory is in second inode, because the first inode is
    Ext2IndexNode *root = (Ext2IndexNode *) ((uint32_t) blockGroup->indexNode + EXT2_INDEX_NODE_STRUCTURE_SIZE);
    Ext2DirectoryEntry *ext2RootDirectoryEntry = (Ext2DirectoryEntry *) ((uint32_t) data +
                                                                         root->directBlockPointer0 * blockSize);

    // let's recursion

    ext2FileSystem->data = data;
    ext2FileSystem->blockSize = blockSize;
    ext2_recursively_fill_superblock(ext2FileSystem, root, rootDirectoryEntry, "initrd");

    LogInfo("[Ext2]: mounted.\n");
}

uint32_t ext2_get_data_block(Ext2FileSystem *ext2FileSystem, Ext2IndexNode *ext2IndexNode, uint32_t blockIndex) {
    uint32_t directBlockMax = 12;
    uint32_t blockPointerNumsInEachBlock = ext2FileSystem->blockSize / sizeof(uint32_t);
    uint32_t singlyIndirectBlocksMax = directBlockMax + blockPointerNumsInEachBlock;
    uint32_t doublyIndirectBlocksMax = directBlockMax + blockPointerNumsInEachBlock * blockPointerNumsInEachBlock;
    uint32_t triplyIndirectBlocksMax =
            directBlockMax + blockPointerNumsInEachBlock * blockPointerNumsInEachBlock * blockPointerNumsInEachBlock;

    switch (blockIndex) {
        case 0:
            return ext2IndexNode->directBlockPointer0;
        case 1:
            return ext2IndexNode->directBlockPointer1;
        case 2:
            return ext2IndexNode->directBlockPointer2;
        case 3:
            return ext2IndexNode->directBlockPointer3;
        case 4:
            return ext2IndexNode->directBlockPointer4;
        case 5:
            return ext2IndexNode->directBlockPointer5;
        case 6:
            return ext2IndexNode->directBlockPointer6;
        case 7:
            return ext2IndexNode->directBlockPointer7;
        case 8:
            return ext2IndexNode->directBlockPointer8;
        case 9:
            return ext2IndexNode->directBlockPointer9;
        case 10:
            return ext2IndexNode->directBlockPointer10;
        case 11:
            return ext2IndexNode->directBlockPointer11;
        default:
            if ((blockIndex > directBlockMax - 1) && (blockIndex < singlyIndirectBlocksMax)) {
                uint32_t singlyIndirectBlock = (uint32_t)(ext2FileSystem->data +
                                                          ext2IndexNode->singlyIndirectBlockPointer *
                                                                  ext2FileSystem->blockSize);

                return ((uint32_t *) singlyIndirectBlock)[blockIndex - directBlockMax];
            } else if ((blockIndex > singlyIndirectBlocksMax - 1) && (blockIndex < doublyIndirectBlocksMax)) {
                uint32_t *level1DataBlock = (uint32_t *) (ext2FileSystem->data +
                                                          ext2IndexNode->doublyIndirectBlockPointer *
                                                                  ext2FileSystem->blockSize);
                uint32_t level1Index = (blockIndex - singlyIndirectBlocksMax) / blockPointerNumsInEachBlock;

                uint32_t level2DataBlockPtr = (level1DataBlock)[level1Index];
                uint32_t level2Index = (blockIndex - singlyIndirectBlocksMax) % blockPointerNumsInEachBlock;

                return ((uint32_t *) (ext2FileSystem->data +
                                      level2DataBlockPtr * ext2FileSystem->blockSize))[level2Index];
            } else if ((blockIndex > doublyIndirectBlocksMax - 1) && (blockIndex < triplyIndirectBlocksMax)) {
                // TODO:
                return 0;
            } else {
                // over,
                return 0;
            }
    }
}

void ext2_read_direct_data_block(Ext2FileSystem *ext2FileSystem, Ext2IndexNode *ext2IndexNode, char *buf,
                                 uint32_t blockIndex) {
    uint32_t dataBlock = ext2_get_data_block(ext2FileSystem, ext2IndexNode, blockIndex);

    for (uint32_t i = 0; i < ext2FileSystem->blockSize; i++) {
        buf[blockIndex * ext2FileSystem->blockSize + i] = ((char *) (ext2FileSystem->data +
                                                                     dataBlock * ext2FileSystem->blockSize))[i];
    }
}

uint32_t ext2_fs_default_read(Ext2FileSystem *ext2FileSystem, Ext2IndexNode *ext2IndexNode, char *buf, uint32_t count) {
    uint32_t fileSize = ext2IndexNode->sizeUpper32Bits << 32 | ext2IndexNode->sizeLower32Bits;

    uint32_t blockNeed = fileSize / ext2FileSystem->blockSize;

    if (fileSize > count) {
        // just read count bytes.
        blockNeed = count / ext2FileSystem->blockSize;
    } else {
        count = fileSize;
    }

    LogInfo("[Ext2]: need %d blocks, read %d bytes.\n", blockNeed + 1, count);

    uint32_t restBytes = count - blockNeed * ext2FileSystem->blockSize;

    if (blockNeed == 0) {
        for (uint32_t i = 0; i < restBytes; i++) {
            buf[i] = ((char *) (ext2FileSystem->data +
                                ext2IndexNode->directBlockPointer0 * ext2FileSystem->blockSize))[i];
        }
        return count;
    } else {
        for (uint32_t i = 0; i < blockNeed; i++) {
            ext2_read_direct_data_block(ext2FileSystem, ext2IndexNode, buf, i);
        }

        for (uint32_t i = 0; i < restBytes; i++) {
            buf[blockNeed * ext2FileSystem->blockSize + i] = ((char *) (ext2FileSystem->data +
                                                                        ext2_get_data_block(ext2FileSystem,
                                                                                            ext2IndexNode, blockNeed) *
                                                                                ext2FileSystem->blockSize))[i];
        }
        return count;
    }
}

Ext2FileSystem *ext2_create() {
    Ext2FileSystem *ext2FileSystem = (Ext2FileSystem *) kernelHeap.operations.alloc(&kernelHeap,
                                                                                    sizeof(Ext2FileSystem));
    ext2FileSystem->operations.mount = ext2_fs_default_mount;
    ext2FileSystem->operations.read = ext2_fs_default_read;
    return ext2FileSystem;
}
