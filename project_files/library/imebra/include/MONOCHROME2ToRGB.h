/*
$fileHeader$
*/

/*! \file MONOCHROME2ToRGB.h
    \brief Declaration of the class MONOCHROME2ToRGB.

*/

#if !defined(imebraMONOCHROME2ToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraMONOCHROME2ToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "colorTransform.h"


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

///////////////////////////////////////////////////////////
/// \brief Transforms an image from the colorspace 
///         MONOCHROME2 into the color space RGB.
///
/// The input image has to have the colorspace MONOCHROME2,
///  while the output image is created by the transform
///  and will have the colorspace RGB.
///
///////////////////////////////////////////////////////////
class MONOCHROME2ToRGB: public colorTransform
{
public:
	virtual std::wstring getInitialColorSpace();
	virtual std::wstring getFinalColorSpace();
	virtual ptr<colorTransform> createColorTransform();

        DEFINE_RUN_TEMPLATE_TRANSFORM;

        template <class inputType, class outputType>
        void templateTransform(
            inputType* inputHandlerData, size_t /* inputHandlerSize */, imbxUint32 inputHandlerWidth, const std::wstring& inputHandlerColorSpace,
            ptr<palette> /* inputPalette */,
            imbxInt32 inputHandlerMinValue, imbxUint32 inputHandlerNumValues,
            imbxInt32 inputTopLeftX, imbxInt32 inputTopLeftY, imbxInt32 inputWidth, imbxInt32 inputHeight,
            outputType* outputHandlerData, size_t /* outputHandlerSize */, imbxInt32 outputHandlerWidth, const std::wstring& outputHandlerColorSpace,
            ptr<palette> /* outputPalette */,
            imbxInt32 outputHandlerMinValue, imbxUint32 outputHandlerNumValues,
            imbxInt32 outputTopLeftX, imbxInt32 outputTopLeftY)

        {
            checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);

            inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            pInputMemory += inputTopLeftY * inputHandlerWidth + inputTopLeftX;
            pOutputMemory += (outputTopLeftY * outputHandlerWidth + outputTopLeftX) * 3;

            outputType outputValue;

            if(inputHandlerNumValues == outputHandlerNumValues)
            {
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        outputValue = (outputType)((imbxInt32)*(pInputMemory++) - inputHandlerMinValue + outputHandlerMinValue);
                        *pOutputMemory = outputValue;
                        *++pOutputMemory = outputValue;
                        *++pOutputMemory = outputValue;
                        ++pOutputMemory;
                    }
                    pInputMemory += inputHandlerWidth - inputWidth;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }
            else
            {
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        outputValue = (outputType)((((imbxInt32)*(pInputMemory++) - inputHandlerMinValue) * outputHandlerNumValues) / inputHandlerNumValues + outputHandlerMinValue);
                        *pOutputMemory = outputValue;
                        *++pOutputMemory = outputValue;
                        *++pOutputMemory = outputValue;
                        ++pOutputMemory;
                    }
                    pInputMemory += inputHandlerWidth - inputWidth;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }
        }

};

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraMONOCHROME2ToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)