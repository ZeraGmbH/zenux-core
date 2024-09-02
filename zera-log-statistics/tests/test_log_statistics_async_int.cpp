#include "test_log_statistics_async_int.h"
#include "logstatisticsasyncint.h"
#include <timemachineobject.h>
#include <timemachinefortest.h>
#include <timerfactoryqtfortest.h>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_log_statistics_async_int)

constexpr int test_period_ms = 10;
constexpr int test_value1 = 39;
constexpr int test_value2 = 42;

void test_log_statistics_async_int::initTestCase()
{
    TimerFactoryQtForTest::enableTest();
}

void test_log_statistics_async_int::noSignalsForNoValuesAdded()
{
    LogStatisticsAsyncInt statistics(test_period_ms);
    QSignalSpy spy(&statistics, &LogStatisticsAsyncInt::sigNewStatistics);

    TimeMachineForTest::getInstance()->processTimers(test_period_ms);
    QCOMPARE(spy.count(), 0);
}

void test_log_statistics_async_int::oneValueAdded()
{
    LogStatisticsAsyncInt statistics(test_period_ms);
    QSignalSpy spy(&statistics, &LogStatisticsAsyncInt::sigNewStatistics);

    statistics.addValue(test_value1);

    TimeMachineForTest::getInstance()->processTimers(test_period_ms);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], test_value1);
    QCOMPARE(spy[0][1], test_value1);
    QCOMPARE(spy[0][2], test_value1);
}

void test_log_statistics_async_int::twoValuesAdded()
{
    LogStatisticsAsyncInt statistics(test_period_ms);
    QSignalSpy spy(&statistics, &LogStatisticsAsyncInt::sigNewStatistics);

    statistics.addValue(test_value1);
    statistics.addValue(test_value2);

    TimeMachineForTest::getInstance()->processTimers(test_period_ms);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], test_value1);
    QCOMPARE(spy[0][1], test_value2);
    QCOMPARE(spy[0][2], float(test_value1+test_value2)/2);
}

void test_log_statistics_async_int::twoValuesAddedTwoTimeSlots()
{
    LogStatisticsAsyncInt statistics(test_period_ms);
    QSignalSpy spy(&statistics, &LogStatisticsAsyncInt::sigNewStatistics);

    statistics.addValue(test_value1);
    statistics.addValue(test_value2);
    TimeMachineForTest::getInstance()->processTimers(test_period_ms);
    QCOMPARE(spy.count(), 1);

    statistics.addValue(test_value1);
    TimeMachineForTest::getInstance()->processTimers(test_period_ms);

    QCOMPARE(spy.count(), 2);
    QCOMPARE(spy[0][0], test_value1);
    QCOMPARE(spy[0][1], test_value2);
    QCOMPARE(spy[0][2], float(test_value1+test_value2)/2);
    QCOMPARE(spy[0][3], 2);

    QCOMPARE(spy[1][0], test_value1);
    QCOMPARE(spy[1][1], test_value1);
    QCOMPARE(spy[1][2], test_value1);
    QCOMPARE(spy[1][3], 1);
}
