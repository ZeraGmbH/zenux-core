#include "wincp1252datavalidator.h"

bool WinCp1252DataValidator::isValidCp1252(const QByteArray &data)
{
    // Windows-1252 (CP1252) is the classic single-byte ANSI encoding of
    // Western Windows. It maps 251 of the 256 byte values; five bytes in
    // the 0x80..0x9F range are undefined:
    //   0x81, 0x8D, 0x8F, 0x90, 0x9D
    // (Reference: https://en.wikipedia.org/wiki/Windows-1252)
    //
    // Note: unlike the UTF-8 validator, we cannot reuse QTextCodec here —
    // Qt's "windows-1252" codec maps *all* 256 bytes to something (the
    // undefined ones become C1 control characters), so its invalidChars
    // count would always be zero and the check would be vacuous.
    for (const char c : data) {
        switch (static_cast<unsigned char>(c)) {
        case 0x81:
        case 0x8D:
        case 0x8F:
        case 0x90:
        case 0x9D:
            return false;
        default:
            break;
        }
    }
    return true;
}
