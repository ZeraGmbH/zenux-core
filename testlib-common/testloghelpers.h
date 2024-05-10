#ifndef TESTLOGHELPERS_H
#define TESTLOGHELPERS_H

#include <QByteArray>
#include <QString>
#include <QJsonObject>

class TestLogHelpers
{
public:
    static bool compareAndLogOnDiff(QString expected, QString dumped);
    static QByteArray dump(QJsonObject json);
};

#endif // TESTLOGHELPERS_H
