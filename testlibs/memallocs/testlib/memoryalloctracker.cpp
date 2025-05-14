#include "memoryalloctracker.h"
#include "backtracerawtools.h"
#include "backtraceconverter.h"
#include <QHash>

static QHash<const void*, AllocatedWithBacktraceRaw> rawAllocations;
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
    rawAllocations.clear();
}

int MemoryAllocTracker::getAllocCount() const
{
    return rawAllocations.size();
}

void MemoryAllocTracker::handleMalloc(size_t size, const void *allocatedMemory)
{
    startIgnoreMallocFrees();
    AllocBacktraceRaw btrace;
    BacktraceRawTools::fillBacktraceRaw(&btrace);
    rawAllocations[allocatedMemory] = { currentAllocationNumber, size, btrace };
    currentAllocationNumber++;
    stopIgnoreMallocFrees();
}

void MemoryAllocTracker::handleFree(const void *allocatedMemory)
{
    startIgnoreMallocFrees();
    rawAllocations.remove(allocatedMemory);
    stopIgnoreMallocFrees();
}

AllocatedWithBacktracesRaw MemoryAllocTracker::getAllocationsRaw()
{
    return rawAllocations.values();
}

AllocatedWithBacktraces MemoryAllocTracker::getAllocationsTimeSorted()
{
    return BacktraceConverter::allocsRawToAllocsTimeSorted(getAllocationsRaw());
}
