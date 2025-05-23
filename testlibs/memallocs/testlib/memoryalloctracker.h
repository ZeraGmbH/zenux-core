#ifndef MEMORYALLOCTRACKER_H
#define MEMORYALLOCTRACKER_H

#include "allocationdatadefinitions.h"
#include <QHash>

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
private:
    QHash<const void*, AllocatedWithBacktraceRaw> rawAllocations;
};

void setTracker(MemoryAllocTracker* tracker);
void startIgnoreMallocFrees();
void stopIgnoreMallocFrees();

#endif // MEMORYALLOCTRACKER_H
