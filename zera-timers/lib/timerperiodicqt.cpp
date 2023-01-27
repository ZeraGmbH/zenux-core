#include "timerperiodicqt.h"

TimerPeriodicQt::TimerPeriodicQt(int expireTimeMs) :
    ZeraTimerTemplate(expireTimeMs)
{
}

void TimerPeriodicQt::setHighAccuracy(bool on)
{
    m_highAccuracy = on;
}

void TimerPeriodicQt::start()
{
    m_qtTimer = std::make_unique<QTimer>();
    m_qtTimer->setSingleShot(false);
    m_qtTimer->setTimerType(m_highAccuracy ? Qt::PreciseTimer: Qt::CoarseTimer);
    connect(m_qtTimer.get(), &QTimer::timeout,
            this, &TimerPeriodicQt::sigExpired);
    m_qtTimer->start(m_expireTimeMs);
}

void TimerPeriodicQt::stop()
{
    m_qtTimer = nullptr;
}
