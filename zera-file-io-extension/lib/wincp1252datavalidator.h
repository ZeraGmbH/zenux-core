#ifndef WINCP1252DATAVALIDATOR_H
#define WINCP1252DATAVALIDATOR_H

#include <QByteArray>

class WinCp1252DataValidator
{
public:
    static bool isValidCp1252(const QByteArray &data);
};

#endif // WINCP1252DATAVALIDATOR_H
