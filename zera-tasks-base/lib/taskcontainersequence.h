#ifndef TASKCONTAINERSEQUENCE_H
#define TASKCONTAINERSEQUENCE_H

#include "taskcontainerinterface.h"
#include <list>

// Task container running tasks sequentially
// * start() is starting firts task / if running do nothing
// * adding tasks while running is valid - they are appended to task queue
// * emits sigFinish after all tasks passed OR first failed
// * ok if all tasks pass
// * delete finished tasks

class TaskContainerSequence : public TaskContainerInterface // for now abort on error
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

#endif // TASKCONTAINERSEQUENCE_H
