/*
$fileHeader$
*/

/*! \file streamReader_swig.cpp
    \brief Implementation of the the class used to read the streams for SWIG.

*/

#include "../include/imebra/streamReader.h"
#include "../implementation/streamReaderImpl.h"

namespace imebra
{

StreamReader::StreamReader(const BaseStream& stream): m_pReader(new puntoexe::streamReader(stream.m_pStream))
{
}


StreamReader::StreamReader(const BaseStream& stream, int virtualStart, int virtualLength): m_pReader(new puntoexe::streamReader(stream.m_pStream, virtualStart, virtualLength))
{
}

StreamReader::StreamReader(const StreamReader& right): m_pReader(right.m_pReader)
{
}

StreamReader& StreamReader::operator=(const StreamReader& right)
{
    m_pReader = right.m_pReader;
    return *this;
}

}