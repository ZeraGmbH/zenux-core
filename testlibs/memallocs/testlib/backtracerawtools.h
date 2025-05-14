#ifndef BACKTRACERAWTOOLS_H
#define BACKTRACERAWTOOLS_H

#include "allocationdatadefinitions.h"
#include <QStringList>

class BacktraceRawTools
{
public:
    static void fillBacktraceRaw(AllocBacktraceRaw *btrace);
    static QStringList generateSymbols(AllocBacktraceRaw *btrace);

private:
    static QStringList removeUnwantedTopTraces(const QStringList &backtrace,
                                               const QString &removeCFunctionAndAllAbove);
    static QStringList removeFileName(const QStringList &backtrace);
};

#endif // BACKTRACERAWTOOLS_H
