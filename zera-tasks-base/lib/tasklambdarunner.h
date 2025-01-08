#ifndef TASKLAMBDARUNNER_H
#define TASKLAMBDARUNNER_H

#include "tasktemplate.h"
#include <functional>

// Task running lambda function

class TaskLambdaRunner : public TaskTemplate
{
    Q_OBJECT
public:
    static TaskTemplatePtr create(std::function<bool ()> startFunc, bool queuedFinish = false);
    TaskLambdaRunner(std::function<bool()> startFunc, bool queuedFinish);
    void start() override;
private:
    std::function<bool()> m_startFunc;
    bool m_queuedFinish;
};

#endif // TASKLAMBDARUNNER_H
