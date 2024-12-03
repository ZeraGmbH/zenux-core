#include "taskdecoratortimeout.h"
#include "taskdecoratorerrorhandler.h"
#include <timerfactoryqt.h>

TaskTemplatePtr TaskDecoratorTimeout::wrapTimeout(int timeout, TaskTemplatePtr decoratedTask,
                                                   std::function<void ()> additionalErrorHandler)
{
    return TaskDecoratorErrorHandler::create(
                std::make_unique<TaskDecoratorTimeout>(
                    TimerFactoryQt::createSingleShot(timeout),
                    std::move(decoratedTask)),
                additionalErrorHandler);
}

TaskDecoratorTimeout::TaskDecoratorTimeout(TimerTemplateQtPtr timer, TaskTemplatePtr decoratedTask) :
    m_decoratedTask(std::move(decoratedTask)),
    m_timer(std::move(timer))
{
}

void TaskDecoratorTimeout::start()
{
    if(m_decoratedTask)
        startDecoratedTask();
    else
        emitFinish(true);
}

void TaskDecoratorTimeout::onFinishDecorated(bool ok)
{
    m_timer->stop();
    emitFinish(ok);
}

void TaskDecoratorTimeout::onTimeout()
{
    qWarning("TaskDecoratorTimeout: Timeout reached!!!");
    emitFinish(false);
}

void TaskDecoratorTimeout::startDecoratedTask()
{
    connect(m_timer.get(), &TimerTemplateQt::sigExpired,
            this, &TaskDecoratorTimeout::onTimeout);
    m_timer->start();
    connect(m_decoratedTask.get(), &TaskTemplate::sigFinish, this, &TaskDecoratorTimeout::onFinishDecorated);
    m_decoratedTask->start();
}

void TaskDecoratorTimeout::emitFinish(bool ok)
{
    m_decoratedTask = nullptr;
    m_timer->stop();
    finishTask(ok);
}
