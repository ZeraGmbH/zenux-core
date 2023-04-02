#include "timemachineobject.h"
#include <QCoreApplication>

// An important fact to understand code better: Each timer occures maximum ONE
// time in m_pendingMap - see alse processOneExpired()

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
        QVector<TTimerEntry> entryListNew;
        QVector<TTimerEntry> entryListOld = iter.value();
        for(const auto& entry : entryListOld)
            if(entry.timer != timer)
                entryListNew.append(entry);
        if(!entryListNew.isEmpty())
            iter.value() = entryListNew;
        else
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
        addTimer(entry.timer, entry.expireMs, entry.singleShot);
    entry.timer->fireExpired();
}
