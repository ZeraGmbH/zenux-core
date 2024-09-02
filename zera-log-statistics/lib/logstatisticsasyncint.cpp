#include "logstatisticsasyncint.h"
#include "timerfactoryqt.h"

LogStatisticsAsyncInt::LogStatisticsAsyncInt(int periodMs)
{
    m_timer = TimerFactoryQt::createPeriodic(periodMs);
    connect(m_timer.get(), &TimerTemplateQt::sigExpired,
            this, &LogStatisticsAsyncInt::onTimer);
    m_timer->start();
}

void LogStatisticsAsyncInt::addValue(int value)
{
    m_values.append(value);
}

void LogStatisticsAsyncInt::onTimer()
{
    if(!m_values.isEmpty()) {
        int valueCount = m_values.size();
        int min = *std::min_element(m_values.begin(), m_values.end());
        int max = *std::max_element(m_values.begin(), m_values.end());
        float mean = std::accumulate(m_values.begin(), m_values.end(), 0.0) / valueCount;
        m_values.clear();
        emit sigNewStatistics(min, max, mean, valueCount);
    }
}
