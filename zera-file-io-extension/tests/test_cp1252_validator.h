#ifndef TEST_CP1252_VALIDATOR_H
#define TEST_CP1252_VALIDATOR_H

#include <QObject>

class test_cp1252_validator : public QObject
{
    Q_OBJECT
private slots:
    void isValidCp1252Cases_data();
    void isValidCp1252Cases();
};

#endif // TEST_CP1252_VALIDATOR_H
