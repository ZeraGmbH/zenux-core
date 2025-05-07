#include "test_backtrace_generator.h"
#include "testbacktracegenerator.h"
#include <QTest>

QTEST_MAIN(test_backtrace_generator)

void test_backtrace_generator::generateBacktrace()
{
    TestBacktraceGenerator::BacktraceRaw btrace;
    TestBacktraceGenerator::createBacktraceRaw(&btrace);
    QStringList symbols = TestBacktraceGenerator::generateSymbols(&btrace);
    QVERIFY(logOnNotContains(symbols[0], "generateBacktrace"));
}

void test_backtrace_generator::generateBacktraceThroughIntermediateFunction()
{
    QStringList rawBacktrace = intermediateBacktraceFkt();
    QVERIFY(logOnNotContains(rawBacktrace[0], "intermediateBacktraceFkt"));
    QVERIFY(logOnNotContains(rawBacktrace[1], "generateBacktraceThroughIntermediateFunction"));
}

bool test_backtrace_generator::logOnNotContains(const QString &found, const QString contains)
{
    if (!found.contains(contains)) {
        qWarning("%s not found in %s", qPrintable(contains), qPrintable(found));
        return false;
    }
    return true;
}

QStringList test_backtrace_generator::intermediateBacktraceFkt()
{
    TestBacktraceGenerator::BacktraceRaw btrace;
    TestBacktraceGenerator::createBacktraceRaw(&btrace);
    return TestBacktraceGenerator::generateSymbols(&btrace);
}
