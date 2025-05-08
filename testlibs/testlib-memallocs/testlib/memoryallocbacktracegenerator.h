#ifndef MEMORYALLOCBACKTRACEGENERATOR_H
#define MEMORYALLOCBACKTRACEGENERATOR_H

#include "memoryallocbacktraceraw.h"
#include "memoryallocatorfunctionptrcache.h"
#include <QStringList>
#include <execinfo.h>


class MemoryAllocBacktraceGenerator
{
public:
    static void createBacktraceRaw(BacktraceRaw *btrace,
                                   MemoryAllocatorFunctionPtrCache* allocFuncPtrCache);
    static QStringList generateSymbols(const BacktraceRaw *btrace);

private:
    static void alignStartPosition(BacktraceRaw *btrace,
                                   MemoryAllocatorFunctionPtrCache* allocFuncPtrCache);
    static QStringList removeFileName(const QStringList &backtrace);
};

#endif // MEMORYALLOCBACKTRACEGENERATOR_H
