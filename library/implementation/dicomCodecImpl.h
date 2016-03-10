/*
$fileHeader$
*/

/*! \file dicomCodec.h
    \brief Declaration of the class dicomCodec.

*/

#if !defined(imebraDicomCodec_CC44A2C5_2B8C_42c1_9704_3F9C582643B9__INCLUDED_)
#define imebraDicomCodec_CC44A2C5_2B8C_42c1_9704_3F9C582643B9__INCLUDED_

#include "codecImpl.h"
#include "dataImpl.h"
#include "dataSetImpl.h"
#include "streamControllerImpl.h"

/// \def IMEBRA_DATASET_MAX_DEPTH
/// \brief Max number of datasets embedded into each 
///        others.
///
/// This value is used to prevent a stack when reading a
///  malformed dataset that has too many datasets embedded
///   into each others.
///
///////////////////////////////////////////////////////////
#define IMEBRA_DATASET_MAX_DEPTH 16 


namespace imebra
{

namespace implementation
{

namespace codecs
{

/// \addtogroup group_codecs
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief The Dicom codec.
///
/// This class is used to decode and encode a DICOM stream.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dicomCodec : public codec
{
public:
	// Get an image from a dicom structure
	///////////////////////////////////////////////////////////
    virtual std::shared_ptr<image> getImage(const dataSet& dataset, std::shared_ptr<streamReader> pSourceStream, const std::string& dataType);

	// Write an image into a dicom structure
	///////////////////////////////////////////////////////////
	virtual void setImage(
		std::shared_ptr<streamWriter> pDestStream,
		std::shared_ptr<image> pImage,
        const std::string& transferSyntax,
        imageQuality_t imageQuality,
        const std::string& dataType,
		std::uint8_t allocatedBits,
		bool bSubSampledX,
		bool bSubSampledY,
		bool bInterleaved,
		bool b2Complement);

	// Create another dicom codec
	///////////////////////////////////////////////////////////
	virtual std::shared_ptr<codec> createCodec();

	/// \brief Parse the dicom stream and fill the data set
	///        with the read tags.
	///
	/// This function doesn't parse the 128 bytes preamble and
	///  the DICM signature, which has to be parsed by the
	///  calling function.
	///
	/// @param pStream    The stream do decode
	/// @param pDataSet   A pointer to the data set to fill
	///                    with the decoded tags
	/// @param bExplicitDataType true if the stream is encoded
	///                    with explicit data type, false
	///                    otherwise.
	///                   Even when this parameter is set,
	///                    the function will automatically
	///                    switch this parameter if a mismatch
	///                    is detected during the decoding
	///                    procedure
	/// @param endianType The stream's endian type.
	///                   Even when this parameter is set,
	///                    the function will automatically
	///                    switch this parameter if a mismatch
	///                    is detected during the decoding
	///                    procedure
	/// @param subItemLength the number of bytes to parse.
	///                   If this parameter is set to
	///                    0xffffffff then the function will
	///                    stop parsing at the end of the
	///                    sequence or at the end of the file
	/// @param maxSizeBufferLoad if a loaded buffer is exceedes
	///                    the size in the parameter then it is
	///                    not loaded immediatly but it will be
	///                    loaded on demand. Some codecs may
	///                    ignore this parameter.
	///                   Set to -1 to load all the buffers
	///                    immediatly
	/// @param pReadSubItemLength a pointer to a std::uint32_t
	///                    that the function will fill with
	///                    the number of bytes read
	/// @param depth      the current dataSet depth:
	///                    - 0 = root dataset
	///                    - >=1 = dataset embedded into 
	///                      another dataset. This value is
	///                      used to prevent a stack overflow
	///
	///////////////////////////////////////////////////////////
	void parseStream(
		std::shared_ptr<streamReader> pStream,
		std::shared_ptr<dataSet> pDataSet,
		bool bExplicitDataType,
		streamController::tByteOrdering endianType,
		std::uint32_t maxSizeBufferLoad = 0xffffffff,
		std::uint32_t subItemLength = 0xffffffff,
		std::uint32_t* pReadSubItemLength = 0,
		std::uint32_t depth = 0);

	/// \brief Write the dataSet to the specified stream
	///         in Dicom format, without the file header and
	///         signature.
	///
	/// @param pStream   the destination stream
	/// @param pDataSet  the dataSet to be written
	/// @param bExplicitDataType true if the function must
	///                   write the data type, false if
	///                   the data type is implicit
	/// @param endianType the endian type to be generated
	///
	///////////////////////////////////////////////////////////
	void buildStream(std::shared_ptr<streamWriter> pStream, std::shared_ptr<dataSet> pDataSet, bool bExplicitDataType, streamController::tByteOrdering endianType);

	// Returns true if the codec can handle the transfer
	//  syntax
	///////////////////////////////////////////////////////////
    virtual bool canHandleTransferSyntax(const std::string& transferSyntax) const;

	// Returns true if the transfer syntax has to be
	//  encapsulated
	//
	///////////////////////////////////////////////////////////
    virtual bool encapsulated(const std::string& transferSyntax) const;

	// Returns the suggested allocated bits
	///////////////////////////////////////////////////////////
    virtual std::uint32_t suggestAllocatedBits(const std::string& transferSyntax, std::uint32_t highBit) const;

protected:
	// Write a dicom stream
	///////////////////////////////////////////////////////////
	virtual void writeStream(std::shared_ptr<streamWriter> pStream, std::shared_ptr<dataSet> pDataSet);

	// Load a dicom stream
	///////////////////////////////////////////////////////////
	virtual void readStream(std::shared_ptr<streamReader> pStream, std::shared_ptr<dataSet> pDataSet, std::uint32_t maxSizeBufferLoad = 0xffffffff);

protected:
	// Read a single tag
	///////////////////////////////////////////////////////////
    std::uint32_t readTag(std::shared_ptr<streamReader> pStream, std::shared_ptr<dataSet> pDataSet, std::uint32_t tagLengthDWord, std::uint16_t tagId, std::uint16_t order, std::uint16_t tagSubId, const std::string& tagType, streamController::tByteOrdering endianType, size_t wordSize, std::uint32_t bufferId, std::uint32_t maxSizeBufferLoad = 0xffffffff);

	// Calculate the tag's length
	///////////////////////////////////////////////////////////
    std::uint32_t getTagLength(const std::shared_ptr<data>& pData, bool bExplicitDataType, std::uint32_t* pHeaderLength, bool *pbSequence) const;

	// Calculate the group's length
	///////////////////////////////////////////////////////////
    std::uint32_t getGroupLength(const dataSet::tTags tags, bool bExplicitDataType) const;

	// Calculate the dataset's length
	///////////////////////////////////////////////////////////
    std::uint32_t getDataSetLength(std::shared_ptr<dataSet>, bool bExplicitDataType) const;

	// Write a single group
	///////////////////////////////////////////////////////////
    void writeGroup(std::shared_ptr<streamWriter> pDestStream, const dataSet::tTags& tags, std::uint16_t groupId, bool bExplicitDataType, streamController::tByteOrdering endianType);

	// Write a single tag
	///////////////////////////////////////////////////////////
	void writeTag(std::shared_ptr<streamWriter> pDestStream, std::shared_ptr<data> pData, std::uint16_t tagId, bool bExplicitDataType, streamController::tByteOrdering endianType);

	// Read an uncompressed interleaved image
	///////////////////////////////////////////////////////////
	void readUncompressedInterleaved(
		std::uint32_t channelsNumber,
		bool bSubSampledX,
		bool bSubSampledY,
		streamReader* pSourceStream,
		std::uint8_t wordSizeBytes,
		std::uint8_t allocatedBits,
		std::uint32_t mask
		);

	// Write an uncompressed interleaved image
	///////////////////////////////////////////////////////////
	void writeUncompressedInterleaved(
		std::uint32_t channelsNumber,
		bool bSubSampledX,
		bool bSubSampledY,
		streamWriter* pDestStream,
		std::uint8_t wordSizeBytes,
		std::uint8_t allocatedBits,
		std::uint32_t mask
		);

	// Read an uncompressed not interleaved image
	///////////////////////////////////////////////////////////
	void readUncompressedNotInterleaved(
		std::uint32_t channelsNumber,
		streamReader* pSourceStream,
		std::uint8_t wordSizeBytes,
		std::uint8_t allocatedBits,
		std::uint32_t mask
		);

	// Write an uncompressed not interleaved image
	///////////////////////////////////////////////////////////
	void writeUncompressedNotInterleaved(
		std::uint32_t channelsNumber,
		streamWriter* pDestStream,
		std::uint8_t wordSizeBytes,
		std::uint8_t allocatedBits,
		std::uint32_t mask
		);

	// Write an RLE compressed image
	///////////////////////////////////////////////////////////
	void writeRLECompressed(
		std::uint32_t imageWidth,
		std::uint32_t imageHeight,
		std::uint32_t channelsNumber,
		streamWriter* pDestStream,
		std::uint8_t allocatedBits,
		std::uint32_t mask
		);

    // Write RLE sequence of different bytes
    ///////////////////////////////////////////////////////////
    size_t writeRLEDifferentBytes(std::vector<std::uint8_t>* pDifferentBytes, streamWriter* pDestStream, bool bWrite);

	// Read an RLE compressed image
	///////////////////////////////////////////////////////////
	void readRLECompressed(
		std::uint32_t imageWidth,
		std::uint32_t imageHeight,
		std::uint32_t channelsNumber,
		streamReader* pSourceStream,
		std::uint8_t allocatedBits,
		std::uint32_t mask,
		bool bInterleaved);


	// Read a single pixel of a RAW dicom image
	///////////////////////////////////////////////////////////
	void readPixel(
					streamReader* pSourceStream,
					std::int32_t* pDest,
					std::uint32_t numPixels,
					std::uint8_t* bitPointer,
					std::uint8_t* pReadBuffer,
					const std::uint8_t wordSizeBytes,
					const std::uint8_t allocatedBits,
					const std::uint32_t mask);

	// Write a single pixel of a RAW dicom image
	///////////////////////////////////////////////////////////
	void writePixel(
					streamWriter* pDestStream,
					std::int32_t pixelValue,
					std::uint8_t*  pBitPointer,
					std::uint8_t wordSizeBytes,
					std::uint8_t allocatedBits,
					std::uint32_t mask);

	// Flush the unwritten bytes of an uncompressed image
	///////////////////////////////////////////////////////////
	void flushUnwrittenPixels(streamWriter* pDestStream, std::uint8_t* pBitPointer, std::uint8_t wordSizeBytes);

	std::uint32_t m_ioDWord;
    std::uint16_t m_ioWord;
	std::uint8_t  m_ioByte;

	void allocChannels(std::uint32_t channelsNumber, std::uint32_t width, std::uint32_t height, bool bSubSampledX, bool bSubSampledY);

	typedef std::shared_ptr<channel> ptrChannel;
	std::vector<ptrChannel> m_channels;
};


/// @}

} // namespace codecs

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDicomCodec_CC44A2C5_2B8C_42c1_9704_3F9C582643B9__INCLUDED_)
