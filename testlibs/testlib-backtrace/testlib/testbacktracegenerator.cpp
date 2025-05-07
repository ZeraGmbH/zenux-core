#include "testbacktracegenerator.h"

static void *mallocPointer = nullptr;

void TestBacktraceGenerator::createBacktraceRaw(BacktraceRaw *btrace)
{
    int backtraceCount = backtrace(btrace->bufferBacktrace, maxStacktraceDepth);
    btrace->startPos = 1; // ignore myself
    btrace->afterLastPos = backtraceCount;
    cacheSpecialFunctionAddresses(btrace); // move because most allocatiions are freed
    alignStartPosition(btrace);
}

void TestBacktraceGenerator::alignStartPosition(BacktraceRaw *btrace)
{
    for (int i=btrace->startPos; i<btrace->afterLastPos-1; ++i) {
        const void* currPointer = btrace->bufferBacktrace[i];
        if (currPointer == mallocPointer) {
            btrace->startPos = i+1;
            break;
        }
    }
}

void TestBacktraceGenerator::cacheSpecialFunctionAddresses(BacktraceRaw *btrace)
{
    if (mallocPointer)
        return;
    const QStringList stackTexts = generateAllSymbols(btrace);
    for (int i=0; i<stackTexts.count()-1; i++) {
        const QString &entry = stackTexts[i];
        if (entry.startsWith("malloc+"))
            mallocPointer = btrace->bufferBacktrace[i];
    }
}

QStringList TestBacktraceGenerator::generateSymbols(BacktraceRaw *btrace) // remove or move somewhere else later?
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

QStringList TestBacktraceGenerator::generateAllSymbols(BacktraceRaw *btrace)
{
    QStringList backtrace;
    char** symbols = backtrace_symbols(btrace->bufferBacktrace,
                                       btrace->afterLastPos);
    for (int i = 0; i < btrace->afterLastPos; i++)
        backtrace.append(symbols[i]);
    free(symbols);
    QStringList backtraceNoFilenames = removeFileName(backtrace);
    return backtraceNoFilenames;
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
