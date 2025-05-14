#ifndef BACKTRACECONVERTER_H
#define BACKTRACECONVERTER_H

#include "memoryalloctracker.h"

class BacktraceConverter
{
public:
    static QList<void*> backtraceRawToVoidList(MemoryAllocBacktraceGenerator::BacktraceRaw backtrace);

    struct AllocMemTrace {
        size_t m_allocatedSize = 0;
        QList<void*> m_backTrace;
    };
    typedef QList<AllocMemTrace> AllocMemTraces;

    static AllocMemTraces backtracesRawToVoidLists(MemoryAllocTracker::MemsAllocated &allocated);
};

#endif // BACKTRACECONVERTER_H
