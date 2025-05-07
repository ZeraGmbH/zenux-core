#ifndef TEST_MEMALLOCS_ATOMIC_H
#define TEST_MEMALLOCS_ATOMIC_H

#include <QObject>

class test_memallocs_atomic : public QObject
{
    Q_OBJECT
private slots:
    void mallocAndFree();
    void mallocTwiceAndFree();
    void newAndDelete();
    void makeSharedAndReset();
    void makeUniqueAndReset();
    void heapNone();
};

#endif // TEST_MEMALLOCS_ATOMIC_H
