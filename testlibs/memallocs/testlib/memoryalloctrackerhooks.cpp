#include "memoryalloctracker.h"
#include <QMutexLocker>
#include <atomic>
#include <stdlib.h>
#include <stddef.h>
#include <dlfcn.h>

static std::atomic_bool ignoreMallocFreess;
static QMutex mutex;
static MemoryAllocTracker* currentTracker;

void setTracker(MemoryAllocTracker* tracker) {
    QMutexLocker locker(&mutex);
    currentTracker = tracker;
}

void startIgnoreMallocFrees() {
    ignoreMallocFreess.store(true);
}
void stopIgnoreMallocFrees() {
    ignoreMallocFreess.store(false);
}

extern "C" void *malloc(size_t size) {
    typedef void *(*malloc_ptr)(size_t size);
    static malloc_ptr real_func = nullptr;

    if (ignoreMallocFreess.load())
        return real_func(size);

    QMutexLocker locker(&mutex);

    if (!real_func)
        real_func = reinterpret_cast<malloc_ptr>(dlsym(RTLD_NEXT, "malloc"));

    void *mem = real_func(size);
    if (currentTracker)
        currentTracker->handleMalloc(size, mem);
    return mem;
}

extern "C" void free(void *ptr) {
    typedef void (*free_ptr)(void *ptr);
    static free_ptr real_func = nullptr;

    if (ignoreMallocFreess.load()) {
        real_func(ptr);
        return;
    }

    QMutexLocker locker(&mutex);

    if (!real_func)
        real_func = reinterpret_cast<free_ptr>(dlsym(RTLD_NEXT, "free"));

    if (currentTracker)
        currentTracker->handleFree(ptr);

    real_func(ptr);
}

extern "C" void *realloc(void *ptr, size_t size) {
    typedef void *(*realloc_ptr)(void *ptr, size_t size);
    static realloc_ptr real_func = nullptr;

    if (ignoreMallocFreess.load())
        return real_func(ptr, size);

    QMutexLocker locker(&mutex);

    if (!real_func)
        real_func = reinterpret_cast<realloc_ptr>(dlsym(RTLD_NEXT, "realloc"));

    void *mem = real_func(ptr, size);
    if (currentTracker) {
        currentTracker->handleFree(ptr);
        currentTracker->handleMalloc(size, mem);
    }
    return mem;
}
