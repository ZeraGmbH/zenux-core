#ifndef TESTFLOATINGPOINTHELPER_H
#define TESTFLOATINGPOINTHELPER_H

class TestFloatingPointHelper
{
public:
    static bool compareFuzzyPrecision(double val1, double val2, int precision = 6);
    static bool compareFuzzyLimit(double val1, double val2, double deviationMax = 0.001);
};

#endif // TESTFLOATINGPOINTHELPER_H
