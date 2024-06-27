#ifndef TIMERFACTORYQTFORTEST_H
#define TIMERFACTORYQTFORTEST_H

#include <timerfactoryqt.h>

class TimerFactoryQtForTest : public TimerFactoryQt
{
public:
    static void enableTest();
    static void disableTest();
};

#endif // TIMERFACTORYQTFORTEST_H
