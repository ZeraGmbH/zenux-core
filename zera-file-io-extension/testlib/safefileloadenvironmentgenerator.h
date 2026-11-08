#ifndef SAFEFILELOADENVIRONMENTGENERATOR_H
#define SAFEFILELOADENVIRONMENTGENERATOR_H

#include <QString>

class SafeFileLoadEnvironmentGenerator
{
public:
    // the following files/softlinks are created:
    // root
    //   outside.txt
    //   inside
    //     subdir
    //       nested.txt
    //     big.bin
    //     too-big.bin
    //     broken-link (-> missing-target)
    //     hello.txt
    //     hardlink-out (hard link -> ../outside.txt)
    //     link-in (-> subdir/nested.txt)
    //     link-out (-> ../outside.txt)
    static void createTestFileStructure();
    static void cleanup();

    static QString getInsidePath();
    static QString getOutsideFilePath();

    static QString getSimpleTextFileName();
    static QString getSimpleTextFileContent();

    static QString getSubDirName();
    static QString getSubDirFileName();
    static QString getSubdirFileContent();

    static QString getBigFileName();
    static QString getTooBigFileName();

    static QString getLinkInsideFileName();
    static QString getLinkOutsideFileName();
    static QString getBrokenLinkFileName();

    static QString getHardLinkOutsideFileName();

private:
    static QString getRootPath();
    static QString getSimpleTextFilePath();
    static QString getOutsideRelFilePath();
    static QString getSubdirFilePath();
    static QString getBigFilePath();
    static QString getTooBigFilePath();
    static QString getLinkInsidePath();
    static QString getLinkOutsidePath();
    static QString getBrokenLinkPath();
    static QString getHardLinkOutsidePath();
};

#endif // SAFEFILELOADENVIRONMENTGENERATOR_H
