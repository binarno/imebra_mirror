/*
$fileHeader$
*/

/*! \file YBRPARTIALToRGB.cpp
    \brief Implementation of the class YBRPARTIALToRGB.

*/

#include "exceptionImpl.h"
#include "YBRPARTIALToRGBImpl.h"
#include "dataHandlerImpl.h"
#include "dataSetImpl.h"
#include "imageImpl.h"


namespace puntoexe
{

namespace imebra
{

namespace transforms
{

namespace colorTransforms
{

static registerColorTransform m_registerTransform(ptr<colorTransform>(new YBRPARTIALToRGB));

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring YBRPARTIALToRGB::getInitialColorSpace()
{
	return L"YBR_PARTIAL";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the final color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring YBRPARTIALToRGB::getFinalColorSpace()
{
	return L"RGB";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a new YBRPARTIALToRGB object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<colorTransform> YBRPARTIALToRGB::createColorTransform()
{
	return ptr<colorTransform>(new YBRPARTIALToRGB);
}




} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe
