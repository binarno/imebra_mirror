/*
$fileHeader$
*/

/// \file writingDataHandlerNumeric.h
/// \brief Declaration of the class WritingDataHandlerNumeric.
///
///////////////////////////////////////////////////////////////////////////////

#if !defined(imebraWritingDataHandlerNumeric__INCLUDED_)
#define imebraWritingDataHandlerNumeric__INCLUDED_

#include <string>
#include <memory>
#include "definitions.h"
#include "readWriteMemory.h"
#include "writingDataHandler.h"

#ifndef SWIG

namespace imebra
{
namespace implementation
{
namespace handlers
{
class writingDataHandlerNumericBase;
}
}
}

#endif


namespace imebra
{

class ReadingDataHandlerNumeric;

///
/// \brief Specialized WritingDataHandler for numeric data types.
///
/// Includes few methods that allow to access the raw memory containing the
/// buffer's data.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API WritingDataHandlerNumeric: public WritingDataHandler
{
    WritingDataHandlerNumeric(const WritingDataHandlerNumeric&) = delete;
    WritingDataHandlerNumeric& operator=(const WritingDataHandlerNumeric&) = delete;

#ifndef SWIG
    friend class Image;
    friend class DataSet;
    friend class Tag;
    friend class ReadingDataHandlerNumeric;
private:
    WritingDataHandlerNumeric(std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> pDataHandler);
#endif

public:

    virtual ~WritingDataHandlerNumeric();

    /// \brief Return a ReadWriteMemory object referencing the raw buffer's data.
    ///
    /// \return a ReadWriteMemory object referencing the raw buffer's data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadWriteMemory* getMemory() const;

    /// \brief Copy the content of the specified buffer into the content managed
    ///        by data handler.
    ///
    /// \param source     a pointer to the source memory buffer
    /// \param sourceSize the number of bytes to copy and the new memory size
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void assign(const char* source, size_t sourceSize);

#ifndef SWIG
    /// \brief Returns a pointer to the buffer's raw memory content.
    ///
    /// The referenced buffer is owned by the WritingDataHandlerNumeric
    /// object and must not be freed by the client.
    ///
    /// \param pDataSize a variable that will contain the raw memory's size in
    ///                  bytes
    /// \return a pointer to the buffer's raw memory. The referenced buffer
    ///         is owned by the WritingDataHandlerNumeric object and must not be
    ///         freed by the client
    ///
    ///////////////////////////////////////////////////////////////////////////////
    char* data(size_t* pDataSize) const;
#endif

    /// \brief Copies the raw memory content into the specified buffer.
    ///
    /// If the allocated buffer is not large enough then the method doesn't
    ///  copy any data and just returns the required buffer' size.
    ///
    /// \param destination     a pointer to the allocated buffer
    /// \param destinationSize the size of the allocated buffer, in bytes
    /// \return the number of bytes to be copied into the pre-allocated buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t data(char* destination, size_t destinationSize) const;

    /// \brief Returns the number of bytes occupied by the numbers handled by the
    ///        data handler
    ///
    /// \return the number of bytes occupied by the numbers handled by the data
    ///         handler
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t getUnitSize() const;

    /// \brief Returns true if the numbers handled by the data handler are signed,
    ///        false otherwise.
    ///
    /// \return true if the numbers handled by the data handler are signed, false
    ///         otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    bool isSigned() const;

    /// \brief Copies data from another data handler, converting the data type
    ///        if necessary.
    ///
    /// The data handler is resized to the same size of the source data handler.
    ///
    /// \param source the data handler from which the data must be copied
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void copyFrom(const ReadingDataHandlerNumeric& source);
};

}

#endif // !defined(imebraWritingDataHandlerNumeric__INCLUDED_)
