/*
$fileHeader$
*/

/*! \file dicomDir.cpp
    \brief Implementation of the classes that parse/create a DICOMDIR
        structure (DicomDir and DicomDirEntry).

*/

#include "../include/imebra/dicomDirEntry.h"
#include "../include/imebra/dataSet.h"
#include "../implementation/dicomDirImpl.h"

namespace imebra
{

DicomDirEntry::DicomDirEntry(const DataSet& fromDataSet, directoryRecordType_t entryType):
    m_pDirectoryRecord(std::make_shared<imebra::implementation::directoryRecord>(fromDataSet.m_pDataSet))
{
    m_pDirectoryRecord->setType(entryType);
}

DicomDirEntry::DicomDirEntry(std::shared_ptr<imebra::implementation::directoryRecord> pDirectoryRecord): m_pDirectoryRecord(pDirectoryRecord)
{
}

DicomDirEntry::~DicomDirEntry()
{
}

DataSet* DicomDirEntry::getEntryDataSet()
{
    return new DataSet(m_pDirectoryRecord->getRecordDataSet());
}

DicomDirEntry* DicomDirEntry::getNextEntry()
{
    return new DicomDirEntry(m_pDirectoryRecord->getNextRecord());
}

DicomDirEntry* DicomDirEntry::getFirstChildEntry()
{
    return new DicomDirEntry(m_pDirectoryRecord->getFirstChildRecord());
}
	
void DicomDirEntry::setNextEntry(const DicomDirEntry& nextEntry)
{
    m_pDirectoryRecord->setNextRecord(nextEntry.m_pDirectoryRecord);
}

void DicomDirEntry::setFirstChildEntry(const DicomDirEntry& firstChildEntry)
{
    m_pDirectoryRecord->setFirstChildRecord(firstChildEntry.m_pDirectoryRecord);
}

fileParts_t DicomDirEntry::getFileParts() const
{
    return m_pDirectoryRecord->getFileParts();
}

void DicomDirEntry::setFileParts(const fileParts_t& fileParts)
{
    m_pDirectoryRecord->setFileParts(fileParts);
}

directoryRecordType_t DicomDirEntry::getType() const
{
    return m_pDirectoryRecord->getType();
}

std::string DicomDirEntry::getTypeString() const
{
    return m_pDirectoryRecord->getTypeString();
}


}
