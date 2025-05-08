#ifndef TEST_MEMORY_ALLOC_BACKTRACE_GENERATOR_H
#define TEST_MEMORY_ALLOC_BACKTRACE_GENERATOR_H

#include <QObject>
#include <QStringList>

class test_memory_alloc_backtrace_generator : public QObject
{
    Q_OBJECT
private slots:
    void generateBacktrace();
    void generateBacktraceThroughIntermediateFunction();
private:
    bool logOnNotContains(const QString &found, const QString contains);
    QStringList intermediateBacktraceFkt();
};

#endif // TEST_MEMORY_ALLOC_BACKTRACE_GENERATOR_H
