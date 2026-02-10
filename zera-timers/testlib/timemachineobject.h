#ifndef TIMEMACHINEOBJECT_H
#define TIMEMACHINEOBJECT_H

#include "timerfortesttemplate.h"
#include <QMap>
#include <QList>
#include <QDate>
#include <QTime>
#include <QTimeZone>
#include <QDateTime>

class TimeMachineObject
{
public:
    TimeMachineObject();
    // Timers
    void setTimerPending(TimerForTestTemplate* timer);
    void removeTimer(TimerForTestTemplate *timer);
    void processTimers(int durationMs);
    bool isRunning(TimerForTestTemplate* timer) const;
    int getCurrentTimeMs() const;
    // Datetime
    void setCurrentTime(const QDate &date, const QTime &time, const QTimeZone &tz = QTimeZone(3*3600));
    void setCurrentTime(const QDateTime &dateTime);
    QDateTime getCurrentTime() const;

    static void feedEventLoop();
private:
    bool areTimersPending(int upToTimestamp);
    void processOneExpired(TimerForTestTemplate *timer);

    int m_currentTimeMs = 0;
    qint64 m_msecsCurrDateTimeTimeOffset = 0;
    QTimeZone m_timezone;

    QMap<int/*expireTimeMs*/, QList<TimerForTestTemplate*>> m_pendingMap;
};

#endif // TIMEMACHINEOBJECT_H
