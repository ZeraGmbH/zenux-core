#include "zeratimerfactorymethods.h"
#include "timersingleshotqt.h"
#include "timerperiodicqt.h"

std::function<ZeraTimerTemplatePtr(int)> ZeraTimerFactoryMethods::m_singleShotCreateFunction = [](int timeout){
    return std::make_unique<TimerSingleShotQt>(timeout);
};

std::function<ZeraTimerTemplatePtr(int)> ZeraTimerFactoryMethods::m_periodicCreateFunction = [](int timeout){
    return std::make_unique<TimerPeriodicQt>(timeout);
};


ZeraTimerTemplatePtr ZeraTimerFactoryMethods::createSingleShot(int timeout)
{
    return m_singleShotCreateFunction(timeout);
}

ZeraTimerTemplatePtr ZeraTimerFactoryMethods::createPeriodic(int timeout)
{
    return m_periodicCreateFunction(timeout);
}
