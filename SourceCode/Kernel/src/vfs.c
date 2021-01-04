//
// Created by XingfengYang on 2020/7/30.
//

#include "kernel/vfs.h"
#include "arm/register.h"
#include "kernel/ext2.h"
#include "kernel/kheap.h"
#include "kernel/log.h"
#include "kernel/percpu.h"
#include "kernel/vfs_dentry.h"
#include "kernel/vfs_inode.h"
#include "kernel/vfs_super_block.h"
#include "libc/string.h"
#include "raspi2/uart.h"

extern Heap kernelHeap;

SuperBlock *vfs_default_mount(VFS *vfs, const char *name, FileSystemType type, void *data) {
    switch (type) {
        case FILESYSTEM_EXT2: {
            Ext2FileSystem *ext2FileSystem = ext2_create();
            ext2FileSystem->superblock.name = name;
            ext2FileSystem->superblock.type = type;
            ext2FileSystem->superblock.operations.createDirectoryEntry = vfs_super_block_default_create_directory_entry;
            ext2FileSystem->superblock.operations.createIndexNode = vfs_super_block_default_create_index_node;
            ext2FileSystem->superblock.operations.destroyDirectoryEntry = vfs_super_block_default_destroy_dentry;
            ext2FileSystem->superblock.operations.destroyIndexNode = vfs_super_block_default_destroy_inode;
            ext2FileSystem->operations.mount(ext2FileSystem, name, data);

            if (vfs->fileSystems == nullptr) {
                vfs->fileSystems = &ext2FileSystem->superblock;
            } else {
                klist_append(&vfs->fileSystems->node, &ext2FileSystem->superblock.node);
            }
            return &ext2FileSystem->superblock;
        }
    }
}

uint32_t vfs_default_open(VFS *vfs, const char *name, uint32_t mode) {
    PerCpu *perCpu = percpu_get(read_cpuid());
    Thread *currThread = perCpu->currentThread;

    uint32_t len = currThread->memoryStruct.virtualMemory.operations.getUserStrLen(
            &currThread->memoryStruct.virtualMemory, name);

    void *dest = kernelHeap.operations.alloc(&kernelHeap, len + 1);

    char *bufferKernel = (char *) currThread->memoryStruct.virtualMemory.operations.copyToKernel(
            &currThread->memoryStruct.virtualMemory, name, dest, len + 1);

    DirectoryEntry *directoryEntry = vfs->operations.lookup(vfs, dest);
    if (directoryEntry == nullptr) {
        LogError("[VFS]: file '%s' not found.\n", dest);
        return 0;
    }

    kernelHeap.operations.free(&kernelHeap, dest);
    //    atomic_inc(&directoryEntry->indexNode->readCount);

    directoryEntry->indexNode->state = INDEX_NODE_STATE_OPENED;

    return currThread->filesStruct.operations.openFile(&(currThread->filesStruct), directoryEntry);
}

uint32_t vfs_default_close(struct VFS *vfs, uint32_t fd) {
    PerCpu *perCpu = percpu_get(read_cpuid());
    Thread *currThread = perCpu->currentThread;

    ListNode *pNode = currThread->filesStruct.fileDescriptorTable.operations.get(
            &currThread->filesStruct.fileDescriptorTable, fd);
    FileDescriptor *pDescriptor = getNode(pNode, FileDescriptor, node);
    pDescriptor->directoryEntry->indexNode->state = INDEX_NODE_STATE_CLOSED;

    // TODO
    //    kvector_remove_index(&currThread->filesStruct.fileDescriptorTable, fd);
    return 0;
}

uint32_t vfs_default_read(VFS *vfs, uint32_t fd, char *buffer, uint32_t pos, uint32_t count) {
    if (fd == FD_STDIN) {

    } else if (fd == FD_STDOUT) {

    } else if (fd == FD_STDERR) {

    } else {
        PerCpu *perCpu = percpu_get(read_cpuid());
        Thread *currThread = perCpu->currentThread;


        return 0;
    }
}

uint32_t vfs_default_write(VFS *vfs, uint32_t fd, char *buffer, uint32_t pos, uint32_t count) {
    if (fd == FD_STDIN) {

    } else if (fd == FD_STDOUT) {
        uart_print(buffer);
    } else if (fd == FD_STDERR) {

    } else {

        PerCpu *perCpu = percpu_get(read_cpuid());
        Thread *currThread = perCpu->currentThread;
    }
    return 0;
}

uint32_t vfs_kernel_read(VFS *vfs, const char *name, char *buf, uint32_t count) {
    DirectoryEntry *directoryEntry = vfs->operations.lookup(vfs, name);
    if (directoryEntry == nullptr) {
        LogError("[VFS]: file '%s' not found.\n", name);
        return 0;
    }
    switch (directoryEntry->superBlock->type) {
        case FILESYSTEM_EXT2: {
            Ext2FileSystem *ext2FileSystem = getNode(directoryEntry->superBlock, Ext2FileSystem, superblock);
            Ext2IndexNode *ext2Node = (Ext2IndexNode *) directoryEntry->indexNode->indexNodePrivate;
            return ext2FileSystem->operations.read(ext2FileSystem, ext2Node, buf, count);
        }
        default:
            LogError("[VFS]: unsupported file system.\n");
            return 0;
    }
}

char peek(char *src, uint32_t index, uint32_t offset) { return src[index + offset]; }

DirectoryEntry *vfs_default_lookup(VFS *vfs, const char *name) {

    typedef enum PathLookUpState {
        PATH_LOOKUP_START,
        PATH_LOOKUP_DOT,
        PATH_LOOKUP_SLASH,
        PATH_LOOKUP_NAME,
    } PathLookUpState;

    PathLookUpState lookupState = PATH_LOOKUP_START;
    uint32_t bufStart = 0;
    uint32_t index = 0;
    uint32_t length = strlen(name);

    DirectoryEntry *currentDirectory = vfs->fileSystems->rootDirectoryEntry;

    while (index <= length) {
        char currentChr = peek(name, index, 0);
        index++;
        switch (lookupState) {
            case PATH_LOOKUP_START: {
                if (currentChr == '.') {
                    lookupState = PATH_LOOKUP_DOT;
                } else if (currentChr == '/') {
                    lookupState = PATH_LOOKUP_SLASH;// /
                    LogWarn("[LookUp]: root\n");
                    currentDirectory = vfs->fileSystems->rootDirectoryEntry;
                } else {
                    lookupState = PATH_LOOKUP_NAME;// name
                    bufStart = index - 1;
                }
                break;
            }
            case PATH_LOOKUP_DOT: {
                if (currentChr == '/') {
                    lookupState = PATH_LOOKUP_SLASH;// ./
                    LogWarn("[LookUp]: current\n");
                    currentDirectory = currentDirectory;
                } else if (currentChr == '.') {
                    if (peek(name, index, 0) == '/') {
                        lookupState = PATH_LOOKUP_SLASH;// ../
                        LogWarn("[LookUp]: up\n");
                        if (currentDirectory->parent != nullptr) {
                            currentDirectory = currentDirectory->parent;
                        } else {
                            currentDirectory = vfs->fileSystems->rootDirectoryEntry;
                        }
                        index++;
                    } else {
                        // illegal path
                    }
                } else {
                    lookupState = PATH_LOOKUP_NAME;
                }
                break;
            }
            case PATH_LOOKUP_SLASH: {
                if (currentChr == '/') {
                    lookupState = PATH_LOOKUP_SLASH;// //
                    LogWarn("[LookUp]: root\n");
                    currentDirectory = vfs->fileSystems->rootDirectoryEntry;
                } else if (currentChr == '.') {
                    lookupState = PATH_LOOKUP_DOT;
                } else {
                    lookupState = PATH_LOOKUP_NAME;
                    bufStart = index - 1;
                }
                break;
            }
            case PATH_LOOKUP_NAME: {
                if (currentChr == '/') {
                    lookupState = PATH_LOOKUP_SLASH;// name/
                    char path[index - bufStart];
                    for (uint32_t i = 0; i < index - bufStart; i++) {
                        path[i] = name[bufStart + i];
                    }
                    path[index - bufStart - 1] = '\0';
                    LogWarn("[LookUp]: %s \n", path);
                    ListNode *tmpNode = &(currentDirectory->children->list);
                    bool isFound = false;
                    while (tmpNode != nullptr) {
                        DirectoryEntry *tmpDirectoryEntry = getNode(tmpNode, DirectoryEntry, list);
                        LogInfo("[LookUp]: %s \n", tmpDirectoryEntry->fileName);
                        if (strcmp(tmpDirectoryEntry->fileName, path)) {
                            currentDirectory = tmpDirectoryEntry;
                            isFound = true;
                            break;
                        }
                        if (tmpNode->prev != nullptr) {
                            tmpNode = tmpNode->prev;
                        } else {
                            break;
                        }
                    }
                    if (!isFound) {
                        // not found
                        char path[index];
                        for (uint32_t i = 0; i < index; i++) {
                            path[i] = name[i];
                        }
                        path[index] = '\0';
                        LogError("[LookUp]: %s not found.\n", path);
                        return nullptr;
                    }
                } else if (index == length) {
                    lookupState = PATH_LOOKUP_SLASH;// name/
                    char path[index - bufStart];
                    for (uint32_t i = 0; i < index - bufStart; i++) {
                        path[i] = name[bufStart + i];
                    }
                    path[index - bufStart] = '\0';
                    LogWarn("[LookUp]: %s \n", path);
                    ListNode *tmpNode = &(currentDirectory->children->list);
                    bool isFound = false;
                    while (tmpNode != nullptr) {
                        DirectoryEntry *tmpDirectoryEntry = getNode(tmpNode, DirectoryEntry, list);
                        LogInfo("[LookUp]: %s \n", tmpDirectoryEntry->fileName);
                        if (strcmp(tmpDirectoryEntry->fileName, path)) {
                            currentDirectory = tmpDirectoryEntry;
                            isFound = true;
                            break;
                        }
                        if (tmpNode->prev != nullptr) {
                            tmpNode = tmpNode->prev;
                        } else {
                            break;
                        }
                    }
                    if (!isFound) {
                        // not found
                        char path[index];
                        for (uint32_t i = 0; i < index; i++) {
                            path[i] = name[i];
                        }
                        path[index] = '\0';
                        LogError("[LookUp]: %s not found.\n", path);
                        return nullptr;
                    }
                } else {
                    // illegal path
                }
                break;
            }
        }
    }

    return currentDirectory;
}

VFS *vfs_create(VFS *vfs) {
    vfs->fileSystems = nullptr;
    vfs->operations.mount = (VFSOperationMount) vfs_default_mount;
    vfs->operations.open = (VFSOperationOpen) vfs_default_open;
    vfs->operations.close = (VFSOperationClose) vfs_default_close;
    vfs->operations.read = (VFSOperationRead) vfs_default_read;
    vfs->operations.write = (VFSOperationWrite) vfs_default_write;
    vfs->operations.lookup = (VFSOperationLookUp) vfs_default_lookup;
    return vfs;
}
