#ifndef TASKCONTAINERINTERFACE_H
#define TASKCONTAINERINTERFACE_H

#include "tasktemplate.h"

class TaskContainerInterface : public TaskTemplate
{
public:
    virtual void addSub(TaskTemplatePtr task) = 0;
};

typedef std::unique_ptr<TaskContainerInterface> TaskContainerInterfacePtr;

#endif // TASKCONTAINERINTERFACE_H
