#include "test_convert_value.h"
#include "jsonprecisionexport.h"
#include <QTest>

QTEST_MAIN(test_convert_value)

void test_convert_value::exportString()
{
    QString value("ÄÖÜ");
    QJsonValue jsonValue(value);
    QCOMPARE(JsonPrecisionExport::valueToString(jsonValue), QString("\"%1\"").arg(value));
}

void test_convert_value::exportBool()
{
    QJsonValue jsonValueTrue(true);
    QCOMPARE(JsonPrecisionExport::valueToString(jsonValueTrue), "true");

    QJsonValue jsonValueFalse(false);
    QCOMPARE(JsonPrecisionExport::valueToString(jsonValueFalse), "false");
}

void test_convert_value::exportNull()
{
    QJsonValue jsonValueNull;
    QCOMPARE(JsonPrecisionExport::valueToString(jsonValueNull), "null");
}

void test_convert_value::exportNumber()
{
    QJsonValue value;

    value = int(5);
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 0), "5");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 1), "5");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 2), "5");

    value = int(-5);
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 0), "-5");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 1), "-5");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 2), "-5");

    value = double(0.1);
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 0), "0.1");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 1), "0.1");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 2), "0.1");
    QVERIFY(JsonPrecisionExport::valueToString(value, 0, 25) != "0.1");

    value = double(0.15);
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 0), "0.1");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 1), "0.1");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 2), "0.15");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 3), "0.15");

    value = double(0.16);
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 0), "0.2");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 1), "0.2");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 2), "0.16");

    value = double(1100000);
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 0), "1e+06");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 6), "1.1e+06");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 7), "1100000");

    value = double(0.1666);
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 2), "0.17");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 3), "0.167");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 4), "0.1666");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 5), "0.1666");

    value = double(-0.1666);
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 2), "-0.17");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 3), "-0.167");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 4), "-0.1666");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 5), "-0.1666");

    value = double(0.1234);
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 3), "0.123");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 4), "0.1234");

    value = double(1.678e-5);
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 3), "1.68e-05");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 4), "1.678e-05");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 5), "1.678e-05");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 6), "1.678e-05");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 7), "1.678e-05");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 8), "1.678e-05");
    QCOMPARE(JsonPrecisionExport::valueToString(value, 0, 9), "1.678e-05");
}
