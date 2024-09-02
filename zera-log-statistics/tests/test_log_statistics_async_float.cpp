#include "test_log_statistics_async_float.h"
#include "logstatisticsasyncfloat.h"
#include <timemachineobject.h>
#include <timemachinefortest.h>
#include <timerfactoryqtfortest.h>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_log_statistics_async_float)

constexpr int test_period_ms = 10;
constexpr float test_value1 = 38.5;
constexpr float test_value2 = 42.0;

void test_log_statistics_async_float::initTestCase()
{
    TimerFactoryQtForTest::enableTest();
}

void test_log_statistics_async_float::noSignalsForNoValuesAdded()
{
    LogStatisticsAsyncFloat statistics(test_period_ms);
    QSignalSpy spy(&statistics, &LogStatisticsAsyncFloat::sigNewStatistics);

    statistics.addValue(qQNaN());

    TimeMachineForTest::getInstance()->processTimers(test_period_ms);
    QCOMPARE(spy.count(), 0);
}

void test_log_statistics_async_float::noSignalsForNanAdded()
{
    LogStatisticsAsyncFloat statistics(test_period_ms);
    QSignalSpy spy(&statistics, &LogStatisticsAsyncFloat::sigNewStatistics);

    TimeMachineForTest::getInstance()->processTimers(test_period_ms);
    QCOMPARE(spy.count(), 0);
}

void test_log_statistics_async_float::oneValueAdded()
{
    LogStatisticsAsyncFloat statistics(test_period_ms);
    QSignalSpy spy(&statistics, &LogStatisticsAsyncFloat::sigNewStatistics);

    statistics.addValue(test_value1);

    TimeMachineForTest::getInstance()->processTimers(test_period_ms);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], test_value1);
    QCOMPARE(spy[0][1], test_value1);
    QCOMPARE(spy[0][2], test_value1);
}

void test_log_statistics_async_float::twoValuesAdded()
{
    LogStatisticsAsyncFloat statistics(test_period_ms);
    QSignalSpy spy(&statistics, &LogStatisticsAsyncFloat::sigNewStatistics);

    statistics.addValue(test_value1);
    statistics.addValue(test_value2);

    TimeMachineForTest::getInstance()->processTimers(test_period_ms);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], test_value1);
    QCOMPARE(spy[0][1], test_value2);
    QCOMPARE(spy[0][2], (test_value1+test_value2)/2);
}

void test_log_statistics_async_float::threValuesAddedNanIgnored()
{
    LogStatisticsAsyncFloat statistics(test_period_ms);
    QSignalSpy spy(&statistics, &LogStatisticsAsyncFloat::sigNewStatistics);

    statistics.addValue(test_value1);
    statistics.addValue(test_value2);
    statistics.addValue(qQNaN());

    TimeMachineForTest::getInstance()->processTimers(test_period_ms);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], test_value1);
    QCOMPARE(spy[0][1], test_value2);
    QCOMPARE(spy[0][2], (test_value1+test_value2)/2);
}

void test_log_statistics_async_float::twoValuesAddedTwoTimeSlots()
{
    LogStatisticsAsyncFloat statistics(test_period_ms);
    QSignalSpy spy(&statistics, &LogStatisticsAsyncFloat::sigNewStatistics);

    statistics.addValue(test_value1);
    statistics.addValue(test_value2);
    TimeMachineForTest::getInstance()->processTimers(test_period_ms);
    QCOMPARE(spy.count(), 1);

    statistics.addValue(test_value1);
    TimeMachineForTest::getInstance()->processTimers(test_period_ms);

    QCOMPARE(spy.count(), 2);
    QCOMPARE(spy[0][0], test_value1);
    QCOMPARE(spy[0][1], test_value2);
    QCOMPARE(spy[0][2], (test_value1+test_value2)/2);
    QCOMPARE(spy[0][3], 2);

    QCOMPARE(spy[1][0], test_value1);
    QCOMPARE(spy[1][1], test_value1);
    QCOMPARE(spy[1][2], test_value1);
    QCOMPARE(spy[1][3], 1);

}
