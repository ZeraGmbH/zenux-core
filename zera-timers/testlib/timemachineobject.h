#ifndef TIMEMACHINEOBJECT_H
#define TIMEMACHINEOBJECT_H

#include "timerfortestinterface.h"
#include "timerfortesttemplate.h"
#include <QMap>
#include <QVector>

class TimeMachineObject
{
public:
    void addTimer(TimerForTestInterface* timer, int expiredMs, bool singleShot);
    void removeTimer(TimerForTestInterface* timer);
    void processTimers(int durationMs);
    bool isRunning(TimerForTestTemplate* timer);
    int getCurrentTimeMs();
private:
    struct TTimerEntry
    {
        int expireMs;
        bool singleShot;
        TimerForTestInterface* timer;

        bool operator == (const TTimerEntry& other) const {
            return
                expireMs == other.expireMs &&
                singleShot == other.singleShot &&
                timer == other.timer;
        }
    };
    bool areTimersPending(int upToTimestamp);
    void feedEventLoop();
    void processOneExpired(TTimerEntry entry);

    int m_currentTimeMs = 0;
    QMap<int/*expireTimeMs*/, QVector<TTimerEntry>> m_pendingMap;
};

#endif // TIMEMACHINEOBJECT_H
