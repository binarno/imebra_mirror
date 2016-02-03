/*
$fileHeader$
*/

/*! \file image_swig.h
    \brief Declaration of the class image for SWIG.

*/

#if !defined(imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
#define imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "definitions.h"
#include "dataHandler.h"

namespace imebra
{
namespace implementation
{
class image;
}
}
#endif

namespace imebra
{

class IMEBRA_API Image
{
public:

    /// \brief Define the size (in bytes) of a each pixel's
    ///        color component and its representation
    ///        (signed/unsigned)
	///
	///////////////////////////////////////////////////////////
    enum class bitDepth
	{
        depthU8 = 0,    ///< Unsigned byte
        depthS8 = 1,    ///< Signed byte
        depthU16 = 2,   ///< Unsigned word (2 bytes)
        depthS16 = 3,   ///< Signed word (2 bytes)
        depthU32 = 4,   ///< Unsigned double word (4 bytes)
        depthS32 = 5    ///< Signed double word (4 bytes)
	};

	// Constructor
	///////////////////////////////////////////////////////////
	Image();

	Image(const Image& right);

	Image& operator=(const Image& right);

#ifndef SWIG
    Image(std::shared_ptr<imebra::implementation::image> pImage);
#endif

    WritingDataHandler create(
        const std::uint32_t sizeX,
        const std::uint32_t sizeY,
		const bitDepth depth,
        const std::string& colorSpace,
        const std::uint32_t highBit);

    void setHighBit(std::uint32_t highBit);

    double getSizeMmY() const;
    double getSizeMmX() const;

	void setSizeMm(const double sizeX, const double sizeY);

    std::uint32_t getSizeX() const;
    std::uint32_t getSizeY() const;

    ReadingDataHandler getReadingDataHandler() const;
    WritingDataHandler getWritingDataHandler();

    std::string getColorSpace() const;

    std::uint32_t getChannelsNumber() const;

    bitDepth getDepth() const;

    std::uint32_t getHighBit() const;

#ifndef SWIG
    std::shared_ptr<imebra::implementation::image> m_pImage;
#endif

};

}

#endif // !defined(imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
