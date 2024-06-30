#include "runtime_utils.h"

#include "build_version_utils.h"
#include "hardware_info_utils.h"

#include <ctime>
#include <sstream>
#include <string>

namespace rtu
{
    //=============================================
    std::string get_current_datetime_str(bool use_gmt) 
    {
        auto now = std::time(nullptr);
        char mbstr[100];
        if (use_gmt)
            std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", std::gmtime(&now));
        else 
            std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return std::string(mbstr);
    }

    //=============================================
    std::string create_banner(const std::string& app_name, bool use_gmt)
    {
        std::stringstream ss;
        ss << "Starting " << app_name << " at " << get_current_datetime_str(use_gmt) << "...";
    #ifdef _DEBUG
        ss << "\n  *** DEBUG BUILD - no optimisations ***";
    #endif 
        return ss.str();
    }

    //=============================================
    std::string get_build_info() 
    {
        std::stringstream ss;
        ss << "Build date-time: " << build_info::get_build_date_time() << "\n";
        ss << "Compiler: " << build_info::get_compiler_info();
        return ss.str();
    }

    //=============================================
    std::string get_machine_info()
    {
        std::stringstream ss;
        ss << hwinfoutils::get_os_version() << "\n";
        ss << hwinfoutils::get_cpu_info() << "\n";
        ss << hwinfoutils::get_ram_info();
        return ss.str();
    }
}