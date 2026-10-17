#include "test_xmlsorteddump.h"
#include "xmldocumentcompare.h"
#include "xmlsorteddump.h"
#include "testloghelpers.h"
#include <QTest>

QTEST_MAIN(test_xmlsorteddump)

void test_xmlsorteddump::sortedXmlReordersTagsAndAttributes()
{
    const QString xml =
        "<root zeta='1' alpha='2'>"
        "<childB/>"
        "<childA name='b'>text</childA>"
        "<childC/>"
        "<childA name='a'/>"
        "</root>";
    // tags in alphabetical order (stable within the same tag), attributes in
    // alphabetical order, leaves without text self-closing, 4-space indentation
    const QString expected =
        "<root alpha=\"2\" zeta=\"1\">\n"
        "  <childA name=\"b\">text</childA>\n"
        "  <childA name=\"a\"/>\n"
        "  <childB/>\n"
        "  <childC/>\n"
        "</root>\n";
    QCOMPARE(XmlSortedDump::sortedXml(xml), expected);
}

void test_xmlsorteddump::sortedXmlReproducibleForDifferentOrders()
{
    const QString xml1 = "<root b='2' a='1'><y/><x v='9'/><z t='8'/></root>";
    const QString xml2 = "<root a='1' b='2'><z t='8'/><x v='9'/><y/></root>";
    const QString xml3 = "<root   a=\"1\"  b=\"2\" > <x v=\"9\"/> <y/> <z t=\"8\"/> </root>";
    QCOMPARE(XmlSortedDump::sortedXml(xml1), XmlSortedDump::sortedXml(xml2));
    QCOMPARE(XmlSortedDump::sortedXml(xml1), XmlSortedDump::sortedXml(xml3));
}

void test_xmlsorteddump::sortedXmlKeepsAllData()
{
    const QString xml =
        "<!DOCTYPE ADW>"
        "<PCB serial='42'>"
        "<Adjustment>"
        "<Sense>"
        "<Channel name='m0'><Range name='480V'><Gain><Status>0</Status></Gain></Range></Channel>"
        "<Channel name='m1'><Range name='240V'><Gain><Status>1</Status></Gain></Range></Channel>"
        "</Sense>"
        "</Adjustment>"
        "<Type>ADW5743</Type>"
        "</PCB>";
    // same data, only the sequence of differently named tags is swapped
    const QString shuffled =
        "<!DOCTYPE ADW>"
        "<PCB serial='42'>"
        "<Type>ADW5743</Type>"
        "<Adjustment>"
        "<Sense>"
        "<Channel name='m0'><Range name='480V'><Gain><Status>0</Status></Gain></Range></Channel>"
        "<Channel name='m1'><Range name='240V'><Gain><Status>1</Status></Gain></Range></Channel>"
        "</Sense>"
        "</Adjustment>"
        "</PCB>";

    XmlDocumentCompare compare;
    // the sorted version still contains all tags/attributes/text of the original data
    QVERIFY(compare.compareXml(XmlSortedDump::sortedXml(xml), xml));
    // ... and is byte-identical no matter which order the input had
    QCOMPARE(XmlSortedDump::sortedXml(xml), XmlSortedDump::sortedXml(shuffled));
}
