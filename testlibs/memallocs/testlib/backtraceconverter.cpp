#include "backtraceconverter.h"
#include <QMap>

QList<void *> BacktraceConverter::backtraceRawToVoidList(const AllocBacktraceRaw &backtrace)
{
    QList<void *> backtraceList;
    for (int i=backtrace.startPos; i<backtrace.afterLastPos; i++)
        backtraceList.append(backtrace.bufferBacktrace[i]);
    return backtraceList;
}

AllocatedWithBacktrace BacktraceConverter::allocRawToAlloc(const AllocatedWithBacktraceRaw &allocRaw)
{
    return {
            allocRaw.m_allocationNumber,
            allocRaw.m_allocatedSize,
            backtraceRawToVoidList(allocRaw.m_backTrace)
    };
}

AllocatedWithBacktraces BacktraceConverter::allocsRawToAllocsTimeSorted(const AllocatedWithBacktracesRaw &allocsRaw)
{
    QMap<quint64, AllocatedWithBacktrace> timeSortedAllocs;
    for (const AllocatedWithBacktraceRaw &allocRaw : allocsRaw) {
        timeSortedAllocs[allocRaw.m_allocationNumber] = {
            allocRaw.m_allocationNumber,
            allocRaw.m_allocatedSize,
            BacktraceConverter::backtraceRawToVoidList(allocRaw.m_backTrace)
        };
    }
    return timeSortedAllocs.values();

}
