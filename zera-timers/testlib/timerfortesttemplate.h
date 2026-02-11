#ifndef TIMERFORTESTTEMPLATE_H
#define TIMERFORTESTTEMPLATE_H

#include "timertemplateqt.h"

class TimerForTestTemplate : public TimerTemplateQt
{
    Q_OBJECT
public:
    enum TimerTypes {
        SINGLESHOT,
        PERIODIC,
    };
    TimerForTestTemplate(int expireTimeMs, TimerTypes type);
    virtual ~TimerForTestTemplate();
    void start() override;
    void stop() override;
    bool isRunning() override;
    void fireExpired();
    int getExpireMs() const;
    TimerTypes getType() const;
private:
    void removeFromRunner();
    const TimerTypes m_type;
};

#endif // TIMERFORTESTTEMPLATE_H
