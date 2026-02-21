#include "test_crc8_maxim.h"
#include "crc8maxim.h"
#include <QTest>

QTEST_MAIN(test_crc8_maxim)

// compare values caclulated by https://tomeko.net/online_tools/crc8.php
void test_crc8_maxim::value1()
{
    quint8 crc = Crc8Maxim::calcByteCrc(0, 0x42);
    QCOMPARE(crc, 0xFA);
}

void test_crc8_maxim::value2()
{
    quint8 crc = Crc8Maxim::calcByteCrc(0, 0x37);
    QCOMPARE(crc, 0x3D);
}

void test_crc8_maxim::subsequent1()
{
    quint8 data[] = {0x01, 0x02, 0x03, 0x04};
    quint8 crc = Crc8Maxim::calcBlockCrc(data, sizeof(data));
    QCOMPARE(crc, 0xF4);
}

void test_crc8_maxim::subsequent2()
{
    quint8 data[] = {0xA7, 0x42, 0x65, 0x24};
    quint8 crc = Crc8Maxim::calcBlockCrc(data, sizeof(data));
    QCOMPARE(crc, 0xB6);
}
