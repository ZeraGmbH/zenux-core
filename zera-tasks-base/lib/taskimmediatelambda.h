#ifndef TASKIMMEDIATELAMBDA_H
#define TASKIMMEDIATELAMBDA_H

#include "tasktemplate.h"
#include <functional>

class TaskImmediateLambda : public TaskTemplate
{
    Q_OBJECT
public:
    static TaskTemplatePtr create(std::function<bool ()> startFunc);
    TaskImmediateLambda(std::function<bool()> startFunc);
    void start() override;
private:
    std::function<bool()> m_startFunc;
};

#endif // TASKIMMEDIATELAMBDA_H
