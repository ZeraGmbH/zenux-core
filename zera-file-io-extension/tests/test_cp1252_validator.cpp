#include "test_cp1252_validator.h"
#include "wincp1252datavalidator.h"
#include <QTest>

QTEST_MAIN(test_cp1252_validator)

void test_cp1252_validator::isValidCp1252Cases_data()
{
    QTest::addColumn<QByteArray>("data");
    QTest::addColumn<bool>("expected");

    QTest::newRow("empty") << QByteArray() << true;
    QTest::newRow("ascii") << QByteArray("plain ascii") << true;

    // Classic Windows ANSI text: German umlauts and sharp s as single bytes.
    QTest::newRow("german umlauts cp1252")
        << QByteArray::fromHex("4765726D616E3A20C4D6DCE4F6FCDF") // "German: Ä Ö Ü ä ö ü ß"
        << true;

    // Bytes that only exist in CP1252, not in Latin-1 — the ones that make
    // this a real Windows check.
    QTest::newRow("euro sign 80") << QByteArray::fromHex("80") << true;
    QTest::newRow("curly quotes 93 94") << QByteArray::fromHex("93Hello94") << true;
    QTest::newRow("em dash 97") << QByteArray::fromHex("419742") << true; // "A—B"

    // A valid UTF-8 sequence is also a valid (but differently decoded) CP1252
    // sequence: C3 A9 is é in UTF-8 but "Ã©" in CP1252. The auto-convert flow
    // resolves this by checking UTF-8 first.
    QTest::newRow("utf8 e-acute c3a9") << QByteArray::fromHex("C3A9") << true;

    // The five undefined bytes of CP1252 — alone...
    QTest::newRow("undefined 81") << QByteArray::fromHex("81") << false;
    QTest::newRow("undefined 8D") << QByteArray::fromHex("8D") << false;
    QTest::newRow("undefined 8F") << QByteArray::fromHex("8F") << false;
    QTest::newRow("undefined 90") << QByteArray::fromHex("90") << false;
    QTest::newRow("undefined 9D") << QByteArray::fromHex("9D") << false;

    // ...and embedded in otherwise valid text.
    QTest::newRow("undefined 81 embedded") << QByteArray::fromHex("4865816C6C6F") // "He\x81llo"
        << false;
}

void test_cp1252_validator::isValidCp1252Cases()
{
    QFETCH(QByteArray, data);
    QFETCH(bool, expected);

    QCOMPARE(WinCp1252DataValidator::isValidCp1252(data), expected);
}
