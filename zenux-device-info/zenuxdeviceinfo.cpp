#include "zenuxdeviceinfo.h"
#include <QFile>
#include <QTextStream>

QString ZenuxDeviceInfo::getZenuxRelease()
{
    QString path = "/opt/zera/conf/CHANGELOG";
    QString releaseNr = "";
    QFile file(path);
    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        int start, end;
        QString line;
        bool releaseNrFound = false;
        do {
            line = stream.readLine();
            if ((start = line.indexOf("'release-")+1) > 0 ||
                (start = line.indexOf("'snapshot-")+1) > 0 ||
                (start = line.indexOf("'no-release-")+1) > 0) {
                end = line.indexOf("'", start);
                releaseNrFound = end > start;
                if (releaseNrFound)
                    releaseNr = line.mid(start, end-start);
            }
        } while (!line.isNull() && !(releaseNrFound));
        file.close();
    }
    return releaseNr;
}

QString ZenuxDeviceInfo::getDeviceNameFromKernelParam()
{
    QString zenuxDevice;
    QString procKernelParamFilename = QStringLiteral("/proc/cmdline");
    QFile file(procKernelParamFilename);
    if(file.open(QIODevice::ReadOnly)) {
        const QStringList kernelParams = QString::fromLatin1(file.readAll()).split(QStringLiteral(" "));
        QString paramSearch = QStringLiteral("zera_device=");
        for(auto param : kernelParams) {
            if(param.contains(paramSearch)) {
                zenuxDevice = param.replace(paramSearch, QString()).trimmed();
                break;
            }
        }
        file.close();
    }
    return zenuxDevice;
}

QString ZenuxDeviceInfo::getCpuInfo()
{
    QString cpuInfo;
    QString eepromDumpFile = QStringLiteral("/tmp/varsom-eeprom.dump");
    QFile file(eepromDumpFile);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray eepromDump = file.readAll();
        file.close();
        // valid dump?
        if(eepromDump.count() >= 64 && eepromDump.left(4) == QByteArray("WARI")) {
            // structure taken from u-boot-variscite / mx6var_eeprom_v1.h
            QString partNumber = eepromDump.mid(4, 16);
            QString assembly = eepromDump.mid(20, 16);
            QString date = eepromDump.mid(36, 16);
            //int version = eepromDump.at(52);
            cpuInfo = QString("{\"PartNumber\":\"%1\",\"Assembly\":\"%2\",\"Date\":\"%3\"}").arg(partNumber).arg(assembly).arg(date);
        }
    }
    return cpuInfo;
}
