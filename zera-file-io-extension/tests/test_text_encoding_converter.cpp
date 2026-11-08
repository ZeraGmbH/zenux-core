#include "test_text_encoding_converter.h"
#include "textencodingconverter.h"
#include <QTest>

QTEST_MAIN(test_text_encoding_converter)

void test_text_encoding_converter::convertCases_data()
{
    QTest::addColumn<QByteArray>("data");
    QTest::addColumn<QString>("expectedText");
    QTest::addColumn<TextEncodingConverter::Detected>("expectedEncoding");
    QTest::addColumn<bool>("expectedOk");

    // --- no BOM -----------------------------------------------------------

    QTest::newRow("empty")
        << QByteArray() << QString() << TextEncodingConverter::Detected::Utf8 << true;
    QTest::newRow("ascii no bom")
        << QByteArray("plain ascii") << QString("plain ascii")
        << TextEncodingConverter::Detected::Utf8 << true;

    // é in UTF-8 (C3 A9) is also a valid CP1252 sequence ("Ã©"); the pipeline
    // must resolve the ambiguity in favor of UTF-8.
    QTest::newRow("utf8 no bom e-acute")
        << QByteArray::fromHex("C3A9") << QString("é")
        << TextEncodingConverter::Detected::Utf8 << true;

    // Classic Windows ANSI text: German umlauts and sharp s as single bytes.
    QTest::newRow("cp1252 umlauts")
        << QByteArray::fromHex("4765726D616E3A20C4D6DCE4F6FCDF") // "German: ÄÖÜäöüß"
        << QString("German: ") + QString::fromLatin1("\xC4\xD6\xDC\xE4\xF6\xFC\xDF") // "ÄÖÜäöüß"
        << TextEncodingConverter::Detected::Cp1252 << true;
    QTest::newRow("cp1252 euro sign")
        << QByteArray::fromHex("80") << QString("€")
        << TextEncodingConverter::Detected::Cp1252 << true;
    QTest::newRow("cp1252 curly quotes")
        << QByteArray::fromHex("91486992") // 0x91 = U+2018, 0x92 = U+2019
        << QString(QChar(0x2018)) + "Hi" + QString(QChar(0x2019)) // "'Hi'"
        << TextEncodingConverter::Detected::Cp1252 << true;
    QTest::newRow("cp1252 em dash")
        << QByteArray::fromHex("419742")
        << "A" + QString(QChar(0x2014)) + "B" // "A—B"
        << TextEncodingConverter::Detected::Cp1252 << true;

    // --- rejected (neither valid UTF-8 nor valid CP1252) ------------------

    QTest::newRow("rejected undefined cp1252 byte")
        << QByteArray::fromHex("81") << QString()
        << TextEncodingConverter::Detected::Undetected << false;
    // E4 81: truncated 3-byte UTF-8 sequence (invalid UTF-8) and 0x81 is
    // undefined in CP1252 — so neither validator accepts it.
    QTest::newRow("rejected truncated utf8 with undefined cp1252 byte")
        << QByteArray::fromHex("E481") << QString()
        << TextEncodingConverter::Detected::Undetected << false;

    // --- BOMs ---------------------------------------------------------------

    // BOM inputs are built from short, individually verified hex pieces to
    // avoid typos in long literals (each piece checked against a probe).
    const QByteArray utf8Bom = QByteArray::fromHex("EFBBBF");   // EF BB BF
    const QByteArray utf16LeBom = QByteArray::fromHex("FFFE");  // FF FE
    const QByteArray utf16BeBom = QByteArray::fromHex("FEFF");  // FE FF

    QTest::newRow("utf8 bom e-acute")
        << utf8Bom + QByteArray::fromHex("C3A9") << QString("é")
        << TextEncodingConverter::Detected::Utf8Bom << true;
    QTest::newRow("utf8 bom only")
        << utf8Bom << QString()
        << TextEncodingConverter::Detected::Utf8Bom << true;

    // A BOM is an authoritative declaration: even a malformed payload is
    // decoded as declared, with Qt substituting U+FFFD for the bad sequence.
    QTest::newRow("utf8 bom truncated payload")
        << utf8Bom + QByteArray::fromHex("C3") << QString(QChar(0xFFFD))
        << TextEncodingConverter::Detected::Utf8Bom << true;

    // --- UTF-16 BOM ----------------------------------------------------------

    QTest::newRow("utf16le bom ascii")
        << utf16LeBom + QByteArray::fromHex("48006900") << QString("Hi")
        << TextEncodingConverter::Detected::Utf16LeBom << true;
    QTest::newRow("utf16le bom umlaut")
        << utf16LeBom + QByteArray::fromHex("C400") << QString("Ä")
        << TextEncodingConverter::Detected::Utf16LeBom << true;

    // Odd payload length: whole 2-byte units are decoded, the stray trailing
    // byte is ignored.
    QTest::newRow("utf16le bom odd payload")
        << utf16LeBom + QByteArray::fromHex("480069") << QString("H")
        << TextEncodingConverter::Detected::Utf16LeBom << true;

    QTest::newRow("utf16be bom ascii")
        << utf16BeBom + QByteArray::fromHex("00480069") << QString("Hi")
        << TextEncodingConverter::Detected::Utf16BeBom << true;
}

void test_text_encoding_converter::convertCases()
{
    QFETCH(QByteArray, data);
    QFETCH(QString, expectedText);
    QFETCH(TextEncodingConverter::Detected, expectedEncoding);
    QFETCH(bool, expectedOk);

    const TextEncodingConverter::Result result = TextEncodingConverter::convert(data);

    QCOMPARE(result.ok, expectedOk);
    QCOMPARE(result.encoding, expectedEncoding);
    QCOMPARE(result.text, expectedText);
}
