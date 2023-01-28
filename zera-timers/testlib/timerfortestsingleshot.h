#ifndef TIMERFORTESTSINGLESHOT_H
#define TIMERFORTESTSINGLESHOT_H

#include "timertemplateqt.h"
#include "timerfortestinterface.h"

class TimerForTestSingleShot : public TimerTemplateQt, public TimerForTestInterface
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
