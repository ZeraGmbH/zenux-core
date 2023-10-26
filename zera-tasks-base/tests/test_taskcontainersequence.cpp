#include "test_taskcontainersequence.h"
#include "taskcontainersequence.h"
#include "taskfortest.h"
#include "tasktesthelper.h"
#include <timemachinefortest.h>
#include <QTest>

QTEST_MAIN(test_taskcontainersequence)

void test_taskcontainersequence::init()
{
    TaskForTest::resetCounters();
    TimeMachineForTest::reset();
}

void test_taskcontainersequence::startEmpty()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 0);
}

void test_taskcontainersequence::oneOk()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 1);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainersequence::twoOk()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();
    TimeMachineForTest::getInstance()->processTimers(2*DEFAULT_EXPIRE);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 2);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 2);
    QCOMPARE(helper.signalDelayMs(), 2*DEFAULT_EXPIRE);
}

void test_taskcontainersequence::oneError()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    task->start();
    TimeMachineForTest::getInstance()->processTimers(2*DEFAULT_EXPIRE);
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainersequence::twoError()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    task->start();
    TimeMachineForTest::getInstance()->processTimers(2*DEFAULT_EXPIRE);
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 2);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainersequence::threeError()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    task->start();
    TimeMachineForTest::getInstance()->processTimers(3*DEFAULT_EXPIRE);
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 3);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainersequence::oneErrorOneOk()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();
    TimeMachineForTest::getInstance()->processTimers(2*DEFAULT_EXPIRE);
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 2);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainersequence::oneOkOneErrorOneOk()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();
    TimeMachineForTest::getInstance()->processTimers(3*DEFAULT_EXPIRE);
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
    QCOMPARE(TaskForTest::okCount(), 1);
    QCOMPARE(TaskForTest::errCount(), 1);
    QCOMPARE(TaskForTest::dtorCount(), 3);
    QCOMPARE(helper.signalDelayMs(), 2*DEFAULT_EXPIRE);
}

void test_taskcontainersequence::taskId()
{
    TaskContainerSequence task1;
    TaskTestHelper helper1(&task1);
    task1.addSub(TaskForTest::create(0, true));
    int taskId1 = task1.getTaskId();
    task1.start();
    QCOMPARE(helper1.lastTaskIdReceived(), taskId1);

    TaskContainerSequence task2;
    TaskTestHelper helper2(&task2);
    task2.addSub(TaskForTest::create(0, true));
    int taskId2 = task2.getTaskId();
    task2.start();
    QCOMPARE(helper2.lastTaskIdReceived(), taskId2);
    QVERIFY(taskId1 != taskId2);
}

void test_taskcontainersequence::startTwice()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();
    task->start();
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

void test_taskcontainersequence::addSecondWhileFirstRunning()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->start();

    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE/2);
    QCOMPARE(TaskForTest::dtorCount(), 0);
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));

    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 2);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 2);
    QCOMPARE(helper.signalDelayMs(), 2*DEFAULT_EXPIRE); // remember sequential: one after another
}

void test_taskcontainersequence::addSecondAndStartWhileFirstRunning()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
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
    QCOMPARE(helper.signalDelayMs(), 2*DEFAULT_EXPIRE); // remember sequential: one after another
}

void test_taskcontainersequence::twoTransactions()
{
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
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
