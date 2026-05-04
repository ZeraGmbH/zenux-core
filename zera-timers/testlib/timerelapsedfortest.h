#ifndef TIMERELAPSEDFORTEST_H
#define TIMERELAPSEDFORTEST_H

#include <timerelapsedtemplateqt.h>

class TimerElapsedForTest : public TimerElapsedTemplateQt
{
public:
    void start() override;
    int getElapsedMs() override;
private:
    int m_startTime = 0;
};

#endif // TIMERELAPSEDFORTEST_H
