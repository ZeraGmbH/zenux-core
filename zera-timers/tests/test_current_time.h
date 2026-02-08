#ifndef TEST_CURRENT_TIME_H
#define TEST_CURRENT_TIME_H

#include <QObject>
#include <QDateTime>

class test_current_time : public QObject
{
    Q_OBJECT
private slots:
    void init();

    void disableTest();
    void enableTestNoTimeProgression();
    void enableTestTimeProgression();
    void enableTestSetTime();
    void enableTestSetTimeProgression();
    void enableTestSetTimeReset();
private:
    QDateTime createTestDateTime() const;
};

#endif // TEST_CURRENT_TIME_H
