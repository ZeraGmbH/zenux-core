#include "timerfortestperiodic.h"

TimerForTestPeriodic::TimerForTestPeriodic(int expireTimeMs) :
    ZeraTimerTemplate(expireTimeMs)
{
}

TimerForTestPeriodic::~TimerForTestPeriodic()
{
    removeFromRunner();
}

void TimerForTestPeriodic::start()
{
    TimerRunnerForTest::getInstance()->addTimer(this, m_expireTimeMs, false);
}

void TimerForTestPeriodic::stop()
{
    removeFromRunner();
}

void TimerForTestPeriodic::fireExpired()
{
    emit sigExpired();
}

void TimerForTestPeriodic::removeFromRunner()
{
    TimerRunnerForTest::getInstance()->removeTimer(this);
}
