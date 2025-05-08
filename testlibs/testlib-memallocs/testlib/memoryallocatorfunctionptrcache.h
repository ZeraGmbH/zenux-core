#ifndef MEMORYALLOCATORFUNCTIONPTRCACHE_H
#define MEMORYALLOCATORFUNCTIONPTRCACHE_H

#include "memoryallocbacktraceraw.h"
#include <QString>

class MemoryAllocatorFunctionPtrCache
{
public:
    MemoryAllocatorFunctionPtrCache();
    struct AllocFunctionPointer {
        bool m_secondary = false;
        void *m_funcPointer;
    };
    typedef QList<AllocFunctionPointer> AllocFunctionPointerList;
    AllocFunctionPointerList getCachedFunctions() const;
private:
    void cacheMalloc();
    void cacheNew();
    void cacheMakeUnique();
    void cacheMakeShared();
    void addAllocPointer(const QString &detectFunctionName,
                         const MemoryChunksAllocated &mems,
                         bool secondaryAllocFunction);
    static QStringList generateAllSymbols(const BacktraceRaw *btrace);

    AllocFunctionPointerList m_cachedFuncPointers;
};

#endif // MEMORYALLOCATORFUNCTIONPTRCACHE_H
