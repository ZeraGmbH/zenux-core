#include "testfloatingpointhelper.h"
#include <QString>
#include <math.h>

bool TestFloatingPointHelper::compareFuzzyPrecision(double val1, double val2, int precision)
{
    QString strVal1 = QString("%1").arg(val1, 0, 'g', precision);
    QString strVal2 = QString("%1").arg(val2, 0, 'g', precision);
    if (strVal1 != strVal2) {
        qWarning("compareFuzzyPrecision failed: %s / %s", qPrintable(strVal1), qPrintable(strVal2));
        return false;
    }
    return true;
}

bool TestFloatingPointHelper::compareFuzzyLimit(double val1, double val2, double deviationMax)
{
    double absDiff = fabs(val1-val2);
    if (absDiff > fabs(deviationMax)) {
        QString strVal1 = QString("%1").arg(val1, 0, 'g', 8);
        QString strVal2 = QString("%1").arg(val2, 0, 'g', 8);
        qWarning("compareFuzzyPrecision failed: %s / %s", qPrintable(strVal1), qPrintable(strVal2));
        return false;
    }
    return true;
}
