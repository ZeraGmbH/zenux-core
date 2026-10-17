#include "test_xmldocumentcompare.h"
#include "xmldocumentcompare.h"
#include "xmlsorteddump.h"
#include "testloghelpers.h"
#include <QTest>

QTEST_MAIN(test_xmldocumentcompare)

void test_xmldocumentcompare::bothEmpty()
{
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml("", ""));
}

void test_xmldocumentcompare::bothSameNoAttribs()
{
    QString xmlFindUpUpUp =
        "<root>"
            "<child1>"
                "<grandchild1>"
                    "<ggrandchild1>"
                        "<gggrandchild1/>"
                    "</ggrandchild1>"
                "</grandchild1>"
            "</child1>"
            "<child2/>"
        "</root>";
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml(xmlFindUpUpUp, xmlFindUpUpUp, true));
}

void test_xmldocumentcompare::bothDifferentNoAttribs()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2/>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE2/>"
            "<NODE3/>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::bothSameNoAttribsDiffSequence()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2/>"
            "<NODE3/>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE3/>"
            "<NODE2/>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml(xml1, xml2, true));
    QVERIFY(compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::firstEmptySecondValid()
{
    QString xml =
        "<NODE1>"
            "<NODE3/>"
            "<NODE2/>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(QString(), xml));
}

void test_xmldocumentcompare::firstValidSecondEmpty()
{
    QString xml =
        "<NODE1>"
            "<NODE3/>"
            "<NODE2/>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml, QString()));
}

void test_xmldocumentcompare::attibsUnequal()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2 a='1' b='2'/>"
            "<NODE3 c='3' d='4' e='5'></NODE3>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE2 a='1' b='2'/>"
            "<NODE3 c='3' d='foo' e='5'></NODE3>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::attibsEqual()
{
    QString xml =
        "<NODE1>"
            "<NODE2 a='1' b='2'/>"
            "<NODE3 c='3' d='4' e='5'></NODE3>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml(xml, xml, true));
}

void test_xmldocumentcompare::attribsDiffSequence()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2 a='1' b='2'/>"
            "<NODE3 c='3' d='4' e='5'></NODE3>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE3 c='3' d='4' e='5'></NODE3>"
            "<NODE2 a='1' b='2'/>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml(xml1, xml2, true));
    QVERIFY(compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::textUnequal()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2>foo</NODE2>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE2>bar</NODE2>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::textEqual()
{
    QString xml =
        "<NODE1>"
            "<NODE2>foo</NODE2>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml(xml, xml, true));
}

void test_xmldocumentcompare::attibsUnequalTextEqual()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2>foo</NODE2>"
            "<NODE3 c='3' d='4' e='5'></NODE3>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE2>foo</NODE2>"
            "<NODE3 c='3' d='foo' e='5'></NODE3>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::attibsEqualTextUnequal()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2>foo</NODE2>"
            "<NODE3 c='3' d='4' e='5'></NODE3>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE2>bar</NODE2>"
            "<NODE3 c='3' d='4' e='5'></NODE3>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::attibsEqualTextEqual()
{
    QString xml =
        "<NODE1>"
            "<NODE2>foo</NODE2>"
            "<NODE3 c='3' d='4' e='5'></NODE3>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml(xml, xml, true));
}

void test_xmldocumentcompare::arraySecondMoreElems()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2 a='1'></NODE2>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE2 a='1'></NODE2>"
            "<NODE2 a='1'></NODE2>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::arraySwappedSequence()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2 a='1'></NODE2>"
            "<NODE2 a='2'></NODE2>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE2 a='2'></NODE2>"
            "<NODE2 a='1'></NODE2>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::arrayNestedSwappedSequence()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2>"
                "<NODE3 a='1'></NODE3>"
                "<NODE3 a='2'></NODE3>"
            "</NODE2>"
            "<NODE2>"
                "<NODE3 b='1'></NODE3>"
                "<NODE3 b='2'></NODE3>"
            "</NODE2>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE2>"
                "<NODE3 a='1'></NODE3>"
                "<NODE3 a='2'></NODE3>"
            "</NODE2>"
            "<NODE2>"
                "<NODE3 b='2'></NODE3>"
                "<NODE3 b='1'></NODE3>"
            "</NODE2>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::arrayNestedMissing()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2>"
                "<NODE3 a='1'></NODE3>"
                "<NODE3 a='2'></NODE3>"
            "</NODE2>"
            "<NODE2>"
                "<NODE3 b='1'></NODE3>"
                "<NODE3 b='2'></NODE3>"
            "</NODE2>"
        "</NODE1>";
    QString xml2 =
        "<NODE1>"
            "<NODE2>"
                "<NODE3 a='1'></NODE3>"
                "<NODE3 a='2'></NODE3>"
            "</NODE2>"
            "<NODE2>"
                "<NODE3 b='1'></NODE3>"
            "</NODE2>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::arrayEqual()
{
    QString xml =
        "<NODE1>"
            "<NODE2>"
                "<NODE3 a='1' b='2'></NODE3>"
                "<NODE3 c='1' d='2'></NODE3>"
            "</NODE2>"
            "<NODE2>"
                "<NODE3 a='1' b='2'></NODE3>"
                "<NODE3 c='1' d='2'></NODE3>"
            "</NODE2>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml(xml, xml, true));
}


void test_xmldocumentcompare::docTypeUnequal()
{
    QString xml1 =
        "<!DOCTYPE foo>"
        "<NODE1>"
            "<NODE2>foo</NODE2>"
        "</NODE1>";
    QString xml2 =
        "<!DOCTYPE bar>"
        "<NODE1>"
            "<NODE2>foo</NODE2>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::docTypeEqual()
{
    QString xml1 =
        "<!DOCTYPE foo>"
        "<NODE1>"
            "<NODE2>foo</NODE2>"
        "</NODE1>";
    QString xml2 =
        "<!DOCTYPE foo>"
        "<NODE1>"
            "<NODE2>foo</NODE2>"
        "</NODE1>";
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml(xml1, xml2, true));
    QVERIFY(compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::sameSizeDifferentElems()
{
    QString xml1 =
        "<NODE1>"
            "<NODE2>foo</NODE2>"
        "</NODE1>";
    QString xml2 =
        "<NODE3>"
            "<NODE4>foo</NODE4>"
        "</NODE3>";
    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXml(xml1, xml2, true));
    QVERIFY(!compare.compareXml(xml2, xml1, true));
}

void test_xmldocumentcompare::sortedReferenceVsDeviceOrderDump()
{
    // mimic of an adjustment module reference dump (regenerated by XmlSortedDump)
    // vs. a device dump in its own tag order: same data, different sibling sequence
    const QString sortedRef =
        "<!DOCTYPE ADW5743AdjustmentData>"
        "<PCB>"
            "<Adjustment>"
                "<Chksum>0xffff</Chksum>"
                "<Sense>"
                    "<Channel>"
                        "<Name>m0</Name>"
                        "<Range><Gain><Status>128</Status></Gain></Range>"
                    "</Channel>"
                "</Sense>"
            "</Adjustment>"
            "<Date>nodate</Date>"
            "<Type>ADW5743</Type>"
        "</PCB>";
    const QString deviceOrderDump =
        "<!DOCTYPE ADW5743AdjustmentData>"
        "<PCB>"
            "<Type>ADW5743</Type>"
            "<Date>nodate</Date>"
            "<Adjustment>"
                "<Sense>"
                    "<Channel>"
                        "<Range><Gain><Status>128</Status></Gain></Range>"
                        "<Name>m0</Name>"
                    "</Channel>"
                "</Sense>"
                "<Chksum>0xffff</Chksum>"
            "</Adjustment>"
        "</PCB>";

    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml(sortedRef, deviceOrderDump));
    QVERIFY(compare.compareXml(deviceOrderDump, sortedRef));

    // a real data change in the reordered dump is still detected
    const QString deviceOrderDumpChanged =
        "<!DOCTYPE ADW5743AdjustmentData>"
        "<PCB>"
            "<Type>ADW5743</Type>"
            "<Date>nodate</Date>"
            "<Adjustment>"
                "<Sense>"
                    "<Channel>"
                        "<Range><Gain><Status>0</Status></Gain></Range>"
                        "<Name>m0</Name>"
                    "</Channel>"
                "</Sense>"
                "<Chksum>0xffff</Chksum>"
            "</Adjustment>"
        "</PCB>";
    QVERIFY(!compare.compareXml(sortedRef, deviceOrderDumpChanged));
}

void test_xmldocumentcompare::equalDataDifferentIndentation()
{
    // same data, different whitespace between child elements
    // (e.g. a device dump in its own formatting vs. a reference regenerated by XmlSortedDump)
    const QString xml1 =
        "<root>\n"
        "    <a>x</a>\n"
        "    <b>y</b>\n"
        "</root>";
    const QString xml2 =
        "<root><a>x</a><b>y</b></root>";
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXml(xml1, xml2));
    QVERIFY(compare.compareXml(xml2, xml1));
}

void test_xmldocumentcompare::compareXmlFileEqualStoresNothing()
{
    QTemporaryDir tempDir;
    QVERIFY(tempDir.isValid());
    const QString fileNameExpected = tempDir.filePath("ref.xml");
    const QByteArray refData = "<root><a v='1'>t1</a><b><c/></b></root>";
    QVERIFY(TestLogHelpers::writeFile(fileNameExpected, refData));

    // same data as the reference, only in a different tag order
    const QString dumped = "<root><b><c/></b><a v='1'>t1</a></root>";
    XmlDocumentCompare compare;
    QVERIFY(compare.compareXmlFile(fileNameExpected, dumped));
    QVERIFY(!QFileInfo::exists((TestLogHelpers::getDumpFilePath(fileNameExpected))));
}

void test_xmldocumentcompare::compareXmlFileUnequalStoresSortedDump()
{
    QTemporaryDir tempDir;
    QVERIFY(tempDir.isValid());
    const QString fileNameExpected = tempDir.filePath("ref.xml");
    const QByteArray refData = "<root><a v='1'>t1</a><b><c/></b></root>";
    QVERIFY(TestLogHelpers::writeFile(fileNameExpected, refData));

    // dump with changed data and shuffled tags/attributes
    const QString dumped =
        "<root z='9'>"
        "<b aattr='x'><c extra='1'/></b>"
        "<a v='42'>t2</a>"
        "</root>";

    XmlDocumentCompare compare;
    QVERIFY(!compare.compareXmlFile(fileNameExpected, dumped));

    const QString storedPath = TestLogHelpers::getDumpFilePath(fileNameExpected);
    QVERIFY(QFileInfo::exists(storedPath));
    const QString stored = QString::fromUtf8(TestLogHelpers::loadFile(storedPath));

    // the stored file is the reproducible (sorted) version of the dump
    QCOMPARE(stored, XmlSortedDump::sortedXml(dumped));

    // ... and still contains all tags/attributes/text of the dump (compareXml ignores order)
    const QString shuffledDumped =
        "<root z='9'>"
        "<a v='42'>t2</a>"
        "<b aattr='x'><c extra='1'/></b>"
        "</root>";
    QVERIFY(compare.compareXml(stored, shuffledDumped));

    // ... while the data change against the reference is still detectable
    QVERIFY(!compare.compareXml(stored, QString::fromUtf8(refData)));

    QFile::remove(storedPath);
}
