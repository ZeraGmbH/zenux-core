#include "test_backtrace_converter.h"
#include "backtraceconverter.h"
#include "testbacktracegenerator.h"
#include <QTest>

QTEST_MAIN(test_backtrace_converter)

constexpr int size1 = 5;
constexpr int size2 = 8;
constexpr int size3 = 17;

void test_backtrace_converter::init()
{
    TestBacktraceGenerator::clearAllocTime();
}

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

void test_backtrace_converter::allocsRawToAllocsTimeSorted()
{
    AllocatedWithBacktracesRaw alloc;
    alloc.append(TestBacktraceGenerator::createAllocatedMemRegion(size1, QList<int>() << 1 << 2 << 3));
    alloc.prepend(TestBacktraceGenerator::createAllocatedMemRegion(size2, QList<int>() << 4 << 5));
    alloc.append(TestBacktraceGenerator::createAllocatedMemRegion(size3, QList<int>() << 6 << 7));

    AllocatedWithBacktraces converted = BacktraceConverter::allocsRawToAllocsTimeSorted(alloc);
    QCOMPARE(converted.count(), 3);
    QCOMPARE(converted[0].m_allocatedSize, size1);
    QCOMPARE(converted[0].m_allocationNumber, 0);
    QCOMPARE(converted[0].m_backTrace[0], reinterpret_cast<void*>(1));
    QCOMPARE(converted[0].m_backTrace[1], reinterpret_cast<void*>(2));
    QCOMPARE(converted[0].m_backTrace[2], reinterpret_cast<void*>(3));

    QCOMPARE(converted[1].m_allocatedSize, size2);
    QCOMPARE(converted[1].m_allocationNumber, 1);
    QCOMPARE(converted[1].m_backTrace[0], reinterpret_cast<void*>(4));
    QCOMPARE(converted[1].m_backTrace[1], reinterpret_cast<void*>(5));

    QCOMPARE(converted[2].m_allocatedSize, size3);
    QCOMPARE(converted[2].m_allocationNumber, 2);
    QCOMPARE(converted[2].m_backTrace[0], reinterpret_cast<void*>(6));
    QCOMPARE(converted[2].m_backTrace[1], reinterpret_cast<void*>(7));
}
