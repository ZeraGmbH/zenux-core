#include "test_xmlconfigreader.h"
#include <xmlconfigreader.h>
#include <QTest>

QTEST_MAIN(test_xmlconfigreader)

static const QString xmlPath = QStringLiteral(TESTLIB_FILES_PATH) + QStringLiteral("/xmls/");
static const QString xsdPath = QStringLiteral(TESTLIB_FILES_PATH) + QStringLiteral("/schemas/");

void test_xmlconfigreader::initTestCase()
{
    Q_INIT_RESOURCE(test_data);
}

void test_xmlconfigreader::schemaFound()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(xsdPath + "with-complex.xsd"));
}

void test_xmlconfigreader::schemaFoundResource()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(":/schemas/with-complex.xsd"));
}

void test_xmlconfigreader::schemaNotFound()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(!reader.loadSchema(":/schemas/foo.xsd"));
}

void test_xmlconfigreader::validPairSchemaXmlResourceFile()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(":/schemas/with-complex.xsd"));
    QVERIFY(reader.loadXMLFile(":/xmls/with-complex-valid.xml"));
}

void test_xmlconfigreader::validPairSchemaXmlFile()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(":/schemas/with-complex.xsd"));
    QVERIFY(reader.loadXMLFile(xmlPath + "with-complex-valid.xml"));
}

void test_xmlconfigreader::invalidNoSchema()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(!reader.loadXMLFile(":/xmls/with-complex-valid.xml"));
}

void test_xmlconfigreader::invalidIP()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(":/schemas/with-complex.xsd"));
    QVERIFY(!reader.loadXMLFile(xmlPath + "with-complex-invalid-ip.xml"));
}

void test_xmlconfigreader::invalidYesNo()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(":/schemas/with-complex.xsd"));
    QVERIFY(!reader.loadXMLFile(xmlPath + "with-complex-invalid-yes-no.xml"));
}

void test_xmlconfigreader::invalidKeySequence()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(":/schemas/with-complex.xsd"));
    QVERIFY(!reader.loadXMLFile(xmlPath + "with-complex-invalid-sequence.xml"));
}

void test_xmlconfigreader::setGetValidIp()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(":/schemas/with-complex.xsd"));
    QVERIFY(reader.loadXMLFile(":/xmls/with-complex-valid.xml"));
    QString newIp = "192.168.2.5";
    QString xml = "testvals:ethernet:ip";
    QVERIFY(reader.setValue(xml, newIp));
    QCOMPARE(reader.getValue(xml), newIp);
}

void test_xmlconfigreader::setGetValidYesNoShouldNotWorkOnInvalid()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(":/schemas/with-complex.xsd"));
    QVERIFY(reader.loadXMLFile(":/xmls/with-complex-valid.xml"));
    QString newYesNoInvalid = "2";
    QString xml = "testvals:yesno";
    QVERIFY(reader.setValue(xml, newYesNoInvalid));
    QCOMPARE(reader.getValue(xml), newYesNoInvalid);
}

void test_xmlconfigreader::setWithInvalidKey()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(":/schemas/with-complex.xsd"));
    QVERIFY(reader.loadXMLFile(":/xmls/with-complex-valid.xml"));
    QString newYesNoInvalid = "0";
    QString xml = "testvals:foo";
    QVERIFY(!reader.setValue(xml, newYesNoInvalid));
}

void test_xmlconfigreader::loadAndModifyExportSequenceOfFields()
{
    Zera::XMLConfig::cReader reader;
    QVERIFY(reader.loadSchema(":/schemas/with-complex.xsd"));
    QString xmlPath = ":/xmls/with-complex-valid.xml";
    QVERIFY(reader.loadXMLFile(xmlPath));
    QString oldIp = "1.2.3.4";
    QString newIp = "192.168.2.5";
    QString xml = "testvals:ethernet:ip";
    QVERIFY(reader.setValue(xml, newIp));

    QString xmlRead = reader.getXMLConfig().simplified().remove(' ');

    QFile xmlFile(xmlPath);
    xmlFile.open(QFile::ReadOnly);
    QString xmlOrig = QString(xmlFile.readAll()).simplified().remove(' ');
    QVERIFY(xmlRead != xmlOrig);

    QString xmlOrigManModify = xmlOrig.replace(oldIp, newIp);
    QCOMPARE(xmlRead, xmlOrigManModify);
}

