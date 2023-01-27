#include "tasktesthelper.h"
#include <timerrunnerfortest.h>

TaskTestHelper::TaskTestHelper(TaskTemplate *taskUnderTest)
{
    connect(taskUnderTest, &TaskTemplate::sigFinish, this, &TaskTestHelper::onTaskFinish);
}

void TaskTestHelper::onTaskFinish(bool ok, int taskId)
{
    if(ok)
        m_okCount++;
    else
        m_errCount++;
    m_signalDelayMs = TimerRunnerForTest::getInstance()->getCurrentTimeMs();
    m_taskIdsReceived.append(taskId);
}
