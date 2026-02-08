#include "timemachineobject.h"
#include <QCoreApplication>
#include <QThread>
#include <QAbstractEventDispatcher>

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
        QVector<TTimerEntry> entryListRemaining;
        for(const auto& entry : qAsConst(iter.value()))
            if(entry.timer != timer)
                entryListRemaining.append(entry);
        if(!entryListRemaining.isEmpty())
            iter.value() = entryListRemaining;
        else // no remove within iteration!
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

const qint64 &TimeMachineObject::getMsecsCurrDateTimeTimeOffset() const
{
    return m_msecsCurrDateTimeTimeOffset;
}

void TimeMachineObject::setCurrentTime(const QDateTime &current)
{
    m_msecsCurrDateTimeTimeOffset = current.toMSecsSinceEpoch() - getCurrentTimeMs();
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
