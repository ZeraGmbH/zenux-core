#include "test_timerperiodicqt.h"
#include "timemachinefortest.h"
#include "realdelaytimerhelpers.h"
#include "timersingleshotqt.h"
#include "timerfortestsingleshot.h"
#include <QTest>

QTEST_MAIN(test_timerperiodicqt)

void test_timerperiodicqt::init()
{
    m_expireTimes.clear();
    m_elapsedTimer = std::make_unique<QElapsedTimer>();
    TimeMachineForTest::reset();
}

void test_timerperiodicqt::inspectTimerByDelay(TimerPeriodicQt *timer)
{
    m_elapsedTimer->start();
    connect(timer, &TimerTemplateQt::sigExpired, [&]{
        m_expireTimes.append(m_elapsedTimer->elapsed());
    });
}

void test_timerperiodicqt::inspectTimerByRunner(TimerForTestPeriodic *timer)
{
    connect(timer, &TimerTemplateQt::sigExpired, [&]{
        m_expireTimes.append(TimeMachineForTest::getInstance()->getCurrentTimeMs());
    });
}

void test_timerperiodicqt::oneInterval()
{
    TimerPeriodicQt timer(DEFAULT_EXPIRE);
    inspectTimerByDelay(&timer);
    timer.setHighAccuracy(true);

    timer.start();
    QTest::qWait(DEFAULT_EXPIRE + DEFAULT_PERIODIC_EXTRA_WAIT);

    QCOMPARE(m_expireTimes.size(), 1);
    QVERIFY(RealDelayTimerHelpers::isExpireTimeWithinLimits(m_expireTimes.at(0), DEFAULT_EXPIRE)); // fuzzy
}

void test_timerperiodicqt::oneIntervalTest()
{
    TimerForTestPeriodic timer(DEFAULT_EXPIRE);
    inspectTimerByRunner(&timer);

    timer.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE + DEFAULT_PERIODIC_EXTRA_WAIT);

    QCOMPARE(m_expireTimes.size(), 1);
    QCOMPARE(m_expireTimes.at(0), DEFAULT_EXPIRE); // on point
}

void test_timerperiodicqt::threeInterval()
{
    TimerPeriodicQt timer(DEFAULT_EXPIRE);
    inspectTimerByDelay(&timer);
    timer.setHighAccuracy(true);

    timer.start();
    QTest::qWait(DEFAULT_EXPIRE*3 + DEFAULT_PERIODIC_EXTRA_WAIT);

    QCOMPARE(m_expireTimes.size(), 3);
    QVERIFY(RealDelayTimerHelpers::isExpireTimeWithinLimits(m_expireTimes.at(0), DEFAULT_EXPIRE)); // fuzzy
    QVERIFY(RealDelayTimerHelpers::isExpireTimeWithinLimits(m_expireTimes.at(1), DEFAULT_EXPIRE*2));
    QVERIFY(RealDelayTimerHelpers::isExpireTimeWithinLimits(m_expireTimes.at(2), DEFAULT_EXPIRE*3));
}

void test_timerperiodicqt::threeIntervalTest()
{
    TimerForTestPeriodic timer(DEFAULT_EXPIRE);
    inspectTimerByRunner(&timer);

    timer.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE*3 + DEFAULT_PERIODIC_EXTRA_WAIT);

    QCOMPARE(m_expireTimes.size(), 3);
    QCOMPARE(m_expireTimes.at(0), DEFAULT_EXPIRE); // on point
    QCOMPARE(m_expireTimes.at(1), DEFAULT_EXPIRE*2);
    QCOMPARE(m_expireTimes.at(2), DEFAULT_EXPIRE*3);
}

void test_timerperiodicqt::stopWhilePendingByOtherTimer()
{
    TimerPeriodicQt timer(DEFAULT_EXPIRE);
    timer.setHighAccuracy(true);
    inspectTimerByDelay(&timer);

    timer.start();
    TimerSingleShotQt timerStop(DEFAULT_EXPIRE*3/2);
    connect(&timerStop, &TimerTemplateQt::sigExpired, &timerStop, [&]() {
        timer.stop();
    });
    timerStop.start();
    QTest::qWait(2*DEFAULT_EXPIRE + DEFAULT_PERIODIC_EXTRA_WAIT);

    QCOMPARE(m_expireTimes.size(), 1);
    QVERIFY(RealDelayTimerHelpers::isExpireTimeWithinLimits(m_expireTimes.at(0), DEFAULT_EXPIRE)); // fuzzy
}

void test_timerperiodicqt::stopWhilePendingByOtherTimerTest()
{
    TimerForTestPeriodic timer(DEFAULT_EXPIRE);
    inspectTimerByRunner(&timer);

    timer.start();
    TimerForTestSingleShot timerStop(DEFAULT_EXPIRE*3/2);
    connect(&timerStop, &TimerTemplateQt::sigExpired, &timerStop, [&]() {
        timer.stop();
    });
    timerStop.start();
    TimeMachineForTest::getInstance()->processTimers(2*DEFAULT_EXPIRE + DEFAULT_PERIODIC_EXTRA_WAIT);

    QCOMPARE(m_expireTimes.size(), 1);
    QCOMPARE(m_expireTimes.at(0), DEFAULT_EXPIRE); // on point
}
