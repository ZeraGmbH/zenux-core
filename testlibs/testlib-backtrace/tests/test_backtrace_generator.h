#ifndef TEST_BACKTRACE_GENERATOR_H
#define TEST_BACKTRACE_GENERATOR_H

#include <QObject>
#include <QStringList>

class test_backtrace_generator : public QObject
{
    Q_OBJECT
private slots:
    void generateBacktrace();
    void generateBacktraceThroughIntermediateFunction();
private:
    bool logOnNotContains(const QString &found, const QString contains);
    QStringList intermediateBacktraceFkt();
};

#endif // TEST_BACKTRACE_GENERATOR_H
