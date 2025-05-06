#include "testbacktracegenerator.h"
#include <execinfo.h>

QStringList TestBacktraceGenerator::createBacktraceRaw(const QString &removeCFunctionAndAllAbove)
{
    void* buffer[50];
    int frames = backtrace(buffer, 50);
    char** symbols = backtrace_symbols(buffer, frames);

    QStringList backtrace;
    for (int i = 0; i < frames; i++)
        backtrace.append(symbols[i]);
    free(symbols);

    return removeUnwantedTopTraces(removeFileName(backtrace), removeCFunctionAndAllAbove);
}

QStringList TestBacktraceGenerator::removeUnwantedTopTraces(const QStringList &backtrace,
                                                            const QString &removeCFunctionAndAllAbove)
{
    int maxIdxCallingFunction = -1;
    for (int currBacktrace = 0; currBacktrace < backtrace.count(); currBacktrace++) {
        if (backtrace[currBacktrace].contains("createBacktraceRaw"))
            maxIdxCallingFunction = currBacktrace;
        if (!removeCFunctionAndAllAbove.isEmpty() && backtrace[currBacktrace].startsWith(removeCFunctionAndAllAbove + "+"))
            maxIdxCallingFunction = currBacktrace;
    }

    QStringList adjustedBacktrace = backtrace;
        if (maxIdxCallingFunction >= 0)
            for (int i=0; i<=maxIdxCallingFunction; i++)
                adjustedBacktrace.removeFirst();
    return adjustedBacktrace;
}

QStringList TestBacktraceGenerator::removeFileName(const QStringList &backtrace)
{
    QStringList adjustedBacktrace;
    for (int currBacktrace = 0; currBacktrace < backtrace.count(); currBacktrace++) {
        QStringList splitBackets = backtrace[currBacktrace].split("(");
        QString withoutFileName = splitBackets[1];
        withoutFileName.remove(")");
        adjustedBacktrace.append(withoutFileName);
    }
    return adjustedBacktrace;
}
