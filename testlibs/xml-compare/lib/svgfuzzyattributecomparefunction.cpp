#include "svgfuzzyattributecomparefunction.h"
#include <math.h>

bool SvgFuzzyAttributeCompareFunction::compareAttribs(const QString &attrib1, const QString &attrib2)
{
    if (attrib1 == attrib2)
        return true;
    AttribExtract extract1 = extractFloatsFromAttribs(attrib1);
    AttribExtract extract2 = extractFloatsFromAttribs(attrib2);
    if (extract1.letters != extract2.letters) {
        qWarning("Removed letters in XML attributes are unequal in '%s' and '%s'", qPrintable(attrib1), qPrintable(attrib2));
        return false;
    }
    if (extract1.valuesExtracted.count() != extract2.valuesExtracted.count()) {
        qWarning("Number of values in XML attributes are unequal in '%s' and '%s'", qPrintable(attrib1), qPrintable(attrib2));
        return false;
    }
    if (extract1.valuesExtracted.isEmpty()) {
        qWarning("Fuzzy compare not possible on XML attribute '%s' / '%s'", qPrintable(attrib1), qPrintable(attrib2));
        return false;
    }
    for (int i=0; i<extract1.valuesExtracted.count(); i++) {
        const QString valueStr1 = extract1.valuesExtracted[i];
        const QString valueStr2 = extract2.valuesExtracted[i];
        if (valueStr1 == valueStr2)
            continue;

        bool conversionOk1 = true;
        bool conversionOk2 = true;
        const double value1 = valueStr1.toDouble(&conversionOk1);
        const double value2 = valueStr2.toDouble(&conversionOk2);
        if (!conversionOk1 || !conversionOk2) {
            qWarning("Cannot convert to double in XML attribute '%s' / '%s'", qPrintable(attrib1), qPrintable(attrib2));
            qWarning("Extend SvgFuzzyAttributeCompareFunction?");
            return false;
        }

        const double deviation = fabs(1-value1/value2);
        if (deviation > 0.0001) { // highest seen by just changing dev host was 1.7e-5
            qWarning("Deviation %f too high in XML attribute '%s' / '%s'",
                     deviation, qPrintable(attrib1), qPrintable(attrib2));
            return false;
        }
    }
    return true;
}

SvgFuzzyAttributeCompareFunction::AttribExtract SvgFuzzyAttributeCompareFunction::extractFloatsFromAttribs(const QString &attrib)
{
    QString attribStripped;
    AttribExtract extract;
    for (int i=0; i<attrib.size(); i++) {
        const QChar &ch = attrib[i];
        if (ch.isLetter())
            extract.letters.append(ch);
        else
            attribStripped.append(ch);
    }

    const QStringList valuePairs = attribStripped.split(" ", Qt::SkipEmptyParts);
    for (const QString &valuePair : valuePairs) {
        const QStringList splittedPair = valuePair.split(",", Qt::SkipEmptyParts);
        for (const QString &splitted : splittedPair)
            extract.valuesExtracted.append(splitted);
    }
    return extract;
}
