//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __BOARD_RASP_MAILBOX_H__
#define __BOARD_RASP_MAILBOX_H__

#include <raspi.h>
#include <stdbool.h>
#include <stdint.h>

extern volatile uint32_t __attribute__((aligned(16))) mailbox[36];
#define VIDEOCORE_MBOX PERIPHERAL_BASE + MAILBOX_OFFSET

#define MAILBOX_CHANNEL_POWER_MANAGEMENT 0
#define MAILBOX_CHANNEL_FRAMEBUFFER 1
#define MAILBOX_CHANNEL_VIRTUAL_UART 2
#define MAILBOX_CHANNEL_VCHIQ 3
#define MAILBOX_CHANNEL_LEDS 4
#define MAILBOX_CHANNEL_BUTTONS 5
#define MAILBOX_CHANNEL_TOUCH_SCREEN 6
#define MAILBOX_CHANNEL_COUNT 7
#define MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC 8
#define MAILBOX_CHANNEL_PROPERTY_TAGS_VC_TO_ARM 9

/**
 * The read register for mailbox 0 at offset (the Linux source mentions something of "and the next 4 words", but I've
 * found it sufficient to read only from this address) 0-3(channel):	The mailbox channel number from which the data
 * originated 4-31(data):	The 28 bits of data sent to the CPU
 */
#define MAIL0_READ ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x0))

// Read from the mailbox without removing data from it.
#define MAIL0_PEAK ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x10))

// Sender ID (bottom 2 bits only)
#define MAIL0_SENDER ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x14))

/**
 * The status register for mailbox 0
 * 0-29:	N/A	Not documented here. Unused?
 * 30:	MAIL_EMPTY	Set if the mailbox is empty, and thus no more data is available to be read from it.
 * 31:	MAIL_FULL	Set if the mailbox is full, and thus no more data can be written to it.
 */
#define MAIL0_STATUS ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x18))

// The configuration register for mailbox 0
#define MAIL0_CONFIG ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x1C))

/**
 *  The write register for mailbox 0 (this is actually the read register for mailbox 1).
 *  0-3:	channel	The mailbox channel number to which the data is to be sent
 *  4-31:	data	The 28 bits of data to be sent to the destination
 */
#define MAIL0_WRITE ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x20))

#define MBOX_REQUEST 0
#define MBOX_RESPONSE 0x80000000
#define MBOX_FULL 1 << 31
#define MBOX_EMPTY 1 << 30

/**
 * all property interface can be found at below link:
 * https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
 */
#define PROPERTY_TAG_END 0x00000000

#define PROPERTY_TAG_GET_FRIMWARE_REVISION 0x00000001
typedef struct PropertyGetFirmwareRevision {
  uint32_t tag;
  uint32_t firmwareRevision;
} PropertyGetFirmwareRevision;

#define PROPERTY_TAG_GET_BOARD_MODEL 0x00010001
typedef struct PropertyGetBoardModel {
  uint32_t tag;
  uint32_t boardModel;
} PropertyGetBoardModel;

#define PROPERTY_TAG_GET_BOARD_REVISION 0x00010002
typedef struct PropertyGetBoardRevision {
  uint32_t tag;
  uint32_t boardRevision;
} PropertyGetBoardRevision;

#define PROPERTY_TAG_GET_BOARD_MAC_ADDRESS 0x00010003
typedef struct PropertyGetBoardMacAddress {
  uint32_t tag;
  uint8_t address1;
  uint8_t address2;
  uint8_t address3;
  uint8_t address4;
  uint8_t address5;
  uint8_t address6;
} PropertyGetBoardMacAddress;

#define PROPERTY_TAG_GET_BOARD_SERIAL 0x00010004
typedef struct PropertyGetBoardSerial {
  uint32_t tag;
  uint64_t boardSerial;
} PropertyGetBoardSerial;

#define PROPERTY_TAG_GET_ARM_MEMORY 0x00010005
typedef struct PropertyGetArmMemory {
  uint32_t tag;
  uint32_t baseAddress;
  uint32_t size;
} PropertyGetArmMemory;

#define PROPERTY_TAG_GET_VIDEOCORE_MEMORY 0x00010006
typedef struct PropertyGetVideoCoreMemory {
  uint32_t tag;
  uint32_t baseAddress;
  uint32_t size;
} PropertyGetVideoCoreMemory;

#define PROPERTY_TAG_GET_CLOCKS 0x00010007
typedef struct PropertyGetClocks {
  uint32_t tag;
  uint32_t parentClockId;
  uint32_t clockId;
  // ...
} PropertyGetClocks;

#define PROPERTY_TAG_GET_COMMAND_LINE 0x00050001
typedef struct PropertyGetCommandLine {
  uint32_t tag;
  uint8_t commandLineStr;
  // ...
} PropertyGetCommandLine;

#define PROPERTY_TAG_GET_DMA_CHANNELS 0x00060001
typedef struct PropertyGetDMAChannels {
  uint32_t tag;
  uint32_t mask; // Bits 0-15: DMA channels 0-15 (0=do not use, 1=usable),Bits 16-31: reserved for future use
} PropertyGetDMAChannels;

#define DEVICE_ID_SD_Card 0x00000000
#define DEVICE_ID_UART0 0x00000001
#define DEVICE_ID_UART1 0x00000002
#define DEVICE_ID_USB_HCD 0x00000003
#define DEVICE_ID_I2C0 0x00000004
#define DEVICE_ID_I2C1 0x00000005
#define DEVICE_ID_I2C2 0x00000006
#define DEVICE_ID_SPI 0x00000007
#define DEVICE_ID_CCP2TX 0x00000008
#define DEVICE_ID_Unknown1_RPi4 0x00000009
#define DEVICE_ID_Unknown2_RPi4 0x0000000a

#define PROPERTY_TAG_GET_POWER_STATE 0x00020001
typedef struct PropertyGetPowerState {
  uint32_t tag;
  uint32_t deviceId;
  uint32_t responseDeviceId;
  /**
   * Bit 0: 0=off, 1=on
   * Bit 1: 0=device exists, 1=device does not exist
   * Bits 2-31: reserved for future use
   */
  uint32_t state;
} PropertyGetPowerState;

#define PROPERTY_TAG_GET_TIMING 0x00020002
typedef struct PropertyGetTiming {
  uint32_t tag;
  uint32_t deviceId;
  uint32_t responseDeviceId;
  uint32_t waitTime;
} PropertyGetTiming;

#define PROPERTY_TAG_SET_POWER_STATE 0x00028001
typedef struct PropertySetPowerState {
  uint32_t tag;
  uint32_t deviceId;
  /**
   * Bit 0: 0=off, 1=on
   * Bit 1: 0=do not wait, 1=wait
   * Bits 2-31: reserved for future use (set to 0)
   */
  uint32_t responseDeviceId;
  /**
   * Bit 0: 0=off, 1=on
   * Bit 1: 0=device exists, 1=device does not exist
   * Bits 2-31: reserved for future use
   */
  uint32_t responseState;
} PropertySetPowerState;

#define CLOCK_ID_reserved 0x000000000
#define CLOCK_ID_EMMC 0x000000001
#define CLOCK_ID_UART 0x000000002
#define CLOCK_ID_ARM 0x000000003
#define CLOCK_ID_CORE 0x000000004
#define CLOCK_ID_V3D 0x000000005
#define CLOCK_ID_H264 0x000000006
#define CLOCK_ID_ISP 0x000000007
#define CLOCK_ID_SDRAM 0x000000008
#define CLOCK_ID_PIXEL 0x000000009
#define CLOCK_ID_PWM 0x00000000a
#define CLOCK_ID_HEVC 0x00000000b
#define CLOCK_ID_EMMC2 0x00000000c
#define CLOCK_ID_M2MC 0x00000000d
#define CLOCK_ID_PIXEL_BVB 0x00000000e

#define PROPERTY_TAG_GET_CLOCK_STATE 0x00030001
typedef struct PropertyGetClockState {
  uint32_t tag;
  uint32_t clockId;
  uint32_t responseClockId;
  /**
   * Bit 0: 0=off, 1=on
   * Bit 1: 0=clock exists, 1=clock does not exist
   * Bits 2-31: reserved for future use
   */
  uint32_t responseState;
} PropertyGetClockState;

#define PROPERTY_TAG_SET_CLOCK_STATE 0x00038001
typedef struct PropertySetClockState {
  uint32_t tag;
  uint32_t clockId;
  /**
   * Bit 0: 0=off, 1=on
   * Bit 1: 0=clock exists, 1=clock does not exist
   * Bits 2-31: reserved for future use (set to 0)
   */
  uint32_t state;
  uint32_t responseClockId;
  /**
   * Bit 0: 0=off, 1=on
   * Bit 1: 0=clock exists, 1=clock does not exist
   * Bits 2-31: reserved for future use
   */
  uint32_t responseState;
} PropertySetClockState;

#define PROPERTY_TAG_GET_CLOCK_RATE 0x00030002
typedef struct PropertyGetClockRate {
  uint32_t tag;
  uint32_t clockId;
  uint32_t responseClockId;
  uint32_t rate;
} PropertyGetClockRate;

#define PROPERTY_TAG_SET_CLOCK_RATE 0x00038002
typedef struct PropertySetClockRate {
  uint32_t tag;
  uint32_t clockId;
  uint32_t rate;
  uint32_t skipSettingTurbo;
  uint32_t responseClockId;
  uint32_t responseRate;
} PropertySetClockRate;

#define PROPERTY_TAG_GET_MAX_CLOCK_RATE 0x00030004
typedef struct PropertyGetMaxClockRate {
  uint32_t tag;
  uint32_t clockId;
  uint32_t responseClockId;
  uint32_t rate;
} PropertyGetMaxClockRate;

#define PROPERTY_TAG_GET_MIN_CLOCK_RATE 0x00030007
typedef struct PropertyGetMinClockRate {
  uint32_t tag;
  uint32_t clockId;
  uint32_t responseClockId;
  uint32_t rate;
} PropertyGetMinClockRate;

#define PROPERTY_TAG_GET_TURBO 0x00030009
typedef struct PropertyGetTurbo {
  uint32_t tag;
  uint32_t id;
  uint32_t responseId;
  uint32_t level;
} PropertyGetTurbo;

#define PROPERTY_TAG_SET_TURBO 0x00038009
typedef struct PropertySetTurbo {
  uint32_t tag;
  uint32_t id;
  uint32_t level;
  uint32_t responseId;
  uint32_t responseLevel;
} PropertySetTurbo;

#define VOLTAGE_IDreserved 0x000000000
#define VOLTAGE_IDCore 0x000000001
#define VOLTAGE_IDSDRAM_C 0x000000002
#define VOLTAGE_IDSDRAM_P 0x000000003
#define VOLTAGE_IDSDRAM_I 0x000000004

#define PROPERTY_TAG_GET_VOLTAGE 0x00030003
typedef struct PropertyGetVoltage {
  uint32_t tag;
  uint32_t voltageId;
  uint32_t responseVoltageId;
  uint32_t value;
} PropertyGetVoltage;

#define PROPERTY_TAG_SET_VOLTAGE 0x00038003
typedef struct PropertySetVoltage {
  uint32_t tag;
  uint32_t voltageId;
  uint32_t value;
  uint32_t responseVoltageId;
  uint32_t responseValue;
} PropertySetVoltage;

#define PROPERTY_TAG_GET_MAX_VOLTAGE 0x00030005
typedef struct PropertyGetMaxVoltage {
  uint32_t tag;
  uint32_t voltageId;
  uint32_t responseVoltageId;
  uint32_t value;
} PropertyGetMaxVoltage;

#define PROPERTY_TAG_GET_MIN_VOLTAGE 0x00030008
typedef struct PropertyGetMinVoltage {
  uint32_t tag;
  uint32_t voltageId;
  uint32_t responseVoltageId;
  uint32_t value;
} PropertyGetMinVoltage;

#define PROPERTY_TAG_GET_TEMPERATURE 0x00030006
typedef struct PropertyGetTemperature {
  uint32_t tag;
  uint32_t temperatureId;
  uint32_t responseTemperatureId;
  uint32_t value;
} PropertyGetTemperature;

#define PROPERTY_TAG_GET_MAX_TEMPERATURE 0x0003000a
typedef struct PropertyGetMaxTemperature {
  uint32_t tag;
  uint32_t temperatureId;
  uint32_t responseTemperatureId;
  uint32_t value;
} PropertyGetMaxTemperature;

#define MEM_FLAG_DISCARDABLE 1 << 0 //  can be resized to 0 at any time. Use for cached data
#define MEM_FLAG_NORMAL 0 << 2      //  normal allocating alias. Don't use from ARM
#define MEM_FLAG_DIRECT 1 << 2      //  0xC alias uncached
#define MEM_FLAG_COHERENT 2 << 2    //  0x8 alias. Non-allocating in L2 but coherent
#define MEM_FLAG_L1_NONALLOCATING (MEM_FLAG_DIRECT | MEM_FLAG_COHERENT) //  Allocating in L2
#define MEM_FLAG_ZERO 1 << 4                                            //   initialise buffer to all zeros
#define MEM_FLAG_NO_INIT 1 << 5        //  don't initialise (default is initialise to all ones
#define MEM_FLAG_HINT_PERMALOCK 1 << 6 //  Likely to be locked for long periods of time.

#define PROPERTY_TAG_ALLOCATE_MEMORY 0x0003000c
typedef struct PropertyAllocateMemory {
  uint32_t tag;
  uint32_t size;
  uint32_t alignment;
  uint32_t flags;
  uint32_t handle;
} PropertyAllocateMemory;

#define PROPERTY_TAG_LOCK_MEMORY 0x0003000d
typedef struct PropertyLockMemory {
  uint32_t tag;
  uint32_t handle;
  uint32_t busAddress;
} PropertyLockMemory;

#define PROPERTY_TAG_UNLOCK_MEMORY 0x0003000e
typedef struct PropertyUnLockMemory {
  uint32_t tag;
  uint32_t handle;
  uint32_t status;
} PropertyUnLockMemory;

#define PROPERTY_TAG_RELEASE_MEMORY 0x0003000f
typedef struct PropertyReleaseMemory {
  uint32_t tag;
  uint32_t handle;
  uint32_t status;
} PropertyReleaseMemory;

#define PROPERTY_TAG_EXECUTE_CODE 0x00030010
typedef struct PropertyExecuteCode {
  uint32_t tag;
  uint32_t functionPointer;
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r4;
  uint32_t r5;
  uint32_t responseR0;
} PropertyExecuteCode;

#define PROPERTY_TAG_GET_DISPMANX_RESOURCE_MEN_HANDLER 0x00030014
typedef struct PropertyGetDispmanxResourceMemHandle {
  uint32_t tag;
  uint32_t dispmanxResourceHandle;
  uint32_t value;
  uint32_t memHandleForResource;
} PropertyGetDispmanxResourceMemHandle;

#define PROPERTY_TAG_GET_EDID_CLOCK 0x00030020
typedef struct PropertyGetEDIDBlock {
  uint32_t tag;
  uint32_t blockNumber;
  uint32_t responseBlockNumber;
  uint32_t status;
  uint8_t EDIDBlock[128];
} PropertyGetEDIDBlock;

#define PROPERTY_TAG_ALLOCATE_BUFFER 0x00040001
typedef struct PropertyAllocateBuffer {
  uint32_t tag;
  uint32_t alignment;
  uint32_t baseAddress;
  uint32_t size;
} PropertyAllocateBuffer;

#define PROPERTY_TAG_RELEASE_BUFFER 0x00048001
typedef struct PropertyReleaseBuffer {
  uint32_t tag;
} PropertyReleaseBuffer;

#define PROPERTY_TAG_BLANK_SCREEN 0x00040002
typedef struct PropertyBlankScreen {
  uint32_t tag;
  /**
   * Bit 0: 0=off, 1=on
   * Bits 1-31: reserved for future use (set to 0)
   */
  uint32_t state;

  /**
   * Bit 0: 0=off, 1=on
   * Bits 1-31: reserved for future use
   */
  uint32_t responseState;
} PropertyBlankScreen;

#define PROPERTY_TAG_GET_PHYSICAL_DISPLAY_WH 0x00040003
typedef struct PropertyGetPhysicalDisplayWH {
  uint32_t tag;
  uint32_t width;
  uint32_t height;
} PropertyGetPhysicalDisplayWH;

#define PROPERTY_TAG_TEST_PHYSICAL_DISPLAY_WH 0x00044003
typedef struct PropertyTestPhysicalDisplayWH {
  uint32_t tag;
  uint32_t width;
  uint32_t height;
  uint32_t responseWidth;
  uint32_t responseHeight;
} PropertyTestPhysicalDisplayWH;

#define PROPERTY_TAG_SET_PHYSICAL_DISPLAY_WH 0x00048003
typedef struct PropertySetPhysicalDisplayWH {
  uint32_t tag;
  uint32_t width;
  uint32_t height;
  uint32_t responseWidth;
  uint32_t responseHeight;
} PropertySetPhysicalDisplayWH;

#define PROPERTY_TAG_GET_VIRTUAL_BUFFER_WH 0x00040004
typedef struct PropertyGetVirtualBufferWH {
  uint32_t tag;
  uint32_t width;
  uint32_t height;
} PropertyGetVirtualBufferWH;

#define PROPERTY_TAG_TEST_VIRTUAL_BUFFER_WH 0x00044004
typedef struct PropertyTestVirtualBufferWH {
  uint32_t tag;
  uint32_t width;
  uint32_t height;
  uint32_t responseWidth;
  uint32_t responseHeight;
} PropertyTestVirtualBufferWH;

#define PROPERTY_TAG_SET_VIRTUAL_BUFFER_WH 0x00048004
typedef struct PropertySetVirtualBufferWH {
  uint32_t tag;
  uint32_t width;
  uint32_t height;
  uint32_t responseWidth;
  uint32_t responseHeight;
} PropertySetVirtualBufferWH;

#define PROPERTY_TAG_GET_DEPTH 0x00040005
typedef struct PropertyGetDepth {
  uint32_t tag;
  uint32_t bitsPerPixel;
} PropertyGetDepth;

#define PROPERTY_TAG_TEST_DEPTH 0x00044005
typedef struct PropertyTestDepth {
  uint32_t tag;
  uint32_t bitsPerPixel;
  uint32_t responseBitsPerPixel;
} PropertyTestDepth;

#define PROPERTY_TAG_SET_DEPTH 0x00048005
typedef struct PropertySetDepth {
  uint32_t tag;
  uint32_t bitsPerPixel;
  uint32_t responseBitsPerPixel;
} PropertySetDepth;

#define PROPERTY_TAG_GET_PIXEL_ORDER 0x00040006
typedef struct PropertyGetPixelOrder {
  uint32_t tag;
  /**
   * 0x0: BGR
   * 0x1: RGB
   */
  uint32_t state;
} PropertyGetPixelOrder;

#define PROPERTY_TAG_TEST_PIXEL_ORDER 0x00044006
typedef struct PropertyTestPixelOrder {
  uint32_t tag;
  /**
   * 0x0: BGR
   * 0x1: RGB
   */
  uint32_t state;
  uint32_t responseState;
} PropertyTestPixelOrder;

#define PROPERTY_TAG_SET_PIXEL_ORDER 0x00048006
typedef struct PropertySetPixelOrder {
  uint32_t tag;
  /**
   * 0x0: BGR
   * 0x1: RGB
   */
  uint32_t state;
  uint32_t responseState;
} PropertySetPixelOrder;

#define PROPERTY_TAG_GET_ALPHA_MODE 0x00040007
typedef struct PropertyGetAlphaMode {
  uint32_t tag;
  /**
   * 0x0: Alpha channel enabled (0 = fully opaque)
   * 0x1: Alpha channel reversed (0 = fully transparent)
   * 0x2: Alpha channel ignored
   */
  uint32_t state;
} PropertyGetAlphaMode;

#define PROPERTY_TAG_TEST_ALPHA_MODE 0x00044007
typedef struct PropertyTestAlphaMode {
  uint32_t tag;
  uint32_t state;
  uint32_t responseState;
} PropertyTestAlphaMode;

#define PROPERTY_TAG_SET_ALPHA_MODE 0x00048007
typedef struct PropertySetAlphaMode {
  uint32_t tag;
  uint32_t state;
  uint32_t responseState;
} PropertySetAlphaMode;

#define PROPERTY_TAG_GET_PITCH 0x00040008
typedef struct PropertyGetPitch {
  uint32_t tag;
  uint32_t bytesPerLine;
} PropertyGetPitch;

#define PROPERTY_TAG_GET_VIRTUAL_OFFSET 0x00040009
typedef struct PropertyGetVirtualOffset {
  uint32_t tag;
  uint32_t xOffset;
  uint32_t yOffset;
} PropertyGetVirtualOffset;

#define PROPERTY_TAG_TEST_VIRTUAL_OFFSET 0x00044009
typedef struct PropertyTestVirtualOffset {
  uint32_t tag;
  uint32_t xOffset;
  uint32_t yOffset;
  uint32_t responseXOffset;
  uint32_t responseYOffset;
} PropertyTestVirtualOffset;

#define PROPERTY_TAG_SET_VIRTUAL_OFFSET 0x00048009
typedef struct PropertySetVirtualOffset {
  uint32_t tag;
  uint32_t xOffset;
  uint32_t yOffset;
  uint32_t responseXOffset;
  uint32_t responseYOffset;
} PropertySetVirtualOffset;

#define PROPERTY_TAG_GET_OVERSCAN 0x0004000a
typedef struct PropertyGetOverscan {
  uint32_t tag;
  uint32_t top;
  uint32_t bottom;
  uint32_t left;
  uint32_t right;
} PropertyGetOverscan;

#define PROPERTY_TAG_TEST_OVERSCAN 0x0004400a
typedef struct PropertyTestOverscan {
  uint32_t tag;
  uint32_t top;
  uint32_t bottom;
  uint32_t left;
  uint32_t right;
  uint32_t responseTop;
  uint32_t responseBottom;
  uint32_t responseLeft;
  uint32_t responseRight;
} PropertyTestOverscan;

#define PROPERTY_TAG_SET_OVERSCAN 0x0004800a
typedef struct PropertySetOverscan {
  uint32_t tag;
  uint32_t top;
  uint32_t bottom;
  uint32_t left;
  uint32_t right;
  uint32_t responseTop;
  uint32_t responseBottom;
  uint32_t responseLeft;
  uint32_t responseRight;
} PropertySetOverscan;

#define PROPERTY_TAG_GET_PALETTE 0x0004000b
typedef struct PropertyGetPalette {
  uint32_t tag;
  uint32_t palette[256];
} PropertyGetPalette;

#define PROPERTY_TAG_TEST_PALETTE 0x0004400b
typedef struct PropertyTestPalette {
  uint32_t tag;
  uint32_t first;
  uint32_t length;
  uint32_t palette[256]; // (offset to offset+length-1)
  /**
   * 0=valid,
   * 1=invalid
   */
  uint32_t value;
} PropertyTestPalette;

#define PROPERTY_TAG_SET_PALETTE 0x0004800b
typedef struct PropertySetPalette {
  uint32_t tag;
  uint32_t first;
  uint32_t length;
  uint32_t palette[256]; // (offset to offset+length-1)
  /**
   * 0=valid,
   * 1=invalid
   */
  uint32_t value;
} PropertySetPalette;

#define PROPERTY_TAG_SET_CURSOR_INFO 0x00008010
typedef struct PropertySetCursorInfo {
  uint32_t tag;
  uint32_t width;
  uint32_t height;
  uint32_t unused;
  uint32_t pointerToPixels;
  uint32_t hotSpotX;
  uint32_t hotSpotY;
  /**
   * 0=valid,
   * 1=invalid
   */
  uint32_t value;
} PropertySetCursorInfo;

#define PROPERTY_TAG_SET_CURSOR_STATE 0x00008011
typedef struct PropertySetCursorState {
  uint32_t tag;
  /**
   * 0=invisable,
   * 1=visable
   */
  uint32_t enable;
  uint32_t x;
  uint32_t y;
  uint32_t flags;
  /**
   * 0=valid,
   * 1=invalid
   */
  uint32_t value;
} PropertySetCursorState;

uint32_t mailbox_call(uint8_t channel, uint32_t mailbox);
uint32_t mailbox_read(uint8_t channel);
void mailbox_write(uint8_t channel, uint32_t data);

void mailboxSetPropertyGetFirmwareRevision(PropertyGetFirmwareRevision property);
void mailboxSetPropertyGetBoardModel(PropertyGetBoardModel property);
void mailboxSetPropertyGetBoardRevision(PropertyGetBoardRevision property);
void mailboxSetPropertyGetBoardMacAddress(PropertyGetBoardMacAddress property);
void mailboxSetPropertyGetBoardSerial(PropertyGetBoardSerial property);
void mailboxSetPropertyGetArmMemory(PropertyGetArmMemory property);
void mailboxSetPropertyGetVideoCoreMemory(PropertyGetVideoCoreMemory property);
void mailboxSetPropertyGetClocks(PropertyGetClocks property);
void mailboxSetPropertyGetCommandLine(PropertyGetCommandLine property);
void mailboxSetPropertyGetDMAChannels(PropertyGetDMAChannels property);
void mailboxSetPropertyGetPowerState(PropertyGetPowerState property);
void mailboxSetPropertyGetTiming(PropertyGetTiming property);
void mailboxSetPropertySetPowerState(PropertySetPowerState property);
void mailboxSetPropertyGetClockState(PropertyGetClockState property);
void mailboxSetPropertySetClockState(PropertySetClockState property);
void mailboxSetPropertyGetClockRate(PropertyGetClockRate property);
void mailboxSetPropertySetClockRate(PropertySetClockRate property);
void mailboxSetPropertyGetMaxClockRate(PropertyGetMaxClockRate property);
void mailboxSetPropertyGetMinClockRate(PropertyGetMinClockRate property);
void mailboxSetPropertyGetTurbo(PropertyGetTurbo property);
void mailboxSetPropertySetTurbo(PropertySetTurbo property);
void mailboxSetPropertyGetVoltage(PropertyGetVoltage property);
void mailboxSetPropertySetVoltage(PropertySetVoltage property);
void mailboxSetPropertyGetMaxVoltage(PropertyGetMaxVoltage property);
void mailboxSetPropertyGetMinVoltage(PropertyGetMinVoltage property);
void mailboxSetPropertyGetTemperature(PropertyGetTemperature property);
void mailboxSetPropertyGetMaxTemperature(PropertyGetMaxTemperature property);
void mailboxSetPropertyAllocateMemory(PropertyAllocateMemory property);
void mailboxSetPropertyLockMemory(PropertyLockMemory property);
void mailboxSetPropertyUnLockMemory(PropertyUnLockMemory property);
void mailboxSetPropertyReleaseMemory(PropertyReleaseMemory property);
void mailboxSetPropertyExecuteCode(PropertyExecuteCode property);
void mailboxSetPropertyGetDispmanxResourceMemHandle(PropertyGetDispmanxResourceMemHandle property);
void mailboxSetPropertyGetEDIDBlock(PropertyGetEDIDBlock property);
void mailboxSetPropertyAllocateBuffer(PropertyAllocateBuffer property);
void mailboxSetPropertyReleaseBuffer(PropertyReleaseBuffer property);
void mailboxSetPropertyBlankScreen(PropertyBlankScreen property);
void mailboxSetPropertyGetPhysicalDisplayWH(PropertyGetPhysicalDisplayWH property);
void mailboxSetPropertyTestPhysicalDisplayWH(PropertyTestPhysicalDisplayWH property);
void mailboxSetPropertySetPhysicalDisplayWH(PropertySetPhysicalDisplayWH property);
void mailboxSetPropertyGetVirtualBufferWH(PropertyGetVirtualBufferWH property);
void mailboxSetPropertyTestVirtualBufferWH(PropertyTestVirtualBufferWH property);
void mailboxSetPropertySetVirtualBufferWH(PropertySetVirtualBufferWH property);
void mailboxSetPropertyGetDepth(PropertyGetDepth property);
void mailboxSetPropertyTestDepth(PropertyTestDepth property);
void mailboxSetPropertySetDepth(PropertySetDepth property);
void mailboxSetPropertyGetPixelOrder(PropertyGetPixelOrder property);
void mailboxSetPropertyTestPixelOrder(PropertyTestPixelOrder property);
void mailboxSetPropertySetPixelOrder(PropertySetPixelOrder property);
void mailboxSetPropertyGetAlphaMode(PropertyGetAlphaMode property);
void mailboxSetPropertyTestAlphaMode(PropertyTestAlphaMode property);
void mailboxSetPropertySetAlphaMode(PropertySetAlphaMode property);
void mailboxSetPropertyGetPitch(PropertyGetPitch property);
void mailboxSetPropertyGetVirtualOffset(PropertyGetVirtualOffset property);
void mailboxSetPropertyTestVirtualOffset(PropertyTestVirtualOffset property);
void mailboxSetPropertySetVirtualOffset(PropertySetVirtualOffset property);
void mailboxSetPropertyGetOverscan(PropertyGetOverscan property);
void mailboxSetPropertyTestOverscan(PropertyTestOverscan property);
void mailboxSetPropertySetOverscan(PropertySetOverscan property);
void mailboxSetPropertyGetPalette(PropertyGetPalette property);
void mailboxSetPropertyTestPalette(PropertyTestPalette property);
void mailboxSetPropertySetPalette(PropertySetPalette property);
void mailboxSetPropertySetCursorInfo(PropertySetCursorInfo property);
void mailboxSetPropertySetCursorState(PropertySetCursorState property);
#endif //__BOARD_RASP_MAILBOX_H__