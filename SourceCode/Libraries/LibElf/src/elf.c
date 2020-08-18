//
// Created by XingfengYang on 2020/8/17.
//

#include <elf.h>
#include <log.h>

void elf_default_parse(Elf *elf) {
  // because we are in 32 bits mode, so the header is 54 byte
  elf->fileHeader = *(ElfFileHeader *)(elf->data);
  if (elf->fileHeader.magic[0] != 0x7E || elf->fileHeader.magic[1] != 0x45 || elf->fileHeader.magic[2] != 0x4c ||
      elf->fileHeader.magic[3] != 0x46) {
    LogError("[Elf]: not an elf file.\n");
    return ERROR;
  }
}

KernelStatus elf_init(Elf *elf, char *data) {
  elf->operations.parse = elf_default_parse;
  if (data[0] == 0x7E && data[1] == 0x45 && data[2] == 0x4c && data[3] == 0x46) {
    elf->data = data;
    return OK;
  }
  return ERROR;
}
