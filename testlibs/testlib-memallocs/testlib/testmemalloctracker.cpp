#include "testmemalloctracker.h"

TestMemAllocTracker::TestMemAllocTracker()
{
}

TestMemAllocTracker::~TestMemAllocTracker()
{
    stop();
}

void TestMemAllocTracker::start()
{
    setTracker(this);
}

void TestMemAllocTracker::stop()
{
    setTracker(nullptr);
}

void TestMemAllocTracker::clear()
{
    m_allocatedRegions.clear();
}

int TestMemAllocTracker::getAllocCount() const
{
    return m_allocatedRegions.size();
}

void TestMemAllocTracker::handleMalloc(size_t size, const void *allocatedMemory)
{
    startIgnoreMallocFrees();
    TestBacktraceGenerator::BacktraceRaw btrace;
    TestBacktraceGenerator::createBacktraceRaw(&btrace);
    m_allocatedRegions[allocatedMemory] = { size, btrace };
    stopIgnoreMallocFreess();
}

void TestMemAllocTracker::handleFree(const void *allocatedMemory)
{
    startIgnoreMallocFrees();
    m_allocatedRegions.remove(allocatedMemory);
    stopIgnoreMallocFreess();
}

const TestMemAllocTracker::MemsAllocated TestMemAllocTracker::getRawMemRegions()
{
    return m_allocatedRegions.values();
}
