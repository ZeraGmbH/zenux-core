#ifndef TASKLAMBDARUNNER_H
#define TASKLAMBDARUNNER_H

#include "tasktemplate.h"
#include <functional>

class TaskLambdaRunner : public TaskTemplate
{
    Q_OBJECT
public:
    static TaskTemplatePtr create(std::function<bool ()> startFunc);
    TaskLambdaRunner(std::function<bool()> startFunc);
    void start() override;
private:
    std::function<bool()> m_startFunc;
};

#endif // TASKLAMBDARUNNER_H
