#ifndef TIMEMACHINEFORTEST_H
#define TIMEMACHINEFORTEST_H

#include "timemachineobject.h"
#include "timertestdefaults.h" // convenience only

class TimeMachineForTest
{
public:
    static TimeMachineObject* getInstance();
    static void reset();
private:
    static TimeMachineObject* m_instance;
};

#endif // TIMEMACHINEFORTEST_H
