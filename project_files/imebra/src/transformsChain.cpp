/*
$fileHeader$
*/

/*! \file transformsChain.cpp
    \brief Implementation of the class transformsChain.

*/

#include "../../base/include/exception.h"
#include "../include/transformsChain.h"
#include "../include/image.h"
#include "../include/dataSet.h"

namespace puntoexe
{

namespace imebra
{

namespace transforms
{



transformsChain::transformsChain():
        m_inputWidth(0),
        m_inputHeight(0),
	m_inputDepth(image::endOfDepths),
	m_inputHighBit(0),
	m_outputDepth(image::endOfDepths),
	m_outputHighBit(0)
{}

///////////////////////////////////////////////////////////
//
// Add a new transform to the chain
//
///////////////////////////////////////////////////////////
void transformsChain::addTransform(ptr<baseTransform> pTransform)
{
	PUNTOEXE_FUNCTION_START(L"transformsChain::addTransform");

	// Store the transform in the chain.
	///////////////////////////////////////////////////////////
	m_transformsList.push_back(pTransform);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Returns true if no transform has been defined
//
///////////////////////////////////////////////////////////
bool transformsChain::isEmpty()
{
	return m_transformsList.empty();
}


void transformsChain::runTransform(
            const ptr<image>& inputImage,
            imbxUint32 inputTopLeftX, imbxUint32 inputTopLeftY, imbxUint32 inputWidth, imbxUint32 inputHeight,
            const ptr<image>& outputImage,
            imbxUint32 outputTopLeftX, imbxUint32 outputTopLeftY)
{
	if(isEmpty())
	{
		throw transformsChainEmptyChainException("Empty transforms chain");
	}

	if(m_transformsList.size() == 1)
	{
		m_transformsList.front()->runTransform(inputImage, inputTopLeftX, inputTopLeftY, inputWidth, inputHeight,
			outputImage, outputTopLeftX, outputTopLeftY);
		return;
	}

	// Get the position of the last transform
	///////////////////////////////////////////////////////////
	tTransformsList::iterator lastTransform(m_transformsList.end());
	--lastTransform;

	std::wstring inputColorSpace(inputImage->getColorSpace());
	image::bitDepth inputDepth(inputImage->getDepth());
	imbxUint32 inputHighBit(inputImage->getHighBit());
	std::wstring outputColorSpace(outputImage->getColorSpace());
	image::bitDepth outputDepth(outputImage->getDepth());
	imbxUint32 outputHighBit(outputImage->getHighBit());
	if(
		m_inputWidth != inputWidth ||
		m_inputHeight != inputHeight ||
		m_inputColorSpace != inputColorSpace ||
		m_inputDepth != inputDepth ||
		m_inputHighBit != inputHighBit ||
		m_outputColorSpace != outputColorSpace ||
		m_outputDepth != outputDepth ||
		m_outputHighBit != outputHighBit)
	{
		m_inputWidth = inputWidth;
		m_inputHeight = inputHeight;
		m_inputColorSpace = inputColorSpace;
		m_inputDepth = inputDepth;
		m_inputHighBit = inputHighBit;
		m_outputColorSpace = outputColorSpace;
		m_outputDepth = outputDepth;
		m_outputHighBit = outputHighBit;

		m_temporaryImages.clear();

		// Allocate temporary images
		///////////////////////////////////////////////////////////
		imbxUint32 allocateRows = 65536 / inputWidth;
		if(allocateRows < 1)
		{
			allocateRows = 1;
		}

		for(tTransformsList::iterator scanTransforms(m_transformsList.begin()); scanTransforms != lastTransform; ++scanTransforms)
		{
			if(scanTransforms == m_transformsList.begin())
			{
				m_temporaryImages.push_back((*scanTransforms)->allocateOutputImage(inputImage, inputWidth, allocateRows));
			}
			else
			{
				m_temporaryImages.push_back((*scanTransforms)->allocateOutputImage(m_temporaryImages.back(), inputWidth, allocateRows));
			}
		}
	}

	// Ron all the transforms. Split the images into several
	//  parts
	///////////////////////////////////////////////////////////
	while(inputHeight != 0)
	{
		imbxUint32 rows = 65536 / inputWidth;
		if(rows < 1)
		{
			rows = 1;
		}
		if(rows > inputHeight)
		{
			rows = inputHeight;
		}
		inputHeight -= rows;
		
		tTransformsList::iterator scanTransforms(m_transformsList.begin());
		tTemporaryImagesList::iterator scanTemporaryImages(m_temporaryImages.begin());
		
		(*scanTransforms)->runTransform(inputImage, inputTopLeftX, inputTopLeftY++, inputWidth, rows, *scanTemporaryImages, 0, 0);
		inputTopLeftY += rows;

		while(scanTransforms != lastTransform)
		{
			ptr<image> temporaryInput(*(scanTemporaryImages++));
			ptr<image> temporaryOutput(*scanTemporaryImages);

			(*scanTransforms)->runTransform(temporaryInput, 0, 0, inputWidth, 1, temporaryOutput, 0, 0);

			++scanTransforms;
		}
		
		(*lastTransform)->runTransform(*scanTemporaryImages, 0, 0, inputWidth, rows, outputImage, outputTopLeftX, outputTopLeftY);
		outputTopLeftY += rows;
	}
}


/// \brief Allocate an output image that is compatible with
///         the transform given the specified input image.
///
///////////////////////////////////////////////////////////
ptr<image> transformsChain::allocateOutputImage(ptr<image> pInputImage, imbxUint32 width, imbxUint32 height)
{
	if(isEmpty())
	{
		throw transformsChainEmptyChainException("Empty transforms chain");
	}

	if(m_transformsList.size() == 1)
	{
		return m_transformsList.front()->allocateOutputImage(pInputImage, width, height);
	}

	// Get the position of the last transform
	///////////////////////////////////////////////////////////
	tTransformsList::iterator lastTransform(m_transformsList.end());
	--lastTransform;

	ptr<image> temporaryImage;

	for(tTransformsList::iterator scanTransforms(m_transformsList.begin()); scanTransforms != lastTransform; ++scanTransforms)
	{
		if(scanTransforms == m_transformsList.begin())
		{
			temporaryImage = (*scanTransforms)->allocateOutputImage(pInputImage, 1, 1);
		}
		else
		{
			ptr <image> newImage( (*scanTransforms)->allocateOutputImage(temporaryImage, 1, 1) );
			temporaryImage = newImage;
		}
	}
	return (*lastTransform)->allocateOutputImage(temporaryImage, width, height);


}


} // namespace transforms

} // namespace imebra

} // namespace puntoexe
