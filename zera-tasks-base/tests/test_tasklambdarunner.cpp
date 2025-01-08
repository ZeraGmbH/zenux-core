#include "test_tasklambdarunner.h"
#include "tasklambdarunner.h"
#include "tasktesthelper.h"
#include "timemachineobject.h"
#include <QTest>

QTEST_MAIN(test_tasklambdarunner)

void test_tasklambdarunner::startPass()
{
    TaskTemplatePtr task = TaskLambdaRunner::create([&](){
        return true;
    });
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
}

void test_tasklambdarunner::startFail()
{
    TaskTemplatePtr task = TaskLambdaRunner::create([&](){
        return false;
    });
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
}

void test_tasklambdarunner::startPassQueued()
{
    TaskTemplatePtr task = TaskLambdaRunner::create([&]() {
        return true;
        },
        true);
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 0);

    TimeMachineObject::feedEventLoop();
    QCOMPARE(helper.okCount(), 1);
    QCOMPARE(helper.errCount(), 0);
}

void test_tasklambdarunner::startFailQueued()
{
    TaskTemplatePtr task = TaskLambdaRunner::create([&]() {
        return false;
        },
        true);
    TaskTestHelper helper(task.get());
    task->start();
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 0);

    TimeMachineObject::feedEventLoop();
    QCOMPARE(helper.okCount(), 0);
    QCOMPARE(helper.errCount(), 1);
}
