#ifndef TESTBACKTRACEGENERATOR_H
#define TESTBACKTRACEGENERATOR_H

#include "allocationdatadefinitions.h"

class TestBacktraceGenerator
{
public:
    static AllocBacktraceRaw fillBacktraceRaw(const QList<int> &backtraceValues,
                                              int stackIgnoreOffset);
    static void clearAllocTime();
    static AllocatedWithBacktraceRaw createAllocatedMemRegion(size_t sizeAlloc,
                                                              const QList<int> &backtraceValues,
                                                              int stackIgnoreOffset = 3);
};

#endif // TESTBACKTRACEGENERATOR_H
