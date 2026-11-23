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

    // Compare / expand fileNameExpected to <test-source-dir/test-data/fileNameExpected
    // In case of error store dumped contents to expanded file name => files in source tree are overwritten
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
