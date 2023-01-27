#ifndef TEST_TASKCONTAINERSEQUENCE_H
#define TEST_TASKCONTAINERSEQUENCE_H

#include <QObject>

class test_taskcontainersequence : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void startEmpty();
    void oneOk();
    void twoOk();
    void oneError();
    void twoError();
    void threeError();
    void oneErrorOneOk();
    void oneOkOneErrorOneOk();
    void taskId();
    void startTwice();
    void onRunningAddAndStartOne();
    void twoTransactions();
};

#endif // TEST_TASKCONTAINERSEQUENCE_H
