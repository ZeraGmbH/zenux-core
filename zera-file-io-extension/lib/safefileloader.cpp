#include "safefileloader.h"
#include <QFileInfo>
#include <QDir>
#include <sys/stat.h>

SafeFileLoader::LoadResult SafeFileLoader::readFile(QByteArray &fileDataToLoad,
                                                    const QString &fileName,
                                                    const QString &fileDirBasePath, qint64 maxFileSize)
{
    // the file path must be relative to our base directory - no absolute paths allowed
    if (fileName.isEmpty() || fileName.startsWith('/') || QFileInfo(fileName).isAbsolute())
        return InvalidFilePath;

    // no relative paths
    if (fileName.startsWith("."))
        return InvalidFilePath;

    // check non existant & broken symlinks
    const QString fullPath = QDir(fileDirBasePath).absoluteFilePath(fileName);
    const QFileInfo fileInfo(fullPath);
    if (!fileInfo.exists())
        return FileNotFound;

    // catch symbolic links pointing outside of our base directory
    const QString canonicalFile = fileInfo.canonicalFilePath();
    const QString canonicalBase = QFileInfo(fileDirBasePath).canonicalFilePath();
    if (canonicalBase.isEmpty() || !canonicalFile.startsWith(canonicalBase + QDir::separator()))
        return InvalidFilePath;

    if (!fileInfo.isFile())
        return NotARegularFile;

    if (fileInfo.size() > maxFileSize)
        return FileTooLarge;

    QFile file(fullPath);
    if (!file.open(QIODevice::ReadOnly))
        return CannotOpenFile;

    struct stat fileStat;
    if (::fstat(static_cast<int>(file.handle()), &fileStat) != 0)
        return CannotOpenFile;
    if (fileStat.st_nlink > 1)
        return HardLinkDetected;

    fileDataToLoad = file.readAll();
    return Ok;
}

QString SafeFileLoader::stringifyLoadResult(LoadResult result)
{
    switch(result) {
    case Ok:
        return QStringLiteral("Ok");
    case InvalidFilePath:
        return QStringLiteral("ERROR: Invalid file path");
    case FileNotFound:
        return QStringLiteral("ERROR: File not found");
    case NotARegularFile:
        return QStringLiteral("ERROR: Not a regular file");
    case FileTooLarge:
        return QStringLiteral("ERROR: File too large");
    case CannotOpenFile:
        return QStringLiteral("ERROR: cannot open file");
    case HardLinkDetected:
        return QStringLiteral("ERROR: hard link detected");
    }
    return QStringLiteral("Unknown error");
}
