#include "memoryalloctracker.h"
#include "backtracerawtools.h"
#include <QHash>


static QHash<const void*, AllocatedWithBacktraceRaw> rawAllocations;
static bool cacheDirty = true;
static QList<AllocatedWithBacktraces> allocationsCached;


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
    cacheDirty = true;
}

int MemoryAllocTracker::getAllocCount() const
{
    return rawAllocations.size();
}

void MemoryAllocTracker::handleMalloc(size_t size, const void *allocatedMemory)
{
    startIgnoreMallocFrees();
    cacheDirty = true;
    AllocBacktraceRaw btrace;
    BacktraceRawTools::fillBacktraceRaw(&btrace);
    rawAllocations[allocatedMemory] = { size, btrace };
    stopIgnoreMallocFrees();
}

void MemoryAllocTracker::handleFree(const void *allocatedMemory)
{
    startIgnoreMallocFrees();
    cacheDirty = true;
    rawAllocations.remove(allocatedMemory);
    stopIgnoreMallocFrees();
}

const AllocatedWithBacktracesRaw MemoryAllocTracker::getRawAllocations()
{
    return rawAllocations.values();
}
