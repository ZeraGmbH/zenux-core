#include "taskcontainersequence.h"

std::unique_ptr<TaskContainerInterface> TaskContainerSequence::create()
{
    return std::make_unique<TaskContainerSequence>();
}

void TaskContainerSequence::start() {
    tryStart();
}

void TaskContainerSequence::addSub(TaskTemplatePtr task)
{
    m_tasks.push_front(std::move(task));
}

void TaskContainerSequence::tryStart()
{
    if(!m_started) {
        m_started = true;
        if(next())
            m_current->start();
        else
            finishTask(true);
    }
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
    m_current = nullptr;
    if(!m_tasks.empty()) {
        m_current = std::move(m_tasks.back());
        m_tasks.pop_back();
        connect(m_current.get(), &TaskTemplate::sigFinish, this, &TaskContainerSequence::onFinishCurr);
    }
    return m_current != nullptr;
}

void TaskContainerSequence::cleanup()
{
    m_started = false;
    m_current = nullptr;
    m_tasks.clear();
}
