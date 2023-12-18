#ifndef TEST_XMLCONFIGREADER_H
#define TEST_XMLCONFIGREADER_H

#include <QObject>

class test_xmlconfigreader : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    void schemaFound();
    void schemaFoundResource();
    void schemaNotFound();
    void validPairSchemaXmlResourceFile();
    void validPairSchemaXmlFile();
    void invalidNoSchema();

    void invalidIP();
    void invalidYesNo();
    void invalidKeySequence();

    void setGetValidIp();
    void setGetValidYesNoShouldNotWorkOnInvalid(); // how can we fix this???

    void setWithInvalidKey();

    void loadAndModifyExportSequenceOfFields();
};

#endif // TEST_XMLCONFIGREADER_H
