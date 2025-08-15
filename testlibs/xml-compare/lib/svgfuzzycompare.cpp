#include "svgfuzzycompare.h"
#include "svgfuzzyattributecomparefunction.h"
#include "xmlelemcomparetag.h"
#include "xmlelemcompareattribs.h"
#include "xmlelemcomparetext.h"
#include "xmldocumentcompare.h"

bool SvgFuzzyCompare::compareXml(QString xml1, QString xml2, bool fatalOnInvalidXml)
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
    return comparer.compareXml(xml1, xml2, fatalOnInvalidXml);
}
