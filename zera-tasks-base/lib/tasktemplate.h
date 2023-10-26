#ifndef TASKTEMPLATE_H
#define TASKTEMPLATE_H

#include <QObject>
#include <memory>

// Template for all tasks

class TaskTemplate : public QObject
{
    Q_OBJECT
public:
    TaskTemplate();
    virtual ~TaskTemplate() = default;
    virtual void start() = 0;
    int getTaskId() const;
signals:
    void sigFinish(bool ok, int taskId);

protected:
    void finishTask(bool ok);
private:
    static int getNextTaskId();
    int m_taskId = 0;
    static int m_taskIdForNext;
};

typedef std::unique_ptr<TaskTemplate> TaskTemplatePtr;

#endif // TASKTEMPLATE_H
