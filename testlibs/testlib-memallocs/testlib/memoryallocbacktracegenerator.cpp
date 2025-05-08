#include "memoryallocbacktracegenerator.h"
#include "memoryallocatorfunctionptrcache.h"

void MemoryAllocBacktraceGenerator::createBacktraceRaw(BacktraceRaw *btrace,
                                                       MemoryAllocatorFunctionPtrCache *allocFuncPtrCache)
{
    int backtraceCount = backtrace(btrace->bufferBacktrace, maxStacktraceDepth);
    btrace->startPos = 1; // ignore myself
    btrace->afterLastPos = backtraceCount;
    alignStartPosition(btrace, allocFuncPtrCache);
}

void MemoryAllocBacktraceGenerator::alignStartPosition(BacktraceRaw *btrace,
                                                       MemoryAllocatorFunctionPtrCache* allocFuncPtrCache)
{
    if (allocFuncPtrCache == nullptr)
        return;
    MemoryAllocatorFunctionPtrCache::AllocFunctionPointerList allocFuncs = allocFuncPtrCache->getCachedFunctions();
    for (int pointerPos = btrace->startPos; pointerPos < btrace->afterLastPos-1; ++pointerPos) {
        const void* currPointer = btrace->bufferBacktrace[pointerPos];
        for (int allocFuncPos = 0; allocFuncPos < allocFuncs.count(); allocFuncPos++) {
            if (currPointer == allocFuncs[allocFuncPos].m_funcPointer) {
                btrace->startPos = pointerPos+1;
                if(allocFuncs[allocFuncPos].m_secondary)
                    return;
            }
        }
    }
}

QStringList MemoryAllocBacktraceGenerator::generateSymbols(const BacktraceRaw *btrace) // remove or move somewhere else later?
{
    QStringList backtrace;
    // we need to fetch full backtrace otherwise 1st has missing symbol
    char** symbols = backtrace_symbols(btrace->bufferBacktrace,
                                       btrace->afterLastPos);
    for (int i = btrace->startPos; i < btrace->afterLastPos; i++)
        backtrace.append(symbols[i]);
    free(symbols);
    return backtrace;
    /*QStringList backtraceNoFilenames = removeFileName(backtrace);
    return backtraceNoFilenames;*/
}

QStringList MemoryAllocBacktraceGenerator::removeFileName(const QStringList &backtrace)
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
