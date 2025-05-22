#ifndef BACKTRACETREEGENERATOR_H
#define BACKTRACETREEGENERATOR_H

#include "allocationdatadefinitions.h"
#include <QMap>

class BacktraceTreeGenerator
{
public:
    explicit BacktraceTreeGenerator(const AllocatedWithBacktraces &allocs);
    const AllocatedWithBacktrace &getAlloc(int allocNo) const;

    struct TreeEntry {
        QList<const AllocatedWithBacktrace*> m_pointersToOrigTraces;
        QMap<const void*, TreeEntry> m_childTraces;

        // for analysis / test
        QList<void*> m_trace;
        int m_callCount = 0;
        int m_totalAlloc = 0;
        QMap<int, QList<const TreeEntry*>> m_childrenBySize;
    };
    typedef QList<TreeEntry> TreeEntries;

    const TreeEntry *getRootEntry() const;
    const QList<TreeEntry *> *getEntryList() const;

private:
    void insertEntry(const AllocatedWithBacktrace &alloc,
                     TreeEntry &parentTraceEntry,
                     int currBacktraceDepth);
    void fillChildrenBySize();

    const AllocatedWithBacktraces m_allocs;
    TreeEntry m_emptyRootTrace;
    QList<TreeEntry *> m_entryList;
};

#endif // BACKTRACETREEGENERATOR_H
