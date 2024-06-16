#ifndef HARDWARE_INFO_UTILS_H
#define HARDWARE_INFO_UTILS_H

#include <string>
#include <stdexcept>
#include <sstream>

#if defined(_WIN32) || defined (__WIN32__)
#include <windows.h>
#elif defined (__linux__)
#include <fstream>
#endif

namespace hwinfoutils
{
#ifdef __linux__
    inline std::string get_info_from_system_file(const std::string& filename) 
    {
        std::ifstream file(filename);
        std::string line;
        if (file.is_open()) {
            std::getline(file, line);
            file.close();
            return line.substr(line.find(":") + 1);
        }
        return "";
    }
#endif

    //*****************************************
    inline std::string get_os_version() noexcept(false)
    {
#if defined(_WIN32) || defined (__WIN32__)
        std::stringstream ss;
        SYSTEM_INFO sysInfo;
        // Get system information
        GetSystemInfo(&sysInfo);
        
        ss << "Windows " LOBYTE(sysInfo.dwMajorVersion) << "." << HIBYTE(sysInfo.dwMajorVersion);
        return ss.str();
#elif defined(__linux__)
        return get_info_from_system_file("/proc/version");
#endif
    }

    //*****************************************
    inline std::string get_cpu_info() noexcept(false)
    {
        std::stringstream ss;
#if defined(_WIN32) || defined (__WIN32__)
        SYSTEM_INFO sysInfo;
        // Get system information
        GetSystemInfo(&sysInfo);

        ss << sysInfo.dwNumberOfProcessors << " cores, " << sysInfo.dwProcessorSpeed / 1000 << " MHz";
#elif defined(__linux__)
        std::string cpuMhz = get_info_from_system_file("/sys/devices/cpu/cpufreq/cpuinfo_min_freq");
        int numCores = std::stoi(get_info_from_system_file("/proc/cpuinfo").substr(5, 3)); // Assuming 3 chars for core count
        ss << numCores << " cores, " << cpuMhz << " MHz";
#endif
        return ss.str();
    }

    //*****************************************
    inline std::string get_ram_info() noexcept(false)
    {
        std::stringstream ss;
#if defined(_WIN32) || defined (__WIN32__)
        SYSTEM_INFO sysInfo;
        // Get system information
        GetSystemInfo(&sysInfo);
        // Convert RAM size from bytes to Gigabytes
        DWORD ramSizeGb = sysInfo.dwTotalPhysicalMem / (1024 * 1024 * 1024);

        ss << ramSizeGb << " GB RAM";
#elif defined(__linux__)
        ss << get_info_from_system_file("/proc/meminfo") << " RAM";
#endif
        return ss.str();
    }

}

#endif // HARDWARE_INFO_UTILS_H
