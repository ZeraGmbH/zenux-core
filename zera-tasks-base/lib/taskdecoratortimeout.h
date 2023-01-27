#ifndef TASKTIMEOUTDECORATOR_H
#define TASKTIMEOUTDECORATOR_H

#include "tasktemplate.h"
#include <zeratimertemplate.h>
#include <memory>

class TaskDecoratorTimeout : public TaskTemplate
{
    Q_OBJECT
public:
    static TaskTemplatePtr wrapTimeout(int timeout, TaskTemplatePtr decoratedTask,
                                        std::function<void()> additionalErrorHandler = []{});
    TaskDecoratorTimeout(ZeraTimerTemplatePtr timer, TaskTemplatePtr decoratedTask);
    void start() override;
private slots:
    void onFinishDecorated(bool ok);
    void onTimeout();
private:
    void startDecoratedTask();
    void emitFinish(bool ok);
    TaskTemplatePtr m_decoratedTask;
    std::unique_ptr<ZeraTimerTemplate> m_timer;
};

#endif // TASKTIMEOUTDECORATOR_H
