#ifndef TEST_CRC8_MAXIM_H
#define TEST_CRC8_MAXIM_H

#include <QObject>

class test_crc8_maxim : public QObject
{
    Q_OBJECT
private slots:
    void value1();
    void value2();
    void subsequent1();
    void subsequent2();
};

#endif // TEST_CRC8_MAXIM_H
