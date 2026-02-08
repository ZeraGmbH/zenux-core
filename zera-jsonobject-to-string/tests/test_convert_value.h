#ifndef TEST_CONVERT_VALUE_H
#define TEST_CONVERT_VALUE_H

#include <QObject>

class test_convert_value : public QObject
{
    Q_OBJECT
private slots:
    void exportString();
    void exportBool();
    void exportNull();
    void exportNumber();
};

#endif // TEST_CONVERT_VALUE_H
