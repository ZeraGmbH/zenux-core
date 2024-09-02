#ifndef TEST_STATISTICS_ASYNC_FLOAT_H
#define TEST_STATISTICS_ASYNC_FLOAT_H

#include <QObject>

class test_log_statistics_async_float : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void noSignalsForNoValuesAdded();
    void noSignalsForNanAdded();
    void oneValueAdded();
    void twoValuesAdded();
    void threValuesAddedNanIgnored();
    void twoValuesAddedTwoTimeSlots();
};

#endif // TEST_STATISTICS_ASYNC_FLOAT_H
