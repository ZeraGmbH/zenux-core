#ifndef TEST_UTF8_VALIDATOR_H
#define TEST_UTF8_VALIDATOR_H

#include <QObject>

class test_utf8_validator : public QObject
{
    Q_OBJECT
private slots:
    void isValidUtf8Cases_data();
    void isValidUtf8Cases();
};

#endif // TEST_UTF8_VALIDATOR_H
