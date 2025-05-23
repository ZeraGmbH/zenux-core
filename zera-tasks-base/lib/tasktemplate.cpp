#include "tasktemplate.h"

TaskTemplate::TaskTemplate() :
    m_taskId(getNextTaskId())
{
}

int TaskTemplate::getTaskId() const
{
    return m_taskId;
}

void TaskTemplate::finishTask(bool ok)
{
    emit sigFinish(ok, m_taskId);
}

void TaskTemplate::finishTaskQueued(bool ok)
{
    QMetaObject::invokeMethod(this,
                              "sigFinish",
                              Qt::QueuedConnection,
                              Q_ARG(bool, ok),
                              Q_ARG(int, m_taskId));
}

int TaskTemplate::m_taskIdForNext = 0;

int TaskTemplate::getNextTaskId()
{
    return ++m_taskIdForNext;
}
