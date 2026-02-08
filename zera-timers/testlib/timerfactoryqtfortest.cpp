#include "timerfactoryqtfortest.h"
#include "timerfortestsingleshot.h"
#include "timerfortestperiodic.h"
#include "timemachinefortest.h"

void TimerFactoryQtForTest::enableTest()
{
    m_singleShotCreateFunction = [](int timeout) {
        return std::make_unique<TimerForTestSingleShot>(timeout);
    };
    m_periodicCreateFunction = [](int timeout) {
        return std::make_unique<TimerForTestPeriodic>(timeout);
    };
    m_getCurrentTimeFunction = []() {
        QDateTime dtTime;
        const TimeMachineObject *instance = TimeMachineForTest::getInstance();
        dtTime.setMSecsSinceEpoch(instance->getCurrentTimeMs() + instance->getMsecsCurrDateTimeTimeOffset());
        return dtTime;
    };
}

void TimerFactoryQtForTest::disableTest()
{
    m_singleShotCreateFunction = defaultSingleShotCreateFunc();
    m_periodicCreateFunction = defaultPeriodicCreateFunc();
    m_getCurrentTimeFunction = defaultGetCurrentTimeFunc();
}
