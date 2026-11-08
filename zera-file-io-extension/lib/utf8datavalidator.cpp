#include "utf8datavalidator.h"
#include <QTextCodec>

bool Utf8DataValidator::isValidUtf8(const QByteArray &data)
{
    // Stolen from: https://stackoverflow.com/questions/18227530/check-if-utf-8-string-is-valid-in-qt
    QTextCodec::ConverterState state;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    codec->toUnicode(data.constData(), data.size(), &state);
    if (state.invalidChars > 0)
        return false;

    // This was AI generated and the code above accepts truncated 3byte sequences. So
    // trust for now.
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
