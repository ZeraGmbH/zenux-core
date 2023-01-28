#include "test_taskdecoratortimeout.h"
#include "taskfortest.h"
#include "taskdecoratortimeout.h"
#include "tasktesthelper.h"
#include <timerfortestsingleshot.h>
#include <timerrunnerfortest.h>
#include <zeratimerfactorymethodstest.h>
#include <QTest>

QTEST_MAIN(test_taskdecoratortimeout)

void test_taskdecoratortimeout::init()
{
    TaskForTest::resetCounters();
    TimerRunnerForTest::reset();
    ZeraTimerFactoryMethodsTest::enableTest();
}

void test_taskdecoratortimeout::startEmpty()
{
    TaskTemplatePtr task = TaskDecoratorTimeout::wrapTimeout(EXPIRE_INFINITE,
                                                             nullptr);
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
}

void test_taskdecoratortimeout::startEmptyCheckDelayed()
{
    TaskTemplatePtr task = TaskDecoratorTimeout::wrapTimeout(DEFAULT_EXPIRE,
                                                             nullptr);
    TaskTestHelper helper(task.get());
    task->start();
    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(helper.signalDelayMs(), 0);
}

void test_taskdecoratortimeout::immediateOk()
{
    TaskTemplatePtr task = TaskDecoratorTimeout::wrapTimeout(EXPIRE_INFINITE,
                                                             TaskForTest::create(0, true));
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 1);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), 0);
}

void test_taskdecoratortimeout::immediateError()
{
    TaskTemplatePtr task = TaskDecoratorTimeout::wrapTimeout(EXPIRE_INFINITE,
                                                             TaskForTest::create(0, false));
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), 0);
}

void test_taskdecoratortimeout::immediateErrorWithErrFunc()
{
    int localErrorCount = 0;
    TaskTemplatePtr task = TaskDecoratorTimeout::wrapTimeout(EXPIRE_INFINITE,
                                                             TaskForTest::create(0, false),
                                                             [&]{
                                                                 localErrorCount++;
                                                             });
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 1);
}

void test_taskdecoratortimeout::infiniteTask()
{
    TaskTemplatePtr task = TaskDecoratorTimeout::wrapTimeout(DEFAULT_EXPIRE,
                                                             TaskForTest::create(EXPIRE_INFINITE, true));
    TaskTestHelper helper(task.get());
    task->start();
    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskdecoratortimeout::delayedOk()
{
    TaskTemplatePtr task = TaskDecoratorTimeout::wrapTimeout(DEFAULT_EXPIRE,
                                                             TaskForTest::create(DEFAULT_EXPIRE/2, true));
    TaskTestHelper helper(task.get());
    task->start();
    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 1);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE/2);
}

void test_taskdecoratortimeout::delayEqualsTimeout()
{
    TaskTemplatePtr task = TaskDecoratorTimeout::wrapTimeout(DEFAULT_EXPIRE,
                                                             TaskForTest::create(DEFAULT_EXPIRE, true));
    TaskTestHelper helper(task.get());
    task->start();
    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount() + helper.errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskdecoratortimeout::taskId()
{
    TaskForTest task1(0, true);
    TaskTestHelper helper1(&task1);
    int taskId1 = task1.getTaskId();
    task1.start();
    QCOMPARE(helper1.lastTaskIdReceived(), taskId1);

    TaskForTest task2(0, true);
    TaskTestHelper helper2(&task2);
    int taskId2 = task2.getTaskId();
    task2.start();
    QCOMPARE(helper2.lastTaskIdReceived(), taskId2);
    QVERIFY(taskId1 != taskId2);
}
