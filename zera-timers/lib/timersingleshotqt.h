#ifndef TIMERSINGLESHOTQT_H
#define TIMERSINGLESHOTQT_H

#include "zeratimertemplate.h"
#include <QTimer>
#include <memory>

class TimerSingleShotQt : public ZeraTimerTemplate
{
    Q_OBJECT
public:
    explicit TimerSingleShotQt(int expireTimeMs);
    void setHighAccuracy(bool on);
    void start() override;
    void stop() override;
private:
    std::unique_ptr<QTimer> m_qtTimer;
    bool m_highAccuracy = false;
};

#endif // TIMERSINGLESHOTQT_H
