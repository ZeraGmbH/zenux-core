#ifndef TASKCONTAINERSEQUENCE_H
#define TASKCONTAINERSEQUENCE_H

#include "taskcontainerinterface.h"
#include <list>

// Task container running tasks sequentially
// * start() is starting first task / if running do nothing
// * adding tasks while running is valid - they are appended to task queue
// * emits sigFinish after
//       errorHandling = StopOnFirstTaskFail: all tasks passed OR first failed
//       errorHandling = RunAllTasks: all tasks run
// * ok if all tasks pass OR errorHandling = RunAllTasks
// * delete all tasks on finish

class TaskContainerSequence : public TaskContainerInterface // for now abort on error
{
    Q_OBJECT
public:
    enum ErrorHandling {
        StopOnFirstTaskFail,
        RunAllTasks
    };
    static std::unique_ptr<TaskContainerInterface> create(ErrorHandling errorHandling = StopOnFirstTaskFail);
    explicit TaskContainerSequence(ErrorHandling errorHandling = StopOnFirstTaskFail);
    void start() override;
    void addSub(TaskTemplatePtr task) override;

private slots:
    void onFinishCurr(bool ok);
private:
    void tryStart();
    bool next();
    void cleanup();
    ErrorHandling m_errorHandling;
    bool m_started = false;
    std::list<TaskTemplatePtr> m_tasks;
    TaskTemplatePtr m_current;
};

#endif // TASKCONTAINERSEQUENCE_H
