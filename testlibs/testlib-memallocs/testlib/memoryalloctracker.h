#ifndef MEMORYALLOCTRACKER_H
#define MEMORYALLOCTRACKER_H

#include "memoryallocbacktraceraw.h"
#include <QHash>
#include <stddef.h>
#include <memory>

class MemoryAllocatorFunctionPtrCache;

class MemoryAllocTracker
{
public:
    MemoryAllocTracker();
    MemoryAllocTracker(std::unique_ptr<MemoryAllocatorFunctionPtrCache> allocFuncPtrCache);
    virtual ~MemoryAllocTracker();
    void start();
    void stop();
    void clear();

    void handleMalloc(size_t size, const void* allocatedMemory);
    void handleFree(const void* allocatedMemory);


    int getAllocCount() const;
    const MemoryChunksAllocated getRawMemRegions();

private:
    std::unique_ptr<MemoryAllocatorFunctionPtrCache> m_allocFuncPtrCache;
    QHash<const void*, MemoryChunkAllocated> m_allocatedRegions;
};

void setTracker(MemoryAllocTracker* tracker);
void startIgnoreMallocFrees();
void stopIgnoreMallocFrees();

#endif // MEMORYALLOCTRACKER_H
