#ifndef TASKCONTAINERINTERFACE_H
#define TASKCONTAINERINTERFACE_H

#include "taskcomposit.h"

class TaskContainerInterface : public TaskComposite
{
public:
    virtual void addSub(TaskCompositePtr task) = 0;
};

typedef std::unique_ptr<TaskContainerInterface> TaskContainerInterfacePtr;

#endif // TASKCONTAINERINTERFACE_H
