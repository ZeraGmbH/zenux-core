#include "timerfortesttemplate.h"
#include "timemachinefortest.h"

TimerForTestTemplate::TimerForTestTemplate(int expireTimeMs) :
    TimerTemplateQt(expireTimeMs)
{
}

TimerForTestTemplate::~TimerForTestTemplate()
{
    removeFromRunner();
}

void TimerForTestTemplate::stop()
{
    removeFromRunner();
}

void TimerForTestTemplate::fireExpired()
{
    emit sigExpired();
}

bool TimerForTestTemplate::isRunning()
{
    return TimeMachineForTest::getInstance()->isRunning(this);
}

void TimerForTestTemplate::removeFromRunner()
{
    TimeMachineForTest::getInstance()->removeTimer(this);
}
