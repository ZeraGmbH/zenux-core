#ifndef MEMORYALLOCTRACKER_H
#define MEMORYALLOCTRACKER_H

#include "memoryallocbacktracegenerator.h"
#include <stddef.h>
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

    struct TAllocatedMemRegion {
        size_t m_allocatedSize = 0;
        MemoryAllocBacktraceGenerator::BacktraceRaw m_backTrace;
    };
    typedef QList<TAllocatedMemRegion> MemsAllocated;

    int getAllocCount() const;
    const MemsAllocated getRawMemRegions();

private:
    QHash<const void*, TAllocatedMemRegion> m_allocatedRegions;
};

void setTracker(MemoryAllocTracker* tracker);
void startIgnoreMallocFrees();
void stopIgnoreMallocFrees();

#endif // MEMORYALLOCTRACKER_H
