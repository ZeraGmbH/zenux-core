#include "tasktimeoutdecorator.h"
#include "taskdecoratorerrorhandler.h"
#include <zeratimerfactorymethods.h>

TaskTemplatePtr TaskTimeoutDecorator::wrapTimeout(int timeout, TaskTemplatePtr decoratedTask,
                                                   std::function<void ()> additionalErrorHandler)
{
    return TaskDecoratorErrorHandler::create(
                std::make_unique<TaskTimeoutDecorator>(
                    ZeraTimerFactoryMethods::createSingleShot(timeout),
                    std::move(decoratedTask)),
                additionalErrorHandler);
}

TaskTimeoutDecorator::TaskTimeoutDecorator(ZeraTimerTemplatePtr timer, TaskTemplatePtr decoratedTask) :
    m_decoratedTask(std::move(decoratedTask)),
    m_timer(std::move(timer))
{
}

void TaskTimeoutDecorator::start()
{
    if(m_decoratedTask)
        startDecoratedTask();
    else
        emitFinish(true);
}

void TaskTimeoutDecorator::onFinishDecorated(bool ok)
{
    m_timer->stop();
    emitFinish(ok);
}

void TaskTimeoutDecorator::onTimeout()
{
    emitFinish(false);
}

void TaskTimeoutDecorator::startDecoratedTask()
{
    connect(m_timer.get(), &ZeraTimerTemplate::sigExpired,
            this, &TaskTimeoutDecorator::onTimeout);
    m_timer->start();
    connect(m_decoratedTask.get(), &TaskTemplate::sigFinish, this, &TaskTimeoutDecorator::onFinishDecorated);
    m_decoratedTask->start();
}

void TaskTimeoutDecorator::emitFinish(bool ok)
{
    m_decoratedTask = nullptr;
    m_timer->stop();
    finishTask(ok);
}
