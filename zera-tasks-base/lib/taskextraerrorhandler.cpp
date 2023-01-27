#include "taskextraerrorhandler.h"

TaskTemplatePtr TaskExtraErrorHandler::create(TaskTemplatePtr decoratedTask, std::function<void ()> additionalErrorHandler)
{
    return std::make_unique<TaskExtraErrorHandler>(std::move(decoratedTask), additionalErrorHandler);
}

TaskExtraErrorHandler::TaskExtraErrorHandler(TaskTemplatePtr decoratedTask, std::function<void ()> additionalErrorHandler) :
    m_decoratedTask(std::move(decoratedTask)),
    m_additionalErrorHandler(additionalErrorHandler)
{
}

void TaskExtraErrorHandler::start()
{
    if(m_decoratedTask)
        startDecoratedTask();
    else
        emitFinish(true);
}

void TaskExtraErrorHandler::onFinishDecorated(bool ok)
{
    if(!ok)
        m_additionalErrorHandler();
    emitFinish(ok);
}

void TaskExtraErrorHandler::startDecoratedTask()
{
    connect(m_decoratedTask.get(), &TaskTemplate::sigFinish, this, &TaskExtraErrorHandler::onFinishDecorated);
    m_decoratedTask->start();
}

void TaskExtraErrorHandler::emitFinish(bool ok)
{
    m_decoratedTask = nullptr;
    finishTask(ok);
}
