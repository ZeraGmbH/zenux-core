#ifndef BACKTRACECONVERTER_H
#define BACKTRACECONVERTER_H

#include "allocationdatadefinitions.h"

class BacktraceConverter
{
public:
    static QList<void*> backtraceRawToVoidList(AllocBacktraceRaw backtrace);
    static AllocatedWithBacktraces backtracesRawToVoidLists(AllocatedWithBacktracesRaw &allocated);
};

#endif // BACKTRACECONVERTER_H
