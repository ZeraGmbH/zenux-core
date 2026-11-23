#include "timerelapsedqt.h"
#include "timertemplateqt.h"

TimerElapsedQt::TimerElapsedQt()
{
    TimerTemplateQt::spawnCriticalWhenCalledFromTest();
}

void TimerElapsedQt::start()
{
    m_timer.start();
}

int TimerElapsedQt::getElapsedMs()
{
    if (!m_timer.isValid())
        return 0;
    return m_timer.elapsed();
}
