#include "../include/imebra/memory.h"

#include "../implementation/memoryImpl.h"

namespace imebra
{



ReadMemory::ReadMemory(): m_pMemory(std::make_shared<const implementation::memory>())
{
}

ReadMemory::ReadMemory(const char* buffer, size_t bufferSize):
    m_pMemory(std::make_shared<const implementation::memory>(new implementation::stringUint8((const std::uint8_t*)buffer, bufferSize)))
{
}

ReadMemory::ReadMemory(const ReadMemory &right): m_pMemory(right.m_pMemory)
{
}

ReadMemory::ReadMemory(std::shared_ptr<const implementation::memory> pMemory): m_pMemory(pMemory)
{
}

ReadMemory::~ReadMemory()
{
}

ReadMemory& ReadMemory::operator=(const ReadMemory& right)
{
    m_pMemory = right.m_pMemory;
    return *this;
}

size_t ReadMemory::size() const
{
    return m_pMemory->size();
}

const char* ReadMemory::data() const
{
    return (const char*)(m_pMemory->data());
}

bool ReadMemory::empty() const
{
    return m_pMemory->empty();
}





ReadWriteMemory::ReadWriteMemory(): ReadMemory()
{
}

ReadWriteMemory::ReadWriteMemory(size_t initialSize)
{
    m_pMemory = std::make_shared<const implementation::memory>(initialSize);
}

ReadWriteMemory::ReadWriteMemory(const char* buffer, size_t bufferSize)
{
    m_pMemory = std::make_shared<const implementation::memory>(new implementation::stringUint8((const std::uint8_t*)buffer, bufferSize));
}

ReadWriteMemory::ReadWriteMemory(const ReadWriteMemory &right)
{
    m_pMemory = right.m_pMemory;
}

ReadWriteMemory::ReadWriteMemory(std::shared_ptr<implementation::memory> pMemory)
{
    m_pMemory = pMemory;
}

ReadWriteMemory& ReadWriteMemory::operator=(const ReadWriteMemory& right)
{
    m_pMemory = right.m_pMemory;
    return *this;
}

void ReadWriteMemory::copyFrom(const ReadMemory& sourceMemory)
{
    std::const_pointer_cast<implementation::memory>(m_pMemory)->copyFrom(sourceMemory.m_pMemory);
}

void ReadWriteMemory::copyFrom(const ReadWriteMemory& sourceMemory)
{
    std::const_pointer_cast<implementation::memory>(m_pMemory)->copyFrom(sourceMemory.m_pMemory);
}

void ReadWriteMemory::clear()
{
    std::const_pointer_cast<implementation::memory>(m_pMemory)->clear();
}

void ReadWriteMemory::resize(size_t newSize)
{
    std::const_pointer_cast<implementation::memory>(m_pMemory)->resize(newSize);
}

void ReadWriteMemory::reserve(size_t reserveSize)
{
    std::const_pointer_cast<implementation::memory>(m_pMemory)->reserve(reserveSize);
}

char* ReadWriteMemory::data()
{
    return (char*)(std::const_pointer_cast<implementation::memory>(m_pMemory)->data());
}

void ReadWriteMemory::assign(const char* pSource, const size_t sourceLength)
{
    std::const_pointer_cast<implementation::memory>(m_pMemory)->assign((const std::uint8_t*)pSource, sourceLength);
}


void MemoryPool::flush()
{
    implementation::memoryPoolGetter::getMemoryPoolLocal().flush();
}

void MemoryPool::setMemoryPoolSize(size_t minMemoryBlockSize, size_t maxMemoryPoolSize)
{
    implementation::memoryPoolGetter::getMemoryPoolLocal().setMinMaxMemory(minMemoryBlockSize, maxMemoryPoolSize);
}

}
