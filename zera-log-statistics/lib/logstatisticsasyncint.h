#ifndef LOGSTATISTICSASYNCINT_H
#define LOGSTATISTICSASYNCINT_H

#include "timertemplateqt.h"
#include <QObject>

class LogStatisticsAsyncInt : public QObject
{
    Q_OBJECT
public:
    LogStatisticsAsyncInt(int periodMs);
    void addValue(int value);
signals:
    void sigNewStatistics(int minVal, int maxVal, float avgVal, int countVal);
private slots:
    void onTimer();
private:
    TimerTemplateQtPtr m_timer;
    QList<int> m_values;
};

#endif // LOGSTATISTICSASYNCINT_H
