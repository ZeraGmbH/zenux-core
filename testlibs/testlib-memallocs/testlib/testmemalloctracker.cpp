#include "testmemalloctracker.h"

TestMemAllocTracker::TestMemAllocTracker()
{
    setTracker(this);
}

TestMemAllocTracker::~TestMemAllocTracker()
{
    setTracker(nullptr);
}

int TestMemAllocTracker::getAllocCount() const
{
    return m_allocatedRegions.size();
}

void TestMemAllocTracker::handleMalloc(size_t size, const void *mem)
{
    startIgnoreMallocFrees();
    m_allocatedRegions[mem] = { size };
    stopIgnoreMallocFreess();
}

void TestMemAllocTracker::handleFree(const void *mem)
{
    startIgnoreMallocFrees();
    m_allocatedRegions.remove(mem);
    stopIgnoreMallocFreess();
}
