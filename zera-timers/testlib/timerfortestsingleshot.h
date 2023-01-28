#ifndef TIMERFORTESTSINGLESHOT_H
#define TIMERFORTESTSINGLESHOT_H

#include "zeratimertemplate.h"
#include "timemachinefortest.h"

class TimerForTestSingleShot : public ZeraTimerTemplate, public TimerForTestInterface
{
    Q_OBJECT
public:
    TimerForTestSingleShot(int expireTimeMs);
    ~TimerForTestSingleShot();
    void start() override;
    void stop() override;
    void fireExpired() override;
private:
    void removeFromRunner();
};

#endif // TIMERFORTESTSINGLESHOT_H
