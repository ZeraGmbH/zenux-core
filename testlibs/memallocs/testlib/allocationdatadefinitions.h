#ifndef ALLOCATIONDATADEFINITIONS_H
#define ALLOCATIONDATADEFINITIONS_H

#include <stddef.h>
#include <QList>

// If
// * we miss important
// * test_memallocs_atomic starts to fail
//
// increase maxStacktraceDepth but be aware it slows down
// tests significantly
static constexpr int maxStacktraceDepth = 15;

struct AllocBacktraceRaw {
    void *bufferBacktrace[maxStacktraceDepth];
    int startPos = 0;
    int afterLastPos = 0;
};

struct AllocatedWithBacktraceRaw {
    quint64 m_allocationNumber = 0;
    size_t m_allocatedSize = 0;
    AllocBacktraceRaw m_backTrace;
};
typedef QList<AllocatedWithBacktraceRaw> AllocatedWithBacktracesRaw;

struct AllocatedWithBacktrace {
    quint64 m_allocationNumber = 0;
    size_t m_allocatedSize = 0;
    QList<void*> m_backTrace;

    bool operator == (const AllocatedWithBacktrace& other) const {
        return
            m_allocationNumber == other.m_allocationNumber &&
            m_allocatedSize == other.m_allocatedSize &&
            m_backTrace == other.m_backTrace;
    }
};
typedef QList<AllocatedWithBacktrace> AllocatedWithBacktraces;

#endif // ALLOCATIONDATADEFINITIONS_H
