#include "zeratimerfactorymethodstest.h"
#include "timerfortestsingleshot.h"
#include "timerfortestperiodic.h"

void ZeraTimerFactoryMethodsTest::enableTest()
{
    m_singleShotCreateFunction = [](int timeout){
        return std::make_unique<TimerForTestSingleShot>(timeout);
    };

    m_periodicCreateFunction = [](int timeout){
        return std::make_unique<TimerForTestPeriodic>(timeout);
    };
}
