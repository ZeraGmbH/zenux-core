#ifndef TEST_BACKTRACE_CONVERTER_H
#define TEST_BACKTRACE_CONVERTER_H

#include <QObject>

class test_backtrace_converter : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void testCreateBacktrace();
    void backtraceRawToVoidList();
    void allocsRawToAllocsTimeSorted();
};

#endif // TEST_BACKTRACE_CONVERTER_H
