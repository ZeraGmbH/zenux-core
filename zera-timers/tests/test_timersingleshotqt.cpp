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
    SKIP_TEST_ON_RELEASE_BUILD
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
    SKIP_TEST_ON_RELEASE_BUILD
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
    SKIP_TEST_ON_RELEASE_BUILD
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

void test_timersingleshotqt::stopWhilePendingByOtherTimer()
{
    SKIP_TEST_ON_RELEASE_BUILD
    TimerSingleShotQt timer(DEFAULT_EXPIRE);
    timer.setHighAccuracy(true);
    inspectTimerByDelay(&timer);

    timer.start();
    TimerSingleShotQt timerStop(DEFAULT_EXPIRE/2);
    connect(&timerStop, &TimerTemplateQt::sigExpired, &timerStop, [&]() {
        timer.stop();
    });
    timerStop.start();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 0);
    QCOMPARE(m_expireTime, 0);
}

void test_timersingleshotqt::stopWhilePendingByOtherTimerTest()
{
    TimerForTestSingleShot timer(DEFAULT_EXPIRE);
    inspectTimerByRunner(&timer);

    timer.start();
    TimerForTestSingleShot timerStop(DEFAULT_EXPIRE/2);
    connect(&timerStop, &TimerTemplateQt::sigExpired, &timerStop, [&]() {
        timer.stop();
    });
    timerStop.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 0);
    QCOMPARE(m_expireTime, 0);
}

void test_timersingleshotqt::stopWhilePendingByOtherSameDelay1()
{
    SKIP_TEST_ON_RELEASE_BUILD
    TimerSingleShotQt timer(DEFAULT_EXPIRE);
    timer.setHighAccuracy(true);
    inspectTimerByDelay(&timer);

    TimerSingleShotQt timerStop(DEFAULT_EXPIRE);
    timerStop.setHighAccuracy(true);
    connect(&timerStop, &TimerTemplateQt::sigExpired, &timerStop, [&]() {
        timer.stop();
    });
    timerStop.start();
    timer.start();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 0);
}

void test_timersingleshotqt::stopWhilePendingByOtherSameDelay1Test()
{
    TimerForTestSingleShot timer(DEFAULT_EXPIRE);
    inspectTimerByRunner(&timer);

    TimerForTestSingleShot timerStop(DEFAULT_EXPIRE);
    connect(&timerStop, &TimerTemplateQt::sigExpired, &timerStop, [&]() {
        timer.stop();
    });
    timerStop.start();
    timer.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 0);
}

void test_timersingleshotqt::stopWhilePendingByOtherSameDelay2()
{
    SKIP_TEST_ON_RELEASE_BUILD
    TimerSingleShotQt timer(DEFAULT_EXPIRE);
    timer.setHighAccuracy(true);
    inspectTimerByDelay(&timer);

    TimerSingleShotQt timerStop(DEFAULT_EXPIRE);
    timerStop.setHighAccuracy(true);
    connect(&timerStop, &TimerTemplateQt::sigExpired, &timerStop, [&]() {
        timer.stop();
    });
    timer.start(); // opposite order than ...Delay1
    timerStop.start();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 1);
}

void test_timersingleshotqt::stopWhilePendingByOtherSameDelay2Test()
{
    TimerForTestSingleShot timer(DEFAULT_EXPIRE);
    inspectTimerByRunner(&timer);

    TimerForTestSingleShot timerStop(DEFAULT_EXPIRE);
    connect(&timerStop, &TimerTemplateQt::sigExpired, &timerStop, [&]() {
        timer.stop();
    });
    timer.start();
    timerStop.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 1);
}

void test_timersingleshotqt::deleteWhilePendingByOtherSameDelay()
{
    SKIP_TEST_ON_RELEASE_BUILD
    TimerSingleShotQt* timer = new TimerSingleShotQt(DEFAULT_EXPIRE);
    timer->setHighAccuracy(true);
    inspectTimerByDelay(timer);

    TimerSingleShotQt timerStop(DEFAULT_EXPIRE);
    timerStop.setHighAccuracy(true);
    connect(&timerStop, &TimerTemplateQt::sigExpired, &timerStop, [&]() {
        delete timer;
    });
    timerStop.start();
    timer->start();
    QTest::qWait(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 0);
}

void test_timersingleshotqt::deleteWhilePendingByOtherSameDelayTest()
{
    TimerForTestSingleShot* timer = new TimerForTestSingleShot(DEFAULT_EXPIRE);
    inspectTimerByRunner(timer);

    TimerForTestSingleShot timerStop(DEFAULT_EXPIRE);
    connect(&timerStop, &TimerTemplateQt::sigExpired, &timerStop, [&]() {
        delete timer;
    });
    timerStop.start();
    timer->start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 0);
}

void test_timersingleshotqt::queuedConnectionsOnExpire()
{
    SKIP_TEST_ON_RELEASE_BUILD
    TimerSingleShotQt timer(DEFAULT_EXPIRE);
    timer.setHighAccuracy(true);
    inspectTimerByDelay(&timer);
    TimerEventLoopWrapper evTest(&timer);
    int expireReceived = 0;
    connect(&evTest, &TimerEventLoopWrapper::sigExpireReceived, &evTest, [&]{
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
    connect(&evTest, &TimerEventLoopWrapper::sigExpireReceived, &evTest, [&]{
        expireReceived++;
    });
    timer.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(expireReceived, 1);
}

void test_timersingleshotqt::nestedStart()
{
    SKIP_TEST_ON_RELEASE_BUILD
    TimerSingleShotQt timer1(DEFAULT_EXPIRE/2);
    timer1.setHighAccuracy(true);
    inspectTimerByDelay(&timer1);
    TimerSingleShotQt timer2(DEFAULT_EXPIRE/2);
    timer2.setHighAccuracy(true);
    inspectTimerByDelay(&timer2);
    connect(&timer1, &TimerTemplateQt::sigExpired, &timer1, [&]{
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
    connect(&timer1, &TimerTemplateQt::sigExpired, &timer1, [&]{
        timer2.start();
    });

    timer1.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 2);
}

void test_timersingleshotqt::nestedStartQueued()
{
    SKIP_TEST_ON_RELEASE_BUILD
    TimerSingleShotQt timer1(DEFAULT_EXPIRE/2);
    timer1.setHighAccuracy(true);
    inspectTimerByDelay(&timer1);
    EventLoopWrapper evLoop1;
    connect(&evLoop1, &EventLoopWrapper::sigReceiveEventLoop, &evLoop1, [&]{
        timer1.start();
    });
    TimerSingleShotQt timer2(DEFAULT_EXPIRE/2);
    timer2.setHighAccuracy(true);
    inspectTimerByDelay(&timer2);
    EventLoopWrapper evLoop2;
    connect(&evLoop2, &EventLoopWrapper::sigReceiveEventLoop, &evLoop2, [&]{
        timer2.start();
    });
    connect(&timer1, &TimerTemplateQt::sigExpired, &timer1, [&]{
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
    connect(&evLoop1, &EventLoopWrapper::sigReceiveEventLoop, &evLoop1, [&]{
        timer1.start();
    });
    TimerForTestSingleShot timer2(DEFAULT_EXPIRE/2);
    inspectTimerByRunner(&timer2);
    EventLoopWrapper evLoop2;
    connect(&evLoop2, &EventLoopWrapper::sigReceiveEventLoop, &evLoop2, [&]{
        timer2.start();
    });
    connect(&timer1, &TimerTemplateQt::sigExpired, &timer1, [&]{
        evLoop2.start();
    });

    evLoop1.start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(m_expireCount, 2);
}

void test_timersingleshotqt::infiniteExpire()
{
    SKIP_TEST_ON_RELEASE_BUILD
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

void test_timersingleshotqt::isRunning()
{
    SKIP_TEST_ON_RELEASE_BUILD
    TimerSingleShotQt timer(DEFAULT_EXPIRE);
    timer.setHighAccuracy(true);
    QCOMPARE(timer.isRunning(), false);
    timer.start();
    QCOMPARE(timer.isRunning(), true);
    timer.stop();
    QCOMPARE(timer.isRunning(), false);
    timer.start();
    QCOMPARE(timer.isRunning(), true);
    QTest::qWait(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(timer.isRunning(), false);
}

void test_timersingleshotqt::isRunningTest()
{
    TimerForTestSingleShot timer(DEFAULT_EXPIRE);
    QCOMPARE(timer.isRunning(), false);
    timer.start();
    QCOMPARE(timer.isRunning(), true);
    timer.stop();
    QCOMPARE(timer.isRunning(), false);
    timer.start();
    QCOMPARE(timer.isRunning(), true);
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(timer.isRunning(), false);
}
