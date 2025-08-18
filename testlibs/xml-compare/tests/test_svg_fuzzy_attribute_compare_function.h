#ifndef TEST_SVG_FUZZY_ATTRIBUTE_COMPARE_FUNCTION_H
#define TEST_SVG_FUZZY_ATTRIBUTE_COMPARE_FUNCTION_H

#include <QObject>

class test_svg_fuzzy_attribute_compare_function : public QObject
{
    Q_OBJECT
private slots:
    void passOnAnyEquals();
    void unequalNoValuesFails();
    void unequalCountOfNumbersFailsWithSpecialWarning();
    void extractNumbers();
    void extractSingleNumber(); // Is this a valid case?
    void conversionToDoubleFails();
    void withinAcceptableLimit();
    void outofAcceptableLimit();
    void extraLettersChange();
};

#endif // TEST_SVG_FUZZY_ATTRIBUTE_COMPARE_FUNCTION_H
