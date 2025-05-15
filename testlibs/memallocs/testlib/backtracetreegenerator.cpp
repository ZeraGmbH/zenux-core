#include "backtracetreegenerator.h"

BacktraceTreeGenerator::BacktraceTreeGenerator(const AllocatedWithBacktraces &allocs) :
    m_allocs(allocs)
{
    for (const AllocatedWithBacktrace &alloc : m_allocs)
        insertEntry(alloc, m_emptyRootTrace, 0);
}

const AllocatedWithBacktrace &BacktraceTreeGenerator::getAlloc(int allocNo) const
{
    return m_allocs[allocNo];
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
    currBacktraceDepth++;
    TreeEntry &child = parentTraceEntry.m_childTraces[backtracePointer];
    child.m_pointersToOrigTraces.append(&alloc);
    child.m_backtraceDepth = currBacktraceDepth;
    insertEntry(alloc, child, currBacktraceDepth);
}
