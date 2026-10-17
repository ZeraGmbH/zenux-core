#ifndef TEST_XMLSORTEDDUMP_H
#define TEST_XMLSORTEDDUMP_H

#include <QObject>

class test_xmlsorteddump : public QObject
{
    Q_OBJECT
private slots:
    void sortedXmlReordersTagsAndAttributes();
    void sortedXmlReproducibleForDifferentOrders();
    void sortedXmlKeepsAllData();
};

#endif // TEST_XMLSORTEDDUMP_H
