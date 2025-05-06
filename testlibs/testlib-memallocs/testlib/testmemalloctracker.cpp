#include "testmemalloctracker.h"
#include "testbacktracegenerator.h"

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

void TestMemAllocTracker::handleMalloc(size_t size, const void *mem)
{
    startIgnoreMallocFrees();
    TestBacktraceGenerator gen;
    m_allocatedRegions[mem] = { size, gen.createBacktraceRaw("malloc") };
    stopIgnoreMallocFreess();
}

void TestMemAllocTracker::handleFree(const void *mem)
{
    startIgnoreMallocFrees();
    m_allocatedRegions.remove(mem);
    stopIgnoreMallocFreess();
}

const TestMemAllocTracker::MemsAllocated TestMemAllocTracker::getRawMemRegions()
{
    return m_allocatedRegions.values();
}
