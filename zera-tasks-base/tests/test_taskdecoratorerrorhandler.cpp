#include "test_taskdecoratorerrorhandler.h"
#include "taskdecoratorerrorhandler.h"
#include "taskfortest.h"
#include "tasktesthelper.h"
#include <timerrunnerfortest.h>
#include <QTest>

QTEST_MAIN(test_taskdecoratorerrorhandler)

void test_taskdecoratorerrorhandler::init()
{
    TaskForTest::resetCounters();
    TimerRunnerForTest::reset();
}

void test_taskdecoratorerrorhandler::startEmpty()
{
    TaskTemplatePtr task = TaskDecoratorErrorHandler::create(nullptr,[&]{});
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
}

void test_taskdecoratorerrorhandler::handleError()
{
    int extraErrCount = 0;
    TaskTemplatePtr task = TaskDecoratorErrorHandler::create(TaskForTest::create(DEFAULT_EXPIRE, false),[&]{
        extraErrCount++;
    });
    TaskTestHelper helper(task.get());
    task->start();
    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(extraErrCount, 1);
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskdecoratorerrorhandler::handleNoError()
{
    int extraErrCount = 0;
    TaskTemplatePtr task = TaskDecoratorErrorHandler::create(TaskForTest::create(DEFAULT_EXPIRE, true),[&]{
        extraErrCount++;
    });
    TaskTestHelper helper(task.get());
    task->start();
    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(extraErrCount, 0);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskdecoratorerrorhandler::taskId()
{
    TaskTemplatePtr task = TaskDecoratorErrorHandler::create(TaskForTest::create(0, true),[&]{});
    int taskId = task->getTaskId();
    int taskIdReceived = 42;
    connect(task.get(), &TaskTemplate::sigFinish, [&](bool , int taskId) {
        taskIdReceived = taskId;
    });
    task->start();
    QCOMPARE(taskId, taskIdReceived);
}

