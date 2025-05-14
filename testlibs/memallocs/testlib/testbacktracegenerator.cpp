#include "testbacktracegenerator.h"

AllocBacktraceRaw TestBacktraceGenerator::fillBacktraceRaw(const QList<int> &backtraceValues,
                                                             int stackIgnoreOffset)
{
    AllocBacktraceRaw backtrace;
    backtrace.startPos = stackIgnoreOffset;
    backtrace.afterLastPos = backtraceValues.count() + stackIgnoreOffset;
    for (int i=0; i<stackIgnoreOffset; i++)
        backtrace.bufferBacktrace[i] = 0;
    for (int i=0; i<backtraceValues.count(); i++)
        backtrace.bufferBacktrace[i+stackIgnoreOffset] = reinterpret_cast<void*>(backtraceValues[i]);
    return backtrace;
}

AllocatedWithBacktraceRaw TestBacktraceGenerator::createAllocatedMemRegion(int sizeAlloc,
                                                                           const QList<int> &backtraceValues,
                                                                           int stackIgnoreOffset)
{
    AllocatedWithBacktraceRaw mem;
    mem.m_allocatedSize = sizeAlloc;
    mem.m_backTrace = fillBacktraceRaw(backtraceValues, stackIgnoreOffset);
    return mem;
}
