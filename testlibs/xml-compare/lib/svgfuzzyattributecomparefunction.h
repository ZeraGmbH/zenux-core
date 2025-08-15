#ifndef SVGFUZZYATTRIBUTECOMPAREFUNCTION_H
#define SVGFUZZYATTRIBUTECOMPAREFUNCTION_H

#include <QString>
#include <QList>

class SvgFuzzyAttributeCompareFunction
{
public:
    static bool compareAttribs(const QString& attrib1, const QString& attrib2);

    static QStringList extractFloatsFromAttribs(const QString& attrib);
};

#endif // SVGFUZZYATTRIBUTECOMPAREFUNCTION_H
