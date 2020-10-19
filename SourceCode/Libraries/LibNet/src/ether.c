//
// Created by XingfengYang on 2020/10/19.
//

#include "ether.h"


const char *getEtherTypeName(EtherType type) {
    switch (type) {
        case ETHER_TYPE_IPV4:
            return "Internet Protocol version 4 (IPv4)";
        case ETHER_TYPE_ARP:
            return "Address Resolution Protocol (ARP)";
        case ETHER_TYPE_LAN:
            return "Wake-on-LAN[9]";
        case ETHER_TYPE_AVTP:
            return "Audio Video Transport Protocol (AVTP)";
        case ETHER_TYPE_IEIF:
            return "IETF TRILL Protocol";
        case ETHER_TYPE_SRP:
            return "Stream Reservation Protocol";
        case ETHER_TYPE_DEC_MOP_RC:
            return "DEC MOP RC";
        case ETHER_TYPE_DECnet:
            return "DECnet Phase IV, DNA Routing";
        case ETHER_TYPE_DEC_LAT:
            return "DEC LAT";
        case ETHER_TYPE_RARP:
            return "Reverse Address Resolution Protocol (RARP)";
        case ETHER_TYPE_ETHERTALK:
            return "AppleTalk (Ethertalk)";
        case ETHER_TYPE_AARP:
            return "AppleTalk Address Resolution Protocol (AARP)";
        case ETHER_TYPE_VLAN:
            return "VLAN-tagged frame (IEEE 802.1Q) and Shortest Path Bridging IEEE 802.1aq with NNI compatibility[10]";
        case ETHER_TYPE_SLPP:
            return "Simple Loop Prevention Protocol (SLPP)";
        case ETHER_TYPE_VLACP:
            return "Virtual Link Aggregation Control Protocol (VLACP)";
        case ETHER_TYPE_IPX:
            return "IPX";
        case ETHER_TYPE_QNET:
            return "QNX Qnet";
        case ETHER_TYPE_IPV6:
            return "Internet Protocol Version 6 (IPv6)";
        case ETHER_TYPE_EFC:
            return "Ethernet flow control";
        case ETHER_TYPE_LACP:
            return "Ethernet Slow Protocols[11] such as the Link Aggregation Control Protocol (LACP)";
        case ETHER_TYPE_COBRA_NET:
            return "CobraNet";
        case ETHER_TYPE_MPLS_UNICAST:
            return "MPLS unicast";
        case ETHER_TYPE_MPLS_MULTICAST:
            return "MPLS multicast";
        case ETHER_TYPE_PPPOE_DS:
            return "PPPoE Discovery Stage";
        case ETHER_TYPE_PPPOE_SS:
            return "PPPoE Session Stage";
        case ETHER_TYPE_HOME_PLUG_MME:
            return "HomePlug 1.0 MME";
        case ETHER_TYPE_EAP_OVER_LAN:
            return "EAP over LAN (IEEE 802.1X)";
        case ETHER_TYPE_PROFINET:
            return "PROFINET Protocol";
        case ETHER_TYPE_HYPER_SCSI:
            return "HyperSCSI (SCSI over Ethernet)";
        case ETHER_TYPE_ATA:
            return "ATA over Ethernet";
        case ETHER_TYPE_ETHER_CAT:
            return "EtherCAT Protocol";
        case ETHER_TYPE_S_TAG:
            return "Service VLAN tag identifier (S-Tag) on Q-in-Q tunnel.";
        case ETHER_TYPE_POWER_LINK:
            return "Ethernet Powerlink[citation needed]";
        case ETHER_TYPE_GOOSE:
            return "GOOSE (Generic Object Oriented Substation event)";
        case ETHER_TYPE_GSE:
            return "GSE (Generic Substation Events) Management Services";
        case ETHER_TYPE_SV:
            return "SV (Sampled Value Transmission)";
        case ETHER_TYPE_ROMON:
            return "MikroTik RoMON (unofficial)";
        case ETHER_TYPE_LLDP:
            return "Link Layer Discovery Protocol (LLDP)";
        case ETHER_TYPE_SERCOS:
            return "SERCOS III";
        case ETHER_TYPE_IEC62439:
            return "Media Redundancy Protocol (IEC62439-2)";
        case ETHER_TYPE_MAC_SECURITY:
            return "MAC security (IEEE 802.1AE)";
        case ETHER_TYPE_PBB:
            return "Provider Backbone Bridges (PBB) (IEEE 802.1ah)";
        case ETHER_TYPE_PTP:
            return "Precision Time Protocol (PTP) over IEEE 802.3 Ethernet";
        case ETHER_TYPE_NC_SI:
            return "NC-SI";
        case ETHER_TYPE_PRP:
            return "Parallel Redundancy Protocol (PRP)";
        case ETHER_TYPE_CFM_OAM:
            return "IEEE 802.1ag Connectivity Fault Management (CFM) Protocol / ITU-T Recommendation Y.1731 (OAM)";
        case ETHER_TYPE_FCOE:
            return "Fibre Channel over Ethernet (FCoE)";
        case ETHER_TYPE_FCOE_I_P:
            return "FCoE Initialization Protocol";
        case ETHER_TYPE_ROCE:
            return "RDMA over Converged Ethernet (RoCE)";
        case ETHER_TYPE_TTE:
            return "TTEthernet Protocol Control Frame (TTE)";
        case ETHER_TYPE_1095_1:
            return "1905.1 IEEE Protocol";
        case ETHER_TYPE_HSR:
            return "High-availability Seamless Redundancy (HSR)";
        case ETHER_TYPE_ECTP:
            return "Ethernet Configuration Testing Protocol[12]";
        case ETHER_TYPE_VLAN_D_T:
            return "VLAN-tagged (IEEE 802.1Q) frame with double tagging";
        case ETHER_TYPE_REDUNDANCY_TAG:
            return "Redundancy Tag (IEEE 802.1CB Frame Replication and Elimination for Reliability)";
        default:
            return "Unknown ether type, may not a ether package";
    }
}
