#include "taskcontainerqueue.h"
#include "taskcontainersequence.h"

std::unique_ptr<TaskContainerInterface> TaskContainerQueue::create()
{
    return std::make_unique<TaskContainerQueue>();
}

TaskContainerQueue::TaskContainerQueue() :
    m_tasks(TaskContainerSequence::create())
{
    connect(m_tasks.get(), &TaskTemplate::sigFinish,
            this, &TaskTemplate::sigFinish);
}

void TaskContainerQueue::addSub(TaskTemplatePtr task)
{
    m_tasks->addSub(std::move(task));
    m_tasks->start();
}

void TaskContainerQueue::start()
{
    m_tasks->start();
}
