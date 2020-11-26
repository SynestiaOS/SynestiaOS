//
// Created by XingfengYang on 2020/8/7.
//

#ifndef __KERNEL_FS_EXT2_H__
#define __KERNEL_FS_EXT2_H__

#include "kernel/type.hpp"
#include "kernel/vfs_super_block.hpp"
#include "libc/stdint.hpp"

typedef enum Ext2FileSystemStates {
    FILE_SYSTEM_CLEAN = 1,
    FILE_SYSTEM_ERROR = 2,
} Ext2FileSystemStates;

typedef enum Ext2ErrorHandlingMethods {
    ERROE_HANDLING_IGNORE = 1,
    ERROE_HANDLING_REMOUNT_AS_RO = 2,
    ERROE_HANDLING_KERNEL_PANIC = 3,
} Ext2ErrorHandlingMethods;

typedef enum Ext2CreatorOperatingSystemIDs {
    CREATOR_OS_LINUX = 0,
    CREATOR_OS_GNU_HURD = 1,
    CREATOR_OS_MASIX = 2,
    CREATOR_OS_FREEBSD = 3,
    CREATOR_OS_OTHERS = 4,
} Ext2CreatorOperatingSystemIDs;

typedef struct Ext2SuperBlock {
    uint32_t indexNodeNums;                // Total number of inodes in file system
    uint32_t blockNums;                    // Total number of blocks in file system
    uint32_t blockReservedForSuperuserNums;// Number of blocks reserved for superuser (see offset 80)
    uint32_t unallocatedBlockNums;         // Total number of unallocated blocks
    uint32_t unallocatedIndexNodeNums;     // Total number of unallocated inodes
    uint32_t blockContainingSuperblockNums;// Block number of the block containing the superblock
    uint32_t log2BlockSizeSub10;           // log2 (block size) - 10. (In other words, the number to shift 1,024 to the left by to
    // obtain the block size)
    uint32_t log2FragmentSizeSub10;// log2 (fragment size) - 10. (In other words, the number to shift 1,024 to the left
    // by to obtain the fragment size)
    uint32_t eachBlockGroupBlockNums;    // Number of blocks in each block group
    uint32_t eachBlockGroupFragmentNums; // Number of fragments in each block group
    uint32_t eachBlockGroupIndexNodeNums;// Number of inodes in each block group
    uint32_t lastMountTime;              // Last mount time (in POSIX time)
    uint32_t lastWrittenTime;            // Last written time (in POSIX time)
    uint16_t numberOfTimes;              // Number of times the volume has been mounted since its last consistency check (fsck)
    uint16_t numberOfMounts;             // Number of mounts allowed before a consistency check (fsck) must be done
    uint16_t signature;                  // Ext2 signature (0xef53), used to help confirm the presence of Ext2 on a volume
    uint16_t state;                      // File system state (see below)
    uint16_t errorHandlingMethods;       // What to do when an error is detected (see below)
    uint16_t minorPortionOfVersion;      // Minor portion of version (combine with Major portion below to construct full
    // version field)
    uint32_t lastConsistencyCheckTime;              // POSIX time of last consistency check (fsck)
    uint32_t intervalBetweenForcedConsistencyChecks;// Interval (in POSIX time) between forced consistency checks (fsck)
    uint32_t operatingSystemID;                     // Operating system ID from which the filesystem on this volume was created (see below)
    uint32_t majorPortionOfVersion;                 // Major portion of version (combine with Minor portion above to construct full
    // version field)
    uint16_t userId;                // User ID that can use reserved blocks
    uint16_t groupId;               // Group ID that can use reserved blocks
    uint32_t firstIndexNode;        // First non-reserved inode in file system. (In versions < 1.0, this is fixed as 11)
    uint16_t indexNodeStructureSize;// Size of each inode structure in bytes. (In versions < 1.0, this is fixed as 128)
    uint16_t blockGroups;           // Block group that this superblock is part of (if backup copy)

    /**
   * Optional features present (features that are not required to read or write, but usually
   * result in a performance increase. see below)
   *
   * 0x0001	Preallocate some number of (contiguous?) blocks (see byte 205 in the superblock) to a directory when
   * creating a new one (to reduce fragmentation?) 0x0002	AFS server inodes exist 0x0004	File system has a
   * journal (Ext3) 0x0008	Inodes have extended attributes 0x0010	File system can resize itself for larger
   * partitions 0x0020	Directories use hash index
   */
    int32_t optionalFeatures;

    /**
   * Required features present (features that are required to be supported to read or write.
   * see below)
   *
   * 0x0001	Compression is used
   * 0x0002	Directory entries contain a type field
   * 0x0004	File system needs to replay its journal
   * 0x0008	File system uses a journal device
   */
    uint32_t requiredFeatures;
    uint32_t notSupportedFeatures;          // Features that if not supported, the volume must be mounted read-only see below)
    uint32_t fileSystemID[4];               // File system ID (what is output by blkid)
    uint8_t volumaName[16];                 // Volume name (C-style string: characters terminated by a 0 byte)
    uint8_t lastMountPath[64];              // Path volume was last mounted to (C-style string: characters terminated by a 0 byte)
    uint32_t compressionAlgorithms;         // Compression algorithms used (see Required features above)
    uint8_t preallocateFilesBlockNums;      // Number of blocks to preallocate for files
    uint8_t preallocateDirectoriesBlockNums;// Number of blocks to preallocate for directories
    uint16_t unused;                        // (Unused)
    uint32_t journalID[4];                  // Journal ID (same style as the File system ID above)
    uint32_t journalIndexNode;              // Journal inode
    uint32_t journalDevice;                 // Journal device
    uint32_t orphanIndexNodeListHead;       // Head of orphan inode list
} Ext2SuperBlock;

typedef struct Ext2BlockGroupDescriptor {
    uint32_t blockUsageBitMapBlock;    // Block address of block usage bitmap
    uint32_t indexNodeUsageBitMapBlock;// Block address of inode usage bitmap
    uint32_t indexNodeTableBlockBlock; // Starting block address of inode table
    uint16_t unallocatedBlocksNums;    // Number of unallocated blocks in group
    uint16_t unallocatedIndexNodeNums; // Number of unallocated inodes in group
    uint16_t directorirsNum;           // Number of directories in group
} Ext2BlockGroupDescriptor;

typedef enum Ext2IndexNodeType {                   // top 16 bits
    EXT2_INDEX_NODE_TYPE_FIFO = 0x1000,            //	FIFO
    EXT2_INDEX_NODE_TYPE_CHARACTER_DEVIDE = 0x2000,//	Character device
    EXT2_INDEX_NODE_TYPE_DIRECTORY = 0x4000,       //	Directory
    EXT2_INDEX_NODE_TYPE_BLOCK_DEVICE = 0x6000,    //	Block device
    EXT2_INDEX_NODE_TYPE_REGULAR_FILE = 0x8000,    //	Regular file
    EXT2_INDEX_NODE_TYPE_SYMBOLIC_LINK = 0xA000,   //	Symbolic link
    EXT2_INDEX_NODE_TYPE_UNIX_SOCKET = 0xC000,     //	Unix socket
} Ext2IndexNodeType;

typedef enum Ext2IndexNodePermission {    // bottom 12 bits
    EXT2_INDEX_NODE_OTHER_EXECUTE = 0x001,//	00001	Other—execute permission
    EXT2_INDEX_NODE_OTHER_WRITE = 0x002,  //	00002	Other—write permission
    EXT2_INDEX_NODE_OTHER_READ = 0x004,   //	00004	Other—read permission
    EXT2_INDEX_NODE_GROUP_EXECUTE = 0x008,//	00010	Group—execute permission
    EXT2_INDEX_NODE_GROUP_WRITE = 0x010,  //	00020	Group—write permission
    EXT2_INDEX_NODE_GROUP_READ = 0x020,   //	00040	Group—read permission
    EXT2_INDEX_NODE_USER_EXECUTE = 0x040, //	00100	User—execute permission
    EXT2_INDEX_NODE_USER_WRITE = 0x080,   //	00200	User—write permission
    EXT2_INDEX_NODE_USER_READ = 0x100,    //	00400	User—read permission
    EXT2_INDEX_NODE_STICKY_BIT = 0x200,   //	01000	Sticky Bit
    EXT2_INDEX_NODE_SET_GROUP_ID = 0x400, //	02000	Set group ID
    EXT2_INDEX_NODE_SET_USER_ID = 0x800,  //	04000	Set user ID
} Ext2IndexNodePermission;

typedef struct Ext2IndexNode {
    uint16_t typeAndPermissions; // Type and Permissions (see below)
    uint16_t userId;             // User ID
    uint32_t sizeLower32Bits;    // Lower 32 bits of size in bytes
    uint32_t lastAccessTime;     // Last Access Time (in POSIX time)
    uint32_t createTime;         // Creation Time (in POSIX time)
    uint32_t lastModficationTime;// Last Modification time (in POSIX time)
    uint32_t deleteTime;         // Deletion time (in POSIX time)
    uint16_t groupId;            // Group ID
    uint16_t hardLinksCount;     // Count of hard links (directory entries) to this inode. When this reaches 0, the data
    // blocks are marked as unallocated.
    uint32_t diskSectorsCount;// Count of disk sectors (not Ext2 blocks) in use by this inode, not counting the actual
    // inode structure nor directory entries linking to the inode.

    /**
   * Flags (see below)
   *
   * 0x00000001	Secure deletion (not used)
   * 0x00000002	Keep a copy of data when deleted (not used)
   * 0x00000004	File compression (not used)
   * 0x00000008	Synchronous updates—new data is written immediately to disk
   * 0x00000010	Immutable file (content cannot be changed)
   * 0x00000020	Append only
   * 0x00000040	File is not included in 'dump' command
   * 0x00000080	Last accessed time should not updated
   * ...	(Reserved)
   * 0x00010000	Hash indexed directory
   * 0x00020000	AFS directory
   * 0x00040000	Journal file data
   */
    uint32_t flags;

    /**
   * Operating System Specific
   *
   * Linux	(reserved)
   * HURD	"translator"?
   * MASIX	(reserved)
   */
    uint32_t operatingSystemSpecificValue1;
    uint32_t directBlockPointer0;       // Direct Block Pointer 0
    uint32_t directBlockPointer1;       // Direct Block Pointer 1
    uint32_t directBlockPointer2;       // Direct Block Pointer 2
    uint32_t directBlockPointer3;       // Direct Block Pointer 3
    uint32_t directBlockPointer4;       // Direct Block Pointer 4
    uint32_t directBlockPointer5;       // Direct Block Pointer 5
    uint32_t directBlockPointer6;       // Direct Block Pointer 6
    uint32_t directBlockPointer7;       // Direct Block Pointer 7
    uint32_t directBlockPointer8;       // Direct Block Pointer 8
    uint32_t directBlockPointer9;       // Direct Block Pointer 9
    uint32_t directBlockPointer10;      // Direct Block Pointer 10
    uint32_t directBlockPointer11;      // Direct Block Pointer 11
    uint32_t singlyIndirectBlockPointer;// Singly Indirect Block Pointer (Points to a block that is a list of block
    // pointers to data)
    uint32_t doublyIndirectBlockPointer;// Doubly Indirect Block Pointer (Points to a block that is a list of block
    // pointers to Singly Indirect Blocks)
    uint32_t triplyIndirectBlockPointer;// Triply Indirect Block Pointer (Points to a block that is a list of block
    // pointers to Doubly Indirect Blocks)
    uint32_t generationNumer;       // Generation number (Primarily used for NFS)
    uint32_t extendedAttributeBlock;// In Ext2 version 0, this field is reserved. In version >= 1, Extended attribute
    // block (File ACL).
    uint32_t sizeUpper32Bits;// In Ext2 version 0, this field is reserved. In version >= 1, Upper 32 bits of file size
    // (if feature bit set) if it's a file, Directory ACL if it's a directory
    uint32_t fragmentBlockAddress;// Block address of fragment

    /**
   * Operating System Specific Value
   *
   * Linux
   * 1	Fragment number
   * 1	Fragment size
   * 2	(reserved)
   * 2	High 16 bits of 32-bit User ID
   * 2	High 16 bits of 32-bit Group ID
   * 4	(reserved)
   *
   * HURD
   * 1	Fragment number
   * 1	Fragment size
   * 2	High 16 bits of 32-bit "Type and Permissions" field
   * 2	High 16 bits of 32-bit User ID
   * 2	High 16 bits of 32-bit Group ID
   * 4	User ID of author (if == 0xFFFFFFFF, the normal User ID will be used)
   *
   * MASIX
   * 1	Fragment number
   * 1	Fragment size
   * X	(reserved)
   */
    uint8_t operatingSystemSpecificValue2[12];
} Ext2IndexNode;

typedef enum Ext2DirectoryEntryType {
    EXT2_DIRECTORY_ENTRY_TYPE_KNOWN = 0,           // Unknown type
    EXT2_DIRECTORY_ENTRY_TYPE_REGULAR_FILE = 1,    // Regular file
    EXT2_DIRECTORY_ENTRY_TYPE_DIRECTORY = 2,       // Directory
    EXT2_DIRECTORY_ENTRY_TYPE_CHARACTER_DEVICE = 3,// Character device
    EXT2_DIRECTORY_ENTRY_TYPE_BLOCK_DEVICE = 4,    // Block device
    EXT2_DIRECTORY_ENTRY_TYPE_FIFO = 5,            // FIFO
    EXT2_DIRECTORY_ENTRY_TYPE_SOCKET = 6,          // Socket
    EXT2_DIRECTORY_ENTRY_TYPE_SYMBOLIC_LINK = 7,   // Symbolic link (soft link)
} Ext2DirectoryEntryType;

typedef struct Ext2DirectoryEntry {
    uint32_t indexNode;      // Inode
    uint16_t sizeOfThisEntry;// Total size of this entry (Including all subfields)
    uint8_t nameLength;      // Name Length least-significant 8 bits
    uint8_t typeIndicator;   // Type indicator (only if the feature bit for "directory entries have file type byte" is set,
    // else this is the most-significant 8 bits of the Name Length)
    uint8_t nameCharacters[];// Name characters
} Ext2DirectoryEntry;

typedef uint32_t Ext2DataBlockBitmap;
typedef uint32_t Ext2IndexNodeBlockBitmap;
typedef uint32_t Ext2DataBlock;
typedef uint32_t Ext2BootBlock;

typedef struct Ext2BlockGroup {
    Ext2SuperBlock *superBlock;
    Ext2BlockGroupDescriptor *blockGroupDescriptor;
    Ext2DataBlockBitmap *dataBlockBitmap;
    Ext2IndexNodeBlockBitmap *indexNodeBitmap;
    Ext2IndexNode *indexNode;
    Ext2DataBlock *dataBlock;
} Ext2BlockGroup;

typedef KernelStatus (*Ext2FileSystemMountOperation)(struct Ext2FileSystem *ext2FileSystem, char *mountName,
                                                     void *data);

typedef uint32_t (*Ext2FileSystemReadOperation)(struct Ext2FileSystem *ext2FileSystem, Ext2IndexNode *indexNode,
                                                char *buf, uint32_t count);

typedef struct Ext2FileSystemOperations {
    Ext2FileSystemMountOperation mount;
    Ext2FileSystemReadOperation read;
} Ext2FileSystemOperations;

typedef struct Ext2FileSystem {
    Ext2SuperBlock *ext2SuperBlock;
    struct SuperBlock superblock;
    Ext2BootBlock *bootBlock;
    Ext2BlockGroup *blockGroups;
    void *data;
    uint32_t blockSize;
    uint32_t blockGroupNums;
    Ext2FileSystemOperations operations;
} Ext2FileSystem;

Ext2FileSystem *ext2_create();

#endif// __KERNEL_FS_EXT2_H__
