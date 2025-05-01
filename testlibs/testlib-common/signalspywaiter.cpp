#include "signalspywaiter.h"
#include <QElapsedTimer>
#include <QTest>

int SignalSpyWaiter::waitForSignals(QSignalSpy *spy, int signalCount, int timeoutMs)
{
    QElapsedTimer timer;
    timer.start();
    while(spy->count() < signalCount  && timer.elapsed() < timeoutMs)
        QTest::qWait(1);
    return timer.elapsed();
}
