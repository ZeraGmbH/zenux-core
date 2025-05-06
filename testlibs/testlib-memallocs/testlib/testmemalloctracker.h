#ifndef TESTMEMALLOCTRACKER_H
#define TESTMEMALLOCTRACKER_H

#include <stddef.h>
#include <QHash>

class TestMemAllocTracker
{
public:
    TestMemAllocTracker();
    virtual ~TestMemAllocTracker();

    int getAllocCount() const;

    void handleMalloc(size_t size, const void* mem);
    void handleFree(const void* mem);

    struct TAllocatedMemRegion {
        size_t m_size;
    };

private:
    QHash<const void*, TAllocatedMemRegion> m_allocatedRegions;
};

void setTracker(TestMemAllocTracker* tracker);
void startIgnoreMallocFrees();
void stopIgnoreMallocFreess();

#endif // TESTMEMALLOCTRACKER_H
