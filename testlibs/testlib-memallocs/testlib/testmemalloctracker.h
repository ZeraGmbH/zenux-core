#ifndef TESTMEMALLOCTRACKER_H
#define TESTMEMALLOCTRACKER_H

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

    int getAllocCount() const;

    void handleMalloc(size_t size, const void* mem);
    void handleFree(const void* mem);

    struct TAllocatedMemRegion {
        size_t m_size;
        QStringList m_backtraceRaw;
    };
    typedef QList<TAllocatedMemRegion> MemsAllocated;
    const MemsAllocated getRawMemRegions();

private:
    QHash<const void*, TAllocatedMemRegion> m_allocatedRegions;
};

void setTracker(TestMemAllocTracker* tracker);
void startIgnoreMallocFrees();
void stopIgnoreMallocFreess();

#endif // TESTMEMALLOCTRACKER_H
