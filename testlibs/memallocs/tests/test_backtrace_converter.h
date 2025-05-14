#ifndef TEST_BACKTRACE_CONVERTER_H
#define TEST_BACKTRACE_CONVERTER_H

#include <QObject>

class test_backtrace_converter : public QObject
{
    Q_OBJECT
private slots:
    void testCreateBacktrace();
    void backtraceRawToVoidList();
    void backtracesRawToVoidLists();
};

#endif // TEST_BACKTRACE_CONVERTER_H
