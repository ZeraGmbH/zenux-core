#include "test_convert_object.h"
#include "jsonprecisionexport.h"
#include <testloghelpers.h>
#include <QJsonDocument>
#include <QTest>

QTEST_MAIN(test_convert_object)

void test_convert_object::exportEmptyObject()
{
    QCOMPARE(JsonPrecisionExport::objectToString(QJsonObject(), 0), "{}");
    QCOMPARE(JsonPrecisionExport::objectToString(QJsonObject(), 2), "{\n}\n");
}

void test_convert_object::exportObjectOneNullValue()
{
    QJsonObject obj;
    obj.insert("null0", QJsonValue());

    bool allOk = true;
    QString dumped = JsonPrecisionExport::objectToString(obj, 0);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectOneNullValueTab0.json", dumped, TEST_SRC_DIR))
        allOk = false;

    dumped = JsonPrecisionExport::objectToString(obj, 2);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectOneNullValueTab2.json", dumped, TEST_SRC_DIR))
        allOk = false;
    QVERIFY(allOk);
}

void test_convert_object::exportObjectTwoNullValue()
{
    QJsonObject obj;
    obj.insert("null0", QJsonValue());
    obj.insert("null1", QJsonValue());

    bool allOk = true;
    QString dumped = JsonPrecisionExport::objectToString(obj, 0);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectTwoNullValueTab0.json", dumped, TEST_SRC_DIR))
        allOk = false;

    dumped = JsonPrecisionExport::objectToString(obj, 2);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectTwoNullValueTab2.json", dumped, TEST_SRC_DIR))
        allOk = false;
    QVERIFY(allOk);
}

void test_convert_object::exportObjectTwoNullValueQtCompare()
{
    QJsonObject obj;
    obj.insert("obj0", QJsonValue());
    obj.insert("obj1", QJsonValue());
    QJsonDocument doc(obj);

    QString dumped = JsonPrecisionExport::objectToString(obj, 0);
    QString expected = doc.toJson(QJsonDocument::Compact);
    QCOMPARE(dumped, expected);

    dumped = JsonPrecisionExport::objectToString(obj, 4);
    expected = doc.toJson(QJsonDocument::Indented);
    QCOMPARE(dumped, expected);
}

void test_convert_object::exportObjectTwoEmptyObjects()
{
    QJsonObject obj;
    obj.insert("obj0", QJsonValue(QJsonObject()));
    obj.insert("obj1", QJsonValue(QJsonObject()));

    bool allOk = true;
    QString dumped = JsonPrecisionExport::objectToString(obj, 0);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectTwoEmptyObjectsTab0.json", dumped, TEST_SRC_DIR))
        allOk = false;

    dumped = JsonPrecisionExport::objectToString(obj, 2);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectTwoEmptyObjectsTab2.json", dumped, TEST_SRC_DIR))
        allOk = false;
    QVERIFY(allOk);
}

void test_convert_object::exportObjectTwoEmptyObjectsQtCompare()
{
    QJsonObject obj;
    obj.insert("obj0", QJsonValue(QJsonObject()));
    obj.insert("obj1", QJsonValue(QJsonObject()));
    QJsonDocument doc(obj);

    QString dumped = JsonPrecisionExport::objectToString(obj, 0);
    QString expected = doc.toJson(QJsonDocument::Compact);
    QCOMPARE(dumped, expected);

    dumped = JsonPrecisionExport::objectToString(obj, 4);
    expected = doc.toJson(QJsonDocument::Indented);
    QCOMPARE(dumped, expected);
}

void test_convert_object::exportObjectTwoEmptyArrays()
{
    QJsonObject obj;
    obj.insert("arr0", QJsonValue(QJsonArray()));
    obj.insert("arr1", QJsonValue(QJsonArray()));

    bool allOk = true;
    QString dumped = JsonPrecisionExport::objectToString(obj, 0);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectTwoEmptyArraysTab0.json", dumped, TEST_SRC_DIR))
        allOk = false;

    dumped = JsonPrecisionExport::objectToString(obj, 2);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectTwoEmptyArraysTab2.json", dumped, TEST_SRC_DIR))
        allOk = false;
    QVERIFY(allOk);
}

void test_convert_object::exportObjectTwoEmptyArraysQtCompare()
{
    QJsonObject obj;
    obj.insert("arr0", QJsonValue(QJsonArray()));
    obj.insert("arr1", QJsonValue(QJsonArray()));
    QJsonDocument doc(obj);

    QString dumped = JsonPrecisionExport::objectToString(obj, 0);
    QString expected = doc.toJson(QJsonDocument::Compact);
    QCOMPARE(dumped, expected);

    dumped = JsonPrecisionExport::objectToString(obj, 4);
    expected = doc.toJson(QJsonDocument::Indented);
    QCOMPARE(dumped, expected);
}

void test_convert_object::exportObjectTwoArraysOfStrings()
{
    QJsonObject obj;
    QJsonArray array1;
    array1.append(QJsonValue("string1"));
    array1.append(QJsonValue("string2"));
    QJsonArray array2;
    array2.append(QJsonValue("string3"));
    array2.append(QJsonValue("string4"));
    obj.insert("arr0", QJsonValue(array1));
    obj.insert("arr1", QJsonValue(array2));

    bool allOk = true;
    QString dumped = JsonPrecisionExport::objectToString(obj, 0);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectTwoArraysOfStringsTab0.json", dumped, TEST_SRC_DIR))
        allOk = false;

    dumped = JsonPrecisionExport::objectToString(obj, 2);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectTwoArraysOfStringsTab2.json", dumped, TEST_SRC_DIR))
        allOk = false;
    QVERIFY(allOk);
}

void test_convert_object::exportObjectTwoArraysOfStringsQtCompare()
{
    QJsonObject obj;
    QJsonArray array1;
    array1.append(QJsonValue("string1"));
    array1.append(QJsonValue("string2"));
    QJsonArray array2;
    array2.append(QJsonValue("string3"));
    array2.append(QJsonValue("string4"));
    obj.insert("arr0", QJsonValue(array1));
    obj.insert("arr1", QJsonValue(array2));
    QJsonDocument doc(obj);

    QString dumped = JsonPrecisionExport::objectToString(obj, 0);
    QString expected = doc.toJson(QJsonDocument::Compact);
    QCOMPARE(dumped, expected);

    dumped = JsonPrecisionExport::objectToString(obj, 4);
    expected = doc.toJson(QJsonDocument::Indented);
    QCOMPARE(dumped, expected);
}

void test_convert_object::exportObjectArrayWithExponetialDoublesQtCompare()
{
    QJsonObject obj;
    QJsonArray array;
    array.append(QJsonValue(1e9));
    array.append(QJsonValue(1e99));
    array.append(QJsonValue(-1e9));
    array.append(QJsonValue(-1e99));
    array.append(QJsonValue(1e-9));
    array.append(QJsonValue(1e-99));
    array.append(QJsonValue(-1e-9));
    array.append(QJsonValue(-1e-99));
    obj.insert("arr", QJsonValue(array));
    QJsonDocument doc(obj);

    QString dumped = JsonPrecisionExport::objectToString(obj, 4, 10);
    QString expected = doc.toJson(QJsonDocument::Indented);
    QCOMPARE(dumped, expected);
}

void test_convert_object::exportObjectOfNestedAll()
{
    QJsonObject obj = createObjectOfNestedAll();

    bool allOk = true;
    QString dumped = JsonPrecisionExport::objectToString(obj, 0);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectOfNestedAllTab0.json", dumped, TEST_SRC_DIR))
        allOk = false;

    dumped = JsonPrecisionExport::objectToString(obj, 2);
    if (!TestLogHelpers::compareAndLogOnDiffJsonSrc("exportObjectOfNestedAllTab2.json", dumped, TEST_SRC_DIR))
        allOk = false;
    QVERIFY(allOk);
}

void test_convert_object::exportObjectOfNestedAllQtCompare()
{
    QJsonObject obj = createObjectOfNestedAll();
    QJsonDocument doc(obj);

    QString dumped = JsonPrecisionExport::objectToString(obj, 4, 10);
    QString expected = doc.toJson(QJsonDocument::Indented);
    QCOMPARE(dumped, expected);
}

QJsonObject test_convert_object::createObjectOfNestedAll()
{
    QJsonValue val1(false);
    QJsonValue val2(true);
    QJsonValue val3;
    QJsonValue val4(42);
    QJsonValue val5("foo");
    QJsonArray val6;
    val6.append(val1);
    val6.append(val2);
    QJsonObject val7;
    val7.insert("val3", val3);

    QJsonObject back1;
    back1.insert("val7", val7);
    QJsonArray back2;
    back2.append(back1);
    back2.append(back1);
    back2.append(val6);
    QJsonObject back3;
    back3.insert("back2", back2);
    back3.insert("val6", val6);
    back3.insert("val5", val5);
    back3.insert("val4", val4);
    back3.insert("val7", val7);

    QJsonObject obj;
    obj.insert("back3", back3);
    return obj;
}
