#ifndef TESTBACKTRACEGENERATOR_H
#define TESTBACKTRACEGENERATOR_H

#include "memoryalloctracker.h"

class TestBacktraceGenerator
{
public:
    static MemoryAllocBacktraceGenerator::BacktraceRaw createBacktrace(const QList<int> &backtraceValues,
                                                                       int stackIgnoreOffset);
    static MemoryAllocTracker::TAllocatedMemRegion createAllocatedMemRegion(int sizeAlloc,
                                                                            const QList<int> &backtraceValues,
                                                                            int stackIgnoreOffset = 3);
};

#endif // TESTBACKTRACEGENERATOR_H
