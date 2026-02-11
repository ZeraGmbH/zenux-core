#include "timerfortesttemplate.h"
#include "timemachinefortest.h"

TimerForTestTemplate::TimerForTestTemplate(int expireTimeMs, TimerTypes type) :
    TimerTemplateQt(expireTimeMs != 0 ? expireTimeMs : 1),
    m_type(type)
{
}

TimerForTestTemplate::~TimerForTestTemplate()
{
    removeFromRunner();
}

void TimerForTestTemplate::start()
{
    TimeMachineForTest::getInstance()->setTimerPending(this);
}

void TimerForTestTemplate::stop()
{
    removeFromRunner();
}

void TimerForTestTemplate::fireExpired()
{
    emit sigExpired();
}

int TimerForTestTemplate::getExpireMs() const
{
    return m_expireTimeMs;
}

TimerForTestTemplate::TimerTypes TimerForTestTemplate::getType() const
{
    return m_type;
}

bool TimerForTestTemplate::isRunning()
{
    return TimeMachineForTest::getInstance()->isRunning(this);
}

void TimerForTestTemplate::removeFromRunner()
{
    TimeMachineForTest::getInstance()->removeTimer(this);
}
