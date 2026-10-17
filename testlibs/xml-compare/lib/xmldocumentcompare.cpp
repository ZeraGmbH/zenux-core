#include "xmldocumentcompare.h"
#include "testloghelpers.h"
#include "xmlelemcompareattribs.h"
#include "xmlelemcomparetext.h"
#include "xmlelemcomparetag.h"
#include "xmlelemiterstrategysort.h"
#include "xmlsorteddump.h"
#include <QHash>

XmlDocumentCompare::XmlDocumentCompare(XmlElemCompareFunc elemCompareFunction) :
    m_elemCompareFunc(elemCompareFunction)
{
}

XmlElemCompareFunc XmlDocumentCompare::m_defaultElemCompareFunc =
[](const QDomElement& elem1, const QDomElement& elem2) -> bool
{
    return
        XmlElemCompareTag::compare(elem1, elem2) &&
        XmlElemCompareAttribs::compare(elem1, elem2) &&
        XmlElemCompareText::compare(elem1, elem2);
};

bool XmlDocumentCompare::compareXml(const QString &xml1, const QString &xml2, bool fatalOnInvalidXml)
{
    XmlDocument doc1;
    doc1.loadXml(xml1, fatalOnInvalidXml);
    XmlDocument doc2;
    doc2.loadXml(xml2, fatalOnInvalidXml);
    if(doc1.isEmpty() && doc2.isEmpty())
        return true;
    if(doc1.isEmpty() || doc2.isEmpty())
        return false;
    if(!compareDocTypes(doc1, doc2))
        return false;
    return compareAllElems(doc1, doc2);
}

bool XmlDocumentCompare::compareXmlFile(const QString &fileNameExpected, const QString &dumped, bool fatalOnInvalidXml)
{
    XmlDocumentCompare xmlCompare;
    bool same = xmlCompare.compareXml(TestLogHelpers::loadFile(fileNameExpected), dumped, fatalOnInvalidXml);
    if (!same) {
        QString sorted = XmlSortedDump::sortedXml(dumped);
        TestLogHelpers::writeFile(TestLogHelpers::getDumpFilePath(fileNameExpected), sorted.toUtf8());
    }
    return same;
}

bool XmlDocumentCompare::compareDocTypes(XmlDocument doc1, XmlDocument doc2)
{
    return doc1.getDocType() == doc2.getDocType();
}

bool XmlDocumentCompare::compareAllElems(XmlDocument doc1, XmlDocument doc2)
{
    auto iter1 = doc1.root(std::make_unique<XmlElemIterStrategySort>());
    auto iter2 = doc2.root(std::make_unique<XmlElemIterStrategySort>());
    for(;!iter1.isEnd(); iter1.next(), iter2.next()) {
        if(!m_elemCompareFunc(iter1.getElem(), iter2.getElem()))
            return false;
    }
    if(!iter2.isEnd())
        return false;
    return true;
}
