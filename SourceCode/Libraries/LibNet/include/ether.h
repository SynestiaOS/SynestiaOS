//
// Created by XingfengYang on 2020/10/19.
//

#ifndef SYNESTIAOS_ETHER_H
#define SYNESTIAOS_ETHER_H

typedef enum EtherType{
    ETHER_TYPE_IPV4= 0x0800,  //	Internet Protocol version 4 (IPv4)
    ETHER_TYPE_ARP= 0x0806,  //	Address Resolution Protocol (ARP)
    ETHER_TYPE_LAN= 0x0842,  //	Wake-on-LAN[9]
    ETHER_TYPE_AVTP= 0x22F0,  //	Audio Video Transport Protocol (AVTP)
    ETHER_TYPE_IEIF= 0x22F3,  //	IETF TRILL Protocol
    ETHER_TYPE_SRP= 0x22EA,  //	Stream Reservation Protocol
    ETHER_TYPE_DEC_MOP_RC= 0x6002,  //	DEC MOP RC
    ETHER_TYPE_DECnet= 0x6003,  //	DECnet Phase IV, DNA Routing
    ETHER_TYPE_DEC_LAT= 0x6004,  //	DEC LAT
    ETHER_TYPE_RARP= 0x8035,  //	Reverse Address Resolution Protocol (RARP)
    ETHER_TYPE_ETHERTALK= 0x809B,  //	AppleTalk (Ethertalk)
    ETHER_TYPE_AARP= 0x80F3,  //	AppleTalk Address Resolution Protocol (AARP)
    ETHER_TYPE_VLAN= 0x8100,  //	VLAN-tagged frame (IEEE 802.1Q) and Shortest Path Bridging IEEE 802.1aq with NNI compatibility[10]
    ETHER_TYPE_SLPP= 0x8102,  //	Simple Loop Prevention Protocol (SLPP)
    ETHER_TYPE_VLACP= 0x8103,  //	Virtual Link Aggregation Control Protocol (VLACP)
    ETHER_TYPE_IPX= 0x8137,  //	IPX
    ETHER_TYPE_QNET= 0x8204,  //	QNX Qnet
    ETHER_TYPE_IPV6= 0x86DD,  //	Internet Protocol Version 6 (IPv6)
    ETHER_TYPE_EFC= 0x8808,  //	Ethernet flow control
    ETHER_TYPE_LACP= 0x8809,  //	Ethernet Slow Protocols[11] such as the Link Aggregation Control Protocol (LACP)
    ETHER_TYPE_COBRA_NET= 0x8819,  //	CobraNet
    ETHER_TYPE_MPLS_UNICAST= 0x8847,  //	MPLS unicast
    ETHER_TYPE_MPLS_MULTICAST= 0x8848,  //	MPLS multicast
    ETHER_TYPE_PPPOE_DS= 0x8863,  //	PPPoE Discovery Stage
    ETHER_TYPE_PPPOE_SS= 0x8864,  //	PPPoE Session Stage
    ETHER_TYPE_HOME_PLUG_MME= 0x887B,  //	HomePlug 1.0 MME
    ETHER_TYPE_EAP_OVER_LAN= 0x888E,  //	EAP over LAN (IEEE 802.1X)
    ETHER_TYPE_PROFINET= 0x8892,  //	PROFINET Protocol
    ETHER_TYPE_HYPER_SCSI= 0x889A,  //	HyperSCSI (SCSI over Ethernet)
    ETHER_TYPE_ATA= 0x88A2,  //	ATA over Ethernet
    ETHER_TYPE_ETHER_CAT= 0x88A4,  //	EtherCAT Protocol
    ETHER_TYPE_S_TAG= 0x88A8,  //	Service VLAN tag identifier (S-Tag) on Q-in-Q tunnel.
    ETHER_TYPE_POWER_LINK= 0x88AB,  //	Ethernet Powerlink[citation needed]
    ETHER_TYPE_GOOSE= 0x88B8,  //	GOOSE (Generic Object Oriented Substation event)
    ETHER_TYPE_GSE= 0x88B9,  //	GSE (Generic Substation Events) Management Services
    ETHER_TYPE_SV= 0x88BA,  //	SV (Sampled Value Transmission)
    ETHER_TYPE_ROMON= 0x88BF,  //	MikroTik RoMON (unofficial)
    ETHER_TYPE_LLDP= 0x88CC,  //	Link Layer Discovery Protocol (LLDP)
    ETHER_TYPE_SERCOS= 0x88CD,  //	SERCOS III
    ETHER_TYPE_IEC62439= 0x88E3,  //	Media Redundancy Protocol (IEC62439-2)
    ETHER_TYPE_MAC_SECURITY= 0x88E5,  //	MAC security (IEEE 802.1AE)
    ETHER_TYPE_PBB= 0x88E7,  //	Provider Backbone Bridges (PBB) (IEEE 802.1ah)
    ETHER_TYPE_PTP= 0x88F7,  //	Precision Time Protocol (PTP) over IEEE 802.3 Ethernet
    ETHER_TYPE_NC_SI= 0x88F8,  //	NC-SI
    ETHER_TYPE_PRP= 0x88FB,  //	Parallel Redundancy Protocol (PRP)
    ETHER_TYPE_CFM_OAM= 0x8902,  //	IEEE 802.1ag Connectivity Fault Management (CFM) Protocol / ITU-T Recommendation Y.1731 (OAM)
    ETHER_TYPE_FCOE= 0x8906,  //	Fibre Channel over Ethernet (FCoE)
    ETHER_TYPE_FCOE_I_P= 0x8914,  //	FCoE Initialization Protocol
    ETHER_TYPE_ROCE= 0x8915,  //	RDMA over Converged Ethernet (RoCE)
    ETHER_TYPE_TTE= 0x891D,  //	TTEthernet Protocol Control Frame (TTE)
    ETHER_TYPE_1095_1= 0x893a,  //	1905.1 IEEE Protocol
    ETHER_TYPE_HSR= 0x892F,  //	High-availability Seamless Redundancy (HSR)
    ETHER_TYPE_ECTP= 0x9000,  //	Ethernet Configuration Testing Protocol[12]
    ETHER_TYPE_VLAN_D_T= 0x9100,  //	VLAN-tagged (IEEE 802.1Q) frame with double tagging
    ETHER_TYPE_REDUNDANCY_TAG= 0xF1C1,  //	Redundancy Tag (IEEE 802.1CB Frame Replication and Elimination for Reliability)
} EtherType;

const char* getEtherTypeName(EtherType type);

typedef struct EtherHeader{
    unsigned char destinationMac[6];
    unsigned char sourceMac[6];
    unsigned short int etherType;
    unsigned char payload[];
} __attribute__((packed)) EtherHeader;


#endif //SYNESTIAOS_ETHER_H
