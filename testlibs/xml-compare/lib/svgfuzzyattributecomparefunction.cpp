#include "svgfuzzyattributecomparefunction.h"

bool SvgFuzzyAttributeCompareFunction::compareAttribs(const QString &attrib1, const QString &attrib2)
{
    bool ok = attrib1 == attrib2;
    if(!ok)
        qWarning("XML attribute '%s' is unequal '%s'", qPrintable(attrib1), qPrintable(attrib2));
    return ok;
}
