#ifndef TEST_MEMALLOCS_ATOMIC_H
#define TEST_MEMALLOCS_ATOMIC_H

#include <QObject>

class test_memallocs_atomic : public QObject
{
    Q_OBJECT
private slots:
    void mallocAndFree();
    void tripleMallocAndFree();
    void newAndDelete();
    void makeSharedAndReset();
    void makeUniqueAndReset();
    void heapNone();
    void mallocInLoop();
    void reallocAndFree();
    void mallocReallocAndFree();
    void mallocFreeByRealloc();
};

#endif // TEST_MEMALLOCS_ATOMIC_H
