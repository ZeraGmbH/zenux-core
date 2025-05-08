#ifndef MEMORYALLOCBACKTRACERAW_H
#define MEMORYALLOCBACKTRACERAW_H

#include <QList>
#include <stddef.h>

// If
// * we miss important
// * test_memallocs_atomic starts to fail
//
// increase maxStacktraceDepth but be aware it slows down
// tests significantly
static constexpr int maxStacktraceDepth = 15;

struct BacktraceRaw {
    void *bufferBacktrace[maxStacktraceDepth];
    int startPos = 0;
    int afterLastPos = 0;
};

struct MemoryChunkAllocated {
    size_t m_allocatedSize = 0;
    BacktraceRaw m_backTrace;
};
typedef QList<MemoryChunkAllocated> MemoryChunksAllocated;


#endif // MEMORYALLOCBACKTRACERAW_H
