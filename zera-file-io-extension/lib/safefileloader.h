#ifndef SAFEFILELOADER_H
#define SAFEFILELOADER_H

#include <QString>

// Intended as gatekeeper for public interfaces this class loads files with
// some safety contraints:
// * Avoid loading files outside base directory
// * Reject hard links
// * Limit file size

class SafeFileLoader
{
public:
    enum LoadResult {
        Ok,
        InvalidFilePath,
        FileNotFound,
        NotARegularFile,
        FileTooLarge,
        CannotOpenFile,
        HardLinkDetected
    };
    static qint64 getDefaultMaxFileSize() { return 1024*100; } // 100K

    static LoadResult readFile(QByteArray &fileDataToLoad,
                               const QString &fileName,
                               const QString &fileDirBasePath, qint64 maxFileSize = getDefaultMaxFileSize());

    static QString stringifyLoadResult(LoadResult result);
};

#endif // SAFEFILELOADER_H
