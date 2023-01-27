#include "tasklambdarunner.h"

TaskTemplatePtr TaskLambdaRunner::create(std::function<bool ()> startFunc)
{
    return std::make_unique<TaskLambdaRunner>(startFunc);
}

TaskLambdaRunner::TaskLambdaRunner(std::function<bool ()> startFunc) :
    m_startFunc(startFunc)
{
}

void TaskLambdaRunner::start()
{
    finishTask(m_startFunc());
}
