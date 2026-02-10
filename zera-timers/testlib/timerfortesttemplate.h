#ifndef TIMERFORTESTTEMPLATE_H
#define TIMERFORTESTTEMPLATE_H

#include "timertemplateqt.h"

class TimerForTestTemplate : public TimerTemplateQt
{
    Q_OBJECT
public:
    TimerForTestTemplate(int expireTimeMs, bool singleShot);
    virtual ~TimerForTestTemplate();
    void start() override;
    void stop() override;
    bool isRunning() override;
    void fireExpired();
    int getExpireMs() const;
    bool getSingleShot() const;
private:
    void removeFromRunner();
    const bool m_singleShot;
};

#endif // TIMERFORTESTTEMPLATE_H
