#include "timemachinefortest.h"

TimeMachineObject *TimeMachineForTest::m_instance = nullptr;

TimeMachineObject *TimeMachineForTest::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new TimeMachineObject;
    return m_instance;
}

void TimeMachineForTest::reset()
{
    delete m_instance;
    m_instance = nullptr;
}

