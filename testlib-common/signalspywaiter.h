#ifndef SIGNALSPYWAITER_H
#define SIGNALSPYWAITER_H

#include <QSignalSpy>

class SignalSpyWaiter
{
public:
    // We have seen QSignalSpy::wait not working as expected...
    static int waitForSignals(QSignalSpy *spy,
                              int signalCount,
                              int timeoutMs = 2000);
};

#endif // SIGNALSPYWAITER_H
