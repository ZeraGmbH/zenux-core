#include "timerfortestsingleshot.h"
#include "timemachinefortest.h"

TimerForTestSingleShot::TimerForTestSingleShot(int expireTimeMs) :
    TimerForTestTemplate(expireTimeMs)
{
}

void TimerForTestSingleShot::start()
{
    TimeMachineForTest::getInstance()->addTimer(this, m_expireTimeMs, true);
}
