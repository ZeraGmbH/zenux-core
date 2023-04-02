#ifndef TIMERFORTESTPERIODIC_H
#define TIMERFORTESTPERIODIC_H

#include "timerfortesttemplate.h"

class TimerForTestPeriodic : public TimerForTestTemplate
{
    Q_OBJECT
public:
    TimerForTestPeriodic(int expireTimeMs);
    void start() override;
};

#endif // TIMERFORTESTPERIODIC_H
