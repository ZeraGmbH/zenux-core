#ifndef TESTMEMALLOCTRACKER_H
#define TESTMEMALLOCTRACKER_H

#include <stddef.h>

class TestMemAllocTracker
{
public:
    TestMemAllocTracker();
    virtual ~TestMemAllocTracker();

    int getAllocCount() const;

    void handleMalloc(size_t size, void* mem);
    void handleFree(void* mem);

private:
    int m_allocCount = 0;
};

void setTracker(TestMemAllocTracker* tracker);

#endif // TESTMEMALLOCTRACKER_H
