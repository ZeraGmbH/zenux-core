#include "backtraceconverter.h"

QList<void *> BacktraceConverter::backtraceRawToVoidList(AllocBacktraceRaw backtrace)
{
    QList<void *> backtraceList;
    for (int i=backtrace.startPos; i<backtrace.afterLastPos; i++)
        backtraceList.append(backtrace.bufferBacktrace[i]);
    return backtraceList;
}

BacktraceConverter::AllocatedWithBacktraces BacktraceConverter::backtracesRawToVoidLists(AllocatedWithBacktracesRaw &allocated)
{
    BacktraceConverter::AllocatedWithBacktraces converted;
    for (int alloc=0; alloc<allocated.count(); alloc++)
        converted.append( {
            allocated[alloc].m_allocatedSize,
            backtraceRawToVoidList(allocated[alloc].m_backTrace)
        });
    return converted;
}
