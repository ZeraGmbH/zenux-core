#include "taskdecoratorerrorhandler.h"

TaskTemplatePtr TaskDecoratorErrorHandler::create(TaskTemplatePtr decoratedTask, std::function<void ()> additionalErrorHandler)
{
    return std::make_unique<TaskDecoratorErrorHandler>(std::move(decoratedTask), additionalErrorHandler);
}

TaskDecoratorErrorHandler::TaskDecoratorErrorHandler(TaskTemplatePtr decoratedTask, std::function<void ()> additionalErrorHandler) :
    m_decoratedTask(std::move(decoratedTask)),
    m_additionalErrorHandler(additionalErrorHandler)
{
}

void TaskDecoratorErrorHandler::start()
{
    if(m_decoratedTask)
        startDecoratedTask();
    else
        emitFinish(true);
}

void TaskDecoratorErrorHandler::onFinishDecorated(bool ok)
{
    if(!ok)
        m_additionalErrorHandler();
    emitFinish(ok);
}

void TaskDecoratorErrorHandler::startDecoratedTask()
{
    connect(m_decoratedTask.get(), &TaskTemplate::sigFinish, this, &TaskDecoratorErrorHandler::onFinishDecorated);
    m_decoratedTask->start();
}

void TaskDecoratorErrorHandler::emitFinish(bool ok)
{
    m_decoratedTask = nullptr;
    finishTask(ok);
}
