//
// Created by XingfengYang on 2020/8/6.
//

#ifndef __BOARD_RASP_SPI_H__
#define __BOARD_RASP_SPI_H__

#include "libc/stdint.h"

#define SPI0 0x7E204000
#define SPIO_CS SPI0 + 0x0
#define SPIO_FIFO SPI0 + 0x4
#define SPIO_CLK SPI0 + 0x8
#define SPIO_DLEN SPI0 + 0xc
#define SPIO_LTOH SPI0 + 0x10
#define SPIO_DC SPI0 + 0x14

typedef struct SPICSRegister {
    uint32_t Reserved : 6;
    uint32_t LEN_LONG : 1;
    uint32_t DMA_LEN : 1;
    uint32_t CSPOL2 : 1;
    uint32_t CSPOL1 : 1;
    uint32_t CSPOL0 : 1;
    uint32_t RXF : 1;
    uint32_t RXR : 1;
    uint32_t TXD : 1;
    uint32_t RXD : 1;
    uint32_t DONE : 1;
    uint32_t TE_EN : 1;
    uint32_t LMONO : 1;
    uint32_t LEN : 1;
    uint32_t REN : 1;
    uint32_t ADCS : 1;
    uint32_t INTR : 1;
    uint32_t INTD : 1;
    uint32_t DMAEN : 1;
    uint32_t TA : 1;
    uint32_t CSPOL : 1;
    uint32_t CLEARL : 2;
    uint32_t CPOL : 1;
    uint32_t CPHA : 1;
    uint32_t CS : 2;
} SPICSRegister;

typedef struct SPIFIFORegister {
    uint32_t data;
} SPIFIFORegister;

typedef struct SPICLKRegister {
    uint32_t reserved : 16;
    uint32_t CDIV : 16;
} SPICLKRegister;

typedef struct SPIDLENRegister {
    uint32_t reserved : 16;
    uint32_t LEN : 16;
} SPIDLENRegister;

typedef struct SPILTOHRegister {
    uint32_t reserved : 16;
    uint32_t TOH : 16;
} SPILTOHRegister;

typedef struct SPIDCRegister {
    uint32_t RPANIC : 8;
    uint32_t RDREQ : 8;
    uint32_t TPANIC : 16;
    uint32_t TDREQ : 8;
} SPIDCRegister;

typedef struct SPIRegister {
    SPICSRegister cs;
    SPIFIFORegister fifo;
    SPICLKRegister clk;
    SPIDLENRegister dlen;
    SPILTOHRegister ltoh;
    SPIDCRegister dc;
} SPIRegister;

#endif// ! __BOARD_RASP_SPI_H__
