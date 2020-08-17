//
// Created by XingfengYang on 2020/8/17.
//

#include <elf.h>
#include <log.h>

void elf_default_parse(Elf *elf) {}

KernelStatus elf_init(Elf *elf, char *data) {
  elf->operations.parse = elf_default_parse;
  if (data[0] == 0x7E && data[1] == 0x45 && data[2] == 0x4c && data[3] == 0x46) {
    elf->data = data;
    return OK;
  }
  LogError("[Elf]: not an elf file.\n");
  return ERROR;
}
