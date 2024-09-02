#ifndef LOGSTATISTICSASYNCFLOAT_H
#define LOGSTATISTICSASYNCFLOAT_H

#include "timertemplateqt.h"
#include <QObject>

class LogStatisticsAsyncFloat : public QObject
{
    Q_OBJECT
public:
    explicit LogStatisticsAsyncFloat(int periodMs);
    void addValue(float value);
signals:
    void sigNewStatistics(float minVal, float maxVal, float avgVal, int countVal);
private slots:
    void onTimer();
private:
    TimerTemplateQtPtr m_timer;
    QList<float> m_values;
};

#endif // LOGSTATISTICSASYNCFLOAT_H
