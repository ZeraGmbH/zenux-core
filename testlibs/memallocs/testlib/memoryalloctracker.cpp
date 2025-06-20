#include "memoryalloctracker.h"
#include "backtracerawtools.h"
#include "backtraceconverter.h"

static quint64 currentAllocationNumber = 0;

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
    m_rawAllocations.clear();
}

int MemoryAllocTracker::getAllocCount() const
{
    return m_rawAllocations.size();
}

void MemoryAllocTracker::handleMalloc(size_t size, const void *allocatedMemory)
{
    if (allocatedMemory == nullptr)
        return;
    startIgnoreMallocFrees();
    AllocBacktraceRaw btrace;
    BacktraceRawTools::fillBacktraceRaw(&btrace);
    m_rawAllocations[allocatedMemory] = { currentAllocationNumber, size, btrace };
    currentAllocationNumber++;
    stopIgnoreMallocFrees();
}

void MemoryAllocTracker::handleFree(const void *allocatedMemory)
{
    if (allocatedMemory == nullptr)
        return;
    startIgnoreMallocFrees();
    m_rawAllocations.remove(allocatedMemory);
    stopIgnoreMallocFrees();
}

AllocatedWithBacktracesRaw MemoryAllocTracker::getAllocationsRaw()
{
    return m_rawAllocations.values();
}

AllocatedWithBacktraces MemoryAllocTracker::getAllocationsTimeSorted()
{
    return BacktraceConverter::allocsRawToAllocsTimeSorted(getAllocationsRaw());
}
