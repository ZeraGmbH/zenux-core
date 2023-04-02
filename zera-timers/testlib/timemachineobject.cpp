#include "timemachineobject.h"
#include <QCoreApplication>

// An important fact to understand code better: Each timer occures maximum ONE
// time in m_pendingMap - see also processOneExpired()

void TimeMachineObject::addTimer(TimerForTestInterface *timer, int expiredMs, bool singleShot)
{
    removeTimer(timer);
    int timeStamp = m_currentTimeMs + expiredMs;
    m_pendingMap[timeStamp].append(TTimerEntry({expiredMs, singleShot, timer}));
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
    int upToTimestamp = m_currentTimeMs + durationMs;
    while(areTimersPending(upToTimestamp)) {
        m_currentTimeMs = m_pendingMap.firstKey();
        QVector<TTimerEntry> expired = m_pendingMap[m_currentTimeMs];
        processOneExpired(expired[0]);
    }
    m_currentTimeMs = upToTimestamp;
}

int TimeMachineObject::getCurrentTimeMs()
{
    return m_currentTimeMs;
}

bool TimeMachineObject::areTimersPending(int upToTimestamp)
{
    feedEventLoop();
    return !m_pendingMap.isEmpty() && m_pendingMap.firstKey() <= upToTimestamp;
}

void TimeMachineObject::feedEventLoop()
{
    QMap<int, QVector<TTimerEntry>> pendingMapBeforeEventLoop;
    do {
        pendingMapBeforeEventLoop = m_pendingMap;
        QCoreApplication::processEvents();
    } while(pendingMapBeforeEventLoop != m_pendingMap);
}

void TimeMachineObject::processOneExpired(TTimerEntry entry)
{
    removeTimer(entry.timer);
    if(!entry.singleShot)
        // No use case yet but - once it is - we have to take cautions on
        // periodic timers with expire time 0 (after analysis what QTimers do)
        addTimer(entry.timer, entry.expireMs, entry.singleShot);
    entry.timer->fireExpired();
}