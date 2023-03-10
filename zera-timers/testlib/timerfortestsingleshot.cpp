#include "timerfortestsingleshot.h"
#include "timemachinefortest.h"

TimerForTestSingleShot::TimerForTestSingleShot(int expireTimeMs) :
    TimerTemplateQt(expireTimeMs)
{
}

TimerForTestSingleShot::~TimerForTestSingleShot()
{
    removeFromRunner();
}

void TimerForTestSingleShot::start()
{
    TimeMachineForTest::getInstance()->addTimer(this, m_expireTimeMs, true);
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
    TimeMachineForTest::getInstance()->removeTimer(this);
}
