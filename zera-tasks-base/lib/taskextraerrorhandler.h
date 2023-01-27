#ifndef TASKEXTRAERRORHANDLER_H
#define TASKEXTRAERRORHANDLER_H

#include "tasktemplate.h"

class TaskExtraErrorHandler : public TaskTemplate
{
    Q_OBJECT
public:
    static TaskTemplatePtr create(TaskTemplatePtr decoratedTask, std::function<void()> additionalErrorHandler);
    TaskExtraErrorHandler(TaskTemplatePtr decoratedTask, std::function<void()> additionalErrorHandler);
    void start() override;
private slots:
    void onFinishDecorated(bool ok);
private:
    void startDecoratedTask();
    void emitFinish(bool ok);
    TaskTemplatePtr m_decoratedTask;
    std::function<void()> m_additionalErrorHandler;
};

#endif // TASKEXTRAERRORHANDLER_H
