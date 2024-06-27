#include "test_current_time.h"
#include "timerfactoryqtfortest.h"
#include "timemachinefortest.h"
#include <QTest>

QTEST_MAIN(test_current_time)

void test_current_time::disableTest()
{
    TimerFactoryQtForTest::disableTest();

    QDateTime dtTime1 = TimerFactoryQtForTest::getCurrentTime();
    QTest::qSleep(10);
    QDateTime dtTime2 = TimerFactoryQtForTest::getCurrentTime();
    QVERIFY(dtTime2 > dtTime1);
}

void test_current_time::enableTestNoTimeProgression()
{
    TimerFactoryQtForTest::enableTest();

    QDateTime dtTime1 = TimerFactoryQtForTest::getCurrentTime();
    QTest::qSleep(10);
    QDateTime dtTime2 = TimerFactoryQtForTest::getCurrentTime();
    QCOMPARE(dtTime2, dtTime1);
}

void test_current_time::enableTestTimeProgression()
{
    TimerFactoryQtForTest::enableTest();

    TimeMachineForTest::getInstance()->processTimers(100);
    QDateTime dtTime1 = TimerFactoryQtForTest::getCurrentTime();
    TimeMachineForTest::getInstance()->processTimers(150);
    QDateTime dtTime2 = TimerFactoryQtForTest::getCurrentTime();

    QDateTime dtTimeTest;

    dtTimeTest.setMSecsSinceEpoch(100);
    QCOMPARE(dtTime1, dtTimeTest);

    dtTimeTest.setMSecsSinceEpoch(100+150);
    QCOMPARE(dtTime2, dtTimeTest);
}
