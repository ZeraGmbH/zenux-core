#ifndef TESTBACKTRACEGENERATOR_H
#define TESTBACKTRACEGENERATOR_H

#include "allocationdatadefinitions.h"

class TestBacktraceGenerator
{
public:
    static AllocBacktraceRaw fillBacktraceRaw(const QList<int> &backtraceValues,
                                                int stackIgnoreOffset);
    static AllocatedWithBacktraceRaw createAllocatedMemRegion(int sizeAlloc,
                                                              const QList<int> &backtraceValues,
                                                              int stackIgnoreOffset = 3);
};

#endif // TESTBACKTRACEGENERATOR_H
