#include "testloghelpers.h"
#include <QJsonDocument>
#include <QFile>
#include <QFileInfo>
#include <QDir>

bool TestLogHelpers::compareAndLogOnDiff(const QString &expected, const QString &dumped)
{
    QString expectedCompare = expected;
    expectedCompare.replace("\n", "");
    QString dumpedCompare = dumped;
    dumpedCompare.replace("\n", "");
    if(expectedCompare != dumpedCompare) {
        qWarning("Expected:");
        qInfo("%s", qPrintable(expected));
        qWarning("Dumped:");
        qInfo("%s", qPrintable(dumped));
        return false;
    }
    return true;
}

bool TestLogHelpers::compareAndLogOnDiffJson(const QString &expected, const QString &dumped)
{
    QJsonParseError expectedParseError;
    QJsonDocument::fromJson(expected.toUtf8(), &expectedParseError);
    QJsonParseError dumpedParseError;
    QJsonDocument::fromJson(dumped.toUtf8(), &dumpedParseError);

    bool expectedIsJson = expectedParseError.error == QJsonParseError::NoError;
    if (!expectedIsJson) {
        qWarning("Expected ist not valid JSON: %s", qPrintable(expectedParseError.errorString()));
        qInfo("%s", qPrintable(expected));
    }
    bool dumpedIsJson = dumpedParseError.error == QJsonParseError::NoError;
    if (!dumpedIsJson) {
        qWarning("Dumped ist not valid JSON: %s", qPrintable(dumpedParseError.errorString()));
        qInfo("%s", qPrintable(dumped));
    }
    bool dumpDiffOK = compareAndLogOnDiff(expected, dumped);

    return expectedIsJson && dumpedIsJson && dumpDiffOK;
}

QByteArray TestLogHelpers::dump(const QJsonObject &json)
{
    QJsonDocument doc(json);
    return doc.toJson(QJsonDocument::Indented);
}

QByteArray TestLogHelpers::loadFile(const QString &fileName)
{
    QByteArray fileData;
    QFile file(fileName);
    if(file.open(QFile::ReadOnly)) {
        fileData = file.readAll();
        file.close();
    }
    return fileData;
}

bool TestLogHelpers::writeFile(const QString &fileName, const QByteArray &data)
{
    const QString dirPath = QFileInfo(fileName).absolutePath();
    QDir dir;
    if (!dir.mkpath(dirPath))
        return false;

    QFile file(fileName);
    if(file.open(QFile::WriteOnly))
        return !data.isEmpty() && file.write(data) == data.length();
    return false;
}
