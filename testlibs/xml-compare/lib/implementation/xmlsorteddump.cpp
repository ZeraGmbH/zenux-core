#include "xmlsorteddump.h"
#include <QStringList>
#include <QMap>
#include <QDomDocument>
#include <algorithm>

QString XmlSortedDump::sortedXml(const QString &xml)
{
    QDomDocument doc;
    if(!doc.setContent(xml))
        return QString();
    const QDomElement root = doc.documentElement();
    if(root.isNull())
        return QString();
    QString ret;
    const QString doctype = doc.doctype().name();
    if(!doctype.isEmpty())
        ret += "<!DOCTYPE " + doctype + ">\n";
    ret += serializeElement(root, 0);
    ret += "\n";
    return ret;
}

QString XmlSortedDump::serializeElement(const QDomElement &elem, int indentLevel)
{
    const QString indent(indentLevel * 2, ' ');
    QString ret = indent + "<" + elem.tagName();

    // attributes in reproducible (alphabetical) order: QDom serializes attributes
    // in unspecified order which makes diffs of stored dumps useless
    QStringList attrNames;
    const QDomNamedNodeMap attribs = elem.attributes();
    for(int i = 0; i < attribs.count(); ++i)
        attrNames << attribs.item(i).toAttr().name();
    std::sort(attrNames.begin(), attrNames.end());
    for(const QString &attrName : attrNames)
        ret += " " + attrName + "=\"" + escapeAttribute(elem.attribute(attrName)) + "\"";

    const QDomElement firstChild = elem.firstChildElement();
    if(firstChild.isNull()) {
        // leaf: keep the text content as compared by compareXml (QDomElement::text());
        // leaves without text are serialized self-closing
        const QString text = elem.text();
        if(text.isEmpty())
            ret += "/>";
        else
            ret += ">" + escapeText(text) + "</" + elem.tagName() + ">";
        return ret;
    }

    // group children by tag name (stable within the same tag) so that the order is
    // reproducible: same canonical grouping as XmlElemIterStrategySort used in compareAllElems
    QMap<QString, QList<QDomElement>> childrenByTag;
    for(QDomElement child = firstChild; !child.isNull(); child = child.nextSiblingElement())
        childrenByTag[child.tagName()].append(child);

    ret += ">";
    for(auto iter = childrenByTag.constBegin(); iter != childrenByTag.constEnd(); ++iter) {
        for(const QDomElement &child : iter.value())
            ret += "\n" + serializeElement(child, indentLevel + 1);
    }
    return ret + "\n" + indent + "</" + elem.tagName() + ">";
}

QString XmlSortedDump::escapeText(const QString &text)
{
    QString ret = text;
    ret.replace("&", "&amp;");
    ret.replace("<", "&lt;");
    ret.replace(">", "&gt;");
    return ret;
}

QString XmlSortedDump::escapeAttribute(const QString &value)
{
    QString ret = value;
    ret.replace("&", "&amp;");
    ret.replace("<", "&lt;");
    ret.replace("\"", "&quot;");
    ret.replace("\n", "&#10;");
    return ret;
}
