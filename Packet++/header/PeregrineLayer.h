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
		uint32_t	ipSrcAddr;
		uint8_t		ipProto;
		uint32_t	length;
		uint64_t	timestamp;
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

		/**
		* @return IpSrcAddr
		*/
		/* uint32_t getIpSrcAddr() const; */
		IPv4Address getIpSrcAddr() const {
			return getPeregrineHeader()->ipSrcAddr;
		}

		/**
		* @return IpProto
		*/
		uint8_t getIpProto() const;

		/**
		* @return length
		*/
		uint32_t getLength() const;

		/**
		* @return timestamp
		*/
		uint64_t getTimestamp() const;

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
