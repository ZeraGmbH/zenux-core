#ifndef TEST_TEXT_ENCODING_CONVERTER_H
#define TEST_TEXT_ENCODING_CONVERTER_H

#include <QObject>

class test_text_encoding_converter : public QObject
{
    Q_OBJECT
private slots:
    void convertCases_data();
    void convertCases();
};

#endif // TEST_TEXT_ENCODING_CONVERTER_H
