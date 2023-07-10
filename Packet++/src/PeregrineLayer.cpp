#define LOG_MODULE PacketLogModulePeregrineLayer

#include "PeregrineLayer.h"
#include "EthLayer.h"
#include <string.h>
#include "EndianPortable.h"
#include <sstream>

namespace pcpp {

/* uint32_t PeregrineLayer::getIpSrcAddr() const { */
/* 	return getPeregrineHeader()->ipSrcAddr; */
/* } */

uint8_t PeregrineLayer::getIpProto() const {
	return getPeregrineHeader()->ipProto;
}

uint32_t PeregrineLayer::getLength() const {
	return getPeregrineHeader()->length;
}

uint64_t PeregrineLayer::getTimestamp() const {
	return getPeregrineHeader()->timestamp;
}

void PeregrineLayer::ToStructuredOutput(std::ostream &os) const {
	os << "PROTOCOL TYPE: Peregrine" << '\n';
	/* os << "IP src addr: " << (uint32_t)getIpSrcAddr() << '\n'; */
	os << "IP src proto: " << (uint32_t)getIpProto() << '\n';
	os << "Length: " << getLength() << '\n';
	os << "Timestamp: " << getTimestamp() << '\n';
	os << std::endl;
}

void PeregrineLayer::computeCalculateFields() {}

std::string PeregrineLayer::toString() const {
	std::stringstream stream;
	ToStructuredOutput(stream);
	return stream.str();
}

} // namespace pcpp
