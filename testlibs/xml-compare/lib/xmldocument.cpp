#include "xmldocument.h"

bool XmlDocument::loadXml(const QString &xml, bool fatalOnInvalidXml)
{
    bool isValid = bool(m_doc.setContent(xml));
    if(!isValid && fatalOnInvalidXml)
        qFatal("Invalid XML\n%s", qPrintable(xml));
    return isValid;
}

void XmlDocument::setXmlDomDoc(QDomDocument xmlDoc)
{
    m_doc = xmlDoc;
}

bool XmlDocument::isEmpty()
{
    return root().getElem() == QDomElement();
}

XmlElemIter XmlDocument::root(XmlElemIterStrategyPtr &&iterStrategy)
{
    return XmlElemIter(std::move(iterStrategy), m_doc.documentElement());
}

bool XmlDocument::findElem(QStringList tagSearchPath, QDomElement &foundElem)
{
    if(tagSearchPath.isEmpty())
        return false;
    QString childName = tagSearchPath.takeFirst();
    foundElem = m_doc.firstChildElement(childName);
    while(!foundElem.isNull() && !tagSearchPath.isEmpty()) {
        childName = tagSearchPath.takeFirst();
        foundElem = foundElem.firstChildElement(childName);
    }
    return !foundElem.isNull();
}

XmlElemIter XmlDocument::find(QStringList tagSearchPath, XmlElemIterStrategyPtr &&iterStrategy)
{
    QDomElement foundElem;
    findElem(tagSearchPath, foundElem);
    return XmlElemIter(std::move(iterStrategy), foundElem);
}

QString XmlDocument::getDocType()
{
    return m_doc.doctype().name();
}
