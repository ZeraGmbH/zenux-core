#include "timerfactoryqtfortest.h"
#include "timerfortesttemplate.h"
#include "timemachinefortest.h"

void TimerFactoryQtForTest::enableTest()
{
    m_singleShotCreateFunction = [](int timeout) {
        return std::make_unique<TimerForTestTemplate>(timeout, TimerForTestTemplate::SINGLESHOT);
    };
    m_periodicCreateFunction = [](int timeout) {
        return std::make_unique<TimerForTestTemplate>(timeout, TimerForTestTemplate::PERIODIC);
    };
    m_getCurrentTimeFunction = []() {
        return TimeMachineForTest::getInstance()->getCurrentTime();
    };
}

void TimerFactoryQtForTest::disableTest()
{
    m_singleShotCreateFunction = defaultSingleShotCreateFunc();
    m_periodicCreateFunction = defaultPeriodicCreateFunc();
    m_getCurrentTimeFunction = defaultGetCurrentTimeFunc();
}
