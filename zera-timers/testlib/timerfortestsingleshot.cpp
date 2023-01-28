#include "timerfortestsingleshot.h"

TimerForTestSingleShot::TimerForTestSingleShot(int expireTimeMs) :
    ZeraTimerTemplate(expireTimeMs)
{
}

TimerForTestSingleShot::~TimerForTestSingleShot()
{
    removeFromRunner();
}

void TimerForTestSingleShot::start()
{
    TimerRunnerForTest::getInstance()->addTimer(this, m_expireTimeMs, true);
}

void TimerForTestSingleShot::stop()
{
    removeFromRunner();
}

void TimerForTestSingleShot::fireExpired()
{
    emit sigExpired();
}

void TimerForTestSingleShot::removeFromRunner()
{
    TimerRunnerForTest::getInstance()->removeTimer(this);
}
