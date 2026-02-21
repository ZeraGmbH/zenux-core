#include "crc8maxim.h"

quint8 Crc8Maxim::calcBlockCrc(const quint8 *pBuff, quint32 iBuffLen)
{
    quint8 crc = 0;
    for (quint32 i = 0; i < iBuffLen; i++)
        crc = calcByteCrc(crc, pBuff[i]);
    return crc;
}

quint8 Crc8Maxim::calcByteCrc(quint8 crc, quint8 data)
{
    crc = crc ^ data;
    for (quint8 i = 0; i < 8; i++) {
        if (crc & 0x01)
            crc = (crc >> 1) ^ 0x8c;
        else
            crc >>= 1;
    }
    return crc;
}
