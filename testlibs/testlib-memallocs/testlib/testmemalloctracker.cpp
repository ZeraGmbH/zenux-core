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
    return m_allocCount;
}

void TestMemAllocTracker::handleMalloc(size_t size, void *mem)
{
    m_allocCount++;
}

void TestMemAllocTracker::handleFree(void *mem)
{
    m_allocCount--;
}
