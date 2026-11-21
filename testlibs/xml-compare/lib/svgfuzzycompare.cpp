#include "svgfuzzycompare.h"
#include "svgfuzzyattributecomparefunction.h"
#include "xmlelemcomparetag.h"
#include "xmlelemcompareattribs.h"
#include "xmlelemcomparetext.h"
#include "xmldocumentcompare.h"
#include "xmlsorteddump.h"
#include "testloghelpers.h"

bool SvgFuzzyCompare::compareXml(const QString &xml1, const QString &xml2)
{
    XmlElemCompareFunc elemCompareFunc =
        [](const QDomElement& elem1, const QDomElement& elem2) -> bool
    {
        return
            XmlElemCompareTag::compare(elem1, elem2) &&
            XmlElemCompareAttribs::compare(elem1, elem2, SvgFuzzyAttributeCompareFunction::compareAttribs) &&
            XmlElemCompareText::compare(elem1, elem2);
    };
    XmlDocumentCompare comparer(elemCompareFunc);
    return comparer.compareXml(xml1, xml2);
}

bool SvgFuzzyCompare::compareXmlSrc(const QString &fileNameExpected, const QString &dumped, const QString &sourceFileName)
{
    const QString fileNameExpectedPath = TestLogHelpers::getDumpStoreSrcFilePath(fileNameExpected, sourceFileName);
    bool same = compareXml(TestLogHelpers::loadFile(fileNameExpectedPath), dumped);
    if (!same) {
        QString sorted = XmlSortedDump::sortedXml(dumped);
        if (TestLogHelpers::runsInOeEnvironment())
            TestLogHelpers::writeFile(TestLogHelpers::getDumpStoreTmpFilePath(fileNameExpected), sorted.toUtf8());
        else
            TestLogHelpers::writeFile(fileNameExpectedPath, sorted.toUtf8());
    }
    return same;
}
