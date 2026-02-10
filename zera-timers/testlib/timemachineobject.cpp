#include "timemachineobject.h"
#include <QCoreApplication>
#include <QThread>
#include <QAbstractEventDispatcher>

TimeMachineObject::TimeMachineObject() :
    m_timezone(0)
{
}

// An important fact to understand code better: Each timer occures maximum ONE
// time in m_pendingMap - see also processOneExpired()

void TimeMachineObject::addTimer(TimerForTestInterface *timer, int expiredMs, bool singleShot)
{
    removeTimer(timer);
    int expireTimeStamp = m_currentTimeMs + expiredMs;
    m_pendingMap[expireTimeStamp].append(TTimerEntry({expiredMs, singleShot, timer}));
}

void TimeMachineObject::removeTimer(TimerForTestInterface *timer)
{
    QList<int> emptyTimeStamps;
    for(auto iter=m_pendingMap.begin(); iter!=m_pendingMap.end(); iter++) {
        QList<TTimerEntry> &timerList = iter.value();
        for (int i=0; i<timerList.count(); ++i) {
            if(timerList[i].timer == timer) {
                timerList.removeAt(i);
                break;
            }
        }
        if (timerList.isEmpty()) // no remove within iteration!
            emptyTimeStamps.append(iter.key());
    }
    for(int timeStamp : emptyTimeStamps)
        m_pendingMap.remove(timeStamp);
}

void TimeMachineObject::processTimers(int durationMs)
{
    Q_ASSERT(durationMs >= 0);
    int processUpToTimestamp = m_currentTimeMs + durationMs;
    while(areTimersPending(processUpToTimestamp)) {
        m_currentTimeMs = m_pendingMap.firstKey();
        QVector<TTimerEntry> expired = m_pendingMap[m_currentTimeMs];
        processOneExpired(expired[0]);
    }
    m_currentTimeMs = processUpToTimestamp;
}

bool TimeMachineObject::isRunning(TimerForTestTemplate *timer) const
{
    for(auto iter=m_pendingMap.begin(); iter!=m_pendingMap.end(); iter++)
        for(const auto& entry : qAsConst(iter.value()))
            if(entry.timer == timer)
                return true;
    return false;
}

int TimeMachineObject::getCurrentTimeMs() const
{
    return m_currentTimeMs;
}

void TimeMachineObject::setCurrentTime(const QDate &date, const QTime &time, const QTimeZone &tz)
{
    QDateTime dateTime(date, time, tz);
    setCurrentTime(dateTime);
}

void TimeMachineObject::setCurrentTime(const QDateTime &dateTime)
{
    m_msecsCurrDateTimeTimeOffset = dateTime.toMSecsSinceEpoch() - getCurrentTimeMs();
    m_timezone = dateTime.timeZone();
}

QDateTime TimeMachineObject::getCurrentTime() const
{
    QDateTime dtTime;
    dtTime.setTimeZone(m_timezone);
    dtTime.setMSecsSinceEpoch(m_currentTimeMs + m_msecsCurrDateTimeTimeOffset);
    return dtTime;
}

bool TimeMachineObject::areTimersPending(int upToTimestamp)
{
    feedEventLoop();
    return !m_pendingMap.isEmpty() && m_pendingMap.firstKey() <= upToTimestamp;
}

void TimeMachineObject::feedEventLoop()
{
    while( QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::AllEvents) );
}

void TimeMachineObject::processOneExpired(TTimerEntry entry)
{
    removeTimer(entry.timer);
    if(!entry.singleShot)
        addTimer(entry.timer, std::max(entry.expireMs, 1), entry.singleShot);
    entry.timer->fireExpired();
}
