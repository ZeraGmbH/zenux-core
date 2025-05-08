#include "test_memallocs_atomic.h"
#include "memoryalloctracker.h"
#include "memoryallocbacktracegenerator.h"
#include <QTest>
#include <memory>
#include <stdlib.h>

QTEST_MAIN(test_memallocs_atomic)

void test_memallocs_atomic::mallocAndFree()
{
    MemoryAllocTracker tracker;
    tracker.start();

    char *mem = reinterpret_cast<char*>(malloc(100));
    QCOMPARE(tracker.getAllocCount(), 1);

    QVERIFY(mem);
    if (mem)
        strcpy(mem, "Avoid optimize out");

    free(mem);
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::mallocTwiceAndFree()
{
    MemoryAllocTracker tracker;

    tracker.start();
    char *mem1 = reinterpret_cast<char*>(malloc(100));
    QCOMPARE(tracker.getAllocCount(), 1);
    char *mem2 = reinterpret_cast<char*>(malloc(200));
    QCOMPARE(tracker.getAllocCount(), 2);
    QVERIFY(mem1);
    if (mem1)
        strcpy(mem1, "Avoid optimize out 1");
    QVERIFY(mem2);
    if (mem2)
        strcpy(mem2, "Avoid optimize out 2");
    tracker.stop();

    MemoryAllocTracker::MemsAllocated mems = tracker.getRawMemRegions();
    QCOMPARE(mems.count(), 2);
    // currently unpredictable sequence / we need some statistics
    //QCOMPARE(mems[0].m_size, 100);
    //QCOMPARE(mems[1].m_size, 200);
    QStringList symbols;
    symbols = MemoryAllocBacktraceGenerator::generateSymbols(&mems[0].m_backTrace);
    QVERIFY(symbols[0].contains("mallocTwiceAndFree"));
    symbols = MemoryAllocBacktraceGenerator::generateSymbols(&mems[1].m_backTrace);
    QVERIFY(symbols[0].contains("mallocTwiceAndFree"));

    tracker.start();
    free(mem1);
    QCOMPARE(tracker.getAllocCount(), 1);
    free(mem2);
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::newAndDelete()
{
    MemoryAllocTracker tracker;
    tracker.start();

    QString *string = new QString;
    QCOMPARE(tracker.getAllocCount(), 1);

    tracker.stop();
    MemoryAllocTracker::MemsAllocated mems = tracker.getRawMemRegions();
    QCOMPARE(mems.count(), 1);
    QStringList symbols = MemoryAllocBacktraceGenerator::generateSymbols(&mems[0].m_backTrace);
    bool found = false;
    for (const QString &entry : symbols)
        if (entry.contains("newAndDelete"))
            found = true;
    QVERIFY(found);

    tracker.start();
    delete string;
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::makeSharedAndReset()
{
    MemoryAllocTracker tracker;
    tracker.start();

    std::shared_ptr<QString> string = std::make_shared<QString>();
    QCOMPARE(tracker.getAllocCount(), 1);

    tracker.stop();
    MemoryAllocTracker::MemsAllocated mems = tracker.getRawMemRegions();
    QCOMPARE(mems.count(), 1);
    QStringList symbols = MemoryAllocBacktraceGenerator::generateSymbols(&mems[0].m_backTrace);
    bool found = false;
    for (const QString &entry : symbols)
        if (entry.contains("makeSharedAndReset"))
            found = true;
    QVERIFY(found);

    tracker.start();
    string.reset();
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::makeUniqueAndReset()
{
    MemoryAllocTracker tracker;
    tracker.start();

    std::unique_ptr<QString> string = std::make_unique<QString>();
    QCOMPARE(tracker.getAllocCount(), 1);

    tracker.stop();
    MemoryAllocTracker::MemsAllocated mems = tracker.getRawMemRegions();
    QCOMPARE(mems.count(), 1);
    QStringList symbols = MemoryAllocBacktraceGenerator::generateSymbols(&mems[0].m_backTrace);
    bool found = false;
    for (const QString &entry : symbols)
        if (entry.contains("makeUniqueAndReset"))
            found = true;
    QVERIFY(found);

    tracker.start();
    string.reset();
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::heapNone()
{
    MemoryAllocTracker tracker;
    tracker.start();

    QString string;
    QCOMPARE(tracker.getAllocCount(), 0);

    string = "testString";

    QCOMPARE(tracker.getAllocCount(), 1);
    qInfo("%s", qPrintable(string));
}
