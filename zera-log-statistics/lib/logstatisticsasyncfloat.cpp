#include "logstatisticsasyncfloat.h"
#include "timerfactoryqt.h"

LogStatisticsAsyncFloat::LogStatisticsAsyncFloat(int periodMs)
{
    m_timer = TimerFactoryQt::createPeriodic(periodMs);
    connect(m_timer.get(), &TimerTemplateQt::sigExpired,
            this, &LogStatisticsAsyncFloat::onTimer);
    m_timer->start();
}

void LogStatisticsAsyncFloat::addValue(float value)
{
    if(!qIsNaN(value))
        m_values.append(value);
}

void LogStatisticsAsyncFloat::onTimer()
{
    if(!m_values.isEmpty()) {
        int valueCount = m_values.size();
        float min = *std::min_element(m_values.begin(), m_values.end());
        float max = *std::max_element(m_values.begin(), m_values.end());
        float mean = std::accumulate(m_values.begin(), m_values.end(), 0.0) / valueCount;
        m_values.clear();
        emit sigNewStatistics(min, max, mean, valueCount);
    }
}
