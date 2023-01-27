#include "taskcontainersequence.h"

std::unique_ptr<TaskContainerInterface> TaskContainerSequence::create()
{
    return std::make_unique<TaskContainerSequence>();
}

void TaskContainerSequence::start()
{
    if(!m_started) {
        m_started = true;
        if(next())
            m_current->start();
        else
            finishTask(true);
    }
}

void TaskContainerSequence::addSub(TaskTemplatePtr task)
{
    m_tasks.push_front(std::move(task));
}

void TaskContainerSequence::onFinishCurr(bool ok)
{
    if(next() && ok)
        m_current->start();
    else {
        cleanup();
        finishTask(ok);
    }
}

bool TaskContainerSequence::next()
{
    if(!m_tasks.empty())
        setNext();
    else
        m_current = nullptr;
    return m_current != nullptr;
}

void TaskContainerSequence::setNext()
{
    m_current = std::move(m_tasks.back());
    m_tasks.pop_back();
    connect(m_current.get(), &TaskTemplate::sigFinish, this, &TaskContainerSequence::onFinishCurr);
}

void TaskContainerSequence::cleanup()
{
    m_started = false;
    m_current = nullptr;
    m_tasks.clear();
}
