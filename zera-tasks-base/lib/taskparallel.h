#ifndef TASKPARALLEL_H
#define TASKPARALLEL_H

#include "taskcontainerinterface.h"
#include <list>
#include <unordered_map>

class TaskParallel : public TaskContainerInterface
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

#endif // TASKPARALLEL_H
