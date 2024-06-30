#include "hardware_info_utils.h"
#include "string_utils.h"

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
    //=============================================
    std::string get_os_version() noexcept(false)
    {
#if defined(_WIN32) || defined (__WIN32__)
        std::stringstream ss;
        SYSTEM_INFO sysInfo;
        // Get system information
        GetSystemInfo(&sysInfo);
        
        ss << "Windows " LOBYTE(sysInfo.dwMajorVersion) << "." << HIBYTE(sysInfo.dwMajorVersion);
        return ss.str();
#elif defined(__linux__)
        std::ifstream file("/proc/version_signature");
        std::string line;
        if (file.is_open()) {
            std::getline(file, line);
            file.close();
            return line;
        }
        return "OS not detected";
#endif
    }

    //=============================================
    std::string get_cpu_info() noexcept(false)
    {
#if defined(_WIN32) || defined (__WIN32__)
        std::stringstream ss;
        SYSTEM_INFO sysInfo;
        // Get system information
        GetSystemInfo(&sysInfo);

        ss << sysInfo.dwNumberOfProcessors << " cores, " << sysInfo.dwProcessorSpeed / 1000 << " MHz";
        return ss.str();
#elif defined(__linux__)
        std::ifstream file("/proc/cpuinfo");
        std::string line;
        if (file.is_open()) {
            for (int i = 0; i < 5; ++i)    
                std::getline(file, line);
            file.close();
            return strutils::strip_non_printable(line.substr(line.find(":") + 1));
        }
        return "cpu info not detected";
#endif
    }

    //=============================================
    std::string get_ram_info() noexcept(false)
    {
#if defined(_WIN32) || defined (__WIN32__)
        std::stringstream ss;
        SYSTEM_INFO sysInfo;
        // Get system information
        GetSystemInfo(&sysInfo);
        // Convert RAM size from bytes to Gigabytes
        DWORD ramSizeGb = sysInfo.dwTotalPhysicalMem / (1024 * 1024 * 1024);

        ss << ramSizeGb << " GB RAM";
        return ss.str();
#elif defined(__linux__)
        std::ifstream file("/proc/meminfo");
        std::string line;
        if (file.is_open()) {
            std::getline(file, line);
            file.close();
            return strutils::strip_non_printable(line.substr(line.find(":") + 1));
        }
        return "RAM info not detected";
#endif
    }

}