#include "test_memory_alloc_pointer_cache.h"
#include "memoryallocatorfunctionptrcache.h"
#include <QTest>
#include <execinfo.h>

QTEST_MAIN(test_memory_alloc_pointer_cache)

static const MemoryAllocatorFunctionPtrCache::AllocFunctionPointer *findAllocFunc(
    const MemoryAllocatorFunctionPtrCache::AllocFunctionPointerList &cachedFuncs,
    const QString &allocFuncTag)
{
    QStringList funcStrings;
    for (int i=0; i<cachedFuncs.count(); i++) {
        void *funcPointers[1];
        funcPointers[0] = cachedFuncs[i].m_funcPointer;
        char** symbols = backtrace_symbols(funcPointers, 1);

        QString funcName = symbols[0];
        free(symbols);
        funcStrings.append(funcName);
    }
    for (int i=0; i<funcStrings.count(); i++) {
        const QString &entry = funcStrings[i];
        if (entry.contains(allocFuncTag))
            return &cachedFuncs[i];
    }

    qWarning("%s", qPrintable(funcStrings.join("\n")));
    return nullptr;
}


void test_memory_alloc_pointer_cache::findMalloc()
{
    MemoryAllocatorFunctionPtrCache cache;
    const MemoryAllocatorFunctionPtrCache::AllocFunctionPointer *allocFuncPointer =
        findAllocFunc(cache.getCachedFunctions(), "(malloc+");
    QVERIFY(allocFuncPointer != nullptr);
    QCOMPARE(allocFuncPointer->m_secondary, false);
}

void test_memory_alloc_pointer_cache::findNew()
{
    MemoryAllocatorFunctionPtrCache cache;
    // backtrace_symbols does not work nicely with new()
    QCOMPARE(cache.getCachedFunctions().count(), 4);
}

void test_memory_alloc_pointer_cache::findMakeUnique()
{
    MemoryAllocatorFunctionPtrCache cache;
    const MemoryAllocatorFunctionPtrCache::AllocFunctionPointer *allocFuncPointer =
        findAllocFunc(cache.getCachedFunctions(), "make_unique");
    QVERIFY(allocFuncPointer != nullptr);
    QCOMPARE(allocFuncPointer->m_secondary, true);
}

void test_memory_alloc_pointer_cache::findMakeShared()
{
    MemoryAllocatorFunctionPtrCache cache;
    const MemoryAllocatorFunctionPtrCache::AllocFunctionPointer *allocFuncPointer =
        findAllocFunc(cache.getCachedFunctions(), "make_shared");
    QVERIFY(allocFuncPointer != nullptr);
    QCOMPARE(allocFuncPointer->m_secondary, true);
}
