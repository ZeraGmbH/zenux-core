#ifndef TEST_TIMERELAPSEDQT_H
#define TEST_TIMERELAPSEDQT_H

#include <QObject>

class test_timerelapsedqt : public QObject
{
    Q_OBJECT
private slots:
    void init();

    void elapsedZeroOnNotStartedTiming();
    void elapsedZeroOnNotStartedTest();

    void startOnceDelayCheckElapsedTiming();
    void startOnceDelayCheckElapsedTest();

    void startTwiceDelayCheckElapsedTiming();
    void startTwiceDelayCheckElapsedTest();
};

#endif // TEST_TIMERELAPSEDQT_H
