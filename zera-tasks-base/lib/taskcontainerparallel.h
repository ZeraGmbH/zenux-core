#ifndef TASKCONTAINERPARALLEL_H
#define TASKCONTAINERPARALLEL_H

#include "taskcontainerinterface.h"
#include <list>
#include <unordered_map>

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
