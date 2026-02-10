#include "timerfortestsingleshot.h"
#include "timemachinefortest.h"

TimerForTestSingleShot::TimerForTestSingleShot(int expireTimeMs) :
    TimerForTestTemplate(expireTimeMs, true)
{
}

void TimerForTestSingleShot::start()
{
    TimeMachineForTest::getInstance()->setTimerPending(this);
}
