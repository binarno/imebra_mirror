/*
$fileHeader$
*/

/*! \file buffer.cpp
    \brief Implementation of the buffer class.

*/

#include "exceptionImpl.h"
#include "streamReaderImpl.h"
#include "streamWriterImpl.h"
#include "bufferImpl.h"
#include "bufferStreamImpl.h"
#include "dataHandlerImpl.h"
#include "dataHandlerNumericImpl.h"
#include "dataHandlerStringAEImpl.h"
#include "dataHandlerStringASImpl.h"
#include "dataHandlerStringCSImpl.h"
#include "dataHandlerStringDSImpl.h"
#include "dataHandlerStringISImpl.h"
#include "dataHandlerStringLOImpl.h"
#include "dataHandlerStringLTImpl.h"
#include "dataHandlerStringPNImpl.h"
#include "dataHandlerStringSHImpl.h"
#include "dataHandlerStringSTImpl.h"
#include "dataHandlerStringUIImpl.h"
#include "dataHandlerStringUTImpl.h"
#include "dataHandlerDateImpl.h"
#include "dataHandlerDateTimeImpl.h"
#include "dataHandlerTimeImpl.h"
#include <vector>


namespace puntoexe
{

namespace imebra
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// imebraBuffer
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
// Buffer's constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
buffer::buffer(const ptr<baseObject>& externalLock, const std::string& defaultType /* ="" */):
	baseObject(externalLock),
		m_originalBufferPosition(0),
		m_originalBufferLength(0),
		m_originalWordLength(1),
        m_originalEndianType(streamController::lowByteEndian)
{
	PUNTOEXE_FUNCTION_START(L"buffer::buffer");

	// Set the buffer's type.
	// If the buffer's type is unspecified, then the buffer
	//  type is set to OB
	///////////////////////////////////////////////////////////
	if(defaultType.length()==2L)
		m_bufferType = defaultType;
	else
		m_bufferType = "OB";

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Buffer's constructor (on demand content)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
buffer::buffer(const ptr<baseObject>& externalLock,
		const std::string& defaultType,
		const ptr<baseStream>& originalStream,
		std::uint32_t bufferPosition,
		std::uint32_t bufferLength,
		std::uint32_t wordLength,
		streamController::tByteOrdering endianType):
	baseObject(externalLock),
		m_originalStream(originalStream),
		m_originalBufferPosition(bufferPosition),
		m_originalBufferLength(bufferLength),
		m_originalWordLength(wordLength),
        m_originalEndianType(endianType)
{
	PUNTOEXE_FUNCTION_START(L"buffer::buffer (on demand)");

	// Set the buffer's type.
	// If the buffer's type is unspecified, then the buffer
	//  type is set to OB
	///////////////////////////////////////////////////////////
	if(defaultType.length()==2L)
		m_bufferType = defaultType;
	else
		m_bufferType = "OB";

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a data handler and connect it to the buffer
// (raw or normal)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<handlers::dataHandler> buffer::getDataHandler(bool bWrite, bool bRaw, std::uint32_t size)
{
	PUNTOEXE_FUNCTION_START(L"buffer::getDataHandler");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	ptr<memory> localMemory(m_memory);

	// If the object must be loaded from the original stream,
	//  then load it...
	///////////////////////////////////////////////////////////
	if(m_originalStream != 0 && (localMemory == 0 || localMemory->empty()) )
	{
		localMemory = ptr<memory>(memoryPool::getMemoryPool()->getMemory(m_originalBufferLength));
		if(m_originalBufferLength != 0)
		{
			ptr<streamReader> reader(new streamReader(m_originalStream, m_originalBufferPosition, m_originalBufferLength));
			std::vector<std::uint8_t> localBuffer;
			localBuffer.resize(m_originalBufferLength);
			reader->read(&localBuffer[0], m_originalBufferLength);
			if(m_originalWordLength != 0)
			{
				reader->adjustEndian(&localBuffer[0], m_originalWordLength, m_originalEndianType, m_originalBufferLength/m_originalWordLength);
			}
			localMemory->assign(&localBuffer[0], m_originalBufferLength);
		}
	}

	// Reset the pointer to the data handler
	///////////////////////////////////////////////////////////
	ptr<handlers::dataHandler> handler;

	// Allocate a raw data handler if bRaw==true
	///////////////////////////////////////////////////////////
	if(bRaw)
	{
        handler = new handlers::dataHandlerRaw();
	}
	else
	{
		// Retrieve an Application entity handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="AE")
		{
            handler = new handlers::dataHandlerStringAE();
		}

		// Retrieve an Age string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="AS")
		{
            handler = new handlers::dataHandlerStringAS();
		}

		// Retrieve a Code string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="CS")
		{
            handler = new handlers::dataHandlerStringCS();
		}

		// Retrieve a Decimal string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="DS")
		{
            handler = new handlers::dataHandlerStringDS();
		}

		// Retrieve an Integer string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="IS")
		{
            handler = new handlers::dataHandlerStringIS();
		}

		// Retrieve a Long string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="LO")
		{
            handler = new handlers::dataHandlerStringLO();
		}

		// Retrieve a Long text data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="LT")
		{
            handler = new handlers::dataHandlerStringLT();
		}

		// Retrieve a Person Name data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="PN")
		{
            handler = new handlers::dataHandlerStringPN();
		}

		// Retrieve a Short string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="SH")
		{
            handler = new handlers::dataHandlerStringSH();
		}

		// Retrieve a Short text data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="ST")
		{
            handler = new handlers::dataHandlerStringST();
		}

		// Retrieve an Unique Identifier data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="UI")
		{
            handler = new handlers::dataHandlerStringUI();
		}

		// Retrieve an Unlimited text data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="UT")
		{
            handler = new handlers::dataHandlerStringUT();
		}

		// Retrieve an object handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="OB")
		{
            handler = new handlers::dataHandlerNumeric<std::uint8_t>();
		}

		// Retrieve a signed-byte object handler.
		// Non standard: used by the images handler.
		///////////////////////////////////////////////////////////
		if(m_bufferType=="SB")
		{
            handler = new handlers::dataHandlerNumeric<std::int8_t>();
		}

		// Retrieve an unknown object handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="UN")
		{
            handler = new handlers::dataHandlerNumeric<std::uint8_t>();
		}

		// Retrieve a WORD handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="OW")
		{
            handler = new handlers::dataHandlerNumeric<std::uint16_t>();
		}

		// Retrieve a WORD handler (AT)
		///////////////////////////////////////////////////////////
		if(m_bufferType=="AT")
		{
            handler = new handlers::dataHandlerNumeric<std::uint16_t>();
		}

		// Retrieve a float handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="FL")
		{
            handler = new handlers::dataHandlerNumeric<float>();
		}

		// Retrieve a double float handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="FD")
		{
            handler = new handlers::dataHandlerNumeric<double>();
		}

		// Retrieve a signed long handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="SL")
		{
            handler = new handlers::dataHandlerNumeric<std::int32_t>();
		}

		// Retrieve a signed short handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="SS")
		{
            handler = new handlers::dataHandlerNumeric<std::int16_t>();
		}

		// Retrieve an unsigned long handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="UL")
		{
            handler = new handlers::dataHandlerNumeric<std::uint32_t>();
		}

		// Retrieve an unsigned short handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="US")
		{
            handler = new handlers::dataHandlerNumeric<std::uint16_t>();
		}

		// Retrieve date
		///////////////////////////////////////////////////////////
		if(m_bufferType=="DA")
		{
            handler = new handlers::dataHandlerDate();
		}

		// Retrieve date-time
		///////////////////////////////////////////////////////////
		if(m_bufferType=="DT")
		{
            handler = new handlers::dataHandlerDateTime();
		}

		// Retrieve time
		///////////////////////////////////////////////////////////
		if(m_bufferType=="TM")
		{
            handler = new handlers::dataHandlerTime();
		}

	} // check bRaw

	// If an error occurred during the data handler creation,
	//  then throw an exception
	///////////////////////////////////////////////////////////
	if(handler == 0)
	{
		PUNTOEXE_THROW(bufferExceptionUnknownType, "Unknown data type requested");
	}

	//  Connect the handler to this buffer
	///////////////////////////////////////////////////////////
	if(localMemory == 0)
	{
		localMemory = ptr<memory>(new memory);
	}
	ptr<memory> parseMemory(localMemory);

	// Set the handler's attributes
	///////////////////////////////////////////////////////////
	if(bWrite)
	{
		handler->m_buffer = this;

		std::uint32_t currentMemorySize(localMemory->size());
                std::uint32_t newMemorySize(currentMemorySize);
		if(newMemorySize == 0)
		{
			newMemorySize = size * handler->getUnitSize();
		}
		parseMemory = memoryPool::getMemoryPool()->getMemory(newMemorySize);
		if(currentMemorySize != 0)
		{
			parseMemory->copyFrom(localMemory);
		}
	}

	handler->m_bufferType = m_bufferType;
	handler->setCharsetsList(&m_charsetsList);
	handler->parseBuffer(parseMemory);

	// Return the allocated handler
	///////////////////////////////////////////////////////////
	return handler;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a data handler and connect it to the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<handlers::dataHandler> buffer::getDataHandler(bool bWrite, std::uint32_t size)
{
	PUNTOEXE_FUNCTION_START(L"buffer::getDataHandler");

	return getDataHandler(bWrite, false, size);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a reading stream for the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<streamReader> buffer::getStreamReader()
{
	PUNTOEXE_FUNCTION_START(L"buffer::getStreamReader");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// If the object must be loaded from the original stream,
	//  then return the original stream
	///////////////////////////////////////////////////////////
	if(m_originalStream != 0 && (m_memory == 0 || m_memory->empty()) )
	{
		ptr<streamReader> reader(new streamReader(m_originalStream, m_originalBufferPosition, m_originalBufferLength));
		return reader;
	}


	// Build a stream from the buffer's memory
	///////////////////////////////////////////////////////////
	ptr<streamReader> reader;
	ptr<handlers::dataHandlerRaw> tempHandlerRaw = getDataHandlerRaw(false);
    if(tempHandlerRaw != 0 && tempHandlerRaw->getSize() != 0)
	{
		ptr<baseStream> localStream(new bufferStream(tempHandlerRaw));
		reader = ptr<streamReader>(new streamReader(localStream));
	}

	return reader;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a writing stream for the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<streamWriter> buffer::getStreamWriter()
{
    PUNTOEXE_FUNCTION_START(L"buffer::getStreamWriter");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// Build a stream from the buffer's memory
	///////////////////////////////////////////////////////////
	ptr<streamWriter> writer;
	ptr<handlers::dataHandlerRaw> tempHandlerRaw = getDataHandlerRaw(true);
	if(tempHandlerRaw != 0)
	{
		ptr<baseStream> localStream(new bufferStream(tempHandlerRaw));
		writer = ptr<streamWriter>(new streamWriter(localStream, tempHandlerRaw->getSize()));
	}

	return writer;

	PUNTOEXE_FUNCTION_END();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a raw data handler and connect it to the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<handlers::dataHandlerRaw> buffer::getDataHandlerRaw(bool bWrite, std::uint32_t size)
{
	PUNTOEXE_FUNCTION_START(L"buffer::getDataHandlerRaw");

	ptr<handlers::dataHandler> returnValue = getDataHandler(bWrite, true, size);
	return ptr<handlers::dataHandlerRaw>((handlers::dataHandlerRaw*)returnValue.get());

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
// Return the buffer's size in bytes
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t buffer::getBufferSizeBytes()
{
	PUNTOEXE_FUNCTION_START(L"buffer::getBufferSizeBytes");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	ptr<memory> localMemory(m_memory);

	// The buffer has not been loaded yet
	///////////////////////////////////////////////////////////
	if(m_originalStream != 0 && (m_memory == 0 || m_memory->empty()) )
	{
		return m_originalBufferLength;
	}

	// The buffer has no memory
	///////////////////////////////////////////////////////////
	if(m_memory == 0)
	{
		return 0;
	}

	// Return the memory's size
	///////////////////////////////////////////////////////////
	return m_memory->size();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
// Commit the changes made by copyBack
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void buffer::commit(ptr<memory> newMemory, const std::string& newBufferType, const charsetsList::tCharsetsList& newCharsetsList)
{
	PUNTOEXE_FUNCTION_START(L"buffer::commit");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// Commit the memory buffer
	///////////////////////////////////////////////////////////
    m_memory = newMemory;

	// Commit the buffer type
	///////////////////////////////////////////////////////////
    m_bufferType = newBufferType;

	// Commit the charsets
	///////////////////////////////////////////////////////////
    m_charsetsList = newCharsetsList;

	// The buffer has been updated and the original stream
	//  is still storing the old version. We don't need
	//  the original stream anymore, then release it.
	///////////////////////////////////////////////////////////
	ptr<baseStream> emptyBaseStream;
	m_originalStream = emptyBaseStream;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the data type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string buffer::getDataType()
{
	return std::string(m_bufferType);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the charsets used by the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void buffer::setCharsetsList(charsetsList::tCharsetsList* pCharsetsList)
{
	PUNTOEXE_FUNCTION_START(L"buffer::setCharsetsList");

	lockObject lockAccess(this);

	m_charsetsList.clear();
	charsetsList::updateCharsets(pCharsetsList, &m_charsetsList);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the charsets used by the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void buffer::getCharsetsList(charsetsList::tCharsetsList* pCharsetsList)
{
	PUNTOEXE_FUNCTION_START(L"buffer::getCharsetsList");

    pCharsetsList->insert(pCharsetsList->end(), m_charsetsList.begin(), m_charsetsList.end());

	PUNTOEXE_FUNCTION_END();
}


} // namespace imebra

} // namespace puntoexe
