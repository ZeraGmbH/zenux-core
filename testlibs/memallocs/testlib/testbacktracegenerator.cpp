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

static quint64 currentAllocationNumber = 0;

void TestBacktraceGenerator::clearAllocTime()
{
    currentAllocationNumber = 0;
}

AllocatedWithBacktraceRaw TestBacktraceGenerator::createAllocatedMemRegion(size_t sizeAlloc,
                                                                           const QList<int> &backtraceValues,
                                                                           int stackIgnoreOffset)
{
    return {
        currentAllocationNumber++,
        sizeAlloc,
        fillBacktraceRaw(backtraceValues, stackIgnoreOffset)
    };
}
