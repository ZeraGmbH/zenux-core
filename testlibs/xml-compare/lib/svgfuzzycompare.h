#ifndef SVGFUZZYCOMPARE_H
#define SVGFUZZYCOMPARE_H

#include <QString>

class SvgFuzzyCompare
{
public:
    static bool compareXml(const QString &xml1, const QString &xml2);
    // * In case of failure source dump files are overwritten and 'git diff' is your friend
    // * On OE builds change into source directory first e.g.
    //   <your-oe-tmp>/oe-zenux/tmp-glibc/work/cortexa9t2hf-neon-imx-mortsgna-linux-gnueabi/zenux-services/2.0.0+gitAUTOINC+<commit>-r0
    //   and check with 'git diff' there
    static bool compareXmlSrc(const QString &fileNameExpected, const QString &dumped, const QString &sourceFileName);
};

#endif // SVGFUZZYCOMPARE_H
