#include "memoryalloctracker.h"

MemoryAllocTracker::MemoryAllocTracker()
{
}

MemoryAllocTracker::~MemoryAllocTracker()
{
    stop();
}

void MemoryAllocTracker::start()
{
    setTracker(this);
}

void MemoryAllocTracker::stop()
{
    setTracker(nullptr);
}

void MemoryAllocTracker::clear()
{
    m_allocatedRegions.clear();
}

int MemoryAllocTracker::getAllocCount() const
{
    return m_allocatedRegions.size();
}

void MemoryAllocTracker::handleMalloc(size_t size, const void *allocatedMemory)
{
    startIgnoreMallocFrees();
    MemoryAllocBacktraceGenerator::BacktraceRaw btrace;
    MemoryAllocBacktraceGenerator::createBacktraceRaw(&btrace);
    m_allocatedRegions[allocatedMemory] = { size, btrace };
    stopIgnoreMallocFrees();
}

void MemoryAllocTracker::handleFree(const void *allocatedMemory)
{
    startIgnoreMallocFrees();
    m_allocatedRegions.remove(allocatedMemory);
    stopIgnoreMallocFrees();
}

const MemoryAllocTracker::MemsAllocated MemoryAllocTracker::getRawMemRegions()
{
    return m_allocatedRegions.values();
}
