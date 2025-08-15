#include "xmlelemcomparetext.h"

bool XmlElemCompareText::compare(const QDomElement &elem1, const QDomElement &elem2)
{
    if(elem1.hasAttributes() || elem2.hasAttributes())
        return true;
    QString text1 = elem1.text();
    QString text2 = elem2.text();
    if (text1 != text2)
        qWarning("XML text '%s' is unequal '%s'", qPrintable(text1), qPrintable(text2));
    return elem1.text() == elem2.text();
}
