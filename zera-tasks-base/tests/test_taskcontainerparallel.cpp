#include "test_taskcontainerparallel.h"
#include "taskcontainerparallel.h"
#include "taskfortest.h"
#include "tasktesthelper.h"
#include <timemachinefortest.h>
#include <QTest>

QTEST_MAIN(test_taskcontainerparallel)

void test_taskcontainerparallel::init()
{
    TaskForTest::resetCounters();
    TimeMachineForTest::reset();
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

    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
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

    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
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

    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
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

    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);

    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 1);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainerparallel::addSecondWhileFirstRunning()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();

    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE/2);
    QCOMPARE(TaskForTest::dtorCount(), 0);
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));

    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    // second was not started!!
    QCOMPARE(TaskForTest::okCount(), 1);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainerparallel::addSecondAndStartWhileFirstRunning()
{
    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();

    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE/2);
    QCOMPARE(TaskForTest::dtorCount(), 0);
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();

    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 2);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 2);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE + DEFAULT_EXPIRE/2);
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

void test_taskcontainerparallel::startOrderAsAdded()
{
    QStringList results;
    TaskForTestPtr subTask1 = TaskForTest::create(0, true);
    connect(subTask1.get(), &TaskTemplate::sigFinish, this, [&](bool) {
        results.append("1");
    });

    TaskForTestPtr subTask2 = TaskForTest::create(0, true);
    connect(subTask2.get(), &TaskTemplate::sigFinish, this, [&](bool) {
        results.append("2");
    });
    TaskForTestPtr subTask3 = TaskForTest::create(0, true);
    connect(subTask3.get(), &TaskTemplate::sigFinish, this, [&](bool) {
        results.append("3");
    });

    TaskContainerInterfacePtr task = TaskContainerParallel::create();
    task->addSub(std::move(subTask1));
    task->addSub(std::move(subTask2));
    task->addSub(std::move(subTask3));

    task->start();
    QCOMPARE(results.size(), 3);
    QCOMPARE(results[0], "1");
    QCOMPARE(results[1], "2");
    QCOMPARE(results[2], "3");
}
