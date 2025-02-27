#include "signalspywaiter.h"
#include <QTest>

int SignalSpyWaiter::waitForSignals(QSignalSpy *spy, int signalCount, int timeoutMs)
{
    int currMs;
    for(currMs=0; currMs<timeoutMs; currMs++) {
        if (spy->count() >= signalCount)
            break;
        QTest::qWait(1);
    }
    return currMs;
}
