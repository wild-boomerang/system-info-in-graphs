#include "systeminfo.h"

SystemInfo::SystemInfo(QObject *parent) : QObject(parent)
{

}

MEMORYSTATUSEX SystemInfo::GetMemoryInfo()
{
//    Code block initialization for the memory referenced in the Kernel
    MEMORYSTATUSEX memStat;
    memStat.dwLength = sizeof(memStat);
    GlobalMemoryStatusEx(&memStat);

    return memStat;
}

long SystemInfo::GetVirtualMemoryCommited()
{
    return long((GetMemoryInfo().ullTotalPageFile - GetMemoryInfo().ullAvailPageFile) / MB);
}

long SystemInfo::GetVirtualMemoryAvailable()
{
    return long(GetMemoryInfo().ullAvailPageFile / MB);
}

long SystemInfo::GetPhysicalMemoryUsed()
{
    return long((GetMemoryInfo().ullTotalPhys - GetMemoryInfo().ullAvailPhys) / MB);
}

long SystemInfo::GetPhysicalMemoryAvailable()
{
    return long(GetMemoryInfo().ullAvailPhys / MB);
}

long SystemInfo::GetPhysicalMemoryLoad()
{
    return long(GetMemoryInfo().dwMemoryLoad);
}

long SystemInfo::GetVirtualTotal()
{
    return long(GetMemoryInfo().ullTotalPageFile / MB);
}

long SystemInfo::GetPhysicalTotal()
{
    return long(GetMemoryInfo().ullTotalPhys / MB);
}

float SystemInfo::CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
   static unsigned long long _previousTotalTicks = 0;
   static unsigned long long _previousIdleTicks = 0;

   unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
   unsigned long long idleTicksSinceLastTime  = idleTicks - _previousIdleTicks;

   float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? (float(idleTicksSinceLastTime))/totalTicksSinceLastTime : 0);

   _previousTotalTicks = totalTicks;
   _previousIdleTicks  = idleTicks;
   return ret;
}

unsigned long long SystemInfo::FileTimeToInt64(const FILETIME & ft)
{
    return (((unsigned long long)ft.dwHighDateTime) << 32) | ((unsigned long long)ft.dwLowDateTime);
}

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// Measures the load between the previous call and the current one. Returns -1.0 on error.
long SystemInfo::GetCPULoad()
{
   FILETIME idleTime, kernelTime, userTime;

   return GetSystemTimes(&idleTime, &kernelTime, &userTime)
           ? long(CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) * 100)
           : -1.0f;
}
