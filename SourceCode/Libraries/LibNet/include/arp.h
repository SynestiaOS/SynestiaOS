//
// Created by XingfengYang on 2020/10/21.
//

#ifndef SYNESTIAOS_ARP_H
#define SYNESTIAOS_ARP_H

typedef struct  ArpHeader{
    unsigned short hardwareType;
    unsigned short protocolType;
    unsigned char hardwareAddressLen;
    unsigned char protocolAddressLen;
    unsigned short operation;
    unsigned char data[];
} __attribute__((packed)) ArpHeader;

typedef struct ArpIpV4{
    unsigned char senderHardwareAddress[6];
    unsigned int  senderIp;
    unsigned char targetHardwareAddress[6];
    unsigned int  targetIp;
} __attribute__((packed)) ArpIpV4;

#endif //SYNESTIAOS_ARP_H
