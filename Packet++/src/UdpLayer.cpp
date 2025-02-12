#define LOG_MODULE PacketLogModuleUdpLayer

#include "EndianPortable.h"
#include "UdpLayer.h"
#include "PayloadLayer.h"
#include "IPv4Layer.h"
#include "IPv6Layer.h"
#include "DnsLayer.h"
#include "DhcpLayer.h"
#include "DhcpV6Layer.h"
#include "VxlanLayer.h"
#include "SipLayer.h"
#include "RadiusLayer.h"
#include "GtpLayer.h"
#include "NtpLayer.h"
#include "SomeIpLayer.h"
#include "WakeOnLanLayer.h"
#include "PacketUtils.h"
#include "Logger.h"
#include <string.h>
#include <sstream>
#include "PeregrineLayer.h"

namespace pcpp
{

UdpLayer::UdpLayer(uint16_t portSrc, uint16_t portDst)
{
	const size_t headerLen = sizeof(udphdr);
	m_DataLen = headerLen;
	m_Data = new uint8_t[headerLen];
	memset(m_Data, 0, headerLen);
	udphdr* udpHdr = (udphdr*)m_Data;
	udpHdr->portDst = htobe16(portDst);
	udpHdr->portSrc = htobe16(portSrc);
	m_Protocol = UDP;
}

uint16_t UdpLayer::getSrcPort() const
{
	return be16toh(getUdpHeader()->portSrc);
}

uint16_t UdpLayer::getDstPort() const
{
	return be16toh(getUdpHeader()->portDst);
}

uint16_t UdpLayer::calculateChecksum(bool writeResultToPacket)
{
	udphdr* udpHdr = (udphdr*)m_Data;
	uint16_t checksumRes = 0;
	uint16_t currChecksumValue = udpHdr->headerChecksum;

	if (m_PrevLayer != NULL)
	{
		udpHdr->headerChecksum = 0;
		ScalarBuffer<uint16_t> vec[2];
		PCPP_LOG_DEBUG("data len =  " << m_DataLen);
		vec[0].buffer = (uint16_t*)m_Data;
		vec[0].len = m_DataLen;

		if (m_PrevLayer->getProtocol() == IPv4)
		{
			uint32_t srcIP = ((IPv4Layer*)m_PrevLayer)->getSrcIPv4Address().toInt();
			uint32_t dstIP = ((IPv4Layer*)m_PrevLayer)->getDstIPv4Address().toInt();
			uint16_t pseudoHeader[6];
			pseudoHeader[0] = srcIP >> 16;
			pseudoHeader[1] = srcIP & 0xFFFF;
			pseudoHeader[2] = dstIP >> 16;
			pseudoHeader[3] = dstIP & 0xFFFF;
			pseudoHeader[4] = 0xffff & udpHdr->length;
			pseudoHeader[5] = htobe16(0x00ff & PACKETPP_IPPROTO_UDP);
			vec[1].buffer = pseudoHeader;
			vec[1].len = 12;
			checksumRes = computeChecksum(vec, 2);
			PCPP_LOG_DEBUG("calculated checksum = 0x" << std::uppercase << std::hex << checksumRes);
		}
		else if (m_PrevLayer->getProtocol() == IPv6)
		{
			uint16_t pseudoHeader[18];
			((IPv6Layer*)m_PrevLayer)->getSrcIPv6Address().copyTo((uint8_t*)pseudoHeader);
			((IPv6Layer*)m_PrevLayer)->getDstIPv6Address().copyTo((uint8_t*)(pseudoHeader+8));
			pseudoHeader[16] = 0xffff & udpHdr->length;
			pseudoHeader[17] = htobe16(0x00ff & PACKETPP_IPPROTO_UDP);
			vec[1].buffer = pseudoHeader;
			vec[1].len = 36;
			checksumRes = computeChecksum(vec, 2);
			PCPP_LOG_DEBUG("calculated checksum = 0x" << std::uppercase << std::hex << checksumRes);
		}
	}

	if (checksumRes == 0)
		checksumRes = 0xffff;

	if(writeResultToPacket)
		udpHdr->headerChecksum = htobe16(checksumRes);
	else
		udpHdr->headerChecksum = currChecksumValue;

	return checksumRes;
}

void UdpLayer::parseNextLayer()
{
	if (m_DataLen <= sizeof(udphdr))
		return;

	uint16_t portDst = getDstPort();
	uint16_t portSrc = getSrcPort();

	uint8_t* udpData = m_Data + sizeof(udphdr);
	size_t udpDataLen = m_DataLen - sizeof(udphdr);

	m_NextLayer = PeregrineLayer::isDataValid(udpData, udpDataLen)
			? static_cast<Layer*>(new PeregrineLayer(udpData, udpDataLen, this, m_Packet))
			: static_cast<Layer*>(new PayloadLayer(udpData, udpDataLen, this, m_Packet));
}

void UdpLayer::computeCalculateFields()
{
	udphdr* udpHdr = (udphdr*)m_Data;
	udpHdr->length = htobe16(m_DataLen);
	calculateChecksum(true);
}

std::string UdpLayer::toString() const
{
	std::ostringstream srcPortStream;
	srcPortStream << getSrcPort();
	std::ostringstream dstPortStream;
	dstPortStream << getDstPort();

	return "UDP Layer, Src port: " + srcPortStream.str() + ", Dst port: " + dstPortStream.str();
}

} // namespace pcpp
