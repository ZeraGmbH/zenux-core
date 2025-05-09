#include "test_openfiletracker_atomic.h"
#include "testopenfiletracker.h"
#include "openfiletrackertestdefaults.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <QTest>

QTEST_MAIN(test_openfiletracker_atomic)

static const char* fileName = "/tmp/test_openfiletracker_atomic";
static int fileCreationFlags = O_CREAT | O_WRONLY | O_TRUNC;
static constexpr mode_t filePrivileges = S_IRUSR | S_IWUSR;

void test_openfiletracker_atomic::initTestCase()
{
    SKIP_TESTS_ON_RELEASE_BUILD
}

void test_openfiletracker_atomic::cleanup()
{
    QFile file(fileName);
    file.remove();
}

void test_openfiletracker_atomic::openAndClose()
{
    TestOpenFileTracker tracker;
    int fd = ::open(fileName,
                    fileCreationFlags,
                    filePrivileges);
    QVERIFY(fd >= 0);

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName], 1);

    ::close(fd);
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);

    struct stat fileStatus;
    QVERIFY(::stat(fileName, &fileStatus) == 0);
    QVERIFY(checkPrivileges(filePrivileges, fileStatus.st_mode));
}

void test_openfiletracker_atomic::openNoModeAndClose()
{
    TestOpenFileTracker tracker;
    // we need a file
    int fd = ::open(fileName,
                    fileCreationFlags,
                    filePrivileges);
    QVERIFY(fd >= 0);
    ::close(fd);

    // no mode param not allowed on O_CREAT / O_TMPFILE
    // otherwise anything can happen...
    fd = ::open(fileName,
                O_RDONLY);
    QVERIFY(fd >= 0);

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName], 1);

    ::close(fd);
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);
}

void test_openfiletracker_atomic::open64AndClose()
{
    TestOpenFileTracker tracker;
    int fd = ::open64(fileName,
                      fileCreationFlags,
                      filePrivileges);
    QVERIFY(fd >= 0);

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName], 1);

    ::close(fd);
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);

    struct stat fileStatus;
    QVERIFY(::stat(fileName, &fileStatus) == 0);
    QVERIFY(checkPrivileges(filePrivileges, fileStatus.st_mode));
}

void test_openfiletracker_atomic::open64NoModeAndClose()
{
    TestOpenFileTracker tracker;
    // we need a file
    int fd = ::open64(fileName,
                      fileCreationFlags,
                      filePrivileges);
    QVERIFY(fd >= 0);
    ::close(fd);

    // no mode param not allowed on O_CREAT / O_TMPFILE
    // otherwise anything can happen...
    fd = ::open64(fileName,
                  O_RDONLY);
    QVERIFY(fd >= 0);

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName], 1);

    ::close(fd);
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);
}

void test_openfiletracker_atomic::fopenAndFClose()
{
    TestOpenFileTracker tracker;
    FILE* file = ::fopen(fileName, "w");
    QVERIFY(file != nullptr);

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName], 1);

    ::fclose(file);
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);
}

void test_openfiletracker_atomic::fopen64AndFClose()
{
    TestOpenFileTracker tracker;
    FILE* file = ::fopen64(fileName, "w");
    QVERIFY(file != nullptr);

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName], 1);

    ::fclose(file);
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);
}

void test_openfiletracker_atomic::creatAndClose()
{
    TestOpenFileTracker tracker;
    int fd = ::creat(fileName,
                     filePrivileges);
    QVERIFY(fd >= 0);

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName], 1);

    ::close(fd);
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);

    struct stat fileStatus;
    QVERIFY(::stat(fileName, &fileStatus) == 0);
    QVERIFY(checkPrivileges(filePrivileges, fileStatus.st_mode));
}

void test_openfiletracker_atomic::openatAndClose()
{
    TestOpenFileTracker tracker;
    int fd = ::openat(0,
                      fileName,
                      fileCreationFlags,
                      filePrivileges);
    QVERIFY(fd >= 0);

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName], 1);

    ::close(fd);
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);

    struct stat fileStatus;
    QVERIFY(::stat(fileName, &fileStatus) == 0);
    QVERIFY(checkPrivileges(filePrivileges, fileStatus.st_mode));
}

void test_openfiletracker_atomic::openatNoModeAndClose()
{
    TestOpenFileTracker tracker;
    // we need a file
    int fd = ::openat(0,
                      fileName,
                      fileCreationFlags,
                      filePrivileges);
    QVERIFY(fd >= 0);
    ::close(fd);

    // no mode param not allowed on O_CREAT / O_TMPFILE
    // otherwise anything can happen...
    fd = ::openat(0,
                  fileName,
                  O_RDONLY);
    QVERIFY(fd >= 0);

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName], 1);

    ::close(fd);
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);
}

bool test_openfiletracker_atomic::checkPrivileges(mode_t expected, mode_t found)
{
    mode_t expectedRegularFile = expected | S_IFREG;
    if (expectedRegularFile  == found)
        return true;
    qInfo("Expected 0x%04X / Found 0x%04X", expectedRegularFile, found);
    return false;
}
