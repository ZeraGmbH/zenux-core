#ifndef TIMEMACHINEOBJECT_H
#define TIMEMACHINEOBJECT_H

#include "timerfortestinterface.h"
#include "timerfortesttemplate.h"
#include <QMap>
#include <QVector>
#include <QDate>
#include <QTime>
#include <QTimeZone>
#include <QDateTime>

class TimeMachineObject
{
public:
    TimeMachineObject();
    // Timers
    void addTimer(TimerForTestInterface* timer, int expiredMs, bool singleShot);
    void removeTimer(TimerForTestInterface* timer);
    void processTimers(int durationMs);
    bool isRunning(TimerForTestTemplate* timer) const;
    int getCurrentTimeMs() const;
    // Datetime
    void setCurrentTime(const QDate &date, const QTime &time, const QTimeZone &tz = QTimeZone(3*3600));
    void setCurrentTime(const QDateTime &dateTime);
    QDateTime getCurrentTime() const;

    static void feedEventLoop();
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
    void processOneExpired(TTimerEntry entry);

    int m_currentTimeMs = 0;
    qint64 m_msecsCurrDateTimeTimeOffset = 0;
    QTimeZone m_timezone;

    QMap<int/*expireTimeMs*/, QVector<TTimerEntry>> m_pendingMap;
};

#endif // TIMEMACHINEOBJECT_H
