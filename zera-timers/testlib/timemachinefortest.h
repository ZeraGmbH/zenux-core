#ifndef TIMEMACHINEFORTEST_H
#define TIMEMACHINEFORTEST_H

#include "timertestdefaults.h"
#include "timerfortestinterface.h"
#include <QMap>
#include <QList>

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
    int calcExpireTime(int expiredMs);
    struct TTimerEntry
    {
        int expireMs;
        bool singleShot;
    };
    typedef QMap<TimerForTestInterface*, TTimerEntry> ExpireEntries;
    typedef QMap<int/*expireTimeMs*/, ExpireEntries> ExpireMap;
    ExpireMap getMapToProcess(int upToTimestamp);
    bool processExpiredTimers(const ExpireMap &map);
    bool tryStartTimersByEventLoop();
    void removeTimers(const QList<int> &expiredTimes);
    int m_currentTimeMs = 0;
    ExpireMap m_expireMap;
    static TimeMachineForTest* m_instance;
};

#endif // TIMEMACHINEFORTEST_H
