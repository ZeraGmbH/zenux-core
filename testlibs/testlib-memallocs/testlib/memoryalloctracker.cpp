#include "memoryalloctracker.h"
#include "memoryallocbacktracegenerator.h"

MemoryAllocTracker::MemoryAllocTracker()
{
}

MemoryAllocTracker::MemoryAllocTracker(std::unique_ptr<MemoryAllocatorFunctionPtrCache> allocFuncPtrCache) :
    m_allocFuncPtrCache(std::move(allocFuncPtrCache))
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
    BacktraceRaw btrace;
    MemoryAllocBacktraceGenerator::createBacktraceRaw(&btrace, m_allocFuncPtrCache.get());
    m_allocatedRegions[allocatedMemory] = { size, btrace };
    stopIgnoreMallocFrees();
}

void MemoryAllocTracker::handleFree(const void *allocatedMemory)
{
    startIgnoreMallocFrees();
    m_allocatedRegions.remove(allocatedMemory);
    stopIgnoreMallocFrees();
}

const MemoryChunksAllocated MemoryAllocTracker::getRawMemRegions()
{
    return m_allocatedRegions.values();
}
