#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QObject>
#include <windows.h>

//creates a static variable to convert Bytes to Megabytes
#define MB 1048576

class SystemInfo  /*final */: public QObject
{
    Q_OBJECT
public:
    explicit SystemInfo(QObject *parent = nullptr)/* = delete*/;

    // Memory
    static MEMORYSTATUSEX GetMemoryInfo();

    static long GetVirtualMemoryCommited();
    static long GetVirtualMemoryAvailable();
    static long GetPhysicalMemoryUsed();
    static long GetPhysicalMemoryAvailable();
    static long GetPhysicalMemoryLoad();
    static long GetVirtualTotal();
    static long GetPhysicalTotal();

    // CPU
    static unsigned long long FileTimeToInt64(const FILETIME & ft);
    static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);

    static long GetCPULoad();
};

#endif // SYSTEMINFO_H
