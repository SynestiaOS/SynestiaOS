//
// Created by XingfengYang on 2020/10/19.
// https://tools.ietf.org/html/rfc791
//

#ifndef SYNESTIAOS_IP_H
#define SYNESTIAOS_IP_H


#include "libc/stdint.h"

#define ICMPV4 0x01
#define IPV4 0x04
#define IP_TCP 0x06


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
typedef struct IpHeader {
    uint8_t version : 4;
    uint8_t ihl : 4;
    int8_t tos;
    uint16_t length;
    uint16_t identification;
    uint16_t flags : 3;
    uint16_t fragmentOffset : 13;
    uint8_t timeToLive;
    uint8_t protocol;
    uint16_t headerChecksum;
    uint32_t sourceAddress;
    uint32_t destinationAddress;
    uint32_t options : 24;
    uint32_t padding : 8;
    uint8_t data[];
} __attribute__((packed));

#endif//SYNESTIAOS_IP_H
