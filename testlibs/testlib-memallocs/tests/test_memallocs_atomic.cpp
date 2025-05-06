#include "test_memallocs_atomic.h"
#include "testmemalloctracker.h"
#include <QTest>
#include <memory>
#include <stdlib.h>

QTEST_MAIN(test_memallocs_atomic)

void test_memallocs_atomic::mallocAndFree()
{
    TestMemAllocTracker tracker;

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
    TestMemAllocTracker tracker;

    char *mem1 = reinterpret_cast<char*>(malloc(100));
    QCOMPARE(tracker.getAllocCount(), 1);
    char *mem2 = reinterpret_cast<char*>(malloc(100));
    QCOMPARE(tracker.getAllocCount(), 2);

    QVERIFY(mem1);
    if (mem1)
        strcpy(mem1, "Avoid optimize out 1");
    QVERIFY(mem2);
    if (mem2)
        strcpy(mem2, "Avoid optimize out 2");

    free(mem1);
    QCOMPARE(tracker.getAllocCount(), 1);
    free(mem2);
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::newAndDelete()
{
    TestMemAllocTracker tracker;

    QString *string = new QString;
    QCOMPARE(tracker.getAllocCount(), 1);

    delete string;
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::makeSharedAndReset()
{
    TestMemAllocTracker tracker;

    std::shared_ptr<QString> string = std::make_shared<QString>();
    QCOMPARE(tracker.getAllocCount(), 1);

    string.reset();
    QCOMPARE(tracker.getAllocCount(), 0);
}

void test_memallocs_atomic::heapNone()
{
    TestMemAllocTracker tracker;

    QString string;
    QCOMPARE(tracker.getAllocCount(), 0);

    string = "testString";

    QCOMPARE(tracker.getAllocCount(), 1);
    qInfo("%s", qPrintable(string));
}
