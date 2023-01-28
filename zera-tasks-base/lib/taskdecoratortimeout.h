#ifndef TASKDECORATORTIMEOUT_H
#define TASKDECORATORTIMEOUT_H

#include "tasktemplate.h"
#include <timertemplateqt.h>
#include <memory>

class TaskDecoratorTimeout : public TaskTemplate
{
    Q_OBJECT
public:
    static TaskTemplatePtr wrapTimeout(int timeout, TaskTemplatePtr decoratedTask,
                                        std::function<void()> additionalErrorHandler = []{});
    TaskDecoratorTimeout(TimerTemplateQtPtr timer, TaskTemplatePtr decoratedTask);
    void start() override;
private slots:
    void onFinishDecorated(bool ok);
    void onTimeout();
private:
    void startDecoratedTask();
    void emitFinish(bool ok);
    TaskTemplatePtr m_decoratedTask;
    std::unique_ptr<TimerTemplateQt> m_timer;
};

#endif // TASKDECORATORTIMEOUT_H
