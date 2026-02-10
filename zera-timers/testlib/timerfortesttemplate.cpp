#include "timerfortesttemplate.h"
#include "timemachinefortest.h"

TimerForTestTemplate::TimerForTestTemplate(int expireTimeMs, bool singleShot) :
    TimerTemplateQt(expireTimeMs != 0 ? expireTimeMs : 1),
    m_singleShot(singleShot)
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

int TimerForTestTemplate::getExpireMs() const
{
    return m_expireTimeMs;
}

bool TimerForTestTemplate::getSingleShot() const
{
    return m_singleShot;
}

bool TimerForTestTemplate::isRunning()
{
    return TimeMachineForTest::getInstance()->isRunning(this);
}

void TimerForTestTemplate::removeFromRunner()
{
    TimeMachineForTest::getInstance()->removeTimer(this);
}
