#define LOG_MODULE PacketLogModulePeregrineLayer

#include "PeregrineLayer.h"
#include "EthLayer.h"
#include <string.h>
#include "EndianPortable.h"
#include <sstream>

namespace pcpp {


uint32_t PeregrineLayer::getDecay() const { return getPeregrineHeader()->decay; }
uint32_t PeregrineLayer::getMacIpSrcPktCnt() const { return getPeregrineHeader()->macIpSrcPktCnt; }
uint32_t PeregrineLayer::getMacIpSrcPktLen() const { return getPeregrineHeader()->macIpSrcPktLen; }
uint32_t PeregrineLayer::getMacIpSrcSs() const { return getPeregrineHeader()->macIpSrcSs; }
uint32_t PeregrineLayer::getMacIpSrcMean() const { return getPeregrineHeader()->macIpSrcMean; }
uint32_t PeregrineLayer::getMacIpSrcStdDev() const { return getPeregrineHeader()->macIpSrcStdDev; }
uint32_t PeregrineLayer::getIpSrcTsDiff() const { return getPeregrineHeader()->ipSrcTsDiff; }
uint32_t PeregrineLayer::getIpSrcPktCnt() const { return getPeregrineHeader()->ipSrcPktCnt; }
uint32_t PeregrineLayer::getIpSrcPktLen() const { return getPeregrineHeader()->ipSrcPktLen; }
uint32_t PeregrineLayer::getIpSrcSs() const { return getPeregrineHeader()->ipSrcSs; }
uint32_t PeregrineLayer::getIpSrcMean() const { return getPeregrineHeader()->ipSrcMean; }
uint32_t PeregrineLayer::getIpSrcStdDev() const { return getPeregrineHeader()->ipSrcStdDev; }
uint32_t PeregrineLayer::getIpPktCnt() const { return getPeregrineHeader()->ipPktCnt; }
uint32_t PeregrineLayer::getIpSs0() const { return getPeregrineHeader()->ipSs0; }
uint32_t PeregrineLayer::getIpSs1() const { return getPeregrineHeader()->ipSs1; }
uint32_t PeregrineLayer::getIpMean0() const { return getPeregrineHeader()->ipMean0; }
uint32_t PeregrineLayer::getIpPktCnt1() const { return getPeregrineHeader()->ipPktCnt1; }
uint32_t PeregrineLayer::getIpMean1() const { return getPeregrineHeader()->ipMean1; }
uint32_t PeregrineLayer::getIpStdDev0() const { return getPeregrineHeader()->ipStdDev0; }
uint32_t PeregrineLayer::getIpMagnitude() const { return getPeregrineHeader()->ipMagnitude; }
uint32_t PeregrineLayer::getIpRadius() const { return getPeregrineHeader()->ipRadius; }
uint32_t PeregrineLayer::getFiveTPktCnt() const { return getPeregrineHeader()->fiveTPktCnt; }
uint32_t PeregrineLayer::getFiveTSs0() const { return getPeregrineHeader()->fiveTSs0; }
uint32_t PeregrineLayer::getFiveTSs1() const { return getPeregrineHeader()->fiveTSs1; }
uint32_t PeregrineLayer::getFiveTMean0() const { return getPeregrineHeader()->fiveTMean0; }
uint32_t PeregrineLayer::getFiveTPktCnt1() const { return getPeregrineHeader()->fiveTPktCnt1; }
uint32_t PeregrineLayer::getFiveTMean1() const { return getPeregrineHeader()->fiveTMean1; }
uint32_t PeregrineLayer::getFiveTStdDev0() const { return getPeregrineHeader()->fiveTStdDev0; }
uint32_t PeregrineLayer::getFiveTMagnitude() const { return getPeregrineHeader()->fiveTMagnitude; }
uint32_t PeregrineLayer::getFiveTRadius() const { return getPeregrineHeader()->fiveTRadius; }
uint64_t PeregrineLayer::getIpSumResProdCov() const { return getPeregrineHeader()->ipSumResProdCov; }
uint64_t PeregrineLayer::getIpPcc() const { return getPeregrineHeader()->ipPcc; }
uint64_t PeregrineLayer::getFiveTSumResProdCov() const { return getPeregrineHeader()->fiveTSumResProdCov; }
uint64_t PeregrineLayer::getFiveTPcc() const { return getPeregrineHeader()->fiveTPcc; }

void PeregrineLayer::ToStructuredOutput(std::ostream &os) const {
	os << "PROTOCOL TYPE: Peregrine" << '\n';
	os << "Decay: " << getDecay() << '\n';
	os << "MAC IP src pkt cnt: " << getMacIpSrcPktCnt() << '\n';
	os << "MAC IP src pkt len: " << getMacIpSrcPktLen() << '\n';
	os << "MAC IP src ss" << getMacIpSrcSs() << '\n';
	os << "MAC IP src mean" << getMacIpSrcMean() << '\n';
	os << "MAC IP src std dev" << getMacIpSrcStdDev() << '\n';
	os << "IP src ts diff: " << getIpSrcTsDiff() << '\n';
	os << "IP src pkt cnt: " << getIpSrcPktCnt() << '\n';
	os << "IP src pkt len: " << getIpSrcPktLen() << '\n';
	os << "IP src ss" << getIpSrcSs() << '\n';
	os << "IP src mean" << getIpSrcMean() << '\n';
	os << "IP src std dev" << getIpSrcStdDev() << '\n';
	os << "IP pkt cnt" << getIpPktCnt() << '\n';
	os << "IP ss 0" << getIpSs0() << '\n';
	os << "IP ss 1" << getIpSs1() << '\n';
	os << "IP mean 0" << getIpMean0() << '\n';
	os << "IP pkt cnt 1" << getIpPktCnt1() << '\n';
	os << "IP mean 1" << getIpMean1() << '\n';
	os << "IP std dev 0" << getIpStdDev0() << '\n';
	os << "IP magnitude" << getIpMagnitude() << '\n';
	os << "IP radius" << getIpRadius() << '\n';
	os << "5-tuple pkt cnt" << getFiveTPktCnt() << '\n';
	os << "5-tuple ss 0" << getFiveTSs0() << '\n';
	os << "5-tuple ss 1" << getFiveTSs1() << '\n';
	os << "5-tuple mean 0" << getFiveTMean0() << '\n';
	os << "5-tuple pkt cnt 1" << getFiveTPktCnt1() << '\n';
	os << "5-tuple mean 1" << getFiveTMean1() << '\n';
	os << "5-tuple std dev 0" << getFiveTStdDev0() << '\n';
	os << "5-tuple magnitude" << getFiveTMagnitude() << '\n';
	os << "5-tuple radius" << getFiveTRadius() << '\n';
	os << "IP sum res prod cov" << getIpSumResProdCov() << '\n';
	os << "IP pcc" << getIpPcc() << '\n';
	os << "5-tuple sum res prod cov" << getFiveTSumResProdCov() << '\n';
	os << "5-tuple pcc" << getFiveTPcc() << '\n';
	os << std::endl;
}

void PeregrineLayer::computeCalculateFields() {}

std::string PeregrineLayer::toString() const {
	std::stringstream stream;
	ToStructuredOutput(stream);
	return stream.str();
}

} // namespace pcpp
