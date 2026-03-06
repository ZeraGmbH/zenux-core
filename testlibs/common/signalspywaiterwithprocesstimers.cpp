#include "signalspywaiterwithprocesstimers.h"
#include "timemachinefortest.h"
#include <QElapsedTimer>
#include <QTest>

int SignalSpyWaiterWithProcessTimers::waitForSignals(const QSignalSpy *spy, int signalCount, int timeoutMs)
{
    QElapsedTimer timer;
    timer.start();
    while(spy->count() < signalCount  && timer.elapsed() < timeoutMs) {
        QTest::qWait(1);
        TimeMachineForTest::getInstance()->processTimers(1);
    }
    return timer.elapsed();
}
