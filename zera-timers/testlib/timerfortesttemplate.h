#ifndef TIMERFORTESTTEMPLATE_H
#define TIMERFORTESTTEMPLATE_H

#include "timertemplateqt.h"
#include "timerfortestinterface.h"

class TimerForTestTemplate : public TimerTemplateQt, public TimerForTestInterface
{
    Q_OBJECT
public:
    TimerForTestTemplate(int expireTimeMs);
    ~TimerForTestTemplate();
    void stop() override;
    void fireExpired() override;
private:
    void removeFromRunner();
};

#endif // TIMERFORTESTTEMPLATE_H
