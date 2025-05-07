#include "testopenfiletracker.h"

TestOpenFileTracker* m_trackerInstance = nullptr;

// C-interface
extern "C" void handleOpenFile(const char *path, int fd) {
    if (m_trackerInstance && fd >= 0)
        m_trackerInstance->onHandleOpenFile(path, fd);
}
extern "C" void handleFOpenFile(const char *path, FILE *stream) {
    if (stream) {
        int fd = fileno(stream);
        handleOpenFile(path, fd);
    }
}
extern "C" void handleCloseFile(int ret, int fd) {
    if (m_trackerInstance && ret == 0)
        m_trackerInstance->onHandleCloseFile(fd);
}


TestOpenFileTracker::TestOpenFileTracker()
{
    m_trackerInstance = this;
}

TestOpenFileTracker::~TestOpenFileTracker()
{
    m_trackerInstance = nullptr;
}

QHash<QString, int> TestOpenFileTracker::getOpenFiles()
{
    const QHash<QString, int> ret = m_openFilesCount;
    return ret;
}

QMap<QString, int> TestOpenFileTracker::getOpenFilesTotal()
{
    const QMap<QString, int> ret = m_openFilesCountTotal;
    return ret;
}

void TestOpenFileTracker::clearAll()
{
    m_openFilesCount.clear();
    m_openFilesByFileDescriptor.clear();
    m_openFilesCountTotal.clear();
}

void TestOpenFileTracker::onHandleOpenFile(const QString &path, int fd)
{
    m_openFilesCount[path]++;
    m_openFilesCountTotal[path]++;
    m_openFilesByFileDescriptor[fd] = path;
}

void TestOpenFileTracker::onHandleCloseFile(int fd)
{
    if (m_openFilesByFileDescriptor.contains(fd)) {
        const QString path = m_openFilesByFileDescriptor[fd];
        if (m_openFilesCount.contains(path)) {
            m_openFilesCount[path]--;
            if (m_openFilesCount[path] <= 0)
                m_openFilesCount.remove(path);
        }
        m_openFilesByFileDescriptor.remove(fd);
    }
    /*else
        qWarning("Trying to close a handle that was not tracked on open");*/
}
