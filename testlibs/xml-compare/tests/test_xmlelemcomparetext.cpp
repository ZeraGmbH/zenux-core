#include "test_xmlelemcomparetext.h"
#include "xmlelemcomparetext.h"
#include <QTest>

QTEST_MAIN(test_xmlelemcomparetext)

void test_xmlelemcomparetext::bothEmpty()
{
    QDomDocument doc;
    QVERIFY(doc.setContent(QString("<root></root>")));
    QDomElement elem = doc.firstChildElement();
    QCOMPARE(elem.text(), "");
    QVERIFY(XmlElemCompareText::compare(elem, elem));
}

void test_xmlelemcomparetext::oneEmpty()
{
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<root></root>")));
    QDomElement elem1 = doc1.firstChildElement();
    QCOMPARE(elem1.text(), "");
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<root>foo</root>")));
    QDomElement elem2 = doc2.firstChildElement();
    QCOMPARE(elem2.text(), "foo");
    QVERIFY(!XmlElemCompareText::compare(elem1, elem2));
}

void test_xmlelemcomparetext::equal()
{
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<root>foo</root>")));
    QDomElement elem1 = doc1.firstChildElement();
    QCOMPARE(elem1.text(), "foo");
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<root>foo</root>")));
    QDomElement elem2 = doc2.firstChildElement();
    QCOMPARE(elem2.text(), "foo");
    QVERIFY(XmlElemCompareText::compare(elem1, elem2));
}

void test_xmlelemcomparetext::unequal()
{
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<root>foo</root>")));
    QDomElement elem1 = doc1.firstChildElement();
    QCOMPARE(elem1.text(), "foo");
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<root>bar</root>")));
    QDomElement elem2 = doc2.firstChildElement();
    QCOMPARE(elem2.text(), "bar");
    QVERIFY(!XmlElemCompareText::compare(elem1, elem2));
}

void test_xmlelemcomparetext::unequalTextEqualAttribs()
{
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<text fill=\"#0000c4\">foo</text>")));
    QDomElement elem1 = doc1.firstChildElement();
    QCOMPARE(elem1.text(), "foo");
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<text fill=\"#0000c4\">bar</text>")));
    QDomElement elem2 = doc2.firstChildElement();
    QCOMPARE(elem2.text(), "bar");
    QVERIFY(!XmlElemCompareText::compare(elem1, elem2));
}

void test_xmlelemcomparetext::equalTextEqualAttribs()
{
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<text fill=\"#0000c4\">foo</text>")));
    QDomElement elem1 = doc1.firstChildElement();
    QCOMPARE(elem1.text(), "foo");
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<text fill=\"#0000c4\">foo</text>")));
    QDomElement elem2 = doc2.firstChildElement();
    QCOMPARE(elem2.text(), "foo");
    QVERIFY(XmlElemCompareText::compare(elem1, elem2));
}

void test_xmlelemcomparetext::equalTextEqualUnequalAttribs()
{
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<text fill=\"#0000c4\">foo</text>")));
    QDomElement elem1 = doc1.firstChildElement();
    QCOMPARE(elem1.text(), "foo");
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<text fill=\"#0000c5\">foo</text>")));
    QDomElement elem2 = doc2.firstChildElement();
    QCOMPARE(elem2.text(), "foo");
    QVERIFY(XmlElemCompareText::compare(elem1, elem2)); // attribs are checked in XmlElemCompareAttribs
}

void test_xmlelemcomparetext::firstHasAttributes()
{
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<root a='1' b='2'/>")));
    QDomElement elem1 = doc1.firstChildElement();
    QCOMPARE(elem1.text(), "");
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<root>foo</root>")));
    QDomElement elem2 = doc2.firstChildElement();
    QCOMPARE(elem2.text(), "foo");
    QVERIFY(!XmlElemCompareText::compare(elem1, elem2));
}

void test_xmlelemcomparetext::secondHasAttibutes()
{
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<root>foo</root>")));
    QDomElement elem1 = doc1.firstChildElement();
    QCOMPARE(elem1.text(), "foo");
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<root a='1' b='2'/>")));
    QDomElement elem2 = doc2.firstChildElement();
    QCOMPARE(elem2.text(), "");
    QVERIFY(!XmlElemCompareText::compare(elem1, elem2));
}

void test_xmlelemcomparetext::childElemsSwappedSequence()
{
    // only the sequence of child elements differs; their own texts are equal.
    // child elements are compared individually by XmlDocumentCompare::compareAllElems,
    // so this comparator must not mix descendant text into the comparison
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<root><b>foo</b><c>bar</c></root>")));
    QDomElement elem1 = doc1.firstChildElement();
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<root><c>bar</c><b>foo</b></root>")));
    QDomElement elem2 = doc2.firstChildElement();
    QVERIFY(XmlElemCompareText::compare(elem1, elem2));
}

void test_xmlelemcomparetext::directTextCompared()
{
    // the element's own (direct) text is still compared
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<root>foo<b>x</b></root>")));
    QDomElement elem1 = doc1.firstChildElement();
    QCOMPARE(elem1.text(), "foox");
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<root>bar<b>x</b></root>")));
    QDomElement elem2 = doc2.firstChildElement();
    QCOMPARE(elem2.text(), "barx");
    QVERIFY(!XmlElemCompareText::compare(elem1, elem2));
}

void test_xmlelemcomparetext::whitespaceOnlyDirectTextIgnored()
{
    // same data, but one side carries whitespace-only text nodes (indentation) between child elements.
    // indentation is formatting, not data, so it must not be part of the comparison
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<root>\n    <a>x</a>\n    <b>y</b>\n</root>")));
    QDomElement elem1 = doc1.firstChildElement();
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<root><a>x</a><b>y</b></root>")));
    QDomElement elem2 = doc2.firstChildElement();
    QVERIFY(XmlElemCompareText::compare(elem1, elem2));
}

void test_xmlelemcomparetext::multipleDirectTextNodesCompared()
{
    // mixed content: the element has multiple direct text nodes around its child elements.
    // all of them are data and must be compared, not only the first one
    QDomDocument doc1;
    QVERIFY(doc1.setContent(QString("<root>foo<b>x</b>bar</root>")));
    QDomElement elem1 = doc1.firstChildElement();
    QDomDocument doc2;
    QVERIFY(doc2.setContent(QString("<root>foo<b>x</b>baz</root>")));
    QDomElement elem2 = doc2.firstChildElement();
    QVERIFY(!XmlElemCompareText::compare(elem1, elem2));

    QDomDocument doc3;
    QVERIFY(doc3.setContent(QString("<root>foo<a>x</a><b>y</b>baz</root>")));
    QDomElement elem3 = doc3.firstChildElement();
    QDomDocument doc4;
    QVERIFY(doc4.setContent(QString("<root>foo<a>y</a><b>x</b>baz</root>")));
    QDomElement elem4 = doc4.firstChildElement();
    QVERIFY(XmlElemCompareText::compare(elem3, elem4)); // ignore inner
}
