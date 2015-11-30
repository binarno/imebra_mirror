/*
$fileHeader$
*/

/*! \file stream.cpp
    \brief Implementation of the stream class.

*/

#include "../include/exception.h"
#include "../include/stream.h"
#include "../include/charsetConversion.h"
#include <sstream>
#include <errno.h>

namespace puntoexe
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// Stream
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
// Destructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
stream::~stream()
{
    if(m_openFile != 0)
    {
        ::fclose(m_openFile);
        m_openFile = 0;
    }
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Open a file (ansi)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void stream::openFile(const std::string& fileName, const int mode)
{
	PUNTOEXE_FUNCTION_START(L"stream::openFile (ansi)");

	std::wstring wFileName;
	size_t fileNameSize(fileName.size());
	wFileName.resize(fileNameSize);
	for(size_t copyChars = 0; copyChars != fileNameSize; ++copyChars)
	{
		wFileName[copyChars] = (wchar_t)fileName[copyChars];
	}
	openFile(wFileName, mode);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Open a file (unicode)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void stream::openFile(const std::wstring& fileName, const int mode)
{
	PUNTOEXE_FUNCTION_START(L"stream::openFile (unicode)");

    close();

	std::wstring strMode;

	int tempMode = mode & (~std::ios::binary);

	if(tempMode == (int)(std::ios::in | std::ios::out))
	{
		strMode = L"r+";
	}

	if(tempMode == (int)(std::ios::in | std::ios::out | std::ios::app))
	{
		strMode = L"a+";
	}
	
	if(tempMode == (int)(std::ios::in | std::ios::out | std::ios::trunc))
	{
		strMode = L"w+";
	}
	
	if(tempMode == (int)(std::ios::out) || tempMode == (int)(std::ios::out | std::ios::trunc))
	{
		strMode = L"w";
	}
	
	if(tempMode == (int)(std::ios::out | std::ios::app))
	{
		strMode = L"a";
	}
	
	if(tempMode == (int)(std::ios::in))
	{
		strMode = L"r";
	}

	strMode += L"b";

#if defined(PUNTOEXE_WINDOWS)
	 errno_t errorCode = ::_wfopen_s(&m_openFile, fileName.c_str(), strMode.c_str());
	 if (errorCode != 0)
	 {
		 m_openFile = 0;
	 }
#else
	// Convert the filename to UTF8
    defaultCharsetConversion toUtf8("ISO-IR 192");
    std::string utf8FileName(toUtf8.fromUnicode(fileName));

	// Convert the filemode to UTF8
    std::string utf8Mode(toUtf8.fromUnicode(strMode));
	
	m_openFile = ::fopen(utf8FileName.c_str(), utf8Mode.c_str());
    int errorCode = errno;
#endif
	if(m_openFile == 0)
	{
        std::ostringstream errorMessage;
        errorMessage << "stream::openFile failure - error code: " << errorCode;
        PUNTOEXE_THROW(streamExceptionOpen, errorMessage.str());
	}

	PUNTOEXE_FUNCTION_END();
}

void stream::close()
{
    PUNTOEXE_FUNCTION_START(L"stream::close");

    if(m_openFile != 0)
    {
        if(::fclose(m_openFile) != 0)
        {
            PUNTOEXE_THROW(streamExceptionClose, "Error while closing the file");
        }
        m_openFile = 0;
    }

    PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Write raw data into the stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void stream::write(std::uint32_t startPosition, const std::uint8_t* pBuffer, std::uint32_t bufferLength)
{
	PUNTOEXE_FUNCTION_START(L"stream::write");

	lockObject lockThis(this);

	::fseek(m_openFile, startPosition, SEEK_SET);
	if(ferror(m_openFile) != 0)
	{
		PUNTOEXE_THROW(streamExceptionWrite, "stream::seek failure");
	}

	if(::fwrite(pBuffer, 1, bufferLength, m_openFile) != bufferLength)
	{
		PUNTOEXE_THROW(streamExceptionWrite, "stream::write failure");
	}

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Read raw data from the stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t stream::read(std::uint32_t startPosition, std::uint8_t* pBuffer, std::uint32_t bufferLength)
{
	PUNTOEXE_FUNCTION_START(L"stream::read");

	lockObject lockThis(this);

	::fseek(m_openFile, startPosition, SEEK_SET);
	if(ferror(m_openFile) != 0)
	{
		return 0;
	}

	std::uint32_t readBytes = (std::uint32_t)::fread(pBuffer, 1, bufferLength, m_openFile);
	if(ferror(m_openFile) != 0)
	{
		PUNTOEXE_THROW(streamExceptionRead, "stream::read failure");
	}
	return readBytes;

	PUNTOEXE_FUNCTION_END();
}


} // namespace puntoexe
