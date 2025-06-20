#include "test_memallocs_atomic.h"
#include "memoryalloctracker.h"
#include "backtracerawtools.h"
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

void test_memallocs_atomic::tripleMallocAndFree()
{
    // start/stop is a bit tricky in here to avoid polution by test code allocs
    MemoryAllocTracker tracker;

    tracker.start();
    char *mem1 = reinterpret_cast<char*>(malloc(100));
    QCOMPARE(tracker.getAllocCount(), 1);
    char *mem2 = reinterpret_cast<char*>(malloc(200));
    QCOMPARE(tracker.getAllocCount(), 2);
    char *mem3 = reinterpret_cast<char*>(malloc(300));
    QCOMPARE(tracker.getAllocCount(), 3);
    tracker.stop();

    QVERIFY(mem1);
    if (mem1)
        strcpy(mem1, "Avoid optimize out 1");
    QVERIFY(mem2);
    if (mem2)
        strcpy(mem2, "Avoid optimize out 2");
    QVERIFY(mem3);
    if (mem3)
        strcpy(mem3, "Avoid optimize out 3");

    AllocatedWithBacktracesRaw allocsRaw = tracker.getAllocationsRaw();
    QCOMPARE(allocsRaw.count(), 3);

    QStringList symbols;
    symbols = BacktraceRawTools::generateSymbols(&allocsRaw[0].m_backTrace);
    QVERIFY(symbols[0].contains("tripleMallocAndFree"));
    symbols = BacktraceRawTools::generateSymbols(&allocsRaw[1].m_backTrace);
    QVERIFY(symbols[0].contains("tripleMallocAndFree"));
    symbols = BacktraceRawTools::generateSymbols(&allocsRaw[2].m_backTrace);
    QVERIFY(symbols[0].contains("tripleMallocAndFree"));

    AllocatedWithBacktraces allocs = tracker.getAllocationsTimeSorted();
    QCOMPARE(allocs.count(), 3);
    QCOMPARE(allocs[0].m_allocatedSize, 100);
    QCOMPARE(allocs[1].m_allocatedSize, 200);
    QCOMPARE(allocs[2].m_allocatedSize, 300);

    quint64 firstAllocNumber = allocs[0].m_allocationNumber;
    QCOMPARE(allocs[1].m_allocationNumber, firstAllocNumber+1);
    QCOMPARE(allocs[2].m_allocationNumber, firstAllocNumber+2);


    tracker.start();
    free(mem1);
    tracker.stop();
    QCOMPARE(tracker.getAllocCount(), 2);
    QCOMPARE(tracker.getAllocationsRaw().count(), 2);
    QCOMPARE(tracker.getAllocationsTimeSorted().count(), 2);

    tracker.start();
    free(mem2);
    tracker.stop();
    QCOMPARE(tracker.getAllocCount(), 1);
    QCOMPARE(tracker.getAllocationsRaw().count(), 1);
    QCOMPARE(tracker.getAllocationsTimeSorted().count(), 1);

    tracker.start();
    free(mem3);
    tracker.stop();
    QCOMPARE(tracker.getAllocCount(), 0);
    QCOMPARE(tracker.getAllocationsRaw().count(), 0);
    QCOMPARE(tracker.getAllocationsTimeSorted().count(), 0);
}

void test_memallocs_atomic::newAndDelete()
{
    MemoryAllocTracker tracker;
    tracker.start();

    QString *string = new QString;
    QCOMPARE(tracker.getAllocCount(), 1);

    tracker.stop();
    AllocatedWithBacktracesRaw allocsRaw = tracker.getAllocationsRaw();
    QCOMPARE(allocsRaw.count(), 1);
    const QStringList symbols = BacktraceRawTools::generateSymbols(&allocsRaw[0].m_backTrace);
    bool found = false;
    for (const QString &entry : symbols)
        if (entry.contains("newAndDelete"))
            found = true;
    QVERIFY(found);

    tracker.start();
    delete string;
    tracker.stop();
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::makeSharedAndReset()
{
    MemoryAllocTracker tracker;
    tracker.start();

    std::shared_ptr<QString> string = std::make_shared<QString>();
    QCOMPARE(tracker.getAllocCount(), 1);

    tracker.stop();
    AllocatedWithBacktracesRaw allocsRaw = tracker.getAllocationsRaw();
    QCOMPARE(allocsRaw.count(), 1);
    const QStringList symbols = BacktraceRawTools::generateSymbols(&allocsRaw[0].m_backTrace);
    bool found = false;
    for (const QString &entry : symbols)
        if (entry.contains("makeSharedAndReset"))
            found = true;
    QVERIFY(found);

    tracker.start();
    string.reset();
    tracker.stop();
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::makeUniqueAndReset()
{
    MemoryAllocTracker tracker;
    tracker.start();

    std::unique_ptr<QString> string = std::make_unique<QString>();
    QCOMPARE(tracker.getAllocCount(), 1);

    tracker.stop();
    AllocatedWithBacktracesRaw allocsRaw = tracker.getAllocationsRaw();
    QCOMPARE(allocsRaw.count(), 1);
    const QStringList symbols = BacktraceRawTools::generateSymbols(&allocsRaw[0].m_backTrace);
    bool found = false;
    for (const QString &entry : symbols)
        if (entry.contains("makeUniqueAndReset"))
            found = true;
    QVERIFY(found);

    tracker.start();
    string.reset();
    tracker.stop();
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
    tracker.stop();
    qInfo("%s", qPrintable(string));
}

void test_memallocs_atomic::mallocInLoop()
{
    constexpr int loopCount = 5;
    char *mem[loopCount];

    MemoryAllocTracker tracker;
    tracker.start();
    for (int i=0; i<loopCount; i++) {
        mem[i] = reinterpret_cast<char*>(malloc(100));
        QCOMPARE(tracker.getAllocCount(), i+1);

        QVERIFY(mem[i]);
        if (mem[i])
            strcpy(mem[i], "Avoid optimize out");
    }

    for (int i=0; i<loopCount; i++) {
        free(mem[i]);
    }
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::reallocAndFree()
{
    MemoryAllocTracker tracker;
    tracker.start();

    char *mem = reinterpret_cast<char*>(realloc(nullptr, 100));
    QCOMPARE(tracker.getAllocCount(), 1);
    QVERIFY(mem);
    if (mem)
        strcpy(mem, "Avoid optimize out");

    free(mem);
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::mallocReallocAndFree()
{
    MemoryAllocTracker tracker;
    tracker.start();

    char *mem = reinterpret_cast<char*>(malloc(100));
    QCOMPARE(tracker.getAllocCount(), 1);
    QVERIFY(mem);
    if (mem)
        strcpy(mem, "Avoid optimize out");

    char *memRealloc = reinterpret_cast<char*>(realloc(mem, 200));
    QCOMPARE(tracker.getAllocCount(), 1);
    QVERIFY(memRealloc);
    if (memRealloc)
        strcpy(memRealloc, "Avoid optimize out");

    free(memRealloc);
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::mallocFreeByRealloc()
{
    MemoryAllocTracker tracker;
    tracker.start();

    char *mem = reinterpret_cast<char*>(malloc(100));
    QCOMPARE(tracker.getAllocCount(), 1);
    QVERIFY(mem);
    if (mem)
        strcpy(mem, "Avoid optimize out");

    char *memRealloc = reinterpret_cast<char*>(realloc(mem, 0));
    QCOMPARE(tracker.getAllocCount(), 0);

    free(memRealloc);
}

void test_memallocs_atomic::oddQStringFree()
{
    MemoryAllocTracker tracker;
    tracker.start();
    {
        QString str("TestString1");
        qInfo("%s", qPrintable(str));
        str += " TestString2";
        qInfo("%s", qPrintable(str));
        QVERIFY(tracker.getAllocCount() != 0);
    }
    QCOMPARE(tracker.getAllocCount(), 0);
}
