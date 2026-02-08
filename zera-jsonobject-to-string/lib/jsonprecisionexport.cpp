#include "jsonprecisionexport.h"

QString JsonPrecisionExport::objectToString(const QJsonObject &object, int tabSize, int floatPrecision, int nestedCount)
{
    QString ret;
    ret += "{";
    ret += newLine(tabSize);
    int elementCountLeft = object.count();
    for (auto iter=object.constBegin(); iter!=object.constEnd(); ++iter) {
        ret += indentation((nestedCount+1) * tabSize);
        ret += "\"" + iter.key() + "\":" + postColonSpace(tabSize);
        ret += valueToString(iter.value(), tabSize, floatPrecision, nestedCount+1);
        ret += comma(elementCountLeft);
        ret += newLine(tabSize);
    }
    ret += indentation(nestedCount * tabSize) + "}";
    if(nestedCount == 0)
        ret += newLine(tabSize);
    return ret;
}

QString JsonPrecisionExport::arrayToString(const QJsonArray &array, int tabSize, int floatPrecision, int nestedCount)
{
    QString ret = "[";
    ret += newLine(tabSize);
    int elementCountLeft = array.count();
    for (const QJsonValue &value : array) {
        ret += indentation((nestedCount+1) * tabSize);
        ret += valueToString(value, tabSize, floatPrecision, nestedCount+1);
        ret += comma(elementCountLeft);
        ret += newLine(tabSize);
    }
    ret += indentation(nestedCount * tabSize) + "]";
    if(nestedCount == 0)
        ret += newLine(tabSize);
    return ret;
}

QString JsonPrecisionExport::valueToString(const QJsonValue &value, int tabSize, int floatPrecision, int nestedCount)
{
    switch(value.type()) {
    case QJsonValue::String:
        return QString("\"%1\"").arg(value.toString());
    case QJsonValue::Bool:
        return value.toBool() ? "true" : "false";
    case QJsonValue::Null:
        return "null";
    case QJsonValue::Double:
        return QString("%1").arg(value.toDouble(), 0, 'g', floatPrecision);
    case QJsonValue::Object:
        return objectToString(value.toObject(), tabSize, floatPrecision, nestedCount);
    case QJsonValue::Array:
        return arrayToString(value.toArray(), tabSize, floatPrecision, nestedCount);

    case QJsonValue::Undefined:
        break;
    }
    qCritical("JsonPrecisionExport::valueToString: Unhandled undefined value!");
    return "";
}

QString JsonPrecisionExport::newLine(int tabSize)
{
    if (tabSize <= 0)
        return "";
    return "\n";
}

QString JsonPrecisionExport::postColonSpace(int tabSize)
{
    if (tabSize > 0)
        return " ";
    return "";
}

QString JsonPrecisionExport::indentation(int nestedCount)
{
    return QString(nestedCount, ' ');
}

QString JsonPrecisionExport::comma(int &elementCountLeft)
{
    elementCountLeft--;
    if(elementCountLeft > 0)
        return ",";
    return "";
}
