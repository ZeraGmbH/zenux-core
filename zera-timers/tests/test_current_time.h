#ifndef TEST_CURRENT_TIME_H
#define TEST_CURRENT_TIME_H

#include <QObject>

class test_current_time : public QObject
{
    Q_OBJECT
private slots:
    void disableTest();
    void enableTestNoTimeProgression();
    void enableTestTimeProgression();
};

#endif // TEST_CURRENT_TIME_H
