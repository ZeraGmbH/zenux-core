#ifndef ZERATIMERFACTORYMETHODS_H
#define ZERATIMERFACTORYMETHODS_H

#include "timertemplateqt.h"
#include <functional>

/* Use ZeraTimerFactoryMethods to create zera-timers - otherwise tests will fail
 * (see testlib/ZeraTimerFactoryMethodsTest why)
*/
class ZeraTimerFactoryMethods
{
public:
    static TimerTemplateQtPtr createSingleShot(int timeout);
    static TimerTemplateQtPtr createPeriodic(int timeout);
protected:
    static std::function<TimerTemplateQtPtr(int)> m_singleShotCreateFunction;
    static std::function<TimerTemplateQtPtr(int)> m_periodicCreateFunction;
};

#endif // ZERATIMERFACTORYMETHODS_H
