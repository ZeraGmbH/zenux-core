#include "timersingleshotqt.h"

TimerSingleShotQt::TimerSingleShotQt(int expireTimeMs) :
    ZeraTimerTemplate(expireTimeMs)
{
}

void TimerSingleShotQt::setHighAccuracy(bool on)
{
    m_highAccuracy = on;
}

void TimerSingleShotQt::start()
{
    m_qtTimer = std::make_unique<QTimer>();
    m_qtTimer->setSingleShot(true);
    m_qtTimer->setTimerType(m_highAccuracy ? Qt::PreciseTimer: Qt::CoarseTimer);
    connect(m_qtTimer.get(), &QTimer::timeout,
            this, &TimerSingleShotQt::sigExpired);
    m_qtTimer->start(m_expireTimeMs);
}

void TimerSingleShotQt::stop()
{
    m_qtTimer = nullptr;
}
