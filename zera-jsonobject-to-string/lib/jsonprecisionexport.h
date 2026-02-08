#ifndef JSONPRECISIONEXPORT_H
#define JSONPRECISIONEXPORT_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class JsonPrecisionExport
{
public:
    static QString objectToString(const QJsonObject &object,
                                  int tabSize=2, int floatPrecision=8,
                                  int nestedCount = 0);
    static QString arrayToString(const QJsonArray &array,
                                 int tabSize=2, int floatPrecision=8,
                                 int nestedCount = 0);
    static QString valueToString(const QJsonValue &value, int tabSize=2, int floatPrecision=8,
                                 int nestedCount = 0);

private:
    static QString newLine(int tabSize);
    static QString postColonSpace(int tabSize);
    static QString indentation(int nestedCount);
    static QString comma(int &elementCountLeft);
};

#endif // JSONPRECISIONEXPORT_H
