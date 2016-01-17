/*
$fileHeader$
*/

/*! \file streamController.cpp
    \brief Implementation of the streamController class.

*/

#include "streamControllerImpl.h"

namespace puntoexe
{

// Used for the endian check
///////////////////////////////////////////////////////////
static const std::uint16_t m_endianCheck(0x00ff);
static std::uint8_t const * const pBytePointer((std::uint8_t*)&m_endianCheck);
static const streamController::tByteOrdering m_platformByteOrder((*pBytePointer)==0xff ? streamController::lowByteEndian : streamController::highByteEndian);

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
streamController::streamController(size_t virtualStart /* =0 */, size_t virtualLength /* =0 */):
	m_bJpegTags(false),
        m_dataBuffer(size_t(IMEBRA_STREAM_CONTROLLER_MEMORY_SIZE), 0),
		m_virtualStart(virtualStart),
		m_virtualLength(virtualLength),
        m_dataBufferStreamPosition(0),
        m_dataBufferCurrent(0), m_dataBufferEnd(0)
{
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
streamController::~streamController()
{
}


///////////////////////////////////////////////////////////
//
// Retrieve the current position
//
///////////////////////////////////////////////////////////
size_t streamController::position()
{
    return m_dataBufferStreamPosition + m_dataBufferCurrent;
}


///////////////////////////////////////////////////////////
//
// Retrieve the position without considering the virtual
//  start's position
//
///////////////////////////////////////////////////////////
size_t streamController::getControlledStreamPosition()
{
    return m_dataBufferStreamPosition + m_dataBufferCurrent + m_virtualStart;
}


///////////////////////////////////////////////////////////
//
// Adjust the byte ordering of pBuffer
//
///////////////////////////////////////////////////////////
void streamController::adjustEndian(std::uint8_t* pBuffer, const size_t wordLength, const tByteOrdering endianType, const size_t words /* =1 */)
{
	if(endianType == m_platformByteOrder || wordLength<2L)
	{
		return;
	}

	switch(wordLength)
	{
	case 2:
        {
            std::uint16_t* pWord((std::uint16_t*)pBuffer);
            for(size_t scanWords = words; scanWords != 0; --scanWords)
            {
                *pWord = ((*pWord & 0x00ff) << 8) | ((*pWord & 0xff00) >> 8);
                ++pWord;
			}
		}
		return;
	case 4:
        {
            std::uint32_t* pDWord((std::uint32_t*)pBuffer);
            for(size_t scanWords = words; scanWords != 0; --scanWords)
            {
                *pDWord = ((*pDWord & 0xff000000) >> 24) | ((*pDWord & 0x00ff0000) >> 8) | ((*pDWord & 0x0000ff00) << 8) | ((*pDWord & 0x000000ff) << 24);
                ++pDWord;
			}
		}
		return;
	}
}

std::uint16_t streamController::adjustEndian(std::uint16_t buffer, const tByteOrdering endianType)
{
    if(endianType == m_platformByteOrder)
    {
        return buffer;
    }
    return ((buffer & 0xff00) >> 8) | ((buffer & 0xff) << 8);
}

std::uint32_t streamController::adjustEndian(std::uint32_t buffer, const tByteOrdering endianType)
{
    if(endianType == m_platformByteOrder)
    {
        return buffer;
    }
    return ((buffer & 0xff000000) >> 24) | ((buffer & 0x00ff0000) >> 8) | ((buffer & 0x0000ff00) << 8) | ((buffer & 0x000000ff) << 24);
}




} // namespace puntoexe
