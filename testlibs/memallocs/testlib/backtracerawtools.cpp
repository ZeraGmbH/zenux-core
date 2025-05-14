#include "backtracerawtools.h"
#include <execinfo.h>

void BacktraceRawTools::fillBacktraceRaw(AllocBacktraceRaw *btrace)
{
    int backtraceCount = backtrace(btrace->bufferBacktrace, maxStacktraceDepth);
    btrace->startPos = 3; // after malloc - we have tests
    btrace->afterLastPos = backtraceCount;
}

QStringList BacktraceRawTools::generateSymbols(AllocBacktraceRaw *btrace) // remove or move somewhere else later?
{
    QStringList backtrace;
    // we need to fetch full backtrace otherwise 1st has missing symbol
    char** symbols = backtrace_symbols(btrace->bufferBacktrace,
                                       btrace->afterLastPos);
    for (int i = btrace->startPos; i < btrace->afterLastPos; i++)
        backtrace.append(symbols[i]);
    free(symbols);
    QStringList backtraceNoFilenames = removeFileName(backtrace);
    return backtraceNoFilenames;
}

QStringList BacktraceRawTools::removeFileName(const QStringList &backtrace)
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
