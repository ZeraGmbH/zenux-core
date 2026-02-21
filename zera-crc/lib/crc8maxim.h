#ifndef CRC8MAXIM_H
#define CRC8MAXIM_H

#include <QtGlobal>

/**
  @brief
  Crc8Maxim is a class to support crc generation introduced from MAXIM for 1 wire connections.
  crc is calculated with polynomial = x^8 + x^5 + x^4 + 1
  */
class Crc8Maxim
{
public:
    static quint8 calcBlockCrc(const quint8* block, quint32 blocklen);
    static quint8 calcByteCrc(quint8 crc, quint8 data);
};

#endif // CRC8MAXIM_H
