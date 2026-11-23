#include "timerfactoryqtfortest.h"
#include "timerfortesttemplate.h"
#include "timerelapsedfortest.h"
#include "timemachinefortest.h"

bool TimerFactoryQtForTest::enableTest()
{
    TimerTemplateQt::silenceNextCriticalWhenCalledFromTest();
    m_singleShotCreateFunction = [](int timeout) {
        return std::make_unique<TimerForTestTemplate>(timeout, TimerForTestTemplate::SINGLESHOT);
    };
    m_periodicCreateFunction = [](int timeout) {
        return std::make_unique<TimerForTestTemplate>(timeout, TimerForTestTemplate::PERIODIC);
    };
    m_elapsedCreateFunction = []() {
        return std::make_unique<TimerElapsedForTest>();
    };
    m_getCurrentTimeFunction = []() {
        return TimeMachineForTest::getInstance()->getCurrentTime();
    };
    return true;
}

void TimerFactoryQtForTest::disableTest()
{
    m_singleShotCreateFunction = defaultSingleShotCreateFunc();
    m_periodicCreateFunction = defaultPeriodicCreateFunc();
    m_elapsedCreateFunction = defaultElapsedCreateFunc();
    m_getCurrentTimeFunction = defaultGetCurrentTimeFunc();
}
