#ifndef MEMORYALLOCTRACKER_H
#define MEMORYALLOCTRACKER_H

#include "allocationdatadefinitions.h"

class MemoryAllocTracker
{
public:
    MemoryAllocTracker();
    virtual ~MemoryAllocTracker();
    void start();
    void stop();
    void clear();

    void handleMalloc(size_t size, const void* allocatedMemory);
    void handleFree(const void* allocatedMemory);

    int getAllocCount() const;
    AllocatedWithBacktracesRaw getAllocationsRaw();
    AllocatedWithBacktraces getAllocationsTimeSorted();
};

void setTracker(MemoryAllocTracker* tracker);
void startIgnoreMallocFrees();
void stopIgnoreMallocFrees();

#endif // MEMORYALLOCTRACKER_H
