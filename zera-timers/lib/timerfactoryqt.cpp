#include "timerfactoryqt.h"
#include "timersingleshotqt.h"
#include "timerperiodicqt.h"
#include "timerelapsedqt.h"

std::function<TimerTemplateQtPtr(int)> TimerFactoryQt::m_singleShotCreateFunction = defaultSingleShotCreateFunc();
std::function<TimerTemplateQtPtr(int)> TimerFactoryQt::m_periodicCreateFunction = defaultPeriodicCreateFunc();
std::function<TimerElapsedTemplateQtPtr ()> TimerFactoryQt::m_elapsedCreateFunction = defaultElapsedCreateFunc();
std::function<QDateTime()> TimerFactoryQt::m_getCurrentTimeFunction = defaultGetCurrentTimeFunc();

TimerTemplateQtPtr TimerFactoryQt::createSingleShot(int timeout)
{
    return m_singleShotCreateFunction(timeout);
}

TimerTemplateQtPtr TimerFactoryQt::createPeriodic(int timeout)
{
    return m_periodicCreateFunction(timeout);
}

TimerElapsedTemplateQtPtr TimerFactoryQt::createElapsed()
{
    return m_elapsedCreateFunction();
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

std::function<TimerElapsedTemplateQtPtr ()> TimerFactoryQt::defaultElapsedCreateFunc()
{
    return []() {
        return std::make_unique<TimerElapsedQt>();
    };
}

std::function<QDateTime ()> TimerFactoryQt::defaultGetCurrentTimeFunc()
{
    return []() {
        TimerTemplateQt::noteWhenCalledFromTest();
        return QDateTime::currentDateTime();
    };
}
