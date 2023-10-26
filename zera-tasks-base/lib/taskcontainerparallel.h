#ifndef TASKCONTAINERPARALLEL_H
#define TASKCONTAINERPARALLEL_H

#include "taskcontainerinterface.h"
#include <list>
#include <unordered_map>

// Task container running tasks parallel
// * start() is starting all tasks not yet started at once
// * adding tasks while running is valid - they are started on NEXT start()
// * emits sigFinish after all started tasks finish
// * ok if all tasks pass
// * delete finished tasks

class TaskContainerParallel : public TaskContainerInterface
{
    Q_OBJECT
public:
    static std::unique_ptr<TaskContainerInterface> create();
    void start() override;
    void addSub(TaskTemplatePtr task) override;
private slots:
    void onFinishTask(bool ok, int taskId);
private:
    void startTasksDirectConnectionSafe();

    std::list<TaskTemplatePtr> m_addedTasks;
    std::unordered_map<int, TaskTemplatePtr> m_startedTasks;
    bool m_allOk = false;
};

#endif // TASKCONTAINERPARALLEL_H
