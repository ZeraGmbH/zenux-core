#include "timerfortestperiodic.h"
#include "timemachinefortest.h"

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
    TimeMachineForTest::getInstance()->addTimer(this, m_expireTimeMs, false);
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
    TimeMachineForTest::getInstance()->removeTimer(this);
}
