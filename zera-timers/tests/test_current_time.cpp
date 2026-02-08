#include "test_current_time.h"
#include "timerfactoryqtfortest.h"
#include "timemachinefortest.h"
#include <QTest>

QTEST_MAIN(test_current_time)

void test_current_time::init()
{
    TimeMachineForTest::reset();
}

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

    QDate date;
    QTime time;
    QTimeZone tz;
    QDateTime dtTimeTest = createTestDateTime(date, time, tz);

    dtTimeTest.setMSecsSinceEpoch(100);
    QCOMPARE(dtTime1, dtTimeTest);

    dtTimeTest.setMSecsSinceEpoch(100+150);
    QCOMPARE(dtTime2, dtTimeTest);
}

void test_current_time::enableTestSetTime()
{
    TimerFactoryQtForTest::enableTest();

    QDate date;
    QTime time;
    QTimeZone tz;
    QDateTime startTime = createTestDateTime(date, time, tz);
    TimeMachineForTest::getInstance()->setCurrentTime(date, time, tz);

    QCOMPARE(TimerFactoryQtForTest::getCurrentTime(), startTime);
}

void test_current_time::enableTestSetTimeProgression()
{
    TimerFactoryQtForTest::enableTest();

    QDate date;
    QTime time;
    QTimeZone tz;
    QDateTime startTime = createTestDateTime(date, time, tz);
    TimeMachineForTest::getInstance()->setCurrentTime(date, time, tz);

    TimeMachineForTest::getInstance()->processTimers(100);
    QDateTime dtTime1 = TimerFactoryQtForTest::getCurrentTime();
    QCOMPARE(startTime.addMSecs(100), dtTime1);

    TimeMachineForTest::getInstance()->setCurrentTime(date, time, tz);
    TimeMachineForTest::getInstance()->processTimers(150);
    QDateTime dtTime2 = TimerFactoryQtForTest::getCurrentTime();
    QCOMPARE(startTime.addMSecs(150), dtTime2);
}

void test_current_time::enableTestSetTimeReset()
{
    TimerFactoryQtForTest::enableTest();

    QDate date;
    QTime time;
    QTimeZone tz;
    QDateTime startTime = createTestDateTime(date, time, tz);
    TimeMachineForTest::getInstance()->setCurrentTime(date, time, tz);

    TimeMachineForTest::reset();
    QDateTime dtTime = TimerFactoryQtForTest::getCurrentTime();
    QCOMPARE(dtTime.toMSecsSinceEpoch(), 0);
}

void test_current_time::enableTestSetProgressionCompareUTC()
{
    TimerFactoryQtForTest::enableTest();

    QDate date;
    QTime time;
    QTimeZone tz;
    QDateTime startTime = createTestDateTime(date, time, tz);
    TimeMachineForTest::getInstance()->setCurrentTime(date, time, tz);
    TimeMachineForTest::getInstance()->processTimers(100);

    QDateTime dtTime = TimerFactoryQtForTest::getCurrentTime();
    QCOMPARE(startTime.addMSecs(100), dtTime);
    QCOMPARE(dtTime.offsetFromUtc(), startTime.offsetFromUtc());
}

void test_current_time::enableTestSetCompareBothSetters()
{
    TimerFactoryQtForTest::enableTest();

    QDate date;
    QTime time;
    QTimeZone tz;
    QDateTime startTime = createTestDateTime(date, time, tz);

    TimeMachineForTest::getInstance()->setCurrentTime(date, time, tz);
    QDateTime dtTime1 = TimerFactoryQtForTest::getCurrentTime();
    TimeMachineForTest::getInstance()->setCurrentTime(startTime.addMSecs(100));
    QDateTime dtTime2 = TimerFactoryQtForTest::getCurrentTime();

    QCOMPARE(dtTime1.addMSecs(100), dtTime2);
}

QDateTime test_current_time::createTestDateTime(QDate &date, QTime &time, QTimeZone &tz) const
{
    date = QDate(2026, 2, 8);
    time = QTime(13, 15, 55, 357);
    tz = QTimeZone(-3600);
    return QDateTime(date, time, tz);
}
