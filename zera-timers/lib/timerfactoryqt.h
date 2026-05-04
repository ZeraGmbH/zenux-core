#ifndef TIMERFACTORYQT_H
#define TIMERFACTORYQT_H

#include "timertemplateqt.h"
#include "timerelapsedtemplateqt.h"
#include <QDateTime>
#include <functional>

// To make code testable, use TimerFactoryQt to
// * create zera-timers (see testlib/TimerFactoryQtForTest why)
// * ask for current time
class TimerFactoryQt
{
public:
    static TimerTemplateQtPtr createSingleShot(int timeout);
    static TimerTemplateQtPtr createPeriodic(int timeout);
    static TimerElapsedTemplateQtPtr createElapsed();
    static QDateTime getCurrentTime();
protected:
    static std::function<TimerTemplateQtPtr(int)> defaultSingleShotCreateFunc();
    static std::function<TimerTemplateQtPtr(int)> defaultPeriodicCreateFunc();
    static std::function<TimerElapsedTemplateQtPtr()> defaultElapsedCreateFunc();
    static std::function<QDateTime()> defaultGetCurrentTimeFunc();

    static std::function<TimerTemplateQtPtr(int)> m_singleShotCreateFunction;
    static std::function<TimerTemplateQtPtr(int)> m_periodicCreateFunction;
    static std::function<TimerElapsedTemplateQtPtr()> m_elapsedCreateFunction;
    static std::function<QDateTime()> m_getCurrentTimeFunction;
};

#endif // TIMERFACTORYQT_H
