//
// Created by XingfengYang on 2020/7/23.
//
#include <elf.h>
#include <type.h>
#define ModuleName(name)
#define ModuleAuthor(author)
#define ModuleDescription(description)
#define ModuleInit(func)
#define ModuleExit(func)

KernelStatus init(){
  return OK;
}

KernelStatus exit(){
  return OK;
}

ModuleName("elf")
ModuleAuthor("neo")
ModuleDescription(load module)
ModuleInit(init);
ModuleExit(exit);