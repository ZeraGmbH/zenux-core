#include "memoryallocatorfunctionptrcache.h"
#include "memoryalloctracker.h"
#include <execinfo.h>
#include <memory>

MemoryAllocatorFunctionPtrCache::MemoryAllocatorFunctionPtrCache()
{
    cacheMalloc();
    cacheNew();
    cacheMakeUnique();
    cacheMakeShared();
}

MemoryAllocatorFunctionPtrCache::AllocFunctionPointerList MemoryAllocatorFunctionPtrCache::getCachedFunctions() const
{
    return m_cachedFuncPointers;
}

void MemoryAllocatorFunctionPtrCache::cacheMalloc()
{
    MemoryAllocTracker tmpTracker;
    tmpTracker.start();
    char *mem = reinterpret_cast<char*>(malloc(100));
    if (mem)
        strcpy(mem, "Avoid optimize out");
    tmpTracker.stop();
    free(mem);

    addAllocPointer(__FUNCTION__, tmpTracker.getRawMemRegions(), false);
}

void MemoryAllocatorFunctionPtrCache::cacheNew()
{
    MemoryAllocTracker tmpTracker;
    tmpTracker.start();
    QString *string = new QString;
    tmpTracker.stop();
    delete string;

    addAllocPointer(__FUNCTION__, tmpTracker.getRawMemRegions(), true);
}

void MemoryAllocatorFunctionPtrCache::cacheMakeUnique()
{
    MemoryAllocTracker tmpTracker;
    tmpTracker.start();
    std::unique_ptr<QString> string = std::make_unique<QString>();
    tmpTracker.stop();

    addAllocPointer(__FUNCTION__, tmpTracker.getRawMemRegions(), true);
}

void MemoryAllocatorFunctionPtrCache::cacheMakeShared()
{
    MemoryAllocTracker tmpTracker;
    tmpTracker.start();
    std::shared_ptr<QString> string = std::make_shared<QString>();
    tmpTracker.stop();

    addAllocPointer(__FUNCTION__, tmpTracker.getRawMemRegions(), true);
}

void MemoryAllocatorFunctionPtrCache::addAllocPointer(const QString &detectFunctionName,
                                                      const MemoryChunksAllocated &mems,
                                                      bool secondaryAllocFunction)
{
    const BacktraceRaw *backTrace = &mems[0].m_backTrace;
    QStringList symbols = generateAllSymbols(backTrace);
    for (int i=0; i<symbols.size()-1; i++)
        if (symbols[i].contains(detectFunctionName)) {
            m_cachedFuncPointers.append( { secondaryAllocFunction, backTrace->bufferBacktrace[i-1]});
            return;
        }
}

QStringList MemoryAllocatorFunctionPtrCache::generateAllSymbols(const BacktraceRaw *btrace)
{
    QStringList backtrace;
    char** symbols = backtrace_symbols(btrace->bufferBacktrace,
                                       btrace->afterLastPos);
    for (int i = 0; i < btrace->afterLastPos; i++)
        backtrace.append(symbols[i]);
    free(symbols);
    return backtrace;
}
