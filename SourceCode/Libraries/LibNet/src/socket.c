//
// Created by XingfengYang on 2020/10/19.
//
// https://tools.ietf.org/html/rfc791
//

#include "stdint.h"


/**
 *     0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |Version|  IHL  |Type of Service|          Total Length         |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |         Identification        |Flags|      Fragment Offset    |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |  Time to Live |    Protocol   |         Header Checksum       |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                       Source Address                          |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                    Destination Address                        |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                    Options                    |    Padding    |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define ICMPV4 0x01
#define IPV4 0x04
#define IP_TCP 0x06

typedef struct IpHeader {
    uint8_t version: 4;
    uint8_t ihl: 4;
    int8_t tos;
    uint16_t length;
    uint16_t identification;
    uint16_t flags: 3;
    uint16_t fragmentOffset: 13;
    uint8_t timeToLive;
    uint8_t ptotocol;
    uint16_t headerChecksum;
    uint32_t sourceAddress;
    uint32_t destnationAddress;
    uint32_t options: 24;
    uint32_t padding: 8;
    uint8_t data[];
} __attribute__((packed));
