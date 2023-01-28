#ifndef TIMERPERIODICQT_H
#define TIMERPERIODICQT_H

#include "timertemplateqt.h"
#include <QTimer>
#include <memory>

class TimerPeriodicQt : public TimerTemplateQt
{
    Q_OBJECT
public:
    explicit TimerPeriodicQt(int expireTimeMs);
    void setHighAccuracy(bool on);
    void start() override;
    void stop() override;
private:
    std::unique_ptr<QTimer> m_qtTimer;
    bool m_highAccuracy = false;
};

#endif // TIMERPERIODICQT_H
