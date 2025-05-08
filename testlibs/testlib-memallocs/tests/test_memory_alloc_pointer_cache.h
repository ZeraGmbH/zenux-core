#ifndef TEST_MEMORY_ALLOC_POINTER_CACHE_H
#define TEST_MEMORY_ALLOC_POINTER_CACHE_H

#include <QObject>

class test_memory_alloc_pointer_cache : public QObject
{
    Q_OBJECT
private slots:
    void findMalloc();
    void findNew();
    void findMakeUnique();
    void findMakeShared();
};

#endif // TEST_MEMORY_ALLOC_POINTER_CACHE_H
