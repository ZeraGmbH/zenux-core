#include "test_taskcontainerparallel.h"
#include "taskcontainerparallel.h"
#include "taskfortest.h"
#include "tasktesthelper.h"
#include <timerrunnerfortest.h>
#include <QTest>

QTEST_MAIN(test_taskcontainerparallel)

void test_taskcontainerparallel::init()
{
    TaskForTest::resetCounters();
    TimerRunnerForTest::reset();
}

void test_taskcontainerparallel::startEmpty()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 0);
}

void test_taskcontainerparallel::startErrorTask()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(0, false));
    task->start();
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 1);
}

void test_taskcontainerparallel::startPassImmediateDelayed()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(0, true));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();

    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 1);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 1);

    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 2);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 2);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainerparallel::startThreeImmediateMiddleFail()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(0, true));
    task->addSub(TaskForTest::create(0, false));
    task->addSub(TaskForTest::create(0, true));
    task->start();

    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 2);
    QCOMPARE(TaskForTest::errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 3);
}

void test_taskcontainerparallel::startThreeImmediateAllOk()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(0, true));
    task->addSub(TaskForTest::create(0, true));
    task->addSub(TaskForTest::create(0, true));
    task->start();

    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 3);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 3);
}

void test_taskcontainerparallel::startThreeDelayedMiddleFail()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();

    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 2);
    QCOMPARE(TaskForTest::errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 3);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainerparallel::startThreeDelayedAllOk()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();

    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 3);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 3);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainerparallel::taskId()
{
    TaskContainerParallel task1;
    TaskTestHelper helper1(&task1);
    task1.addSub(TaskForTest::create(0, true));
    int taskId1 = task1.getTaskId();
    task1.start();
    QCOMPARE(helper1.lastTaskIdReceived(), taskId1);

    TaskContainerParallel task2;
    TaskTestHelper helper2(&task2);
    task2.addSub(TaskForTest::create(0, true));
    int taskId2 = task2.getTaskId();
    task2.start();
    QCOMPARE(helper2.lastTaskIdReceived(), taskId2);
    QVERIFY(taskId1 != taskId2);
}

void test_taskcontainerparallel::startTwice()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();
    task->start();
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 0);
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 0);

    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 1);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainerparallel::onRunningAddAndStartOne()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();

    task->addSub(TaskForTest::create(0, true));
    task->start();
    QCOMPARE(TaskForTest::okCount(), 1);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 0);

    TimerRunnerForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 2);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 2);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainerparallel::twoTransactions()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(0, true));
    task->start();
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);

    task->addSub(TaskForTest::create(0, true));
    task->start();
    QCOMPARE(helper.okCount(), 2);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 2);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 2);
}
