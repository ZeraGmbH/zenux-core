#ifndef ZENUXDEVICEINFO_H
#define ZENUXDEVICEINFO_H

#include <QString>
class ZenuxDeviceInfo
{
public:
    static QString getZenuxRelease();
    static QString getDeviceNameFromKernelParam();
    static QString getCpuInfo();
};

#endif // ZENUXDEVICEINFO_H
