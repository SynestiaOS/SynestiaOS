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

#define CODE_REQUEST 0x00000000
#define CODE_RESPONSE_SUCCESS 0x80000000
#define CODE_RESPONSE_FAILURE 0x80000001
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
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t firmwareRevision;
} PropertyGetFirmwareRevision;

#define PROPERTY_TAG_GET_BOARD_MODEL 0x00010001
typedef struct PropertyGetBoardModel {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t boardModel;
} PropertyGetBoardModel;

#define PROPERTY_TAG_GET_BOARD_REVISION 0x00010002
typedef struct PropertyGetBoardRevision {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t boardRevision;
} PropertyGetBoardRevision;

#define PROPERTY_TAG_GET_BOARD_MAC_ADDRESS 0x00010003
typedef struct PropertyGetBoardMacAddress {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
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
  uint32_t bufferSzie;
  uint32_t code;
  uint64_t boardSerial;
} PropertyGetBoardSerial;

#define PROPERTY_TAG_GET_ARM_MEMORY 0x00010005
typedef struct PropertyGetArmMemory {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t baseAddress;
  uint32_t size;
} PropertyGetArmMemory;

#define PROPERTY_TAG_GET_VIDEOCORE_MEMORY 0x00010006
typedef struct PropertyGetVideoCoreMemory {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t baseAddress;
  uint32_t size;
} PropertyGetVideoCoreMemory;

#define PROPERTY_TAG_GET_CLOCKS 0x00010007
typedef struct PropertyGetClocks {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t parentClockId;
  uint32_t clockId;
  // ...
} PropertyGetClocks;

#define PROPERTY_TAG_GET_COMMAND_LINE 0x00050001
typedef struct PropertyGetCommandLine {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint8_t commandLineStr;
  // ...
} PropertyGetCommandLine;

#define PROPERTY_TAG_GET_DMA_CHANNELS 0x00060001
typedef struct PropertyGetDMAChannels {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
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
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t deviceId;
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
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t deviceId;
  uint32_t waitTime;
} PropertyGetTiming;

#define PROPERTY_TAG_SET_POWER_STATE 0x00028001
typedef struct PropertySetPowerState {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t deviceId;
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
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t clockId;
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
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t clockId;
  /**
   * Bit 0: 0=off, 1=on
   * Bit 1: 0=clock exists, 1=clock does not exist
   * Bits 2-31: reserved for future use (set to 0)
   */
  uint32_t state;
} PropertySetClockState;

#define PROPERTY_TAG_GET_CLOCK_RATE 0x00030002
typedef struct PropertyGetClockRate {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t clockId;
  uint32_t rate;
} PropertyGetClockRate;

#define PROPERTY_TAG_SET_CLOCK_RATE 0x00038002
typedef struct PropertySetClockRate {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t clockId;
  uint32_t rate;
  uint32_t skipSettingTurbo;
} PropertySetClockRate;

#define PROPERTY_TAG_GET_MAX_CLOCK_RATE 0x00030004
typedef struct PropertyGetMaxClockRate {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t clockId;
  uint32_t rate;
} PropertyGetMaxClockRate;

#define PROPERTY_TAG_GET_MIN_CLOCK_RATE 0x00030007
typedef struct PropertyGetMinClockRate {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t clockId;
  uint32_t rate;
} PropertyGetMinClockRate;

#define PROPERTY_TAG_GET_TURBO 0x00030009
typedef struct PropertyGetTurbo {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t id;
  uint32_t level;
} PropertyGetTurbo;

#define PROPERTY_TAG_SET_TURBO 0x00038009
typedef struct PropertySetTurbo {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t id;
  uint32_t level;
} PropertySetTurbo;

#define VOLTAGE_IDreserved 0x000000000
#define VOLTAGE_IDCore 0x000000001
#define VOLTAGE_IDSDRAM_C 0x000000002
#define VOLTAGE_IDSDRAM_P 0x000000003
#define VOLTAGE_IDSDRAM_I 0x000000004

#define PROPERTY_TAG_GET_VOLTAGE 0x00030003
typedef struct PropertyGetVoltage {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t voltageId;
  uint32_t value;
} PropertyGetVoltage;

#define PROPERTY_TAG_SET_VOLTAGE 0x00038003
typedef struct PropertySetVoltage {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t voltageId;
  uint32_t value;
} PropertySetVoltage;

#define PROPERTY_TAG_GET_MAX_VOLTAGE 0x00030005
typedef struct PropertyGetMaxVoltage {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t voltageId;
  uint32_t value;
} PropertyGetMaxVoltage;

#define PROPERTY_TAG_GET_MIN_VOLTAGE 0x00030008
typedef struct PropertyGetMinVoltage {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t voltageId;
  uint32_t value;
} PropertyGetMinVoltage;

#define PROPERTY_TAG_GET_TEMPERATURE 0x00030006
typedef struct PropertyGetTemperature {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t temperatureId;
  uint32_t value;
} PropertyGetTemperature;

#define PROPERTY_TAG_GET_MAX_TEMPERATURE 0x0003000a
typedef struct PropertyGetMaxTemperature {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t temperatureId;
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
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t size;
  uint32_t alignment;
  uint32_t flags;
  uint32_t handle;
} PropertyAllocateMemory;

#define PROPERTY_TAG_LOCK_MEMORY 0x0003000d
typedef struct PropertyLockMemory {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t handle;
  uint32_t busAddress;
} PropertyLockMemory;

#define PROPERTY_TAG_UNLOCK_MEMORY 0x0003000e
typedef struct PropertyUnLockMemory {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t handle;
  uint32_t status;
} PropertyUnLockMemory;

#define PROPERTY_TAG_RELEASE_MEMORY 0x0003000f
typedef struct PropertyReleaseMemory {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t handle;
  uint32_t status;
} PropertyReleaseMemory;

#define PROPERTY_TAG_EXECUTE_CODE 0x00030010
typedef struct PropertyExecuteCode {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t functionPointer;
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r4;
  uint32_t r5;
} PropertyExecuteCode;

#define PROPERTY_TAG_GET_DISPMANX_RESOURCE_MEN_HANDLER 0x00030014
typedef struct PropertyGetDispmanxResourceMemHandle {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t dispmanxResourceHandle;
  uint32_t value;
  uint32_t memHandleForResource;
} PropertyGetDispmanxResourceMemHandle;

#define PROPERTY_TAG_GET_EDID_CLOCK 0x00030020
typedef struct PropertyGetEDIDBlock {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t blockNumber;
  uint32_t status;
  uint8_t EDIDBlock[128];
} PropertyGetEDIDBlock;

#define PROPERTY_TAG_ALLOCATE_BUFFER 0x00040001
typedef struct PropertyAllocateBuffer {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  union {
    uint32_t alignment;
    uint32_t baseAddress;
  } PACKED;
  uint32_t size;
} PropertyAllocateBuffer;

#define PROPERTY_TAG_RELEASE_BUFFER 0x00048001
typedef struct PropertyReleaseBuffer {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
} PropertyReleaseBuffer;

#define PROPERTY_TAG_BLANK_SCREEN 0x00040002
typedef struct PropertyBlankScreen {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  /**
   * Bit 0: 0=off, 1=on
   * Bits 1-31: reserved for future use (set to 0)
   */
  uint32_t state;
} PropertyBlankScreen;

#define PROPERTY_TAG_GET_PHYSICAL_DISPLAY_WH 0x00040003
typedef struct PropertyGetPhysicalDisplayWH {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t width;
  uint32_t height;
} PropertyGetPhysicalDisplayWH;

#define PROPERTY_TAG_TEST_PHYSICAL_DISPLAY_WH 0x00044003
typedef struct PropertyTestPhysicalDisplayWH {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t width;
  uint32_t height;
} PropertyTestPhysicalDisplayWH;

#define PROPERTY_TAG_SET_PHYSICAL_DISPLAY_WH 0x00048003
typedef struct PropertySetPhysicalDisplayWH {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t width;
  uint32_t height;
} PropertySetPhysicalDisplayWH;

#define PROPERTY_TAG_GET_VIRTUAL_BUFFER_WH 0x00040004
typedef struct PropertyGetVirtualBufferWH {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t width;
  uint32_t height;
} PropertyGetVirtualBufferWH;

#define PROPERTY_TAG_TEST_VIRTUAL_BUFFER_WH 0x00044004
typedef struct PropertyTestVirtualBufferWH {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t width;
  uint32_t height;
} PropertyTestVirtualBufferWH;

#define PROPERTY_TAG_SET_VIRTUAL_BUFFER_WH 0x00048004
typedef struct PropertySetVirtualBufferWH {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t width;
  uint32_t height;
} PropertySetVirtualBufferWH;

#define PROPERTY_TAG_GET_DEPTH 0x00040005
typedef struct PropertyGetDepth {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t bitsPerPixel;
} PropertyGetDepth;

#define PROPERTY_TAG_TEST_DEPTH 0x00044005
typedef struct PropertyTestDepth {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t bitsPerPixel;
} PropertyTestDepth;

#define PROPERTY_TAG_SET_DEPTH 0x00048005
typedef struct PropertySetDepth {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t bitsPerPixel;
} PropertySetDepth;

#define PROPERTY_TAG_GET_PIXEL_ORDER 0x00040006
typedef struct PropertyGetPixelOrder {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  /**
   * 0x0: BGR
   * 0x1: RGB
   */
  uint32_t state;
} PropertyGetPixelOrder;

#define PROPERTY_TAG_TEST_PIXEL_ORDER 0x00044006
typedef struct PropertyTestPixelOrder {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  /**
   * 0x0: BGR
   * 0x1: RGB
   */
  uint32_t state;
} PropertyTestPixelOrder;

#define PROPERTY_TAG_SET_PIXEL_ORDER 0x00048006
typedef struct PropertySetPixelOrder {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  /**
   * 0x0: BGR
   * 0x1: RGB
   */
  uint32_t state;
} PropertySetPixelOrder;

#define PROPERTY_TAG_GET_ALPHA_MODE 0x00040007
typedef struct PropertyGetAlphaMode {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
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
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t state;
} PropertyTestAlphaMode;

#define PROPERTY_TAG_SET_ALPHA_MODE 0x00048007
typedef struct PropertySetAlphaMode {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t state;
} PropertySetAlphaMode;

#define PROPERTY_TAG_GET_PITCH 0x00040008
typedef struct PropertyGetPitch {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t bytesPerLine;
} PropertyGetPitch;

#define PROPERTY_TAG_GET_VIRTUAL_OFFSET 0x00040009
typedef struct PropertyGetVirtualOffset {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t xOffset;
  uint32_t yOffset;
} PropertyGetVirtualOffset;

#define PROPERTY_TAG_TEST_VIRTUAL_OFFSET 0x00044009
typedef struct PropertyTestVirtualOffset {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t xOffset;
  uint32_t yOffset;
} PropertyTestVirtualOffset;

#define PROPERTY_TAG_SET_VIRTUAL_OFFSET 0x00048009
typedef struct PropertySetVirtualOffset {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t xOffset;
  uint32_t yOffset;
} PropertySetVirtualOffset;

#define PROPERTY_TAG_GET_OVERSCAN 0x0004000a
typedef struct PropertyGetOverscan {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t top;
  uint32_t bottom;
  uint32_t left;
  uint32_t right;
} PropertyGetOverscan;

#define PROPERTY_TAG_TEST_OVERSCAN 0x0004400a
typedef struct PropertyTestOverscan {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t top;
  uint32_t bottom;
  uint32_t left;
  uint32_t right;
} PropertyTestOverscan;

#define PROPERTY_TAG_SET_OVERSCAN 0x0004800a
typedef struct PropertySetOverscan {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t top;
  uint32_t bottom;
  uint32_t left;
  uint32_t right;
} PropertySetOverscan;

#define PROPERTY_TAG_GET_PALETTE 0x0004000b
typedef struct PropertyGetPalette {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
  uint32_t palette[256];
} PropertyGetPalette;

#define PROPERTY_TAG_TEST_PALETTE 0x0004400b
typedef struct PropertyTestPalette {
  uint32_t tag;
  uint32_t bufferSzie;
  uint32_t code;
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
  uint32_t bufferSzie;
  uint32_t code;
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
  uint32_t bufferSzie;
  uint32_t code;
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
  uint32_t bufferSzie;
  uint32_t code;
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

typedef struct PropertyGetFirmwareRevisionMail {
  uint32_t size;
  uint32_t code;
  PropertyGetFirmwareRevision property;
  uint32_t end;
} PropertyGetFirmwareRevisionMail;
typedef struct PropertyGetBoardModelMail {
  uint32_t size;
  uint32_t code;
  PropertyGetBoardModel property;
  uint32_t end;
} PropertyGetBoardModelMail;
typedef struct PropertyGetBoardRevisionMail {
  uint32_t size;
  uint32_t code;
  PropertyGetBoardRevision property;
  uint32_t end;
} PropertyGetBoardRevisionMail;
typedef struct PropertyGetBoardMacAddressMail {
  uint32_t size;
  uint32_t code;
  PropertyGetBoardMacAddress property;
  uint32_t end;
} PropertyGetBoardMacAddressMail;
typedef struct PropertyGetBoardSerialMail {
  uint32_t size;
  uint32_t code;
  PropertyGetBoardSerial property;
  uint32_t end;
} PropertyGetBoardSerialMail;
typedef struct PropertyGetArmMemoryMail {
  uint32_t size;
  uint32_t code;
  PropertyGetArmMemory property;
  uint32_t end;
} PropertyGetArmMemoryMail;
typedef struct PropertyGetVideoCoreMemoryMail {
  uint32_t size;
  uint32_t code;
  PropertyGetVideoCoreMemory property;
  uint32_t end;
} PropertyGetVideoCoreMemoryMail;
typedef struct PropertyGetClocksMail {
  uint32_t size;
  uint32_t code;
  PropertyGetClocks property;
  uint32_t end;
} PropertyGetClocksMail;
typedef struct PropertyGetCommandLineMail {
  uint32_t size;
  uint32_t code;
  PropertyGetCommandLine property;
  uint32_t end;
} PropertyGetCommandLineMail;
typedef struct PropertyGetDMAChannelsMail {
  uint32_t size;
  uint32_t code;
  PropertyGetDMAChannels property;
  uint32_t end;
} PropertyGetDMAChannelsMail;
typedef struct PropertyGetPowerStateMail {
  uint32_t size;
  uint32_t code;
  PropertyGetPowerState property;
  uint32_t end;
} PropertyGetPowerStateMail;
typedef struct PropertyGetTimingMail {
  uint32_t size;
  uint32_t code;
  PropertyGetTiming property;
  uint32_t end;
} PropertyGetTimingMail;
typedef struct PropertySetPowerStateMail {
  uint32_t size;
  uint32_t code;
  PropertySetPowerState property;
  uint32_t end;
} PropertySetPowerStateMail;
typedef struct PropertyGetClockStateMail {
  uint32_t size;
  uint32_t code;
  PropertyGetClockState property;
  uint32_t end;
} PropertyGetClockStateMail;
typedef struct PropertySetClockStateMail {
  uint32_t size;
  uint32_t code;
  PropertySetClockState property;
  uint32_t end;
} PropertySetClockStateMail;
typedef struct PropertyGetClockRateMail {
  uint32_t size;
  uint32_t code;
  PropertyGetClockRate property;
  uint32_t end;
} PropertyGetClockRateMail;
typedef struct PropertySetClockRateMail {
  uint32_t size;
  uint32_t code;
  PropertySetClockRate property;
  uint32_t end;
} PropertySetClockRateMail;
typedef struct PropertyGetMaxClockRateMail {
  uint32_t size;
  uint32_t code;
  PropertyGetMaxClockRate property;
  uint32_t end;
} PropertyGetMaxClockRateMail;
typedef struct PropertyGetMinClockRateMail {
  uint32_t size;
  uint32_t code;
  PropertyGetMinClockRate property;
  uint32_t end;
} PropertyGetMinClockRateMail;
typedef struct PropertyGetTurboMail {
  uint32_t size;
  uint32_t code;
  PropertyGetTurbo property;
  uint32_t end;
} PropertyGetTurboMail;
typedef struct PropertySetTurboMail {
  uint32_t size;
  uint32_t code;
  PropertySetTurbo property;
  uint32_t end;
} PropertySetTurboMail;
typedef struct PropertyGetVoltageMail {
  uint32_t size;
  uint32_t code;
  PropertyGetVoltage property;
  uint32_t end;
} PropertyGetVoltageMail;
typedef struct PropertySetVoltageMail {
  uint32_t size;
  uint32_t code;
  PropertySetVoltage property;
  uint32_t end;
} PropertySetVoltageMail;
typedef struct PropertyGetMaxVoltageMail {
  uint32_t size;
  uint32_t code;
  PropertyGetMaxVoltage property;
  uint32_t end;
} PropertyGetMaxVoltageMail;
typedef struct PropertyGetMinVoltageMail {
  uint32_t size;
  uint32_t code;
  PropertyGetMinVoltage property;
  uint32_t end;
} PropertyGetMinVoltageMail;
typedef struct PropertyGetTemperatureMail {
  uint32_t size;
  uint32_t code;
  PropertyGetTemperature property;
  uint32_t end;
} PropertyGetTemperatureMail;
typedef struct PropertyGetMaxTemperatureMail {
  uint32_t size;
  uint32_t code;
  PropertyGetMaxTemperature property;
  uint32_t end;
} PropertyGetMaxTemperatureMail;
typedef struct PropertyAllocateMemoryMail {
  uint32_t size;
  uint32_t code;
  PropertyAllocateMemory property;
  uint32_t end;
} PropertyAllocateMemoryMail;
typedef struct PropertyLockMemoryMail {
  uint32_t size;
  uint32_t code;
  PropertyLockMemory property;
  uint32_t end;
} PropertyLockMemoryMail;
typedef struct PropertyUnLockMemoryMail {
  uint32_t size;
  uint32_t code;
  PropertyUnLockMemory property;
  uint32_t end;
} PropertyUnLockMemoryMail;
typedef struct PropertyReleaseMemoryMail {
  uint32_t size;
  uint32_t code;
  PropertyReleaseMemory property;
  uint32_t end;
} PropertyReleaseMemoryMail;
typedef struct PropertyExecuteCodeMail {
  uint32_t size;
  uint32_t code;
  PropertyExecuteCode property;
  uint32_t end;
} PropertyExecuteCodeMail;
typedef struct PropertyGetDispmanxResourceMemHandleMail {
  uint32_t size;
  uint32_t code;
  PropertyGetDispmanxResourceMemHandle property;
  uint32_t end;
} PropertyGetDispmanxResourceMemHandleMail;
typedef struct PropertyGetEDIDBlockMail {
  uint32_t size;
  uint32_t code;
  PropertyGetEDIDBlock property;
  uint32_t end;
} PropertyGetEDIDBlockMail;
typedef struct PropertyAllocateBufferMail {
  uint32_t size;
  uint32_t code;
  PropertyAllocateBuffer property;
  uint32_t end;
} PropertyAllocateBufferMail;
typedef struct PropertyReleaseBufferMail {
  uint32_t size;
  uint32_t code;
  PropertyReleaseBuffer property;
  uint32_t end;
} PropertyReleaseBufferMail;
typedef struct PropertyBlankScreenMail {
  uint32_t size;
  uint32_t code;
  PropertyBlankScreen property;
  uint32_t end;
} PropertyBlankScreenMail;
typedef struct PropertyGetPhysicalDisplayWHMail {
  uint32_t size;
  uint32_t code;
  PropertyGetPhysicalDisplayWH property;
  uint32_t end;
} PropertyGetPhysicalDisplayWHMail;
typedef struct PropertyTestPhysicalDisplayWHMail {
  uint32_t size;
  uint32_t code;
  PropertyTestPhysicalDisplayWH property;
  uint32_t end;
} PropertyTestPhysicalDisplayWHMail;
typedef struct PropertySetPhysicalDisplayWHMail {
  uint32_t size;
  uint32_t code;
  PropertySetPhysicalDisplayWH property;
  uint32_t end;
} PropertySetPhysicalDisplayWHMail;
typedef struct PropertyGetVirtualBufferWHMail {
  uint32_t size;
  uint32_t code;
  PropertyGetVirtualBufferWH property;
  uint32_t end;
} PropertyGetVirtualBufferWHMail;
typedef struct PropertyTestVirtualBufferWHMail {
  uint32_t size;
  uint32_t code;
  PropertyTestVirtualBufferWH property;
  uint32_t end;
} PropertyTestVirtualBufferWHMail;
typedef struct PropertySetVirtualBufferWHMail {
  uint32_t size;
  uint32_t code;
  PropertySetVirtualBufferWH property;
  uint32_t end;
} PropertySetVirtualBufferWHMail;
typedef struct PropertyGetDepthMail {
  uint32_t size;
  uint32_t code;
  PropertyGetDepth property;
  uint32_t end;
} PropertyGetDepthMail;
typedef struct PropertyTestDepthMail {
  uint32_t size;
  uint32_t code;
  PropertyTestDepth property;
  uint32_t end;
} PropertyTestDepthMail;
typedef struct PropertySetDepthMail {
  uint32_t size;
  uint32_t code;
  PropertySetDepth property;
  uint32_t end;
} PropertySetDepthMail;
typedef struct PropertyGetPixelOrderMail {
  uint32_t size;
  uint32_t code;
  PropertyGetPixelOrder property;
  uint32_t end;
} PropertyGetPixelOrderMail;
typedef struct PropertyTestPixelOrderMail {
  uint32_t size;
  uint32_t code;
  PropertyTestPixelOrder property;
  uint32_t end;
} PropertyTestPixelOrderMail;
typedef struct PropertySetPixelOrderMail {
  uint32_t size;
  uint32_t code;
  PropertySetPixelOrder property;
  uint32_t end;
} PropertySetPixelOrderMail;
typedef struct PropertyGetAlphaModeMail {
  uint32_t size;
  uint32_t code;
  PropertyGetAlphaMode property;
  uint32_t end;
} PropertyGetAlphaModeMail;
typedef struct PropertyTestAlphaModeMail {
  uint32_t size;
  uint32_t code;
  PropertyTestAlphaMode property;
  uint32_t end;
} PropertyTestAlphaModeMail;
typedef struct PropertySetAlphaModeMail {
  uint32_t size;
  uint32_t code;
  PropertySetAlphaMode property;
  uint32_t end;
} PropertySetAlphaModeMail;
typedef struct PropertyGetPitchMail {
  uint32_t size;
  uint32_t code;
  PropertyGetPitch property;
  uint32_t end;
} PropertyGetPitchMail;
typedef struct PropertyGetVirtualOffsetMail {
  uint32_t size;
  uint32_t code;
  PropertyGetVirtualOffset property;
  uint32_t end;
} PropertyGetVirtualOffsetMail;
typedef struct PropertyTestVirtualOffsetMail {
  uint32_t size;
  uint32_t code;
  PropertyTestVirtualOffset property;
  uint32_t end;
} PropertyTestVirtualOffsetMail;
typedef struct PropertySetVirtualOffsetMail {
  uint32_t size;
  uint32_t code;
  PropertySetVirtualOffset property;
  uint32_t end;
} PropertySetVirtualOffsetMail;
typedef struct PropertyGetOverscanMail {
  uint32_t size;
  uint32_t code;
  PropertyGetOverscan property;
  uint32_t end;
} PropertyGetOverscanMail;
typedef struct PropertyTestOverscanMail {
  uint32_t size;
  uint32_t code;
  PropertyTestOverscan property;
  uint32_t end;
} PropertyTestOverscanMail;
typedef struct PropertySetOverscanMail {
  uint32_t size;
  uint32_t code;
  PropertySetOverscan property;
  uint32_t end;
} PropertySetOverscanMail;
typedef struct PropertyGetPaletteMail {
  uint32_t size;
  uint32_t code;
  PropertyGetPalette property;
  uint32_t end;
} PropertyGetPaletteMail;
typedef struct PropertyTestPaletteMail {
  uint32_t size;
  uint32_t code;
  PropertyTestPalette property;
  uint32_t end;
} PropertyTestPaletteMail;
typedef struct PropertySetPaletteMail {
  uint32_t size;
  uint32_t code;
  PropertySetPalette property;
  uint32_t end;
} PropertySetPaletteMail;
typedef struct PropertySetCursorInfoMail {
  uint32_t size;
  uint32_t code;
  PropertySetCursorInfo property;
  uint32_t end;
} PropertySetCursorInfoMail;
typedef struct PropertySetCursorStateMail {
  uint32_t size;
  uint32_t code;
  PropertySetCursorState property;
  uint32_t end;
} PropertySetCursorStateMail;

typedef struct MailMessage {
  uint8_t channel : 4;
  uint32_t data : 28;
} MailMessage;

typedef struct MailStatus {
  uint32_t reserved : 30;
  uint8_t empty : 1;
  uint8_t full : 1;
} MailStatus;

MailMessage mailbox_call(MailMessage msg);
MailMessage mailbox_read(uint8_t channel);
void mailbox_send(MailMessage msg);
#endif //__BOARD_RASP_MAILBOX_H__