#include "test_convert_array.h"
#include "jsonprecisionexport.h"
#include <testloghelpers.h>
#include <QTest>

QTEST_MAIN(test_convert_array)

void test_convert_array::exportEmptyArray()
{
    QCOMPARE(JsonPrecisionExport::arrayToString(QJsonArray(), 0), "[]");
    QCOMPARE(JsonPrecisionExport::arrayToString(QJsonArray(), 2), "[\n]\n");
}
