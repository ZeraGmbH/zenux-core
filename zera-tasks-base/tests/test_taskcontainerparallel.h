#ifndef TEST_TASKCONTAINERPARALLEL_H
#define TEST_TASKCONTAINERPARALLEL_H

#include <QObject>

class test_taskcontainerparallel : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void startEmpty();
    void startErrorTask();
    void startPassImmediateDelayed();
    void startThreeImmediateMiddleFail();
    void startThreeImmediateAllOk();
    void startThreeDelayedMiddleFail();
    void startThreeDelayedAllOk();
    void taskId();
    void startTwice();
    void addSecondWhileFirstRunning();
    void addSecondAndStartWhileFirstRunning();
    void twoTransactions();
    void startOrderAsAdded();
};

#endif // TEST_TASKCONTAINERPARALLEL_H
