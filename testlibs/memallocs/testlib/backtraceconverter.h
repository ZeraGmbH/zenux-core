#ifndef BACKTRACECONVERTER_H
#define BACKTRACECONVERTER_H

#include "allocationdatadefinitions.h"

class BacktraceConverter
{
public:
    static QList<void*> backtraceRawToVoidList(AllocBacktraceRaw backtrace);

    struct AllocatedWithBacktrace {
        size_t m_allocatedSize = 0;
        QList<void*> m_backTrace;
    };
    typedef QList<AllocatedWithBacktrace> AllocatedWithBacktraces;

    static AllocatedWithBacktraces backtracesRawToVoidLists(AllocatedWithBacktracesRaw &allocated);
};

#endif // BACKTRACECONVERTER_H
