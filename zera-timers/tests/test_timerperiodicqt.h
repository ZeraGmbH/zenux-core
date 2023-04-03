#ifndef TEST_TIMERPERIODICQT_H
#define TEST_TIMERPERIODICQT_H

#include "timerfortestperiodic.h"
#include "timerperiodicqt.h"
#include <QElapsedTimer>
#include <QList>
#include <memory>

class test_timerperiodicqt : public QObject
{
    Q_OBJECT
private slots:
    void init();

    void oneInterval();
    void oneIntervalTest();

    void threeInterval();
    void threeIntervalTest();

    void stopWhilePendingByOtherTimer();
    void stopWhilePendingByOtherTimerTest();

    void isRunning();
    void isRunningTest();
private:
    void inspectTimerByDelay(TimerPeriodicQt *timer);
    void inspectTimerByRunner(TimerForTestPeriodic *timer);
    QList<int> m_expireTimes;
    std::unique_ptr<QElapsedTimer> m_elapsedTimer;
};

#endif // TEST_TIMERPERIODICQT_H
