#ifndef SVGFUZZYATTRIBUTECOMPAREFUNCTION_H
#define SVGFUZZYATTRIBUTECOMPAREFUNCTION_H

#include <QString>

class SvgFuzzyAttributeCompareFunction
{
public:
    static bool compareAttribs(const QString& attrib1, const QString& attrib2);
};

#endif // SVGFUZZYATTRIBUTECOMPAREFUNCTION_H
