#ifndef TESTMEMALLOCTRACKER_H
#define TESTMEMALLOCTRACKER_H

#include "memoryallocbacktracegenerator.h"
#include <stddef.h>
#include <QHash>

class TestMemAllocTracker
{
public:
    TestMemAllocTracker();
    virtual ~TestMemAllocTracker();
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

void setTracker(TestMemAllocTracker* tracker);
void startIgnoreMallocFrees();
void stopIgnoreMallocFreess();

#endif // TESTMEMALLOCTRACKER_H
