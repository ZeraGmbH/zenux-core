#include "textencodingconverter.h"
#include "utf8datavalidator.h"
#include "wincp1252datavalidator.h"

// Windows-1252 codepoints for bytes 0x80..0x9F (indexed by byte - 0x80).
// Bytes undefined in CP1252 are zero; they can never reach the table,
// because WinCp1252DataValidator rejects them beforehand.
// see https://www.i18nqa.com/debug/utf8-debug.html
const quint16 win1252HighBytes[] = {
    0x20AC, // 0x80 EURO SIGN
    0x0000, // 0x81 undefined
    0x201A, // 0x82 SINGLE LOW-9 QUOTATION MARK
    0x0192, // 0x83 LATIN SMALL LETTER F WITH HOOK
    0x201E, // 0x84 DOUBLE LOW-9 QUOTATION MARK
    0x2026, // 0x85 HORIZONTAL ELLIPSIS
    0x2020, // 0x86 DAGGER
    0x2021, // 0x87 DOUBLE DAGGER
    0x02C6, // 0x88 MODIFIER LETTER CIRCUMFLEX ACCENT
    0x2030, // 0x89 PER MILLE SIGN
    0x0160, // 0x8A LATIN CAPITAL LETTER S WITH CARON
    0x2039, // 0x8B SINGLE LEFT-POINTING ANGLE QUOTATION MARK
    0x0152, // 0x8C LATIN CAPITAL LIGATURE OE
    0x0000, // 0x8D undefined
    0x017D, // 0x8E LATIN CAPITAL LETTER Z WITH CARON
    0x0000, // 0x8F undefined
    0x0000, // 0x90 undefined
    0x2018, // 0x91 LEFT SINGLE QUOTATION MARK
    0x2019, // 0x92 RIGHT SINGLE QUOTATION MARK
    0x201C, // 0x93 LEFT DOUBLE QUOTATION MARK
    0x201D, // 0x94 RIGHT DOUBLE QUOTATION MARK
    0x2022, // 0x95 BULLET
    0x2013, // 0x96 EN DASH
    0x2014, // 0x97 EM DASH
    0x02DC, // 0x98 SMALL TILDE
    0x2122, // 0x99 TRADE MARK SIGN
    0x0161, // 0x9A LATIN SMALL LETTER S WITH CARON
    0x203A, // 0x9B SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
    0x0153, // 0x9C LATIN SMALL LIGATURE OE
    0x0000, // 0x9D undefined
    0x017E, // 0x9E LATIN SMALL LETTER Z WITH CARON
    0x0178, // 0x9F LATIN CAPITAL LETTER Y WITH DIAERESIS
};

static QString decodeCp1252(const QByteArray &data)
{
    Q_ASSERT(sizeof(win1252HighBytes)/sizeof(quint16) == 0xA0-0x80);
    // fromLatin1 maps byte N to U+00NN; remap the 0x80..0x9F range, where
    // CP1252 deviates from Latin-1.
    QString result = QString::fromLatin1(data);
    for (int i = 0; i < result.size(); ++i) {
        const quint16 codeUnit = result.at(i).unicode();
        if (codeUnit >= 0x80 && codeUnit < 0xA0)
            result[i] = QChar(win1252HighBytes[codeUnit - 0x80]);
    }
    return result;
}

static QString decodeUtf16Payload(const QByteArray &payload, bool littleEndian)
{
    // Decodes the payload following a UTF-16 BOM. If the payload length is odd,
    // decode whole 2-byte units and ignore the stray trailing byte.
    const int units = payload.size() / 2;
    if (littleEndian) {
        // fromUtf16 interprets in host byte order; all supported platforms
        // are little-endian, so the stream can be reinterpreted directly.
        return QString::fromUtf16(reinterpret_cast<const char16_t *>(payload.constData()), units);
    }

    // Qt 6 has no fromUtf16be: swap the byte pairs of the big-endian stream
    // into host (little-endian) order, then reinterpret.
    QByteArray swapped(2 * units, Qt::Uninitialized);
    for (int i = 0; i < units; ++i) {
        swapped[2 * i] = payload.at(2 * i + 1);
        swapped[2 * i + 1] = payload.at(2 * i);
    }
    return QString::fromUtf16(reinterpret_cast<const char16_t *>(swapped.constData()), units);
}

TextEncodingConverter::Result TextEncodingConverter::convert(const QByteArray &data)
{
    // 1. BOM sniffing — a BOM is an authoritative declaration and is honored
    //    unconditionally (no re-validation of the payload).
    // Qt5 & Qt6 docs read:
    // However, invalid sequences are possible with UTF-8 and, if any such are found, they will
    // be replaced with one or more "replacement characters", or suppressed
    // => sane fallback
    if (data.startsWith("\xEF\xBB\xBF"))
        return { QString::fromUtf8(data.mid(3)), Detected::Utf8Bom, true };
    if (data.startsWith("\xFF\xFE"))
        return { decodeUtf16Payload(data.mid(2), true), Detected::Utf16LeBom, true };
    if (data.startsWith("\xFE\xFF"))
        return { decodeUtf16Payload(data.mid(2), false), Detected::Utf16BeBom, true };

    // 2. No BOM: strict UTF-8 first — genuine Windows ANSI files with accented
    //    characters fail this check and fall through to step 3.
    if (Utf8DataValidator::isValidUtf8(data))
        return { QString::fromUtf8(data), Detected::Utf8, true };

    // 3. No BOM: Windows-1252 (classic Western Windows ANSI).
    if (WinCp1252DataValidator::isValidCp1252(data))
        return { decodeCp1252(data), Detected::Cp1252, true };

    // 4. Neither: reject.
    return { QString(), Detected::Undetected, false };
}
