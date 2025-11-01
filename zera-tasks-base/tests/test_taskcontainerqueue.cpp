#include "test_taskcontainerqueue.h"
#include "taskcontainerqueue.h"
#include "taskfortest.h"
#include "tasktesthelper.h"
#include <timemachinefortest.h>
#include <QTest>

QTEST_MAIN(test_taskcontainerqueue)

void test_taskcontainerqueue::init()
{
    TaskForTest::resetCounters();
    TimeMachineForTest::reset();
}

void test_taskcontainerqueue::startEmpty()
{
    TaskContainerInterfacePtr task = TaskContainerQueue::create();
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 0);
}

void test_taskcontainerqueue::oneOk()
{
    TaskContainerInterfacePtr task = TaskContainerQueue::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    // no start!
    TimeMachineForTest::getInstance()->processTimers(DEFAULT_EXPIRE_WAIT);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 1);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 1);
    QCOMPARE(helper.signalDelayMs(), DEFAULT_EXPIRE);
}

void test_taskcontainerqueue::oneOkWithStart()
{
    TaskContainerInterfacePtr task = TaskContainerQueue::create();
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

void test_taskcontainerqueue::twoOk()
{
    TaskContainerInterfacePtr task = TaskContainerQueue::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, true));
    // no start!
    TimeMachineForTest::getInstance()->processTimers(2*DEFAULT_EXPIRE);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 2);
    QCOMPARE(TaskForTest::errCount(), 0);
    QCOMPARE(TaskForTest::dtorCount(), 2);
    QCOMPARE(helper.signalDelayMs(), 2*DEFAULT_EXPIRE);
}

void test_taskcontainerqueue::twoError()
{
    TaskContainerInterfacePtr task = TaskContainerQueue::create();
    TaskTestHelper helper(task.get());
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    task->addSub(TaskForTest::create(DEFAULT_EXPIRE, false));
    // no start!
    TimeMachineForTest::getInstance()->processTimers(2*DEFAULT_EXPIRE);
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
    QCOMPARE(TaskForTest::okCount(), 0);
    QCOMPARE(TaskForTest::errCount(), 2);
    QCOMPARE(TaskForTest::dtorCount(), 2);
    QCOMPARE(helper.signalDelayMs(), 2*DEFAULT_EXPIRE);
}
