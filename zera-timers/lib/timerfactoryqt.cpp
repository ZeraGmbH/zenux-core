#include "timerfactoryqt.h"
#include "timersingleshotqt.h"
#include "timerperiodicqt.h"

std::function<TimerTemplateQtPtr(int)> TimerFactoryQt::m_singleShotCreateFunction = [](int timeout){
    return std::make_unique<TimerSingleShotQt>(timeout);
};

std::function<TimerTemplateQtPtr(int)> TimerFactoryQt::m_periodicCreateFunction = [](int timeout){
    return std::make_unique<TimerPeriodicQt>(timeout);
};


TimerTemplateQtPtr TimerFactoryQt::createSingleShot(int timeout)
{
    return m_singleShotCreateFunction(timeout);
}

TimerTemplateQtPtr TimerFactoryQt::createPeriodic(int timeout)
{
    return m_periodicCreateFunction(timeout);
}
