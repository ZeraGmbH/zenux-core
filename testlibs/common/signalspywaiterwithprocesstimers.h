#ifndef SIGNALSPYWAITERWITHPROCESSTIMERS_H
#define SIGNALSPYWAITERWITHPROCESSTIMERS_H

#include <QSignalSpy>

class SignalSpyWaiterWithProcessTimers
{
public:
    // We have seen QSignalSpy::wait not working as expected...
    static int waitForSignals(const QSignalSpy *spy,
                              int signalCount,
                              int timeoutMs = 2000);
};

#endif // SIGNALSPYWAITERWITHPROCESSTIMERS_H
