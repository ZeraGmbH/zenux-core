#include "zeratimerfactorymethods.h"
#include "timersingleshotqt.h"
#include "timerperiodicqt.h"

std::function<TimerTemplateQtPtr(int)> ZeraTimerFactoryMethods::m_singleShotCreateFunction = [](int timeout){
    return std::make_unique<TimerSingleShotQt>(timeout);
};

std::function<TimerTemplateQtPtr(int)> ZeraTimerFactoryMethods::m_periodicCreateFunction = [](int timeout){
    return std::make_unique<TimerPeriodicQt>(timeout);
};


TimerTemplateQtPtr ZeraTimerFactoryMethods::createSingleShot(int timeout)
{
    return m_singleShotCreateFunction(timeout);
}

TimerTemplateQtPtr ZeraTimerFactoryMethods::createPeriodic(int timeout)
{
    return m_periodicCreateFunction(timeout);
}
