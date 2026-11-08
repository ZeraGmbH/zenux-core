#include "safefileloadenvironmentgenerator.h"
#include "safefileloader.h"
#include <testloghelpers.h>
#include <QDir>
#include <QTest>
#include <unistd.h>

void SafeFileLoadEnvironmentGenerator::createTestFileStructure()
{
    cleanup();
    QVERIFY(TestLogHelpers::writeFile(getSimpleTextFilePath(), "hello world\n"));
    QVERIFY(TestLogHelpers::writeFile(getSubdirFilePath(), getSubdirFileContent().toUtf8()));

    QFile bigFile(getBigFilePath());
    QVERIFY(bigFile.open(QIODevice::WriteOnly));
    bigFile.write(QByteArray(SafeFileLoader::getDefaultMaxFileSize(), 'A'));
    bigFile.close();

    QFile tooBigFile(getTooBigFilePath());
    QVERIFY(tooBigFile.open(QIODevice::WriteOnly));
    tooBigFile.write(QByteArray(SafeFileLoader::getDefaultMaxFileSize()+1, 'A'));
    tooBigFile.close();

    QVERIFY(TestLogHelpers::writeFile(getInsidePath() + "/" + getOutsideRelFilePath(), "outside content\n"));
    QVERIFY(QFile(getOutsideRelFilePath()).link(getLinkOutsidePath()));
    QVERIFY(QFile(getSubDirFileName()).link(getLinkInsidePath()));
    QVERIFY(QFile("missing-target").link(getBrokenLinkPath()));
    QVERIFY(::link(getOutsideFilePath().toLocal8Bit().constData(),
                   getHardLinkOutsidePath().toLocal8Bit().constData()) == 0);
}

void SafeFileLoadEnvironmentGenerator::cleanup()
{
    QDir dir(getRootPath());
    dir.removeRecursively();
}

QString SafeFileLoadEnvironmentGenerator::getRootPath()
{
    return "/tmp/" + QCoreApplication::instance()->applicationName();
}

QString SafeFileLoadEnvironmentGenerator::getInsidePath()
{
    return getRootPath() + "/inside";
}

QString SafeFileLoadEnvironmentGenerator::getOutsideFilePath()
{
    return getRootPath() + "/outside.txt";
}

QString SafeFileLoadEnvironmentGenerator::getSimpleTextFileName()
{
    return "hello.txt";
}

QString SafeFileLoadEnvironmentGenerator::getSimpleTextFilePath()
{
    return getInsidePath() + QDir::separator() + getSimpleTextFileName();
}

QString SafeFileLoadEnvironmentGenerator::getSimpleTextFileContent()
{
    return "hello world\n";
}

QString SafeFileLoadEnvironmentGenerator::getSubDirName()
{
    return "subdir";
}

QString SafeFileLoadEnvironmentGenerator::getSubDirFileName()
{
    return SafeFileLoadEnvironmentGenerator::getSubDirName() + QDir::separator() + "nested.txt";
}

QString SafeFileLoadEnvironmentGenerator::getSubdirFileContent()
{
    return "nested content\n";
}

QString SafeFileLoadEnvironmentGenerator::getBigFileName()
{
    return "big.bin";
}

QString SafeFileLoadEnvironmentGenerator::getBigFilePath()
{
    return getInsidePath() + QDir::separator() + getBigFileName();
}

QString SafeFileLoadEnvironmentGenerator::getTooBigFileName()
{
    return "too-big.bin";
}

QString SafeFileLoadEnvironmentGenerator::getTooBigFilePath()
{
    return getInsidePath() + QDir::separator() + getTooBigFileName();
}

QString SafeFileLoadEnvironmentGenerator::getOutsideRelFilePath()
{
    return "../outside.txt";
}

QString SafeFileLoadEnvironmentGenerator::getSubdirFilePath()
{
    return getInsidePath() + "/subdir/nested.txt";
}


QString SafeFileLoadEnvironmentGenerator::getLinkInsidePath()
{
    return getInsidePath()  + QDir::separator() + getLinkInsideFileName();
}

QString SafeFileLoadEnvironmentGenerator::getLinkInsideFileName()
{
    return "link-in";
}

QString SafeFileLoadEnvironmentGenerator::getLinkOutsidePath()
{
    return getInsidePath()  + QDir::separator() + getLinkOutsideFileName();
}

QString SafeFileLoadEnvironmentGenerator::getLinkOutsideFileName()
{
    return "link-out";
}

QString SafeFileLoadEnvironmentGenerator::getBrokenLinkFileName()
{
    return "broken-link";
}

QString SafeFileLoadEnvironmentGenerator::getBrokenLinkPath()
{
    return getInsidePath() + QDir::separator() + getBrokenLinkFileName();
}

QString SafeFileLoadEnvironmentGenerator::getHardLinkOutsideFileName()
{
    return "hardlink-out";
}

QString SafeFileLoadEnvironmentGenerator::getHardLinkOutsidePath()
{
    return getInsidePath() + QDir::separator() + getHardLinkOutsideFileName();
}
