/*
$fileHeader$
*/

/*! \file dataHandlerStringAE.h
    \brief Declaration of the class dataHandlerStringAE.

*/

#if !defined(imebraDataHandlerStringAE_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringAE_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringImpl.h"
#include <map>
#include <string>


///////////////////////////////////////////////////////////
//
// Everything is in the namespace imebra::implementation
//
///////////////////////////////////////////////////////////
namespace imebra
{

namespace implementation
{

namespace handlers
{


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Handles the Dicom data type "AE" (application
///         entity
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringAE : public readingDataHandlerString
{
public:
    readingDataHandlerStringAE(const memory& parseMemory);
};

class writingDataHandlerStringAE: public writingDataHandlerString
{
public:
    writingDataHandlerStringAE(const std::shared_ptr<buffer>& pBuffer);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringAE_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
