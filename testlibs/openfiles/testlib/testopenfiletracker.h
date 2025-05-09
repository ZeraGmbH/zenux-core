#ifndef TESTOPENFILETRACKER_H
#define TESTOPENFILETRACKER_H

#include <QString>
#include <QHash>
#include <QMap>

/* Usage:
Add in your CMake
    target_link_libraries(${_testname}
        PUBLIC
        -Wl,--whole-archive
        Zera::testlib-openfiles
        -Wl,--no-whole-archive
        ...

Important:
* Test on OE crash qemu!!!
* Zera::testlib-openfiles must be linked first!

Example usage found in test_openfiletracker
*/

class TestOpenFileTracker
{
public:
    TestOpenFileTracker();
    virtual ~TestOpenFileTracker();
    QHash<QString, int> getOpenFiles();
    QMap<QString, int> getOpenFilesTotal();
    void clearAll();

    void onHandleOpenFile(const QString &path, int fd);
    void onHandleCloseFile(int fd);
private:
    QHash<QString, int> m_openFilesCount;
    QHash<int, QString> m_openFilesByFileDescriptor;
    QMap<QString, int> m_openFilesCountTotal;
};

#endif // TESTOPENFILETRACKER_H
