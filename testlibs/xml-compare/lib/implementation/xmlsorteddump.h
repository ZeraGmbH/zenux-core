#ifndef XMLSORTEDDUMP_H
#define XMLSORTEDDUMP_H

#include <QString>
#include <QDomElement>

class XmlSortedDump
{
public:
    static QString sortedXml(const QString &xml);

private:
    static QString serializeElement(const QDomElement &elem, int indentLevel);
    static QString escapeText(const QString &text);
    static QString escapeAttribute(const QString &value);
};

#endif // XMLSORTEDDUMP_H
