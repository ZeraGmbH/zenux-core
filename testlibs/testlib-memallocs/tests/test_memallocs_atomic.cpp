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
