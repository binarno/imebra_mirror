/*
$fileHeader$
*/

/*! \file memoryPool.h
    \brief Declaration of the class MemoryPool.

*/

#if !defined(imebraMemoryPool__INCLUDED_)
#define imebraMemoryPool__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
class memoryPool;
}
}
#endif

namespace imebra
{

///
/// \brief Used by Imebra to allocate memory.
///
/// MemoryPool keeps around recently deleted memory regions so they can be
/// repurposed quickly when new memory regions are requested.
///
/// Each thread has its own MemoryPool object.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API MemoryPool
{
public:
    /// \brief Release all the unused memory regions.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    static void flush();

    /// \brief Set the maximum size of the kept unused memory.
    ///
    /// \param minMemoryBlockSize  if a memory region is smaller than this size
    ///                            then when it is released it is deleted
    ///                            immediately, otherwise it is kept in the memory
    ///                            pool
    /// \param maxMemoryPoolSize   the maximum size of the sum of all the unused
    ///                            memory regions. When the total size of the
    ///                            unused memory regions is greater than this
    ///                            parameter then the oldest memory regions are
    ///                            deleted permanently
    ///
    ///////////////////////////////////////////////////////////////////////////////
    static void setMemoryPoolSize(size_t minMemoryBlockSize, size_t maxMemoryPoolSize);
};

}

#endif // !defined(imebraMemoryPool__INCLUDED_)