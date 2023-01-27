#ifndef TIMERPERIODICQT_H
#define TIMERPERIODICQT_H

#include "zeratimertemplate.h"
#include <QTimer>
#include <memory>

class TimerPeriodicQt : public ZeraTimerTemplate
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
