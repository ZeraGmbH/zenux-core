#include "test_timersingleshotqt.h"
#include "timertestdefaults.h"
#include "timemachinefortest.h"
#include "realdelaytimerhelpers.h"
#include <QTest>

QTEST_MAIN(test_timersingleshotqt)

void test_timersingleshotqt::init()
{
    m_expireCount = 0;
    m_expireTime = 0;
    m_elapsedTimer = std::make_unique<QElapsedTimer>();
    TimeMachineForTest::reset();
}

void test_timersingleshotqt::inspectTimerByDelay(TimerSingleShotQt *timer)
{
    m_elapsedTimer->start();
    connect(timer, &TimerSingleShotQt::sigExpired, [&]{
        m_expireCount++;
        m_expireTime = m_elapsedTimer->elapsed();
    });
}

void test_timersingleshotqt::inspectTimerByRunner(TimerForTestSingleShot *timer)
{
    connect(timer, &TimerSingleShotQt::sigExpired, [&]{
        m_expireCount++;
        m_expireTime = TimeMachineForTest::getInstance()->getCurrentTimeMs();
    });
}

void test_timersingleshotqt::signalOnExpireTiming()
{
    TimerSingleShotQt timer(DEFAULT_EXPIRE);
    timer.setHighAccuracy(true);
    inspectTimerByDelay(&timer);

    timer.start();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 1);
    QVERIFY(RealDelayTimerHelpers::isExpireTimeWithinLimits(m_expireTime, DEFAULT_EXPIRE)); // fuzzy
}

void test_timersingleshotqt::signalOnExpireTimingTest()
{
    TimerForTestSingleShot timer(DEFAULT_EXPIRE);
    inspectTimerByRunner(&timer);

    timer.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 1);
    QCOMPARE(m_expireTime, DEFAULT_EXPIRE); // on point
}

void test_timersingleshotqt::restartTiming()
{
    TimerSingleShotQt timer(DEFAULT_EXPIRE);
    timer.setHighAccuracy(true);
    inspectTimerByDelay(&timer);

    timer.start();
    QTest::qWait(DEFAULT_EXPIRE/2);
    timer.start();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 1);
    QVERIFY(RealDelayTimerHelpers::isExpireTimeWithinLimits(m_expireTime, DEFAULT_EXPIRE*1.5)); // fuzzy
}

void test_timersingleshotqt::restartTimingTest()
{
    TimerForTestSingleShot timer(DEFAULT_EXPIRE);
    inspectTimerByRunner(&timer);

    timer.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE/2);
    timer.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 1);
    QCOMPARE(m_expireTime, DEFAULT_EXPIRE*1.5); // on point
}

void test_timersingleshotqt::stopWhilePending()
{
    TimerSingleShotQt timer(DEFAULT_EXPIRE);
    timer.setHighAccuracy(true);
    inspectTimerByDelay(&timer);

    timer.start();
    QTest::qWait(DEFAULT_EXPIRE/2);
    timer.stop();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 0);
    QCOMPARE(m_expireTime, 0);
}

void test_timersingleshotqt::stopWhilePendingTest()
{
    TimerForTestSingleShot timer(DEFAULT_EXPIRE);
    inspectTimerByRunner(&timer);

    timer.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE/2);
    timer.stop();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 0);
    QCOMPARE(m_expireTime, 0);
}

void test_timersingleshotqt::queuedConnectionsOnExpire()
{
    TimerSingleShotQt timer(DEFAULT_EXPIRE);
    timer.setHighAccuracy(true);
    inspectTimerByDelay(&timer);
    TimerEventLoopWrapper evTest(&timer);
    int expireReceived = 0;
    connect(&evTest, &TimerEventLoopWrapper::sigExpireReceived, [&]{
        expireReceived++;
    });

    timer.start();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(expireReceived, 1);
}

void test_timersingleshotqt::queuedConnectionsOnExpireTest()
{
    TimerForTestSingleShot timer(DEFAULT_EXPIRE);
    inspectTimerByRunner(&timer);
    TimerEventLoopWrapper evTest(&timer);
    int expireReceived = 0;
    connect(&evTest, &TimerEventLoopWrapper::sigExpireReceived, [&]{
        expireReceived++;
    });

    timer.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(expireReceived, 1);
}

void test_timersingleshotqt::nestedStart()
{
    TimerSingleShotQt timer1(DEFAULT_EXPIRE/2);
    timer1.setHighAccuracy(true);
    inspectTimerByDelay(&timer1);
    TimerSingleShotQt timer2(DEFAULT_EXPIRE/2);
    timer2.setHighAccuracy(true);
    inspectTimerByDelay(&timer2);
    connect(&timer1, &TimerTemplateQt::sigExpired, [&]{
        timer2.start();
    });

    timer1.start();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 2);
}

void test_timersingleshotqt::nestedStartTest()
{
    TimerForTestSingleShot timer1(DEFAULT_EXPIRE/2);
    inspectTimerByRunner(&timer1);
    TimerForTestSingleShot timer2(DEFAULT_EXPIRE/2);
    inspectTimerByRunner(&timer2);
    connect(&timer1, &TimerTemplateQt::sigExpired, [&]{
        timer2.start();
    });

    timer1.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 2);
}

void test_timersingleshotqt::nestedStartQueued()
{
    TimerSingleShotQt timer1(DEFAULT_EXPIRE/2);
    timer1.setHighAccuracy(true);
    inspectTimerByDelay(&timer1);
    EventLoopWrapper evLoop1;
    connect(&evLoop1, &EventLoopWrapper::sigReceiveEventLoop, [&]{
        timer1.start();
    });
    TimerSingleShotQt timer2(DEFAULT_EXPIRE/2);
    timer2.setHighAccuracy(true);
    inspectTimerByDelay(&timer2);
    EventLoopWrapper evLoop2;
    connect(&evLoop2, &EventLoopWrapper::sigReceiveEventLoop, [&]{
        timer2.start();
    });
    connect(&timer1, &TimerTemplateQt::sigExpired, [&]{
        evLoop2.start();
    });

    evLoop1.start();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 2);
}

void test_timersingleshotqt::nestedStartQueuedTest()
{
    TimerForTestSingleShot timer1(DEFAULT_EXPIRE/2);
    inspectTimerByRunner(&timer1);
    EventLoopWrapper evLoop1;
    connect(&evLoop1, &EventLoopWrapper::sigReceiveEventLoop, [&]{
        timer1.start();
    });
    TimerForTestSingleShot timer2(DEFAULT_EXPIRE/2);
    inspectTimerByRunner(&timer2);
    EventLoopWrapper evLoop2;
    connect(&evLoop2, &EventLoopWrapper::sigReceiveEventLoop, [&]{
        timer2.start();
    });
    connect(&timer1, &TimerTemplateQt::sigExpired, [&]{
        evLoop2.start();
    });

    evLoop1.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 2);
}

void test_timersingleshotqt::infiniteExpire()
{
    TimerSingleShotQt timer(EXPIRE_INFINITE);
    timer.setHighAccuracy(true);
    inspectTimerByDelay(&timer);

    timer.start();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 0);
    QCOMPARE(m_expireTime, 0);
}

void test_timersingleshotqt::infiniteExpireTest()
{
    TimerForTestSingleShot timer(EXPIRE_INFINITE);
    inspectTimerByRunner(&timer);

    timer.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 0);
    QCOMPARE(m_expireTime, 0);
}
