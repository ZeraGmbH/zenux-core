#ifndef SVGFUZZYCOMPARE_H
#define SVGFUZZYCOMPARE_H

#include <QString>

class SvgFuzzyCompare
{
public:
    bool compareXml(QString xml1, QString xml2, bool fatalOnInvalidXml=false);
};

#endif // SVGFUZZYCOMPARE_H
