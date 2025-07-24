#ifndef TESTLOGHELPERS_H
#define TESTLOGHELPERS_H

#include <QByteArray>
#include <QString>
#include <QJsonObject>

class TestLogHelpers
{
public:
    static bool compareAndLogOnDiff(QString expected, QString dumped);
    static bool compareAndLogOnDiffJson(QString expected, QString dumped);
    static QByteArray dump(QJsonObject json);
    static QByteArray loadFile(QString fileName);
};

#endif // TESTLOGHELPERS_H
