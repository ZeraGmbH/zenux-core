#include "timerfortestperiodic.h"
#include "timemachinefortest.h"

TimerForTestPeriodic::TimerForTestPeriodic(int expireTimeMs) :
    TimerForTestTemplate(expireTimeMs)
{
}

void TimerForTestPeriodic::start()
{
    TimeMachineForTest::getInstance()->addTimer(this, m_expireTimeMs, false);
}
