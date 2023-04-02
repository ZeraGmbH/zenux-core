#ifndef TIMERFORTESTSINGLESHOT_H
#define TIMERFORTESTSINGLESHOT_H

#include "timerfortesttemplate.h"

class TimerForTestSingleShot : public TimerForTestTemplate
{
    Q_OBJECT
public:
    TimerForTestSingleShot(int expireTimeMs);
    void start() override;
};

#endif // TIMERFORTESTSINGLESHOT_H
