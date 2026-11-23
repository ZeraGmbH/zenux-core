#include "xmlelemcomparetext.h"

// QDomElement::text() returns the text of all descendant elements concatenated in document order.
// That concatenation changes whenever sibling elements are reordered, which would make the
// comparison depend on tag sequence. Only compare the element's own (direct) text nodes;
// child elements are compared individually by XmlDocumentCompare::compareAllElems' iteration.
static QString directText(const QDomElement &elem)
{
    QString ret;
    for(QDomNode node = elem.firstChild(); !node.isNull(); node = node.nextSibling()) {
        if(node.isText())
            ret += node.toText().data();
    }
    return ret;
}

bool XmlElemCompareText::compare(const QDomElement &elem1, const QDomElement &elem2)
{
    QString text1 = directText(elem1);
    QString text2 = directText(elem2);
    if (text1 != text2)
        qWarning("XML text '%s' is unequal '%s'", qPrintable(text1), qPrintable(text2));
    return text1 == text2;
}
