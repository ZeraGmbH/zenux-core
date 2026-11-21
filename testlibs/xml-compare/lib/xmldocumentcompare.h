#ifndef XMLDOCUMENTCOMPARE_H
#define XMLDOCUMENTCOMPARE_H

#include "xmldocument.h"
#include <QString>
#include <QDomElement>
#include <functional>

typedef std::function<bool (const QDomElement, const QDomElement)> XmlElemCompareFunc;

class XmlDocumentCompare
{
public:
    // Just compare
    bool compareXml(const QString &xml1, const QString &xml2, bool fatalOnInvalidXml=false);

    // Compare / in case of error store dumped contents to /tmp/<test-name>/<fileNameExpected>
    static bool compareXmlFile(const QString &fileNameExpected, const QString &dumped, bool fatalOnInvalidXml=false);

    // Compare / expand fileNameExpected to <test-source-dir/test-data/fileNameExpected
    // in case of error store dumped contents to
    // * On local build expanded file name => files in source tree are overwritten
    //   Important: After red tests 'git diff' is your friend to decide if change is a regression or intended
    // * On OE build: /tmp/<test-name>/<fileNameExpected>
    static bool compareXmlSrc(const QString &fileNameExpected, const QString &dumped, const QString &sourceFileName, bool fatalOnInvalidXml=false);

    explicit XmlDocumentCompare(XmlElemCompareFunc elemCompareFunction = m_defaultElemCompareFunc);
private:
    static bool compareDocTypes(XmlDocument doc1, XmlDocument doc2);
    bool compareAllElems(XmlDocument doc1, XmlDocument doc2);

    XmlElemCompareFunc m_elemCompareFunc;
    static XmlElemCompareFunc m_defaultElemCompareFunc;
};

#endif // XMLDOCUMENTCOMPARE_H
