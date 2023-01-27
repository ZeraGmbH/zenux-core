#ifndef TASKSEQUENCE_H
#define TASKSEQUENCE_H

#include "taskcontainerinterface.h"
#include <list>

class TaskSequence : public TaskContainerInterface // for now abort on error
{
    Q_OBJECT
public:
    static std::unique_ptr<TaskContainerInterface> create();
    void start() override;
    void addSub(TaskTemplatePtr task) override;

private slots:
    void onFinishCurr(bool ok);
private:
    bool next();
    void setNext();
    void cleanup();
    bool m_started = false;
    std::list<TaskTemplatePtr> m_tasks;
    TaskTemplatePtr m_current;
    int m_taskId;
};

#endif // TASKSEQUENCE_H
