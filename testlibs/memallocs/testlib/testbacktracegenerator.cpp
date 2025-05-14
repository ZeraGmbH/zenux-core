#include "testbacktracegenerator.h"

MemoryAllocBacktraceGenerator::BacktraceRaw TestBacktraceGenerator::createBacktrace(const QList<int> &backtraceValues,
                                                                                    int stackIgnoreOffset)
{
    MemoryAllocBacktraceGenerator::BacktraceRaw backtrace;
    backtrace.startPos = stackIgnoreOffset;
    backtrace.afterLastPos = backtraceValues.count() + stackIgnoreOffset;
    for (int i=0; i<stackIgnoreOffset; i++)
        backtrace.bufferBacktrace[i] = 0;
    for (int i=0; i<backtraceValues.count(); i++)
        backtrace.bufferBacktrace[i+stackIgnoreOffset] = reinterpret_cast<void*>(backtraceValues[i]);
    return backtrace;
}

MemoryAllocTracker::TAllocatedMemRegion TestBacktraceGenerator::createAllocatedMemRegion(int sizeAlloc,
                                                                                         const QList<int> &backtraceValues,
                                                                                         int stackIgnoreOffset)
{
    MemoryAllocTracker::TAllocatedMemRegion mem;
    mem.m_allocatedSize = sizeAlloc;
    mem.m_backTrace = createBacktrace(backtraceValues, stackIgnoreOffset);
    return mem;
}
