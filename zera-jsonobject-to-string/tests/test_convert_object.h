#ifndef TEST_CONVERT_OBJECT_H
#define TEST_CONVERT_OBJECT_H

#include <QObject>
#include <QJsonObject>

class test_convert_object : public QObject
{
    Q_OBJECT
private slots:
    void exportEmptyObject();
    void exportObjectOneNullValue();
    void exportObjectTwoNullValue();
    void exportObjectTwoNullValueQtCompare();
    void exportObjectTwoEmptyObjects();
    void exportObjectTwoEmptyObjectsQtCompare();
    void exportObjectTwoEmptyArrays();
    void exportObjectTwoEmptyArraysQtCompare();
    void exportObjectTwoArraysOfStrings();
    void exportObjectTwoArraysOfStringsQtCompare();
    void exportObjectArrayWithExponetialDoublesQtCompare();
    void exportObjectOfNestedAll();
    void exportObjectOfNestedAllQtCompare();

private:
    QJsonObject createObjectOfNestedAll();
};

#endif // TEST_CONVERT_OBJECT_H
