//
// Created by XingfengYang & ChengyuZhao on 2020/7/30.
//

#include <hash.h>
#include <log.h>
#include <string.h>
#include <vfs_dentry.h>
#include <vfs_inode.h>
#include <vfs_super_block.h>

uint64_t vfs_directory_entry_default_hash(DirectoryEntry *directoryEntry) {
  return adler32(directoryEntry->fileName, strlen(directoryEntry->fileName));
}

char *vfs_directory_entry_default_get_name(DirectoryEntry *directoryEntry) {
  // todo
  return "";
}

KernelStatus vfs_directory_entry_default_delete(DirectoryEntry *directory) {
  if (directory->indexNode->type == INDEX_NODE_FILE) {
    directory->superBlock->operations->destroyDirectoryEntry(directory->superBlock, directory);
  } else {
  }
  // todo
  return OK;
}

KernelStatus vfs_directory_entry_default_release(DirectoryEntry *directory) {
  // todo
  return OK;
}

KernelStatus vfs_directory_entry_default_init(DirectoryEntry *directory, DirectoryEntry *parent, IndexNode *inode) {
  // todo
  return OK;
}
