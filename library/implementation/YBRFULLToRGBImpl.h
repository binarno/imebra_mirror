/*
$fileHeader$
*/

/*! \file YBRFULLToRGB.h
    \brief Declaration of the class YBRFULLToRGB.

*/

#if !defined(imebraYBRFULLToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraYBRFULLToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "colorTransformImpl.h"


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

namespace transforms
{

namespace colorTransforms
{

/// \addtogroup group_transforms
///
/// @{

///////////////////////////////////////////////////////////
/// \brief Transforms an image from the colorspace 
///         YBR_FULL into the color space RGB.
///
/// The input image has to have the colorspace YBR_FULL,
///  while the output image is created by the transform
///  and will have the colorspace RGB.
///
///////////////////////////////////////////////////////////
class YBRFULLToRGB: public colorTransform
{
public:
	virtual std::wstring getInitialColorSpace();
	virtual std::wstring getFinalColorSpace();
	virtual std::shared_ptr<colorTransform> createColorTransform();

        DEFINE_RUN_TEMPLATE_TRANSFORM;

        template <class inputType, class outputType>
        void templateTransform(
            inputType* inputHandlerData, size_t /* inputHandlerSize */, std::uint32_t inputHandlerWidth, const std::wstring& inputHandlerColorSpace,
            std::shared_ptr<palette> /* inputPalette */,
            std::int32_t inputHandlerMinValue, std::uint32_t inputHighBit,
            std::int32_t inputTopLeftX, std::int32_t inputTopLeftY, std::int32_t inputWidth, std::int32_t inputHeight,
            outputType* outputHandlerData, size_t /* outputHandlerSize */, std::int32_t outputHandlerWidth, const std::wstring& outputHandlerColorSpace,
            std::shared_ptr<palette> /* outputPalette */,
            std::int32_t outputHandlerMinValue, std::uint32_t outputHighBit,
            std::int32_t outputTopLeftX, std::int32_t outputTopLeftY)

        {
            checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);

            inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            pInputMemory += (inputTopLeftY * inputHandlerWidth + inputTopLeftX) * 3;
            pOutputMemory += (outputTopLeftY * outputHandlerWidth + outputTopLeftX) * 3;
            
            std::int32_t inputMiddleValue(inputHandlerMinValue + ((std::int32_t)1 << inputHighBit));
            std::int32_t sourceY, sourceB, sourceR, destination;

            std::int32_t inputHandlerNumValues = (std::int32_t)1 << (inputHighBit + 1);
            std::int32_t outputHandlerNumValues = (std::int32_t)1 << (outputHighBit + 1);

            if(inputHighBit > outputHighBit)
            {
                std::uint32_t rightShift = inputHighBit - outputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceY = (std::int32_t)( *(pInputMemory++) );
                        sourceB = (std::int32_t)( *(pInputMemory++) ) - inputMiddleValue;
                        sourceR = (std::int32_t)( *(pInputMemory++) ) - inputMiddleValue;

                        destination = sourceY + ((22970 * sourceR + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (std::int32_t)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination >> rightShift));
                        }

                        destination = sourceY - ((5638 * sourceB + 11700 * sourceR + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (std::int32_t)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination >> rightShift));
                        }

                        destination = sourceY + ((29032 * sourceB + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (std::int32_t)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination >> rightShift));
                        }
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }
            else
            {
                std::uint32_t leftShift = outputHighBit - inputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceY = (std::int32_t)( *(pInputMemory++) );
                        sourceB = (std::int32_t)( *(pInputMemory++) ) - inputMiddleValue;
                        sourceR = (std::int32_t)( *(pInputMemory++) ) - inputMiddleValue;

                        destination = sourceY + ((22970 * sourceR + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (std::int32_t)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination << leftShift));
                        }

                        destination = sourceY - ((5638 * sourceB + 11700 * sourceR + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (std::int32_t)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination << leftShift));
                        }

                        destination = sourceY + ((29032 * sourceB + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (std::int32_t)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination << leftShift));
                        }
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }
        }
};

/// @}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraYBRFULLToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
