#include "test_safe_file_loader.h"
#include "safefileloader.h"
#include "safefileloadenvironmentgenerator.h"
#include "timerfactoryqtfortest.h"
#include <QTest>

QTEST_MAIN(test_safe_file_loader)

void test_safe_file_loader::initTestCase()
{
    qputenv("QT_FATAL_CRITICALS", "1");
    TimerFactoryQtForTest::enableTest();

    SafeFileLoadEnvironmentGenerator::createTestFileStructure();
}

void test_safe_file_loader::cleanupTestCase()
{
    SafeFileLoadEnvironmentGenerator::cleanup();
}

void test_safe_file_loader::readSimpleFile()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 SafeFileLoadEnvironmentGenerator::getSimpleTextFileName(),
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::Ok);
    QCOMPARE(readData, SafeFileLoadEnvironmentGenerator::getSimpleTextFileContent());
}

void test_safe_file_loader::readFileInSubdirectory()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 SafeFileLoadEnvironmentGenerator::getSubDirFileName(),
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::Ok);
    QCOMPARE(readData, SafeFileLoadEnvironmentGenerator::getSubdirFileContent());
}

void test_safe_file_loader::rejectPathReleativeDot()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 "./foo.txt",
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::InvalidFilePath);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::rejectPathReleativeDotDot()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 "../foo.txt",
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::InvalidFilePath);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::rejectAbsoluteFilePaths()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 "/etc/passwd",
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::InvalidFilePath);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::rejectSymlinkEscapingBaseDirectory()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 SafeFileLoadEnvironmentGenerator::getLinkOutsideFileName(),
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::InvalidFilePath);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::allowSymlinkInsideBaseDirectory()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 SafeFileLoadEnvironmentGenerator::getLinkInsideFileName(),
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::Ok);
    QCOMPARE(readData, SafeFileLoadEnvironmentGenerator::getSubdirFileContent());
}

void test_safe_file_loader::rejectBrokenSymlink()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 SafeFileLoadEnvironmentGenerator::getBrokenLinkFileName(),
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::FileNotFound);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::rejectInteriorTraversal()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 "subdir/../../outside.txt",
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::InvalidFilePath);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::rejectHardLinkEscapingBaseDirectory()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 SafeFileLoadEnvironmentGenerator::getHardLinkOutsideFileName(),
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::HardLinkDetected);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::rejectWrongFileName()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 "does-not-exist.txt",
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::FileNotFound);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::rejectSubdirectorySelected()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 SafeFileLoadEnvironmentGenerator::getSubDirName(),
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::NotARegularFile);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::rejectEmptyFileName()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 "",
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::InvalidFilePath);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::readAllowedLengthFile()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 SafeFileLoadEnvironmentGenerator::getBigFileName(),
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::Ok);
    QCOMPARE(readData.size(), SafeFileLoader::getDefaultMaxFileSize());
}

void test_safe_file_loader::rejectFileTooLarge()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 SafeFileLoadEnvironmentGenerator::getTooBigFileName(),
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath());
    QCOMPARE(result, SafeFileLoader::FileTooLarge);
    QCOMPARE(readData, "");
}

void test_safe_file_loader::rejectFileTooLargeParam()
{
    QByteArray readData;
    SafeFileLoader::LoadResult result = SafeFileLoader::readFile(readData,
                                                                 SafeFileLoadEnvironmentGenerator::getBigFileName(),
                                                                 SafeFileLoadEnvironmentGenerator::getInsidePath(),
                                                                 SafeFileLoader::getDefaultMaxFileSize()-1);
    QCOMPARE(result, SafeFileLoader::FileTooLarge);
    QCOMPARE(readData, "");
}
