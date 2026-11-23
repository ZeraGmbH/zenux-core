#ifndef TESTLOGHELPERS_H
#define TESTLOGHELPERS_H

#include <QByteArray>
#include <QString>
#include <QJsonObject>

class TestLogHelpers
{
public:
    // Just compare
    static bool compareAndLogOnDiff(const QString &expected, const QString &dumped);
    static bool compareAndLogOnDiffJson(const QString &expected, const QString &dumped);

    // * In case of failure source dump files are overwritten and 'git diff' is your friend
    // * On OE builds change into source directory first e.g.
    //   <your-oe-tmp>/oe-zenux/tmp-glibc/work/cortexa9t2hf-neon-imx-mortsgna-linux-gnueabi/zenux-services/2.0.0+gitAUTOINC+<commit>-r0
    //   and check with 'git diff' there
    static bool compareAndLogOnDiffSrc(const QString &fileNameExpected, const QString &dumped, const QString &sourceFileName);
    static bool compareAndLogOnDiffJsonSrc(const QString &fileNameExpected, const QString &dumped, const QString &sourceFileName);

    static QString getDumpStoreSrcFilePath(const QString &fileNameExpected, const QString &sourceCodeDir);

    static QByteArray dump(const QJsonObject &json);
    static QByteArray loadFile(const QString &fileName);
    static bool writeFile(const QString &fileName, const QByteArray &data);
    static bool copyFile(const QString &sourceFileName, const QString &targetFileName);

    static QString removeResourceLeadFromPath(const QString &resourceFilePath);
};

#endif // TESTLOGHELPERS_H
