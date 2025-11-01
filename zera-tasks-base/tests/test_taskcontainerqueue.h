#ifndef TEST_TASKCONTAINERQUEUE_H
#define TEST_TASKCONTAINERQUEUE_H

#include <QObject>

class test_taskcontainerqueue : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void startEmpty();
    void oneOk();
    void oneOkWithStart();
    void twoOk();
};

#endif // TEST_TASKCONTAINERQUEUE_H
