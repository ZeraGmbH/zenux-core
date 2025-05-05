#include "test_openfiletracker.h"
#include "testopenfiletracker.h"
#include "openfiletrackertestdefaults.h"
#include <QFile>
#include <QTest>

QTEST_MAIN(test_openfiletracker)

static const char* fileName1 = "/tmp/test_openfiletracker1";
static const char* fileName2 = "/tmp/test_openfiletracker2";

void test_openfiletracker::initTestCase()
{
    SKIP_TESTS_ON_RELEASE_BUILD
}

void test_openfiletracker::init()
{
    QFile file1(fileName1);
    file1.remove();
    QVERIFY(file1.open(QFile::WriteOnly));
    file1.write("foo");
    file1.close();

    QFile file2(fileName2);
    file2.remove();
    QVERIFY(file2.open(QFile::WriteOnly));
    file2.write("bar");
    file2.close();
}

void test_openfiletracker::cleanup()
{
    QFile file1(fileName1);
    file1.remove();

    QFile file2(fileName2);
    file2.remove();
}

void test_openfiletracker::openFileOnce()
{
    TestOpenFileTracker tracker;

    QFile file(fileName1);
    QVERIFY(file.open(QFile::ReadOnly));

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QVERIFY(openFiles.contains(fileName1));

    QMap<QString, int> openFilesTotal = tracker.getOpenFilesTotal();
    QCOMPARE(openFilesTotal.count(), 1);
    QVERIFY(openFilesTotal.contains(fileName1));

    file.close();
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);

    openFilesTotal = tracker.getOpenFilesTotal();
    QCOMPARE(openFilesTotal.count(), 1);
    QVERIFY(openFilesTotal.contains(fileName1));
}

void test_openfiletracker::openFileTwice()
{
    TestOpenFileTracker tracker;

    QFile file1(fileName1);
    QFile file2(fileName1);

    QVERIFY(file1.open(QFile::ReadOnly));
    QVERIFY(file2.open(QFile::ReadOnly));
    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName1], 2);

    file1.close();
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName1], 1);

    file2.close();
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);
    QMap<QString, int> openFilesTotal = tracker.getOpenFilesTotal();
    QCOMPARE(openFilesTotal.count(), 1);
    QCOMPARE(openFilesTotal[fileName1], 2);
}

void test_openfiletracker::openTwoFilesOnce()
{
    TestOpenFileTracker tracker;

    QFile file1(fileName1);
    QFile file2(fileName2);

    QVERIFY(file1.open(QFile::ReadOnly));
    QVERIFY(file2.open(QFile::ReadOnly));

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 2);
    QCOMPARE(openFiles[fileName1], 1);
    QCOMPARE(openFiles[fileName2], 1);

    QMap<QString, int> openFilesTotal = tracker.getOpenFilesTotal();
    QCOMPARE(openFilesTotal.count(), 2);
    QCOMPARE(openFilesTotal[fileName1], 1);
    QCOMPARE(openFilesTotal[fileName2], 1);

    file1.close();
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 1);
    QCOMPARE(openFiles[fileName2], 1);

    openFilesTotal = tracker.getOpenFilesTotal();
    QCOMPARE(openFilesTotal.count(), 2);
    QCOMPARE(openFilesTotal[fileName1], 1);
    QCOMPARE(openFilesTotal[fileName2], 1);

    file2.close();
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);

    openFilesTotal = tracker.getOpenFilesTotal();
    QCOMPARE(openFilesTotal.count(), 2);
    QCOMPARE(openFilesTotal[fileName1], 1);
    QCOMPARE(openFilesTotal[fileName2], 1);
}

void test_openfiletracker::openTwoFilesOnceClear()
{
    TestOpenFileTracker tracker;

    QFile file1(fileName1);
    QFile file2(fileName2);

    QVERIFY(file1.open(QFile::ReadOnly));
    QVERIFY(file2.open(QFile::ReadOnly));

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 2);
    QMap<QString, int> openFilesTotal = tracker.getOpenFilesTotal();
    QCOMPARE(openFilesTotal.count(), 2);

    tracker.clearAll();
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);
    openFilesTotal = tracker.getOpenFilesTotal();
    QCOMPARE(openFilesTotal.count(), 0);
}

void test_openfiletracker::openTwoFilesTwice()
{
    TestOpenFileTracker tracker;

    QFile file1_1(fileName1);
    QFile file1_2(fileName1);
    QFile file2_1(fileName2);
    QFile file2_2(fileName2);

    QVERIFY(file1_1.open(QFile::ReadOnly));
    QVERIFY(file1_2.open(QFile::ReadOnly));
    QVERIFY(file2_1.open(QFile::ReadOnly));
    QVERIFY(file2_2.open(QFile::ReadOnly));

    QHash<QString, int> openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 2);
    QCOMPARE(openFiles[fileName1], 2);
    QCOMPARE(openFiles[fileName2], 2);

    QMap<QString, int> openFilesTotal = tracker.getOpenFilesTotal();
    QCOMPARE(openFilesTotal.count(), 2);
    QCOMPARE(openFilesTotal[fileName1], 2);
    QCOMPARE(openFilesTotal[fileName2], 2);

    file1_1.close();
    file1_2.close();
    file2_1.close();
    file2_2.close();
    openFiles = tracker.getOpenFiles();
    QCOMPARE(openFiles.count(), 0);
    openFilesTotal = tracker.getOpenFilesTotal();
    QCOMPARE(openFilesTotal.count(), 2);
    QCOMPARE(openFilesTotal[fileName1], 2);
    QCOMPARE(openFilesTotal[fileName2], 2);
}
