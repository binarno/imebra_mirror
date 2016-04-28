/*
$fileHeader$
*/

/*! \file drawBitmap.h
    \brief Declaration of the class DrawBitmap.

*/

#if !defined(imebraDrawBitmap__INCLUDED_)
#define imebraDrawBitmap__INCLUDED_

#include <memory>
#include "definitions.h"
#include "readWriteMemory.h"

#ifndef SWIG
namespace imebra
{
namespace implementation
{
class drawBitmap;
}

}
#endif

namespace imebra
{

class TransformsChain;
class Image;

///
/// \brief DrawBitmap takes care of converting an Image object into an array
///        of bytes that can be displayed by the operating system facilities.
/// 
/// DrawBitmap can apply several transformations to the Image before generating
/// the bitmap.
/// 
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DrawBitmap
{
    DrawBitmap(const DrawBitmap&) = delete;
    DrawBitmap& operator=(const DrawBitmap&) = delete;

public:
    /// \brief Construct a DrawBitmap with no transforms.
    /// 
    /// The getBitmap() method will not apply any Transform to the Image before
    /// generating the bitmap.
    /// 
    ///////////////////////////////////////////////////////////////////////////////
    DrawBitmap();

    /// \brief Construct a DrawBitmap object that always apply the transforms in
    ///        the specified TransformsChain before calculating the bitmap of the
    ///        Image in the getBitmap() method.
    ///
    /// \param transformsChain the transforms to apply to the Image in the
    ///        getBitmap() method
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DrawBitmap(const TransformsChain& transformsChain);

    /// \brief Destructor
    ///
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~DrawBitmap();

    /// \brief Apply the transforms defined in the constructor (if any) to the
    ///        input image, then calculate an array of bytes containing a bitmap
    ///        that can be rendered by the operating system.
    ///
    /// \param Image          the image for which the bitmap must be calculated
    /// \param drawBitmapType the type of bitmap to generate
    /// \param rowAlignBytes  the number of bytes on which the bitmap rows are
    ///                       aligned
    /// \param buffer         a pointer to the pre-allocated buffer where
    ///                       getBitmap() will store the generated bitmap
    /// \param bufferSize     the size of the allocated buffer
    /// \return the number of bytes occupied by the bitmap in the pre-allocated
    ///         buffer. If the number of occupied bytes is bigger than the value
    ///         of the parameter bufferSize then the method doesn't generate
    ///         the bitmap
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t getBitmap(const Image& image, drawBitmapType_t drawBitmapType, std::uint32_t rowAlignBytes, char* buffer, size_t bufferSize);

    /// \brief Apply the transforms defined in the constructor (if any) to the
    ///        input image, then calculate an array of bytes containing a bitmap
    ///        that can be rendered by the operating system.
    ///
    /// \param Image          the image for which the bitmap must be calculated
    /// \param drawBitmapType the type of bitmap to generate
    /// \param rowAlignBytes  the number of bytes on which the bitmap rows are
    ///                       aligned
    /// \return a ReadWriteMemory object referencing the buffer containing the
    ///         generated bitmap
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadWriteMemory* getBitmap(const Image& image, drawBitmapType_t drawBitmapType, std::uint32_t rowAlignBytes);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::drawBitmap> m_pDrawBitmap;
#endif

};

}

#endif // !defined(imebraDrawBitmap__INCLUDED_)