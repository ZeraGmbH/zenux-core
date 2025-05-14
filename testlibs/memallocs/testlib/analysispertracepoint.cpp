#include "analysispertracepoint.h"

CalculateSumsOnPointers::CalculateSumsOnPointers(const AllocatedWithBacktracesRaw &allocations)
{
    for (int allocPos=0; allocPos<allocations.count(); allocPos++) {
        const AllocatedWithBacktraceRaw &entry = allocations[allocPos];
        for (int btracePos = entry.m_backTrace.startPos;
             btracePos < entry.m_backTrace.afterLastPos;
             btracePos++) {
            void *pointer = entry.m_backTrace.bufferBacktrace[btracePos];
            m_allocationsByPointer[pointer].append( { entry, btracePos } );
        }
    }

    for (auto iter=m_allocationsByPointer.cbegin(); iter !=m_allocationsByPointer.cend(); ++iter) {
        int count = iter.value().count();
        m_allocationsByCount[count].append(iter.value());
    }

    qInfo("done");
}

const QMap<int, QList<CalculateSumsOnPointers::EntryData> > &CalculateSumsOnPointers::getAllocationsByCount() const
{
    return m_allocationsByCount;
}

const QHash<const void *, QList<CalculateSumsOnPointers::EntryData> > &CalculateSumsOnPointers::getAllocationsByPointer() const
{
    return m_allocationsByPointer;
}
