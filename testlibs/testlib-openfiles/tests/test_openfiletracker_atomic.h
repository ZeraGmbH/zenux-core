#ifndef TEST_OPENFILETRACKER_ATOMIC_H
#define TEST_OPENFILETRACKER_ATOMIC_H

#include <QObject>
#include <sys/stat.h>

class test_openfiletracker_atomic : public QObject
{
    Q_OBJECT
private slots:
    void cleanup();

    void openAndClose();
    void openNoModeAndClose();
    void open64AndClose();
    void open64NoModeAndClose();
    void fopenAndFClose();
    void fopen64AndFClose();
    void creatAndClose();
    void openatAndClose();
    void openatNoModeAndClose();

private:
    bool checkPrivileges(mode_t expected, mode_t found);
};

#endif // TEST_OPENFILETRACKER_ATOMIC_H
