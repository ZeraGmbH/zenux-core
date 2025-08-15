#ifndef XMLELEMCOMPAREATTRIBS_H
#define XMLELEMCOMPAREATTRIBS_H

#include <QDomElement>
#include <functional>

typedef std::function<bool (const QString&, const QString&)> XmlAttribCompareFunc;

class XmlElemCompareAttribs
{
public:
    static bool compare(const QDomElement &elem1, const QDomElement &elem2,
                        XmlAttribCompareFunc attrCompare = m_defaultAttribCompareFunc);
private:
    static bool isEmpty(const QDomElement &elem);
    static bool bothEmpty(const QDomElement &elem1, const QDomElement &elem2);
    static bool compareAll(const QDomElement &elem1, const QDomElement &elem2, XmlAttribCompareFunc attrCompare);

    static XmlAttribCompareFunc m_defaultAttribCompareFunc;
};

#endif // XMLELEMCOMPAREATTRIBS_H
