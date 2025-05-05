#include "testmemalloctracker.h"
#include <QMutexLocker>
#include <stdlib.h>
#include <stddef.h>
#include <dlfcn.h>

static QMutex mutex;
static TestMemAllocTracker* currentTracker;

void setTracker(TestMemAllocTracker* tracker) {
    QMutexLocker locker(&mutex);
    currentTracker = tracker;
}

extern "C" void *malloc(size_t size) {
    QMutexLocker locker(&mutex);

    typedef void *(*malloc_ptr)(size_t size);
    static malloc_ptr real_func = nullptr;
    if (!real_func)
        real_func = reinterpret_cast<malloc_ptr>(dlsym(RTLD_NEXT, "malloc"));

    void *mem = real_func(size);
    if (currentTracker)
        currentTracker->handleMalloc(size, mem);
    return mem;
}

extern "C" void free(void *ptr) {
    QMutexLocker locker(&mutex);

    typedef void (*free_ptr)(void *ptr);
    static free_ptr real_func = nullptr;
    if (!real_func)
        real_func = reinterpret_cast<free_ptr>(dlsym(RTLD_NEXT, "free"));

    real_func(ptr);

    if (currentTracker)
        currentTracker->handleFree(ptr);
}
