#include "timerfortestperiodic.h"
#include "timemachinefortest.h"

TimerForTestPeriodic::TimerForTestPeriodic(int expireTimeMs) :
    TimerForTestTemplate(expireTimeMs, false)
{
}

void TimerForTestPeriodic::start()
{
    TimeMachineForTest::getInstance()->setTimerPending(this);
}
