#ifndef SVGFUZZYCOMPARE_H
#define SVGFUZZYCOMPARE_H

#include <QString>

class SvgFuzzyCompare
{
public:
    static bool compareXml(const QString &xml1, const QString &xml2);
};

#endif // SVGFUZZYCOMPARE_H
