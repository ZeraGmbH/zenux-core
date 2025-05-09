#include "analysispertracepoint.h"

CalculateSumsOnPointers::CalculateSumsOnPointers(const MemoryAllocTracker::MemsAllocated &allocations)
{
    for (int allocPos=0; allocPos<allocations.count(); allocPos++) {
        const MemoryAllocTracker::TAllocatedMemRegion &entry = allocations[allocPos];
        for (int btracePos = entry.m_backTrace.startPos;
             btracePos < entry.m_backTrace.afterLastPos;
             btracePos++) {
            void *pointer = entry.m_backTrace.bufferBacktrace[btracePos];
            m_allocationsByPointer[pointer].append( { entry, btracePos } );
        }
    }

    for (auto iter=m_allocationsByPointer.cbegin(); iter !=m_allocationsByPointer.cend(); ++iter) {
        int count = iter.value().count();
        m_pointersByCount[count].append(iter.key());
    }

    qInfo("done");
}

const QHash<const void *, QList<CalculateSumsOnPointers::EntryData> > &CalculateSumsOnPointers::getAllocationsByPointer() const
{
    return m_allocationsByPointer;
}

const QMap<int, QList<const void *> > &CalculateSumsOnPointers::getPointersByCount() const
{
    return m_pointersByCount;
}
