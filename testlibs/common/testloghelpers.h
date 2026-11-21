#ifndef TESTLOGHELPERS_H
#define TESTLOGHELPERS_H

#include <QByteArray>
#include <QString>
#include <QJsonObject>

class TestLogHelpers
{
public:
    // OE environment is very special => detect it
    static bool runsInOeEnvironment();

    // Just compare
    static bool compareAndLogOnDiff(const QString &expected, const QString &dumped);
    static bool compareAndLogOnDiffJson(const QString &expected, const QString &dumped);

    // Compare / in case of error store dumped contents to /tmp/<test-name>/<fileNameExpected>
    static bool compareAndLogOnDiffFile(const QString &fileNameExpected, const QString &dumped);
    static bool compareAndLogOnDiffJsonFile(const QString &fileNameExpected, const QString &dumped);

    // Compare / expand fileNameExpected to <test-source-dir/test-data/fileNameExpected
    // in case of error store dumped contents to
    // * On local build expanded file name => files in source tree are overwritten
    //   Important: After red tests 'git diff' is your friend to decide if change is a regression or intended
    // * On OE build: /tmp/<test-name>/<fileNameExpected>
    static bool compareAndLogOnDiffSrc(const QString &fileNameExpected, const QString &dumped, const QString &sourceFileName);
    static bool compareAndLogOnDiffJsonSrc(const QString &fileNameExpected, const QString &dumped, const QString &sourceFileName);

    static QString getDumpStoreTmpFilePath(const QString &fileNameExpected);
    static QString getDumpStoreSrcFilePath(const QString &fileNameExpected, const QString &sourceCodeDir);

    static QByteArray dump(const QJsonObject &json);
    static QByteArray loadFile(const QString &fileName);
    static bool writeFile(const QString &fileName, const QByteArray &data);
    static bool copyFile(const QString &sourceFileName, const QString &targetFileName);

    static QString removeResourceLeadFromPath(const QString &resourceFilePath);
};

#endif // TESTLOGHELPERS_H
