#include "testloghelpers.h"
#include <QJsonDocument>

bool TestLogHelpers::compareAndLogOnDiff(QString expected, QString dumped)
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

QByteArray TestLogHelpers::dump(QJsonObject json)
{
    QJsonDocument doc(json);
    return doc.toJson(QJsonDocument::Indented);
}
