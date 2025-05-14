#ifndef BACKTRACECONVERTER_H
#define BACKTRACECONVERTER_H

#include "allocationdatadefinitions.h"

class BacktraceConverter
{
public:
    static QList<void*> backtraceRawToVoidList(const AllocBacktraceRaw &backtrace);
    static AllocatedWithBacktrace allocRawToAlloc(const AllocatedWithBacktraceRaw &allocRaw);
    static AllocatedWithBacktraces allocsRawToAllocsTimeSorted(const AllocatedWithBacktracesRaw &allocsRaw);
};

#endif // BACKTRACECONVERTER_H
