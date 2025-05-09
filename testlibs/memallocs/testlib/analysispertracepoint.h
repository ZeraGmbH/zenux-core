#ifndef ANALYSISPERTRACEPOINT_H
#define ANALYSISPERTRACEPOINT_H

#include "memoryalloctracker.h"
#include <QHash>
#include <QList>
#include <QMap>

class CalculateSumsOnPointers
{
public:
    CalculateSumsOnPointers(const MemoryAllocTracker::MemsAllocated &allocations);
    struct EntryData {
        MemoryAllocTracker::TAllocatedMemRegion m_allocation;
        int m_posInBacktrace;
    };
    const QHash<const void*, QList<EntryData>> &getAllocationsByPointer() const;
    const QMap<int, QList<const void*>> &getPointersByCount() const;
private:
    QHash<const void*, QList<EntryData>> m_allocationsByPointer;
    QMap<int, QList<const void*>> m_pointersByCount;
};

#endif // ANALYSISPERTRACEPOINT_H
