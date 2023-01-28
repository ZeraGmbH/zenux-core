#ifndef TEST_TIMERSINGLESHOTQT_H
#define TEST_TIMERSINGLESHOTQT_H

#include "timerfortestinterface.h"
#include "timersingleshotqt.h"
#include "timerfortestsingleshot.h"
#include <QObject>
#include <QElapsedTimer>
#include <memory>

// This test compares behavior of TimerSingleShotQt with TimerForTestSingleShot
// with the following target: By using only TimerForTestSingleShot in tests timing
// measurements are done here once and nowhere else because of
// * timing measurements are slow
// * timing measurement are fragile
// Here we make fragility less an issue by running timers with high accuracy

class test_timersingleshotqt : public QObject
{
    Q_OBJECT
private slots:
    void init();

    void signalOnExpireTiming();
    void signalOnExpireTimingTest();

    void restartTiming();
    void restartTimingTest();

    void stopWhilePending();
    void stopWhilePendingTest();

    void queuedConnectionsOnExpire();
    void queuedConnectionsOnExpireTest();

    void nestedStart();
    void nestedStartTest();

    void nestedStartQueued();
    void nestedStartQueuedTest();

    void infiniteExpire();
    void infiniteExpireTest();

private:
    void inspectTimerByDelay(TimerSingleShotQt *timer);
    void inspectTimerByRunner(TimerForTestSingleShot *timer);
    int m_expireCount;
    int m_expireTime;
    std::unique_ptr<QElapsedTimer> m_elapsedTimer;
};

class EventLoopWrapper : public QObject
{
    Q_OBJECT
public:
    EventLoopWrapper() {
        connect(this, &EventLoopWrapper::sigStart,
                this, &EventLoopWrapper::sigReceiveEventLoop,
                Qt::QueuedConnection);
    }
    void start() {
        emit sigStart();
    }
signals:
    void sigStart();
    void sigReceiveEventLoop();
};

class TimerEventLoopWrapper : public QObject
{
    Q_OBJECT
public:
    TimerEventLoopWrapper(TimerTemplateQt* timer) {
        connect(timer, &TimerTemplateQt::sigExpired,
                this, &TimerEventLoopWrapper::sigExpireReceived,
                Qt::QueuedConnection);
    }
signals:
    void sigExpireReceived();
};

#endif // TEST_TIMERSINGLESHOTQT_H
