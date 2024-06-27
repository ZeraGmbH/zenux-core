#include "timerfactoryqt.h"
#include "timersingleshotqt.h"
#include "timerperiodicqt.h"

std::function<TimerTemplateQtPtr(int)> TimerFactoryQt::m_singleShotCreateFunction = defaultSingleShotCreateFunc();
std::function<TimerTemplateQtPtr(int)> TimerFactoryQt::m_periodicCreateFunction = defaultPeriodicCreateFunc();
std::function<QDateTime()> TimerFactoryQt::m_getCurrentTimeFunction = defaultGetCurrentTimeFunc();

TimerTemplateQtPtr TimerFactoryQt::createSingleShot(int timeout)
{
    return m_singleShotCreateFunction(timeout);
}

TimerTemplateQtPtr TimerFactoryQt::createPeriodic(int timeout)
{
    return m_periodicCreateFunction(timeout);
}

QDateTime TimerFactoryQt::getCurrentTime()
{
    return m_getCurrentTimeFunction();
}

std::function<TimerTemplateQtPtr (int)> TimerFactoryQt::defaultSingleShotCreateFunc()
{
    return [](int timeout) {
        return std::make_unique<TimerSingleShotQt>(timeout);
    };
}

std::function<TimerTemplateQtPtr (int)> TimerFactoryQt::defaultPeriodicCreateFunc()
{
    return [](int timeout) {
        return std::make_unique<TimerPeriodicQt>(timeout);
    };
}

std::function<QDateTime ()> TimerFactoryQt::defaultGetCurrentTimeFunc()
{
    return []() {
        return QDateTime::currentDateTime();
    };
}
