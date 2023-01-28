#ifndef TIMERFORTESTPERIODIC_H
#define TIMERFORTESTPERIODIC_H

#include "zeratimertemplate.h"
#include "timerfortestinterface.h"

class TimerForTestPeriodic : public ZeraTimerTemplate, public TimerForTestInterface
{
    Q_OBJECT
public:
    TimerForTestPeriodic(int expireTimeMs);
    ~TimerForTestPeriodic();
    void start() override;
    void stop() override;
    void fireExpired() override;
private:
    void removeFromRunner();
};

#endif // TIMERFORTESTPERIODIC_H
