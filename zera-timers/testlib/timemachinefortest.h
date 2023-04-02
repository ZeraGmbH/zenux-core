#ifndef TIMEMACHINEFORTEST_H
#define TIMEMACHINEFORTEST_H

#include "timertestdefaults.h"
#include "timerfortestinterface.h"
#include <QMap>
#include <QVector>

class TimeMachineForTest
{
public:
    static TimeMachineForTest* getInstance();
    static void reset();
    void addTimer(TimerForTestInterface* timer, int expiredMs, bool singleShot);
    void removeTimer(TimerForTestInterface* timer);
    void processTimers(int durationMs);
    int getCurrentTimeMs();
private:
    TimeMachineForTest() = default;
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
    static TimeMachineForTest* m_instance;
};

#endif // TIMEMACHINEFORTEST_H
