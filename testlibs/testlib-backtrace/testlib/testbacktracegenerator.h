#ifndef TESTBACKTRACEGENERATOR_H
#define TESTBACKTRACEGENERATOR_H

#include <QStringList>

class TestBacktraceGenerator
{
public:
    static QStringList createBacktraceRaw(const QString &removeCFunctionAndAllAbove = QString());
private:
    static QStringList removeUnwantedTopTraces(const QStringList &backtrace,
                                               const QString &removeCFunctionAndAllAbove);
    static QStringList removeFileName(const QStringList &backtrace);
};

#endif // TESTBACKTRACEGENERATOR_H
