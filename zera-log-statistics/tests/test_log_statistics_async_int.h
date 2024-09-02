#ifndef TEST_STATISTICS_ASYNC_INT_H
#define TEST_STATISTICS_ASYNC_INT_H

#include <QObject>

class test_log_statistics_async_int : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void noSignalsForNoValuesAdded();
    void oneValueAdded();
    void twoValuesAdded();
    void twoValuesAddedTwoTimeSlots();
};

#endif // TEST_STATISTICS_ASYNC_INT_H
