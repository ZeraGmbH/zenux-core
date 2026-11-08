#include "utf8datavalidator.h"

bool Utf8DataValidator::isValidUtf8(const QByteArray &data)
{
    // UTF-8 validation: rejects overlong encodings, codepoints above
    // U+10FFFF, stray continuation bytes and truncated sequences.
    // Deliberately accepts surrogate encodings (U+D800..U+DFFF, e.g. ED A0 80),
    // which RFC 3629 forbids: such files are still salvaged by
    // QString::fromUtf8 (which replaces them with U+FFFD), which yields
    // better results than falling through to CP1252 in the converter
    // pipeline. See the test rows in test_utf8_validator.cpp.
    const auto *p = reinterpret_cast<const unsigned char*>(data.constData());
    const int n = data.size();
    int i = 0;
    while (i < n) {
        const unsigned char c = p[i];
        int trailingBytes;
        if (c <= 0x7F)
            trailingBytes = 0;
        else if ((c & 0xE0) == 0xC0) {
            trailingBytes = 1;
            if (c < 0xC2) // overlong encoding of ascii character
                return false;
        }
        else if ((c & 0xF0) == 0xE0) {
            trailingBytes = 2;
            if (c == 0xE0 && i + 1 < n && p[i + 1] < 0xA0) // overlong encoding of U+0080..U+07FF
                return false;
        }
        else if ((c & 0xF8) == 0xF0) {
            trailingBytes = 3;
            if (c > 0xF4) // above U+10FFFF
                return false;
            if (c == 0xF4 && i + 1 < n && p[i + 1] > 0x8F) // above U+10FFFF
                return false;
            if (c == 0xF0 && i + 1 < n && p[i + 1] < 0x90) // overlong encoding of U+1000..U+3FFF
                return false;
        }
        else
            return false; // continuation byte without leading byte or invalid leading byte

        for (int j = 1; j <= trailingBytes; ++j) {
            if (i + j >= n || (p[i + j] & 0xC0) != 0x80)
                return false;
        }
        i += trailingBytes + 1;
    }
    return true;
}
