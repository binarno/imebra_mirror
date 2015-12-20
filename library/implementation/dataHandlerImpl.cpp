/*
$fileHeader$
*/

/*! \file dataHandler.cpp
    \brief Implementation of the base class for the data handlers.

*/

#include "exceptionImpl.h"
#include "dataHandlerImpl.h"

namespace puntoexe
{

namespace imebra
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// imebraDataHandler
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
dataHandler::dataHandler(const uint8_t paddingByte): m_paddingByte(paddingByte)
{

}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Disconnect the handler
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
dataHandler::~dataHandler()
{
    if(m_commitMemory != 0)
    {
        lockObject lockAccess(m_buffer.get());

        charsetsList::tCharsetsList temporaryCharsets;
        m_buffer->getCharsetsList(&temporaryCharsets);
        charsetsList::updateCharsets(&m_commitCharsetsList, &temporaryCharsets);

        // The buffer's size must be an even number
        ///////////////////////////////////////////////////////////
        std::uint32_t memorySize = m_commitMemory->size();
        if((memorySize & 0x1) != 0)
        {
            m_commitMemory->resize(++memorySize);
            *(m_commitMemory->data() + (memorySize - 1)) = m_paddingByte;
        }

        m_buffer->commit(m_commitMemory, m_bufferType, temporaryCharsets);
    }
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve an element's size
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataHandler::getUnitSize() const
{
	return 0;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the padding byte
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint8_t dataHandler::getPaddingByte() const
{
    return m_paddingByte;
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the data 's type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string dataHandler::getDataType() const
{
	return m_bufferType;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Parse the buffer's content
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandler::parseBuffer(const std::uint8_t* pBuffer, const std::uint32_t bufferLength)
{
	PUNTOEXE_FUNCTION_START(L"dataHandler::parseBuffer");

	ptr<memory> tempMemory(memoryPool::getMemoryPool()->getMemory(bufferLength));
	if(pBuffer && bufferLength)
	{
		tempMemory->assign(pBuffer, bufferLength);
	}
	parseBuffer(tempMemory);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the date
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandler::getDate(const std::uint32_t /* index */,
		std::int32_t* pYear, 
		std::int32_t* pMonth, 
		std::int32_t* pDay, 
		std::int32_t* pHour, 
		std::int32_t* pMinutes,
		std::int32_t* pSeconds,
		std::int32_t* pNanoseconds,
		std::int32_t* pOffsetHours,
		std::int32_t* pOffsetMinutes) const
{
	*pYear = 0;
	*pMonth = 0;
	*pDay = 0;
	*pHour = 0;
	*pMinutes = 0;
	*pSeconds = 0;
	*pNanoseconds = 0;
	*pOffsetHours = 0;
	*pOffsetMinutes = 0;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the date
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandler::setDate(const std::uint32_t /* index */,
		std::int32_t /* year */, 
		std::int32_t /* month */, 
		std::int32_t /* day */, 
		std::int32_t /* hour */, 
		std::int32_t /*minutes */,
		std::int32_t /*seconds */,
		std::int32_t /*nanoseconds */,
		std::int32_t /*offsetHours */,
		std::int32_t /*offsetMinutes */)
{
	return;
}

void dataHandler::setCharsetsList(charsetsList::tCharsetsList* /* pCharsetsList */)
{
	// Intentionally empty
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe