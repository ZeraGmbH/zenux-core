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
        int m_backtraceDepth = 0;
        QMap<const void*, TreeEntry> m_childTraces;
    };
    typedef QList<TreeEntry> TreeEntries;

    const TreeEntry *getRootEntry() const;
    const QList<const TreeEntry *> *getEntryList() const;

private:
    void insertEntry(const AllocatedWithBacktrace &alloc,
                     TreeEntry &parentTraceEntry,
                     int currBacktraceDepth);

    const AllocatedWithBacktraces m_allocs;
    TreeEntry m_emptyRootTrace;
    QList<const TreeEntry *> m_entryList;
};

#endif // BACKTRACETREEGENERATOR_H
