#ifndef TIMERELAPSEDQT_H
#define TIMERELAPSEDQT_H

#include "timerelapsedtemplateqt.h"
#include <QElapsedTimer>

class TimerElapsedQt : public TimerElapsedTemplateQt
{
public:
    TimerElapsedQt();
    void start() override;
    int getElapsedMs() override;
private:
    QElapsedTimer m_timer;
};

#endif // TIMERELAPSEDQT_H
