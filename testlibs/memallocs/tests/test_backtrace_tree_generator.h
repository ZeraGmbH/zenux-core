#ifndef TEST_BACKTRACE_TREE_GENERATOR_H
#define TEST_BACKTRACE_TREE_GENERATOR_H

#include <QObject>

class test_backtrace_tree_generator : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void oneAlloc();
    void twoAllocsCompleteDifferentBacktrace();
    void twoAllocsSameFirstBacktrace();
};

#endif // TEST_BACKTRACE_TREE_GENERATOR_H
