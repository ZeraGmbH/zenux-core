#ifndef ANALYSISPERTRACEPOINT_H
#define ANALYSISPERTRACEPOINT_H

#include "allocationdatadefinitions.h"
#include <QHash>
#include <QList>
#include <QMap>

class CalculateSumsOnPointers
{
public:
    CalculateSumsOnPointers(const AllocatedWithBacktracesRaw &allocations);
    struct EntryData {
        AllocatedWithBacktraceRaw m_allocation;
        int m_posInBacktrace;
    };
    const QHash<const void*, QList<EntryData>> &getAllocationsByPointer() const;
    const QMap<int, QList<EntryData>> &getAllocationsByCount() const;
private:
    QHash<const void*, QList<EntryData>> m_allocationsByPointer;
    QMap<int, QList<EntryData>> m_allocationsByCount;
};

#endif // ANALYSISPERTRACEPOINT_H
