#include "test_svg_fuzzy_attribute_compare_function.h"
#include "svgfuzzyattributecomparefunction.h"
#include <QTest>

QTEST_MAIN(test_svg_fuzzy_attribute_compare_function)

void test_svg_fuzzy_attribute_compare_function::passOnAnyEquals()
{
    const QString attrib1 = "foo bar";
    const QString attrib2 = attrib1;
    QVERIFY(SvgFuzzyAttributeCompareFunction::compareAttribs(attrib1, attrib2));
}

void test_svg_fuzzy_attribute_compare_function::unequalNoValuesFails()
{
    QVERIFY(!SvgFuzzyAttributeCompareFunction::compareAttribs("foo", "bar"));
}

void test_svg_fuzzy_attribute_compare_function::unequalCountOfNumbersFailsWithSpecialWarning()
{
    QVERIFY(!SvgFuzzyAttributeCompareFunction::compareAttribs("100,2,3", "100,2"));
}

void test_svg_fuzzy_attribute_compare_function::extractNumbers()
{
    // taken from vf-qmllib vector svg tests
    const QString attrib1 = "M-66,1000 L-6,975.147 L-5.99999,1024.85 L-66,1000";
    QStringList values = SvgFuzzyAttributeCompareFunction::extractFloatsFromAttribs(attrib1).valuesExtracted;
    QCOMPARE(values.count(), 8);
    QCOMPARE(values[0], "-66");
    QCOMPARE(values[1], "1000");
    QCOMPARE(values[2], "-6");
    QCOMPARE(values[3], "975.147");
    QCOMPARE(values[4], "-5.99999");
    QCOMPARE(values[5], "1024.85");
    QCOMPARE(values[6], "-66");
    QCOMPARE(values[7], "1000");
}

void test_svg_fuzzy_attribute_compare_function::extractSingleNumber()
{
    QStringList values = SvgFuzzyAttributeCompareFunction::extractFloatsFromAttribs("42").valuesExtracted;
    QCOMPARE(values.count(), 1);
    QCOMPARE(values[0], "42");
}

void test_svg_fuzzy_attribute_compare_function::conversionToDoubleFails()
{
    QVERIFY(!SvgFuzzyAttributeCompareFunction::compareAttribs("()", "(())"));
}

void test_svg_fuzzy_attribute_compare_function::withinAcceptableLimit()
{
    QVERIFY(SvgFuzzyAttributeCompareFunction::compareAttribs("100,1000.0", "100,1000.1"));
}

void test_svg_fuzzy_attribute_compare_function::outofAcceptableLimit()
{
    QVERIFY(!SvgFuzzyAttributeCompareFunction::compareAttribs("100,1000.0", "100,1000.2"));
}

void test_svg_fuzzy_attribute_compare_function::extraLettersChange()
{
    const QString attrib1 = "M-66,1000 L-6,975.147 L-5.99999,1024.85 L-66,1000";
    const QString attrib2 = "L-66,1000 L-6,975.147 L-5.99999,1024.85 L-66,1000";
    QVERIFY(!SvgFuzzyAttributeCompareFunction::compareAttribs(attrib1, attrib2));
}
