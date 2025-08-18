#ifndef TESTLOGHELPERS_H
#define TESTLOGHELPERS_H

#include <QByteArray>
#include <QString>
#include <QJsonObject>

class TestLogHelpers
{
public:
    static bool compareAndLogOnDiff(const QString &expected, const QString &dumped);
    static bool compareAndLogOnDiffJson(const QString &expected, const QString &dumped);
    static QByteArray dump(const QJsonObject &json);
    static QByteArray loadFile(const QString &fileName);
};

#endif // TESTLOGHELPERS_H
