#ifndef TIMERELAPSEDTEMPLATEQT_H
#define TIMERELAPSEDTEMPLATEQT_H

#include <memory>

class TimerElapsedTemplateQt
{
public:
    virtual ~TimerElapsedTemplateQt() = default;
    virtual void start() = 0;
    virtual int getElapsedMs() = 0;
};

typedef std::unique_ptr<TimerElapsedTemplateQt> TimerElapsedTemplateQtPtr;

#endif // TIMERELAPSEDTEMPLATEQT_H
