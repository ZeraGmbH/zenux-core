#ifndef TEST_TASKEXTRAERRORHANDLER_H
#define TEST_TASKEXTRAERRORHANDLER_H

#include <QObject>

class test_taskdecoratorerrorhandler : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void startEmpty();
    void handleError();
    void handleNoError();
    void taskId();
};

#endif // TEST_TASKEXTRAERRORHANDLER_H
