#ifndef PACKETPP_PEREGRINE_LAYER
#define PACKETPP_PEREGRINE_LAYER

#include "IpAddress.h"
#include "Layer.h"

/// @file

/**
 * \namespace pcpp
 * \brief The main namespace for the PcapPlusPlus lib
 */
namespace pcpp
{

	/**
	 * @struct peregrinehdr
	 * Represents a PEREGRINE protocol header
	 */
#pragma pack(push, 1)
	struct peregrinehdr {
		uint32_t 	decay;
		uint32_t 	macIpSrcPktCnt;
		uint32_t 	macIpSrcPktLen;
		uint32_t 	macIpSrcSs;
		uint32_t 	macIpSrcMean;
		uint32_t 	macIpSrcStdDev;
		uint32_t 	ipSrcTsDiff;
		uint32_t 	ipSrcPktCnt;
		uint32_t 	ipSrcPktLen;
		uint32_t 	ipSrcSs;
		uint32_t 	ipSrcMean;
		uint32_t 	ipSrcStdDev;
		uint32_t 	ipPktCnt;
		uint32_t 	ipSs0;
		uint32_t 	ipSs1;
		uint32_t 	ipMean0;
		uint32_t 	ipPktCnt1;
		uint32_t 	ipMean1;
		uint32_t 	ipStdDev0;
		uint32_t 	ipMagnitude;
		uint32_t 	ipRadius;
		uint32_t 	fiveTPktCnt;
		uint32_t 	fiveTSs0;
		uint32_t 	fiveTSs1;
		uint32_t 	fiveTMean0;
		uint32_t 	fiveTPktCnt1;
		uint32_t 	fiveTMean1;
		uint32_t 	fiveTStdDev0;
		uint32_t 	fiveTMagnitude;
		uint32_t 	fiveTRadius;
		uint64_t 	ipSumResProdCov;
		uint64_t 	ipPcc;
		uint64_t 	fiveTSumResProdCov;
		uint64_t 	fiveTPcc;
	};
#pragma pack(pop)

	/**
	 * @class PeregrineLayer
	 * Represents a Peregrine protocol layer.
	 */
	class PeregrineLayer : public Layer {
	public:
		/**
		 * A constructor that creates the layer from an existing packet raw data
		 * @param[in] data A pointer to the raw data (will be casted to @ref peregrinehdr)
		 * @param[in] dataLen Size of the data in bytes
		 * @param[in] prevLayer A pointer to the previous layer
		 * @param[in] packet A pointer to the Packet instance where layer will be stored in
		 */
		PeregrineLayer(uint8_t* data, size_t dataLen, Layer* prevLayer, Packet* packet) : Layer(data, dataLen, prevLayer, packet) {
			m_Protocol = Peregrine;
			m_DataLen = sizeof(peregrinehdr);
		}

		static bool isPeregrineProto(uint8_t proto) {
			return proto == 253;
		}

		/**
		 * Get a pointer to the Peregrine header. Notice this points directly to the data, so every change will change the actual packet data
		 * @return A pointer to the @ref peregrinehdr
		 */
		inline peregrinehdr* getPeregrineHeader() const {
			return (peregrinehdr*)m_Data;
		}

		// return hdr fields

		uint32_t getDecay() const;
		uint32_t getMacIpSrcPktCnt() const;
		uint32_t getMacIpSrcPktLen() const;
		uint32_t getMacIpSrcSs() const;
		uint32_t getMacIpSrcMean() const;
		uint32_t getMacIpSrcStdDev() const;
		uint32_t getIpSrcTsDiff() const;
		uint32_t getIpSrcPktCnt() const;
		uint32_t getIpSrcPktLen() const;
		uint32_t getIpSrcSs() const;
		uint32_t getIpSrcMean() const;
		uint32_t getIpSrcStdDev() const;
		uint32_t getIpPktCnt() const;
		uint32_t getIpSs0() const;
		uint32_t getIpSs1() const;
		uint32_t getIpMean0() const;
		uint32_t getIpPktCnt1() const;
		uint32_t getIpMean1() const;
		uint32_t getIpStdDev0() const;
		uint32_t getIpMagnitude() const;
		uint32_t getIpRadius() const;
		uint32_t getFiveTPktCnt() const;
		uint32_t getFiveTSs0() const;
		uint32_t getFiveTSs1() const;
		uint32_t getFiveTMean0() const;
		uint32_t getFiveTPktCnt1() const;
		uint32_t getFiveTMean1() const;
		uint32_t getFiveTStdDev0() const;
		uint32_t getFiveTMagnitude() const;
		uint32_t getFiveTRadius() const;
		uint64_t getIpSumResProdCov() const;
		uint64_t getIpPcc() const;
		uint64_t getFiveTSumResProdCov() const;
		uint64_t getFiveTPcc() const;

		// implement abstract methods

		void ToStructuredOutput(std::ostream &os) const;

		/**
		 * Does nothing for this layer (PeregrineLayer is always last)
		 */
		void parseNextLayer() {}

		/**
		 * @return The size of @ref peregrinehdr
		 */
		size_t getHeaderLen() const {
			return sizeof(peregrinehdr);
		}

		void computeCalculateFields();

		std::string toString() const;

		OsiModelLayer getOsiModelLayer() const { return OsiModelTransportLayer; }

		static bool isDataValid(const uint8_t *data, size_t dataLen) {
			return dataLen >= sizeof(peregrinehdr);
		}
	};

} // namespace pcpp
#endif /* PACKETPP_PEREGRINE_LAYER */
