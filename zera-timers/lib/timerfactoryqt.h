#ifndef TIMERFACTORYQT_H
#define TIMERFACTORYQT_H

#include "timertemplateqt.h"
#include <functional>

/* Use TimerFactoryQt to create zera-timers - otherwise tests will fail
 * (see testlib/TimerFactoryQtForTest why)
*/
class TimerFactoryQt
{
public:
    static TimerTemplateQtPtr createSingleShot(int timeout);
    static TimerTemplateQtPtr createPeriodic(int timeout);
protected:
    static std::function<TimerTemplateQtPtr(int)> m_singleShotCreateFunction;
    static std::function<TimerTemplateQtPtr(int)> m_periodicCreateFunction;
};

#endif // TIMERFACTORYQT_H
