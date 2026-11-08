#ifndef TEST_SAFE_FILE_LOADER_H
#define TEST_SAFE_FILE_LOADER_H

#include <QObject>

class test_safe_file_loader : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();

    void readSimpleFile();
    void readFileInSubdirectory();
    void rejectPathReleativeDot();
    void rejectPathReleativeDotDot();
    void rejectAbsoluteFilePaths();
    void rejectSymlinkEscapingBaseDirectory();
    void allowSymlinkInsideBaseDirectory();
    void rejectBrokenSymlink();
    void rejectInteriorTraversal();
    void rejectHardLinkEscapingBaseDirectory();
    void rejectWrongFileName();
    void rejectSubdirectorySelected();
    void rejectEmptyFileName();
    void readAllowedLengthFile();
    void rejectFileTooLarge();
    void rejectFileTooLargeParam();
};

#endif // TEST_SAFE_FILE_LOADER_H
