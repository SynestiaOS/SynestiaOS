//
// Created by XingfengYang on 2020/8/7.
//

#ifndef __KERNEL_FS_EXT2_H__
#define __KERNEL_FS_EXT2_H__
#include <stdint.h>

typedef enum FileSystemStates {
  FILE_SYSTEM_CLEAN = 1,
  FILE_SYSTEM_ERROR = 2,
} FileSystemStates;

typedef enum ErrorHandlingMethods {
  ERROE_HANDLING_IGNORE = 1,
  ERROE_HANDLING_REMOUNT_AS_RO = 2,
  ERROE_HANDLING_KERNEL_PANIC = 3,
} ErrorHandlingMethods;

typedef enum CreatorOperatingSystemIDs {
  CREATOR_OS_LINUX = 0,
  CREATOR_OS_GNU_HURD = 1,
  CREATOR_OS_MASIX = 2,
  CREATOR_OS_FREEBSD = 3,
  CREATOR_OS_OTHERS = 4,
} CreatorOperatingSystemIDs;

typedef struct Ext2SuperBlock {
  uint32_t indexNodeNums;                 // Total number of inodes in file system
  uint32_t blockNums;                     // Total number of blocks in file system
  uint32_t blockReservedForSuperuserNums; // Number of blocks reserved for superuser (see offset 80)
  uint32_t unallocatedBlockNums;          // Total number of unallocated blocks
  uint32_t unallocatedIndexNodeNums;      // Total number of unallocated inodes
  uint32_t blockContainingSuperblockNums; // Block number of the block containing the superblock
  uint32_t log2BlockSizeSub10; // log2 (block size) - 10. (In other words, the number to shift 1,024 to the left by to
                               // obtain the block size)
  uint32_t log2FragmentSizeSub10;   // log2 (fragment size) - 10. (In other words, the number to shift 1,024 to the left
                                    // by to obtain the fragment size)
  uint32_t eachBlockGroupBlockNums; // Number of blocks in each block group
  uint32_t eachBlockGroupFragmentNums;  // Number of fragments in each block group
  uint32_t eachBlockGroupIndexNodeNums; // Number of inodes in each block group
  uint32_t lastMountTime;               // Last mount time (in POSIX time)
  uint32_t lastWrittenTime;             // Last written time (in POSIX time)
  uint16_t numberOfTimes;         // Number of times the volume has been mounted since its last consistency check (fsck)
  uint16_t numberOfMounts;        // Number of mounts allowed before a consistency check (fsck) must be done
  uint16_t signature;             // Ext2 signature (0xef53), used to help confirm the presence of Ext2 on a volume
  uint16_t state;                 // File system state (see below)
  uint16_t errorHandlingMethods;  // What to do when an error is detected (see below)
  uint16_t minorPortionOfVersion; // Minor portion of version (combine with Major portion below to construct full
                                  // version field)
  uint32_t lastConsistencyCheckTime;               // POSIX time of last consistency check (fsck)
  uint32_t intervalBetweenForcedConsistencyChecks; // Interval (in POSIX time) between forced consistency checks (fsck)
  uint32_t operatingSystemID; // Operating system ID from which the filesystem on this volume was created (see below)
  uint32_t majorPortionOfVersion;  // Major portion of version (combine with Minor portion above to construct full
                                   // version field)
  uint16_t userId;                 // User ID that can use reserved blocks
  uint16_t groupId;                // Group ID that can use reserved blocks
  uint32_t firstIndexNode;         // First non-reserved inode in file system. (In versions < 1.0, this is fixed as 11)
  uint16_t indexNodeStructureSize; // Size of each inode structure in bytes. (In versions < 1.0, this is fixed as 128)
  uint16_t blockGrousp;            // Block group that this superblock is part of (if backup copy)

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
  uint32_t notSupportedFeatures;  // Features that if not supported, the volume must be mounted read-only see below)
  uint32_t fileSystemID[4];       // File system ID (what is output by blkid)
  uint8_t volumaName[16];         // Volume name (C-style string: characters terminated by a 0 byte)
  uint8_t lastMountPath[64];      // Path volume was last mounted to (C-style string: characters terminated by a 0 byte)
  uint32_t compressionAlgorithms; // Compression algorithms used (see Required features above)
  uint8_t preallocateFilesBlockNums;       // Number of blocks to preallocate for files
  uint8_t preallocateDirectoriesBlockNums; // Number of blocks to preallocate for directories
  uint16_t unused;                         // (Unused)
  uint32_t journalID[4];                   // Journal ID (same style as the File system ID above)
  uint32_t journalIndexNode;               // Journal inode
  uint32_t journalDevice;                  // Journal device
  uint32_t orphanIndexNodeListHead;        // Head of orphan inode list
} Ext2SuperBlock;

typedef struct BlockGroupDescriptor {
  uint32_t blockUsageBitMapAddress;     // Block address of block usage bitmap
  uint32_t indexNodeUsageBitMapAddress; // Block address of inode usage bitmap
  uint32_t indexNodeTableBlockAddress;  // Starting block address of inode table
  uint16_t unallocatedBlocksNums;       // Number of unallocated blocks in group
  uint16_t unallocatedIndexNodeNums;    // Number of unallocated inodes in group
  uint16_t directorirsNum;              // Number of directories in group
} BlockGroupDescriptor;

#endif // __KERNEL_FS_EXT2_H__