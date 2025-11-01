#ifndef TASKCONTAINERQUEUE_H
#define TASKCONTAINERQUEUE_H

#include "taskcontainerinterface.h"

// A convenienece class for task queues
// * wraps TaskContainerSequence
// * (re)starts on addSub

class TaskContainerQueue : public TaskContainerInterface
{
    Q_OBJECT
public:
    static std::unique_ptr<TaskContainerInterface> create();
    TaskContainerQueue();
    void addSub(TaskTemplatePtr task) override;
private:
    void start() override;

    TaskContainerInterfacePtr m_tasks;
};

#endif // TASKCONTAINERQUEUE_H
