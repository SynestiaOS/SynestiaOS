//
// Created by XingfengYang on 2020/8/7.
//

#include <ext2.h>
#include <log.h>
#include <stdint.h>
#include <vfs_dentry.h>
#include <vfs_inode.h>
#include <vfs_super_block.h>
#include <string.h>
#include <kheap.h>

#define EXT2_SIGNATURE 0xef53
#define EXT2_BLOCK_GROUP_DESCRIPTOR_SIZE 32
#define EXT2_INDEX_NODE_STRUCTURE_SIZE 128
#define EXT2_SUPER_BLOCK_OFFSET 1024

void ext2_recursively_fill_superblock(Ext2FileSystem *ext2FileSystem, Ext2IndexNode *ext2IndexNode, SuperBlock *vfsSuperBlock, DirectoryEntry *vfsDirectoryEntry, uint32_t blockSize, void *data, char* name){
  if ((ext2IndexNode->typeAndPermissions & 0xF000) == EXT2_INDEX_NODE_TYPE_DIRECTORY) {
    // create directory vfs inode, and dentry, and fill them
    DirectoryEntry *directoryEntry = vfsSuperBlock->operations.createDirectoryEntry(vfsSuperBlock, name);
    IndexNode *indexNode = vfsSuperBlock->operations.createIndexNode(vfsSuperBlock, directoryEntry);
    directoryEntry->operations.initOperation(directoryEntry, nullptr, indexNode);
    // TODO: fill them

    // inode is a empty directory
    if (ext2IndexNode->hardLinksCount == 2) {
      // just return
      return;
    }

    Ext2DirectoryEntry *dEntry = (Ext2DirectoryEntry *)((uint32_t)data + ext2IndexNode->directBlockPointer0 * blockSize);
    for (uint32_t hardlink = 0; hardlink < ext2IndexNode->hardLinksCount; hardlink++) {
      LogInfo("[Ext2]: dir : %s\n", dEntry->nameCharacters);
      if (strcmp(dEntry->nameCharacters,"..") || strcmp(dEntry->nameCharacters,".")) {
        // ignore
        dEntry = (Ext2DirectoryEntry *)((uint32_t)dEntry + dEntry->sizeOfThisEntry);
        continue;
      }
      // inode is directory , it's means should recursion
      Ext2IndexNode *nextNode = (Ext2IndexNode*)((uint32_t)ext2FileSystem->blockGroups->indexNode + (uint32_t)dEntry->indexNode * EXT2_INDEX_NODE_STRUCTURE_SIZE);
      ext2_recursively_fill_superblock(ext2FileSystem, nextNode, vfsSuperBlock, directoryEntry, blockSize,  data, dEntry->nameCharacters);
      dEntry = (Ext2DirectoryEntry *)((uint32_t)dEntry + dEntry->sizeOfThisEntry);
    }
  } else if ((ext2IndexNode->typeAndPermissions & 0xF000) == EXT2_INDEX_NODE_TYPE_REGULAR_FILE) {
    // create vfs inode, create vfs dentry , and fill them
    DirectoryEntry *directoryEntry = vfsSuperBlock->operations.createDirectoryEntry(vfsSuperBlock, name);
    IndexNode *indexNode = vfsSuperBlock->operations.createIndexNode(vfsSuperBlock, directoryEntry);
    directoryEntry->operations.initOperation(directoryEntry, nullptr, indexNode);
    // TODO: fill them

    return;
  }
}

KernelStatus ext2_fs_default_mount(Ext2FileSystem *ext2FileSystem, struct SuperBlock *vfsSuperBlock, char *mountName, void *data) {
  Ext2SuperBlock *ext2SuperBlock = (Ext2SuperBlock *)((uint32_t)data + EXT2_SUPER_BLOCK_OFFSET);

  if (ext2SuperBlock->signature != EXT2_SIGNATURE) {
    LogError("[Ext2]: not a ext2 file system.\n");
    return ERROR;
  }

  // make root
  DirectoryEntry *rootDirectoryEntry = vfsSuperBlock->operations.createDirectoryEntry(vfsSuperBlock, "root");
  IndexNode *rootIndexNode = vfsSuperBlock->operations.createIndexNode(vfsSuperBlock, rootDirectoryEntry);
  rootDirectoryEntry->operations.initOperation(rootDirectoryEntry, nullptr, rootIndexNode);

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

  // Block size
  uint32_t blockSize = 1 << (ext2SuperBlock->log2BlockSizeSub10 + 10);

  uint32_t blockNumsInEachBlockGroup = (blockSize * 8);

  // Block Group Descriptor numbers , other words, this is super block numbers or block group number
  uint32_t blockGroupNums = ext2SuperBlock->blockNums / blockNumsInEachBlockGroup +
          (ext2SuperBlock->blockNums % blockNumsInEachBlockGroup) > 0 ? 1 : 0;

  uint32_t blockGroupDescriptorNumsInEachBlock = blockSize / EXT2_BLOCK_GROUP_DESCRIPTOR_SIZE;
  // block nums for all block group descriptor
  uint32_t blockForBlockGroupDescriptor = blockGroupNums / blockGroupDescriptorNumsInEachBlock;
  uint32_t blockForBlockGroupDescriptorMod = (blockGroupNums % blockGroupDescriptorNumsInEachBlock) > 0 ? 1 : 0;
  blockForBlockGroupDescriptor += blockForBlockGroupDescriptorMod;
  LogInfo("[Ext2]: block group descriptor blocks: %d .\n", blockForBlockGroupDescriptor);

  uint32_t indexNodeNumsInEachBlock = blockSize / EXT2_INDEX_NODE_STRUCTURE_SIZE;
  uint32_t blockForIndexNodeTable = ext2SuperBlock->indexNodeNums / indexNodeNumsInEachBlock;
  uint32_t blockForIndexNodeTableMod =
      ((ext2SuperBlock->indexNodeNums % indexNodeNumsInEachBlock) > 0) ? 1 : 0;
  blockForIndexNodeTable += blockForIndexNodeTableMod;
  LogInfo("[Ext2]: index node table  blocks: %d .\n", blockForIndexNodeTable);

  Ext2BlockGroup* blockGroup  = (Ext2BlockGroup*)kheap_alloc(sizeof(Ext2BlockGroup));
  blockGroup->superBlock = (Ext2SuperBlock *)((uint32_t)data + EXT2_SUPER_BLOCK_OFFSET);
  blockGroup->blockGroupDescriptor = (Ext2BlockGroupDescriptor *)((uint32_t)blockGroup->superBlock + blockSize);
  blockGroup->dataBlockBitmap =
      (Ext2DataBlockBitmap *)((uint32_t)data + blockGroup->blockGroupDescriptor->blockUsageBitMapBlock * blockSize);
  blockGroup->indexNodeBitmap =
      (Ext2IndexNodeBlockBitmap *)((uint32_t)data +
                                   blockGroup->blockGroupDescriptor->indexNodeUsageBitMapBlock * blockSize);
  blockGroup->indexNode =
      (Ext2IndexNode *)((uint32_t)data +
                                     blockGroup->blockGroupDescriptor->indexNodeTableBlockBlock * blockSize);
  blockGroup->dataBlock =
      (Ext2DataBlock *)((uint32_t)blockGroup->indexNode + blockForIndexNodeTable * blockSize);

  ext2FileSystem->blockGroups = blockGroup;

  // assume that the root directory is in second inode, because the first inode is
  Ext2IndexNode *root =
      (Ext2IndexNode *)((uint32_t)blockGroup->indexNode + EXT2_INDEX_NODE_STRUCTURE_SIZE);
  Ext2DirectoryEntry *ext2RootDirectoryEntry =
      (Ext2DirectoryEntry *)((uint32_t)data + root->directBlockPointer0 * blockSize);

//   LogInfo("[root]: dir : %s\n", ext2RootDirectoryEntry->nameCharacters);
//   for (uint32_t hardlink = 0; hardlink < root->hardLinksCount; hardlink++) {
//     ext2RootDirectoryEntry =
//         (Ext2DirectoryEntry *)((uint32_t)ext2RootDirectoryEntry + ext2RootDirectoryEntry->sizeOfThisEntry);
//     LogInfo("[root]: dir : %s\n", ext2RootDirectoryEntry->nameCharacters);
//   }

  // let's recursion
  ext2_recursively_fill_superblock(ext2FileSystem, root, vfsSuperBlock, rootDirectoryEntry, blockSize, data,"initrd");

  LogInfo("[Ext2]: mounted.\n");
}

KernelStatus ext2_init(Ext2FileSystem *ext2FileSystem) { ext2FileSystem->operations.mount = ext2_fs_default_mount; }
