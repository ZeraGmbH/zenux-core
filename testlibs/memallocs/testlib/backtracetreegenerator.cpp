#include "backtracetreegenerator.h"

BacktraceTreeGenerator::BacktraceTreeGenerator(const AllocatedWithBacktraces &allocs) :
    m_allocs(allocs)
{
    for (const AllocatedWithBacktrace &alloc : m_allocs)
        insertEntry(alloc, m_emptyRootTrace, 0);
    fillChildrenBySize();
}

const AllocatedWithBacktrace &BacktraceTreeGenerator::getAlloc(int allocNo) const
{
    return m_allocs.at(allocNo);
}

const QList<BacktraceTreeGenerator::TreeEntry *> *BacktraceTreeGenerator::getEntryList() const
{
    return &m_entryList;
}

const BacktraceTreeGenerator::TreeEntry *BacktraceTreeGenerator::getRootEntry() const
{
    return &m_emptyRootTrace;
}

void BacktraceTreeGenerator::insertEntry(const AllocatedWithBacktrace &alloc,
                                         TreeEntry &parentTraceEntry,
                                         int currBacktraceDepth)
{
    if (currBacktraceDepth >= alloc.m_backTrace.size())
        return;
    const void* backtracePointer = alloc.m_backTrace[currBacktraceDepth];
    if(currBacktraceDepth == 0) {
        m_emptyRootTrace.m_callCount++;
        m_emptyRootTrace.m_totalAlloc += alloc.m_allocatedSize;
    }
    currBacktraceDepth++;
    TreeEntry &child = parentTraceEntry.m_childTraces[backtracePointer];
    if (child.m_callCount == 0) {
        m_entryList.append(&child);
        for (int i=0; i<currBacktraceDepth; i++)
            child.m_trace.append(alloc.m_backTrace[i]);
    }
    child.m_pointersToOrigTraces.append(&alloc);
    child.m_callCount++;
    child.m_totalAlloc += alloc.m_allocatedSize;
    insertEntry(alloc, child, currBacktraceDepth);
}

void BacktraceTreeGenerator::fillChildrenBySize()
{
    for (auto iter=m_emptyRootTrace.m_childTraces.cbegin(); iter!=m_emptyRootTrace.m_childTraces.cend(); iter++) {
        m_emptyRootTrace.m_childrenBySize[iter.value().m_totalAlloc].append(&iter.value());
    }
    for (TreeEntry *entry : m_entryList) {
        for (auto iter=entry->m_childTraces.cbegin(); iter!=entry->m_childTraces.cend(); iter++) {
            entry->m_childrenBySize[iter.value().m_totalAlloc].append(&iter.value());
        }
    }
}
