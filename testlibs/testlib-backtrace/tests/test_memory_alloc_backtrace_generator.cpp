#include "test_memory_alloc_backtrace_generator.h"
#include "memoryallocbacktracegenerator.h"
#include <QTest>

QTEST_MAIN(test_memory_alloc_backtrace_generator)

void test_memory_alloc_backtrace_generator::generateBacktrace()
{
    MemoryAllocBacktraceGenerator::BacktraceRaw btrace;
    MemoryAllocBacktraceGenerator::createBacktraceRaw(&btrace);
    QStringList symbols = MemoryAllocBacktraceGenerator::generateSymbols(&btrace);
    QVERIFY(logOnNotContains(symbols[0], "generateBacktrace"));
}

void test_memory_alloc_backtrace_generator::generateBacktraceThroughIntermediateFunction()
{
    QStringList rawBacktrace = intermediateBacktraceFkt();
    QVERIFY(logOnNotContains(rawBacktrace[0], "intermediateBacktraceFkt"));
    QVERIFY(logOnNotContains(rawBacktrace[1], "generateBacktraceThroughIntermediateFunction"));
}

bool test_memory_alloc_backtrace_generator::logOnNotContains(const QString &found, const QString contains)
{
    if (!found.contains(contains)) {
        qWarning("%s not found in %s", qPrintable(contains), qPrintable(found));
        return false;
    }
    return true;
}

QStringList test_memory_alloc_backtrace_generator::intermediateBacktraceFkt()
{
    MemoryAllocBacktraceGenerator::BacktraceRaw btrace;
    MemoryAllocBacktraceGenerator::createBacktraceRaw(&btrace);
    return MemoryAllocBacktraceGenerator::generateSymbols(&btrace);
}
