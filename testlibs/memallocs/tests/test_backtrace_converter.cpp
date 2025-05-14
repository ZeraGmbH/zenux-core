#include "test_backtrace_converter.h"
#include "backtracerawtools.h"
#include "backtraceconverter.h"
#include "testbacktracegenerator.h"
#include <QTest>

QTEST_MAIN(test_backtrace_converter)

constexpr int size1 = 5;
constexpr int size2 = 8;

void test_backtrace_converter::testCreateBacktrace()
{
    constexpr int ignoreOffset = 2;
    QList<int> testTace = QList<int>() << 1 << 2 << 3;
    AllocBacktraceRaw backtrace =
        TestBacktraceGenerator::fillBacktraceRaw(testTace, ignoreOffset);
    QCOMPARE(backtrace.startPos, ignoreOffset);
    QCOMPARE(backtrace.afterLastPos, testTace.count() + ignoreOffset);
    QCOMPARE(backtrace.bufferBacktrace[0], reinterpret_cast<void*>(0));
    QCOMPARE(backtrace.bufferBacktrace[1], reinterpret_cast<void*>(0));
    QCOMPARE(backtrace.bufferBacktrace[2], reinterpret_cast<void*>(1));
    QCOMPARE(backtrace.bufferBacktrace[3], reinterpret_cast<void*>(2));
    QCOMPARE(backtrace.bufferBacktrace[4], reinterpret_cast<void*>(3));
}

void test_backtrace_converter::backtraceRawToVoidList()
{
    constexpr int ignoreOffset = 2;
    QList<int> testTace = QList<int>() << 1 << 2 << 3;
    AllocBacktraceRaw backtrace =
        TestBacktraceGenerator::fillBacktraceRaw(testTace, ignoreOffset);
    QList<void*> backtraceList = BacktraceConverter::backtraceRawToVoidList(backtrace);
    QCOMPARE(backtraceList[0], reinterpret_cast<void*>(1));
    QCOMPARE(backtraceList[1], reinterpret_cast<void*>(2));
    QCOMPARE(backtraceList[2], reinterpret_cast<void*>(3));
}

void test_backtrace_converter::backtracesRawToVoidLists()
{
    AllocatedWithBacktracesRaw alloc;
    alloc.append(TestBacktraceGenerator::createAllocatedMemRegion(size1, QList<int>() << 1 << 2 << 3));
    alloc.append(TestBacktraceGenerator::createAllocatedMemRegion(size2, QList<int>() << 4 << 5));

    BacktraceConverter::AllocatedWithBacktraces converted = BacktraceConverter::backtracesRawToVoidLists(alloc);
    QCOMPARE(converted.count(), 2);
    QCOMPARE(converted[0].m_allocatedSize, size1);
    QCOMPARE(converted[0].m_backTrace[0], reinterpret_cast<void*>(1));
    QCOMPARE(converted[0].m_backTrace[1], reinterpret_cast<void*>(2));
    QCOMPARE(converted[0].m_backTrace[2], reinterpret_cast<void*>(3));

    QCOMPARE(converted[1].m_allocatedSize, size2);
    QCOMPARE(converted[1].m_backTrace[0], reinterpret_cast<void*>(4));
    QCOMPARE(converted[1].m_backTrace[1], reinterpret_cast<void*>(5));
}
