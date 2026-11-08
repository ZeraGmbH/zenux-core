#ifndef UTF8DATAVALIDATOR_H
#define UTF8DATAVALIDATOR_H

#include <QByteArray>

class Utf8DataValidator
{
public:
    static bool isValidUtf8(const QByteArray &data);
};

#endif // UTF8DATAVALIDATOR_H
