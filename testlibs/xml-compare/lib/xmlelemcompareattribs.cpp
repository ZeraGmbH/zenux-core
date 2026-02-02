#include "xmlelemcompareattribs.h"
#include <QStringList>

XmlAttribCompareFunc XmlElemCompareAttribs::m_defaultAttribCompareFunc =
    [](const QString& attrib1, const QString& attrib2) -> bool
{
    bool ok = attrib1 == attrib2;
    if(!ok)
        qWarning("XML attribute '%s' is unequal '%s'", qPrintable(attrib1), qPrintable(attrib2));
    return ok;
};


bool XmlElemCompareAttribs::compare(const QDomElement &elem1, const QDomElement &elem2,
                                    XmlAttribCompareFunc attrCompare)
{
    if(bothEmpty(elem1, elem2))
        return true;
    if(elem1.attributes().count() != elem2.attributes().count())
        return false;
    return compareAll(elem1, elem2, attrCompare);
}

bool XmlElemCompareAttribs::isEmpty(const QDomElement &elem)
{
    return !elem.hasAttributes();
}

bool XmlElemCompareAttribs::bothEmpty(const QDomElement &elem1, const QDomElement &elem2)
{
    return isEmpty(elem1) && isEmpty(elem2);
}

bool XmlElemCompareAttribs::compareAll(const QDomElement &elem1, const QDomElement &elem2,
                                       XmlAttribCompareFunc attrCompare)
{
    QStringList keysToBeIgnored= QStringList() << "transform" << "y";
    auto elem1Attribs = elem1.attributes();
    auto elem2Attribs = elem2.attributes();
    for(int i=0; i<elem1Attribs.count(); ++i) {
        QString attrKey = elem1Attribs.item(i).toAttr().name();
        if(keysToBeIgnored.contains(attrKey))
            continue;
        if(!elem2Attribs.contains(attrKey))
            return false;
        QString attrib1 = elem1Attribs.item(i).toAttr().value();
        QString attrib2 = elem2.attribute(attrKey);
        bool ok = attrCompare(attrib1, attrib2);
        if (!ok)
            return false;
    }
    return true;
}
