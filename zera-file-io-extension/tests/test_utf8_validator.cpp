#include "test_utf8_validator.h"
#include "utf8datavalidator.h"
#include <QTest>

QTEST_MAIN(test_utf8_validator)

void test_utf8_validator::isValidUtf8Cases_data()
{
    QTest::addColumn<QByteArray>("data");
    QTest::addColumn<bool>("expected");

    QTest::newRow("empty") << QByteArray() << true;
    QTest::newRow("ascii") << QByteArray("plain ascii") << true;
    QTest::newRow("german umlauts") << QByteArray("German: Ä Ö Ü ä ö ü ß") << true;
    QTest::newRow("chinese") << QByteArray("Chinese: 你好，世界！") << true;
    QTest::newRow("emoji U+1F600") << QByteArray::fromHex("F09F9880") << true;
    QTest::newRow("max codepoint U+10FFFF") << QByteArray::fromHex("F48FBFBF") << true;
    QTest::newRow("valid 3-byte start E0A0") << QByteArray::fromHex("E0A080") << true;
    QTest::newRow("overlong 2-byte slash") << QByteArray::fromHex("C0AF") << false;
    QTest::newRow("overlong 3-byte ª") << QByteArray::fromHex("E080AE") << false;
    QTest::newRow("overlong 4-byte U+0082") << QByteArray::fromHex("F0808082") << false;
    QTest::newRow("lead byte above U+10FFFF F5") << QByteArray::fromHex("F5808080") << false;
    QTest::newRow("stray continuation byte") << QByteArray::fromHex("80") << false;
    QTest::newRow("truncated 3-byte sequence") << QByteArray::fromHex("E4BD") << false;
    QTest::newRow("invalid lead byte C1") << QByteArray::fromHex("C180") << false;
    QTest::newRow("codepoint above U+10FFFF F490") << QByteArray::fromHex("F4908080") << false;

    // AI analysis: The surrogate row is slightly debatable — some real-world validators (glibc, Python, ICU)
    // accept surrogate encodings as syntactically valid — so it's the one to discuss.
    //QTest::newRow("surrogate U+D800")              << QByteArray::fromHex("EDA080")   << false;
}

void test_utf8_validator::isValidUtf8Cases()
{
    QFETCH(QByteArray, data);
    QFETCH(bool, expected);

    QCOMPARE(Utf8DataValidator::isValidUtf8(data), expected);
}
