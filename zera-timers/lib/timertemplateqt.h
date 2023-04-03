#ifndef TIMERTEMPLATEQT_H
#define TIMERTEMPLATEQT_H

#include <QObject>
#include <memory>

class TimerTemplateQt : public QObject
{
    Q_OBJECT
public:
    explicit TimerTemplateQt(int expireTimeMs);
    virtual ~TimerTemplateQt() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() = 0;
protected:
    int m_expireTimeMs;
signals:
    void sigExpired();
};

typedef std::unique_ptr<TimerTemplateQt> TimerTemplateQtPtr;

#endif // TIMERTEMPLATEQT_H
