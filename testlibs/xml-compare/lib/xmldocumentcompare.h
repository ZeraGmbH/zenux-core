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
    // * In case of failure source dump files are overwritten and 'git diff' is your friend
    // * On OE builds change into source directory first e.g.
    //   <your-oe-tmp>/oe-zenux/tmp-glibc/work/cortexa9t2hf-neon-imx-mortsgna-linux-gnueabi/zenux-services/2.0.0+gitAUTOINC+<commit>-r0
    //   and check with 'git diff' there
    static bool compareXmlSrc(const QString &fileNameExpected, const QString &dumped, const QString &sourceFileName);

    // Just compare (initial implementation - use more enhanced methods above)
    bool compareXml(const QString &xml1, const QString &xml2, bool fatalOnInvalidXml=false);

    explicit XmlDocumentCompare(XmlElemCompareFunc elemCompareFunction = m_defaultElemCompareFunc);
private:
    static bool compareDocTypes(XmlDocument doc1, XmlDocument doc2);
    bool compareAllElems(XmlDocument doc1, XmlDocument doc2);

    XmlElemCompareFunc m_elemCompareFunc;
    static XmlElemCompareFunc m_defaultElemCompareFunc;
};

#endif // XMLDOCUMENTCOMPARE_H
