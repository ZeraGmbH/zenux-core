#include "test_backtrace_tree_generator.h"
#include "backtracetreegenerator.h"
#include "backtraceconverter.h"
#include "testbacktracegenerator.h"
#include <QTest>

QTEST_MAIN(test_backtrace_tree_generator)

constexpr int size1 = 5;
constexpr int size2 = 8;

void test_backtrace_tree_generator::init()
{
    TestBacktraceGenerator::clearAllocTime();
}

void test_backtrace_tree_generator::oneAlloc()
{
    AllocatedWithBacktracesRaw allocRaw;
    allocRaw.append(TestBacktraceGenerator::createAllocatedMemRegion(size1, QList<int>() << 10 << 20));

    AllocatedWithBacktraces allocs = BacktraceConverter::allocsRawToAllocsTimeSorted(allocRaw);
    BacktraceTreeGenerator tree(allocs);

    const BacktraceTreeGenerator::TreeEntry *rootEntry = tree.getRootEntry();
    QCOMPARE(rootEntry->m_childTraces.count(), 1);
    QCOMPARE(rootEntry->m_trace.count(), 0);
    QCOMPARE(rootEntry->m_callCount, 1);
    QCOMPARE(rootEntry->m_totalAlloc, size1);

    void* traceDepth1 = reinterpret_cast<void*>(10);
    const BacktraceTreeGenerator::TreeEntry &childDepth1 = rootEntry->m_childTraces[traceDepth1];
    QCOMPARE(childDepth1.m_pointersToOrigTraces.count(), 1);
    QCOMPARE(childDepth1.m_pointersToOrigTraces[0], &tree.getAlloc(0));
    QCOMPARE(childDepth1.m_trace.count(), 1);
    QCOMPARE(childDepth1.m_callCount, 1);
    QCOMPARE(childDepth1.m_totalAlloc, size1);

    void* traceDepth2 = reinterpret_cast<void*>(20);
    const BacktraceTreeGenerator::TreeEntry &childDepth2 = childDepth1.m_childTraces[traceDepth2];
    QCOMPARE(childDepth2.m_pointersToOrigTraces.count(), 1);
    QCOMPARE(childDepth2.m_pointersToOrigTraces[0], &tree.getAlloc(0));
    QCOMPARE(childDepth2.m_trace.count(), 2);
    QCOMPARE(childDepth2.m_callCount, 1);
    QCOMPARE(childDepth2.m_totalAlloc, size1);

    QCOMPARE(tree.getEntryList()->count(), 2);
}

void test_backtrace_tree_generator::twoAllocsCompleteDifferentBacktrace()
{
    AllocatedWithBacktracesRaw allocRaw;
    allocRaw.append(TestBacktraceGenerator::createAllocatedMemRegion(size1, QList<int>() << 10 << 20));
    allocRaw.append(TestBacktraceGenerator::createAllocatedMemRegion(size2, QList<int>() << 30 << 40));

    AllocatedWithBacktraces allocs = BacktraceConverter::allocsRawToAllocsTimeSorted(allocRaw);
    BacktraceTreeGenerator tree(allocs);

    const BacktraceTreeGenerator::TreeEntry *rootEntry = tree.getRootEntry();
    QCOMPARE(rootEntry->m_childTraces.count(), 2);
    QCOMPARE(rootEntry->m_trace.count(), 0);
    QCOMPARE(rootEntry->m_callCount, 2);
    QCOMPARE(rootEntry->m_totalAlloc, size1+size2);

    void* trace1Depth1 = reinterpret_cast<void*>(10);
    const BacktraceTreeGenerator::TreeEntry &child1Depth1 = rootEntry->m_childTraces[trace1Depth1];
    QCOMPARE(child1Depth1.m_pointersToOrigTraces.count(), 1);
    QCOMPARE(child1Depth1.m_pointersToOrigTraces[0], &tree.getAlloc(0));
    QCOMPARE(child1Depth1.m_trace.count(), 1);
    QCOMPARE(child1Depth1.m_callCount, 1);
    QCOMPARE(child1Depth1.m_totalAlloc, size1);

    void* trace1Depth2 = reinterpret_cast<void*>(20);
    const BacktraceTreeGenerator::TreeEntry &child1Depth2 = child1Depth1.m_childTraces[trace1Depth2];
    QCOMPARE(child1Depth2.m_pointersToOrigTraces.count(), 1);
    QCOMPARE(child1Depth2.m_pointersToOrigTraces[0], &tree.getAlloc(0));
    QCOMPARE(child1Depth2.m_trace.count(), 2);
    QCOMPARE(child1Depth2.m_callCount, 1);
    QCOMPARE(child1Depth2.m_totalAlloc, size1);

    void* trace2Depth1 = reinterpret_cast<void*>(30);
    const BacktraceTreeGenerator::TreeEntry &child2Depth1 = rootEntry->m_childTraces[trace2Depth1];
    QCOMPARE(child2Depth1.m_pointersToOrigTraces.count(), 1);
    QCOMPARE(child2Depth1.m_pointersToOrigTraces[0], &tree.getAlloc(1));
    QCOMPARE(child2Depth1.m_trace.count(), 1);
    QCOMPARE(child2Depth1.m_callCount, 1);
    QCOMPARE(child2Depth1.m_totalAlloc, size2);

    void* trace2Depth2 = reinterpret_cast<void*>(40);
    const BacktraceTreeGenerator::TreeEntry &child2Depth2 = child2Depth1.m_childTraces[trace2Depth2];
    QCOMPARE(child2Depth2.m_pointersToOrigTraces.count(), 1);
    QCOMPARE(child2Depth2.m_pointersToOrigTraces[0], &tree.getAlloc(1));
    QCOMPARE(child2Depth2.m_trace.count(), 2);
    QCOMPARE(child2Depth2.m_callCount, 1);
    QCOMPARE(child2Depth2.m_totalAlloc, size2);

    QCOMPARE(tree.getEntryList()->count(), 4);
}

void test_backtrace_tree_generator::twoAllocsSameFirstBacktrace()
{
    AllocatedWithBacktracesRaw allocRaw;
    allocRaw.append(TestBacktraceGenerator::createAllocatedMemRegion(size1, QList<int>() << 10 << 20));
    allocRaw.append(TestBacktraceGenerator::createAllocatedMemRegion(size2, QList<int>() << 10 << 30));

    AllocatedWithBacktraces allocs = BacktraceConverter::allocsRawToAllocsTimeSorted(allocRaw);
    BacktraceTreeGenerator tree(allocs);

    const BacktraceTreeGenerator::TreeEntry *rootEntry = tree.getRootEntry();
    QCOMPARE(rootEntry->m_childTraces.count(), 1);
    QCOMPARE(rootEntry->m_trace.count(), 0);
    QCOMPARE(rootEntry->m_callCount, 2);
    QCOMPARE(rootEntry->m_totalAlloc, size1+size2);

    void* traceDepth1 = reinterpret_cast<void*>(10);
    const BacktraceTreeGenerator::TreeEntry &childDepth1 = rootEntry->m_childTraces[traceDepth1];
    QCOMPARE(childDepth1.m_pointersToOrigTraces.count(), 2);
    QCOMPARE(childDepth1.m_pointersToOrigTraces[0], &tree.getAlloc(0));
    QCOMPARE(childDepth1.m_pointersToOrigTraces[1], &tree.getAlloc(1));
    QCOMPARE(childDepth1.m_trace.count(), 1);
    QCOMPARE(childDepth1.m_callCount, 2);
    QCOMPARE(childDepth1.m_totalAlloc, size1+size2);

    void* trace1Depth2 = reinterpret_cast<void*>(20);
    const BacktraceTreeGenerator::TreeEntry &child1Depth2 = childDepth1.m_childTraces[trace1Depth2];
    QCOMPARE(child1Depth2.m_pointersToOrigTraces.count(), 1);
    QCOMPARE(child1Depth2.m_pointersToOrigTraces[0], &tree.getAlloc(0));
    QCOMPARE(child1Depth2.m_trace.count(), 2);
    QCOMPARE(child1Depth2.m_callCount, 1);
    QCOMPARE(child1Depth2.m_totalAlloc, size1);

    void* trace2Depth2 = reinterpret_cast<void*>(30);
    const BacktraceTreeGenerator::TreeEntry &child2Depth2 = childDepth1.m_childTraces[trace2Depth2];
    QCOMPARE(child2Depth2.m_pointersToOrigTraces.count(), 1);
    QCOMPARE(child2Depth2.m_pointersToOrigTraces[0], &tree.getAlloc(1));
    QCOMPARE(child2Depth2.m_trace.count(), 2);
    QCOMPARE(child2Depth2.m_callCount, 1);
    QCOMPARE(child2Depth2.m_totalAlloc, size2);

    QCOMPARE(tree.getEntryList()->count(), 3);
}

void test_backtrace_tree_generator::twoAllocsSameFirstBacktraceTwoSame()
{
    AllocatedWithBacktracesRaw allocRaw;
    allocRaw.append(TestBacktraceGenerator::createAllocatedMemRegion(size1, QList<int>() << 10 << 20));
    allocRaw.append(TestBacktraceGenerator::createAllocatedMemRegion(size2, QList<int>() << 10 << 30));
    allocRaw.append(TestBacktraceGenerator::createAllocatedMemRegion(size1, QList<int>() << 10 << 20));

    AllocatedWithBacktraces allocs = BacktraceConverter::allocsRawToAllocsTimeSorted(allocRaw);
    BacktraceTreeGenerator tree(allocs);

    const BacktraceTreeGenerator::TreeEntry *rootEntry = tree.getRootEntry();
    QCOMPARE(rootEntry->m_childTraces.count(), 1);
    QCOMPARE(rootEntry->m_trace.count(), 0);
    QCOMPARE(rootEntry->m_callCount, 3);
    QCOMPARE(rootEntry->m_totalAlloc, size1+size1+size2);

    void* traceDepth1 = reinterpret_cast<void*>(10);
    const BacktraceTreeGenerator::TreeEntry &childDepth1 = rootEntry->m_childTraces[traceDepth1];
    QCOMPARE(childDepth1.m_pointersToOrigTraces.count(), 3);
    QCOMPARE(childDepth1.m_pointersToOrigTraces[0], &tree.getAlloc(0));
    QCOMPARE(childDepth1.m_pointersToOrigTraces[1], &tree.getAlloc(1));
    QCOMPARE(childDepth1.m_trace.count(), 1);
    QCOMPARE(childDepth1.m_callCount, 3);
    QCOMPARE(childDepth1.m_totalAlloc, size1+size1+size2);

    void* trace1Depth2 = reinterpret_cast<void*>(20);
    const BacktraceTreeGenerator::TreeEntry &child1Depth2 = childDepth1.m_childTraces[trace1Depth2];
    QCOMPARE(child1Depth2.m_pointersToOrigTraces.count(), 2);
    QCOMPARE(child1Depth2.m_pointersToOrigTraces[0], &tree.getAlloc(0));
    QCOMPARE(child1Depth2.m_trace.count(), 2);
    QCOMPARE(child1Depth2.m_callCount, 2);
    QCOMPARE(child1Depth2.m_totalAlloc, size1+size1);

    void* trace2Depth2 = reinterpret_cast<void*>(30);
    const BacktraceTreeGenerator::TreeEntry &child2Depth2 = childDepth1.m_childTraces[trace2Depth2];
    QCOMPARE(child2Depth2.m_pointersToOrigTraces.count(), 1);
    QCOMPARE(child2Depth2.m_pointersToOrigTraces[0], &tree.getAlloc(1));
    QCOMPARE(child2Depth2.m_trace.count(), 2);
    QCOMPARE(child2Depth2.m_callCount, 1);
    QCOMPARE(child2Depth2.m_totalAlloc, size2);

    QCOMPARE(tree.getEntryList()->count(), 3);
}
