#ifndef TEXTENCODINGCONVERTER_H
#define TEXTENCODINGCONVERTER_H

#include <QByteArray>
#include <QString>
#include <QMetaType>

// Decodes raw text file data into a QString, determining the encoding.
// Pipeline:
//   1. BOM sniffing (EF BB BF / FF FE / FE FF) — a BOM is an authoritative
//      declaration and is honored unconditionally.
//   2. No BOM: strict UTF-8 (Utf8DataValidator) -> QString::fromUtf8.
//   3. No BOM, not UTF-8: Windows-1252 (WinCp1252DataValidator) -> CP1252 decode.
//   4. Neither: rejected (ok == false, encoding == Undetected).
class TextEncodingConverter
{
public:
    enum class Detected
    {
        Utf8Bom,     // EF BB BF BOM, payload decoded as UTF-8
        Utf16LeBom,  // FF FE BOM, payload decoded as UTF-16 Little Endian
        Utf16BeBom,  // FE FF BOM, payload decoded as UTF-16 Big Endian
        Utf8,        // no BOM, validated as strict UTF-8
        Cp1252,      // no BOM, validated as Windows-1252
        Undetected   // only ever reported together with ok == false
    };

    struct Result
    {
        QString text;
        Detected encoding = Detected::Undetected;
        bool ok = false;
    };

    static Result convert(const QByteArray &data);
};

Q_DECLARE_METATYPE(TextEncodingConverter::Detected)

#endif // TEXTENCODINGCONVERTER_H
