#include "timerelapsedfortest.h"
#include <timemachinefortest.h>

void TimerElapsedForTest::start()
{
    m_startTime = TimeMachineForTest::getInstance()->getCurrentTimeMs();
}

int TimerElapsedForTest::getElapsedMs()
{
    return TimeMachineForTest::getInstance()->getCurrentTimeMs() - m_startTime;
}
