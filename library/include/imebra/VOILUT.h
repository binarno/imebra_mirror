/*
$fileHeader$
*/

/*! \file VOILUT.h
    \brief Declaration of the class VOILUT.

*/

#if !defined(imebraVOILUT__INCLUDED_)
#define imebraVOILUT__INCLUDED_

#include "transform.h"
#include "definitions.h"

namespace imebra
{

class DataSet;
class LUT;

///
/// \brief A VOILUT transform enhances the visibility of a specific range of
///        brightness in an image.
///
///
/// VOILUTSequence_0028_3010
/// DataSet::getVOIs() and applied with setCenterWidth().
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API VOILUT: public Transform
{
    VOILUT(const VOILUT&) = delete;
    VOILUT& operator=(const VOILUT&) = delete;

public:
    /// \brief Constructor.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    VOILUT();

    /// \brief Find the optimal VOI settings for a specific image's area and apply
    ///        it with setCenterWidth().
    ///
    /// \param inputImage   the image to analyze
    /// \param topLeftX     the horizontal coordinate of the top-left angle of the
    ///                     area to analyze
    /// \param topLeftY     the vertical coordinate of the top-left angle of the
    ///                     area to analyze
    /// \param width        the width of the area to analyze
    /// \param height       the height of the area to analyze
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void applyOptimalVOI(const Image& inputImage, std::uint32_t topLeftX, std::uint32_t topLeftY, std::uint32_t width, std::uint32_t height);

    /// \brief Set the VOI settings applied by the transform.
    ///
    /// \param center the VOI center
    /// \param width  the VOI width
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setCenterWidth(double center, double width);

    /// \brief Set the LUT that will be used by the transform to enhance the
    ///        contrast.
    ///
    /// The LUTs to be used for the VOILUT transform are stored in the DataSet's
    /// sequence tagId_t::VOILUTSequence_0028_3010.
    /// Each item in the sequence stores the a single LUT.
    ///
    /// Use DataSet::getLUT() to retrieve the LUT from the DataSet.
    ///
    /// \param lut  the LUT to apply
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setLUT(const LUT& lut);

    /// \brief Retrieve the VOI center applied by the transform.
    ///
    /// \return the VOI center applied by the transform
    ///
    ///////////////////////////////////////////////////////////////////////////////
    double getCenter() const;

    /// \brief Retrieve the VOI width applied by the transform.
    ///
    /// \return the VOI width applied by the transform
    ///
    ///////////////////////////////////////////////////////////////////////////////
    double getWidth() const;


};

}

#endif // imebraVOILUT__INCLUDED_
