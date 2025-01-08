#include "tasklambdarunner.h"

TaskTemplatePtr TaskLambdaRunner::create(std::function<bool ()> startFunc, bool queuedFinish)
{
    return std::make_unique<TaskLambdaRunner>(startFunc, queuedFinish);
}

TaskLambdaRunner::TaskLambdaRunner(std::function<bool ()> startFunc, bool queuedFinish) :
    m_startFunc(startFunc),
    m_queuedFinish(queuedFinish)
{
}

void TaskLambdaRunner::start()
{
    if(m_queuedFinish)
        finishTaskQueued(m_startFunc());
    else
        finishTask(m_startFunc());
}
