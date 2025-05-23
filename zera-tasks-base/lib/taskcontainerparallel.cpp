#include "taskcontainerparallel.h"
#include <QList>

std::unique_ptr<TaskContainerInterface> TaskContainerParallel::create()
{
    return std::make_unique<TaskContainerParallel>();
}

void TaskContainerParallel::start()
{
    if(!m_addedTasks.empty())
        startTasksDirectConnectionSafe();
    else if(m_startedTasks.empty())
        finishTask(true);
}

void TaskContainerParallel::addSub(TaskTemplatePtr task)
{
    m_addedTasks.push_front(std::move(task));
}

void TaskContainerParallel::onFinishTask(bool ok, int taskId)
{
    if(m_startedTasks.erase(taskId)) {
        m_allOk = m_allOk && ok;
        if(m_startedTasks.empty())
            finishTask(m_allOk);
    }
}

void TaskContainerParallel::startTasksDirectConnectionSafe()
{
    m_allOk = true;
    QList<int> taskIdsToStart;
    while(!m_addedTasks.empty()) {
        auto task = std::move(m_addedTasks.back());
        m_addedTasks.pop_back();
        connect(task.get(), &TaskTemplate::sigFinish, this, &TaskContainerParallel::onFinishTask);
        int taskId = task->getTaskId();
        taskIdsToStart.push_back(taskId);
        m_startedTasks[taskId] = std::move(task);
    }
    for(const int &taskId : taskIdsToStart)
        m_startedTasks[taskId]->start();
}
