//
// Created by XingfengYang on 2020/7/7.
//

#include <mailbox.h>
#include <stdbool.h>
#include <stdlib.h>

volatile uint32_t __attribute__((aligned(16))) mailbox[36];

struct mbox_registers {
  const volatile uint32_t read_0; // 0x00         Read data from VC to ARM
  uint32_t unused[3];             // 0x04-0x0F
  volatile uint32_t peek_0;       // 0x10
  volatile uint32_t sender_0;     // 0x14
  volatile uint32_t status_0;     // 0x18         Status of VC to ARM
  volatile uint32_t config0;      // 0x1C
  volatile uint32_t write_1;      // 0x20         Write data from ARM to VC
  uint32_t unused_2[3];           // 0x24-0x2F
  volatile uint32_t peek_1;       // 0x30
  volatile uint32_t sender_1;     // 0x34
  volatile uint32_t status_1;     // 0x38         Status of ARM to VC
  volatile uint32_t config_1;     // 0x3C
} __attribute__((__packed__, aligned(4)));

uint32_t mailbox_call(uint8_t channel, uint32_t mailbox) {
  mailbox_write(channel, mailbox);
  uint32_t data = mailbox_read(channel);
  return data;
}

uint32_t mailbox_read(uint8_t channel) {
  // Loop until we receive something from the requested channel
  for (;;) {
    while ((*(uint32_t *)(MAIL0_STATUS)&MBOX_EMPTY) != 0) {
      // Wait for data
    }
    // Read the data
    uint32_t data = *(uint32_t *)(MAIL0_READ);
    uint32_t readChannel = data & 0xF;
    data >>= 4;
    // Return it straight away if it's for the requested channel
    if (readChannel == channel) {
      return data;
    }
  }
}

void mailbox_write(uint8_t channel, uint32_t data) {
  while ((*(uint32_t *)(MAIL0_STATUS)&MBOX_FULL) != 0) {
    // Wait for data
  }
  // Write the value to the requested channel
  *(uint32_t *)(MAIL0_WRITE) = ((data & ~0xF) | channel);
}

void mailboxSetPropertyGetFirmwareRevision(PropertyGetFirmwareRevision property) {}

void mailboxSetPropertyGetBoardModel(PropertyGetBoardModel property) {}

void mailboxSetPropertyGetBoardRevision(PropertyGetBoardRevision property) {}

void mailboxSetPropertyGetBoardMacAddress(PropertyGetBoardMacAddress property) {}

void mailboxSetPropertyGetBoardSerial(PropertyGetBoardSerial property) {}

void mailboxSetPropertyGetArmMemory(PropertyGetArmMemory property) {}

void mailboxSetPropertyGetVideoCoreMemory(PropertyGetVideoCoreMemory property) {}

void mailboxSetPropertyGetClocks(PropertyGetClocks property) {}

void mailboxSetPropertyGetCommandLine(PropertyGetCommandLine property) {}

void mailboxSetPropertyGetDMAChannels(PropertyGetDMAChannels property) {}

void mailboxSetPropertyGetPowerState(PropertyGetPowerState property) {}

void mailboxSetPropertyGetTiming(PropertyGetTiming property) {}

void mailboxSetPropertySetPowerState(PropertySetPowerState property) {}

void mailboxSetPropertyGetClockState(PropertyGetClockState property) {}

void mailboxSetPropertySetClockState(PropertySetClockState property) {}

void mailboxSetPropertyGetClockRate(PropertyGetClockRate property) {}

void mailboxSetPropertySetClockRate(PropertySetClockRate property) {}

void mailboxSetPropertyGetMaxClockRate(PropertyGetMaxClockRate property) {}

void mailboxSetPropertyGetMinClockRate(PropertyGetMinClockRate property) {}

void mailboxSetPropertyGetTurbo(PropertyGetTurbo property) {}

void mailboxSetPropertySetTurbo(PropertySetTurbo property) {}

void mailboxSetPropertyGetVoltage(PropertyGetVoltage property) {}

void mailboxSetPropertySetVoltage(PropertySetVoltage property) {}

void mailboxSetPropertyGetMaxVoltage(PropertyGetMaxVoltage property) {}

void mailboxSetPropertyGetMinVoltage(PropertyGetMinVoltage property) {}

void mailboxSetPropertyGetTemperature(PropertyGetTemperature property) {}

void mailboxSetPropertyGetMaxTemperature(PropertyGetMaxTemperature property) {}

void mailboxSetPropertyAllocateMemory(PropertyAllocateMemory property) {}

void mailboxSetPropertyLockMemory(PropertyLockMemory property) {}

void mailboxSetPropertyUnLockMemory(PropertyUnLockMemory property) {}

void mailboxSetPropertyReleaseMemory(PropertyReleaseMemory property) {}

void mailboxSetPropertyExecuteCode(PropertyExecuteCode property) {}

void mailboxSetPropertyGetDispmanxResourceMemHandle(PropertyGetDispmanxResourceMemHandle property) {}

void mailboxSetPropertyGetEDIDBlock(PropertyGetEDIDBlock property) {}

void mailboxSetPropertyAllocateBuffer(PropertyAllocateBuffer property) {}

void mailboxSetPropertyReleaseBuffer(PropertyReleaseBuffer property) {}

void mailboxSetPropertyBlankScreen(PropertyBlankScreen property) {}

void mailboxSetPropertyGetPhysicalDisplayWH(PropertyGetPhysicalDisplayWH property) {}

void mailboxSetPropertyTestPhysicalDisplayWH(PropertyTestPhysicalDisplayWH property) {}

void mailboxSetPropertySetPhysicalDisplayWH(PropertySetPhysicalDisplayWH property) {}

void mailboxSetPropertyGetVirtualBufferWH(PropertyGetVirtualBufferWH property) {}

void mailboxSetPropertyTestVirtualBufferWH(PropertyTestVirtualBufferWH property) {}

void mailboxSetPropertySetVirtualBufferWH(PropertySetVirtualBufferWH property) {}

void mailboxSetPropertyGetDepth(PropertyGetDepth property) {}

void mailboxSetPropertyTestDepth(PropertyTestDepth property) {}

void mailboxSetPropertySetDepth(PropertySetDepth property) {}

void mailboxSetPropertyGetPixelOrder(PropertyGetPixelOrder property) {}

void mailboxSetPropertyTestPixelOrder(PropertyTestPixelOrder property) {}

void mailboxSetPropertySetPixelOrder(PropertySetPixelOrder property) {}

void mailboxSetPropertyGetAlphaMode(PropertyGetAlphaMode property) {}

void mailboxSetPropertyTestAlphaMode(PropertyTestAlphaMode property) {}

void mailboxSetPropertySetAlphaMode(PropertySetAlphaMode property) {}

void mailboxSetPropertyGetPitch(PropertyGetPitch property) {}

void mailboxSetPropertyGetVirtualOffset(PropertyGetVirtualOffset property) {}

void mailboxSetPropertyTestVirtualOffset(PropertyTestVirtualOffset property) {}

void mailboxSetPropertySetVirtualOffset(PropertySetVirtualOffset property) {}

void mailboxSetPropertyGetOverscan(PropertyGetOverscan property) {}

void mailboxSetPropertyTestOverscan(PropertyTestOverscan property) {}

void mailboxSetPropertySetOverscan(PropertySetOverscan property) {}

void mailboxSetPropertyGetPalette(PropertyGetPalette property) {}

void mailboxSetPropertyTestPalette(PropertyTestPalette property) {}

void mailboxSetPropertySetPalette(PropertySetPalette property) {}

void mailboxSetPropertySetCursorInfo(PropertySetCursorInfo property) {}

void mailboxSetPropertySetCursorState(PropertySetCursorState property) {}
