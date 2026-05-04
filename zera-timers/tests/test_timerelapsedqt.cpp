#include "test_timerelapsedqt.h"
#include "timerelapsedqt.h"
#include "timerelapsedfortest.h"
#include "timemachinefortest.h"
#include <QTest>

QTEST_MAIN(test_timerelapsedqt)

void test_timerelapsedqt::init()
{
    TimeMachineForTest::reset();
}

void test_timerelapsedqt::elapsedZeroOnNotStartedTiming()
{
    TimerElapsedQt timer;
    QCOMPARE(timer.getElapsedMs(), 0);
}

void test_timerelapsedqt::elapsedZeroOnNotStartedTest()
{
    TimerElapsedForTest timer;
    QCOMPARE(timer.getElapsedMs(), 0);
}

void test_timerelapsedqt::startOnceDelayCheckElapsedTiming()
{
    SKIP_TEST_ON_RELEASE_BUILD
    TimerElapsedQt timer;

    timer.start();
    QTest::qWait(100);

    int elapsed = timer.getElapsedMs();
    QVERIFY(elapsed>=90 && elapsed<=110);
}

void test_timerelapsedqt::startOnceDelayCheckElapsedTest()
{
    TimerElapsedForTest timer;

    timer.start();
    TimeMachineForTest::getInstance()->processTimers(100);

    QCOMPARE(timer.getElapsedMs(), 100);
}

void test_timerelapsedqt::startTwiceDelayCheckElapsedTiming()
{
    SKIP_TEST_ON_RELEASE_BUILD
        TimerElapsedQt timer;

    timer.start();
    QTest::qWait(100);
    timer.start();
    QTest::qWait(100);

    int elapsed = timer.getElapsedMs();
    QVERIFY(elapsed>=90 && elapsed<=110);
}

void test_timerelapsedqt::startTwiceDelayCheckElapsedTest()
{
    TimerElapsedForTest timer;

    timer.start();
    TimeMachineForTest::getInstance()->processTimers(100);
    timer.start();
    TimeMachineForTest::getInstance()->processTimers(100);

    QCOMPARE(timer.getElapsedMs(), 100);
}
