#include "timemachinefortest.h"
#include <QCoreApplication>

TimeMachineForTest *TimeMachineForTest::m_instance = nullptr;

TimeMachineForTest *TimeMachineForTest::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new TimeMachineForTest;
    return m_instance;
}

void TimeMachineForTest::reset()
{
    delete m_instance;
    m_instance = nullptr;
}

int TimeMachineForTest::getCurrentTimeMs()
{
    return m_currentTimeMs;
}

// An important fact to understand code better: Each timer occures maximum ONE
// time in m_pendingMap - see alse processOneExpired()

void TimeMachineForTest::addTimer(TimerForTestInterface *timer, int expiredMs, bool singleShot)
{
    removeTimer(timer);
    int expireTime = m_currentTimeMs + expiredMs;
    if(!m_pendingMap.contains(expireTime)) // remove?
        m_pendingMap[expireTime] = QVector<TTimerEntry>();
    m_pendingMap[expireTime].append(TTimerEntry({expiredMs, singleShot, timer}));
}

void TimeMachineForTest::removeTimer(TimerForTestInterface *timer)
{
    QList<int> emptyEntries;
    for(auto iter=m_pendingMap.begin(); iter!=m_pendingMap.end(); iter++) {
        QVector<TTimerEntry> entryListOld = iter.value();
        QVector<TTimerEntry> entryListNew;
        for(const auto& entry : entryListOld)
            if(entry.timer != timer)
                entryListNew.append(entry);
        if(!entryListNew.isEmpty())
            iter.value() = entryListNew;
        else
            emptyEntries.append(iter.key());
    }
    for(int expireTime : emptyEntries)
        m_pendingMap.remove(expireTime);
}

void TimeMachineForTest::processTimers(int durationMs)
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

bool TimeMachineForTest::areTimersPending(int upToTimestamp)
{
    feedEventLoop();
    return !m_pendingMap.isEmpty() && m_pendingMap.firstKey() <= upToTimestamp;
}

void TimeMachineForTest::feedEventLoop()
{
    QMap<int, QVector<TTimerEntry>> pendingMapBeforeEventLoop;
    do {
        pendingMapBeforeEventLoop = m_pendingMap;
        QCoreApplication::processEvents();
    } while(pendingMapBeforeEventLoop != m_pendingMap);
}

void TimeMachineForTest::processOneExpired(TTimerEntry entry)
{
    removeTimer(entry.timer);
    if(!entry.singleShot)
        addTimer(entry.timer, entry.expireMs, entry.singleShot);
    entry.timer->fireExpired();
}
