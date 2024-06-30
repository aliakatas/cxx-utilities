#ifndef HARDWARE_INFO_UTILS_H
#define HARDWARE_INFO_UTILS_H

#include <string>

namespace hwinfoutils
{
    /**
     * @brief Returns the version of the OS.
     * 
     * @return std::string
     */
    std::string get_os_version() noexcept(false);
    
    /**
     * @brief Returns the CPU make and model.
     * 
     * @return std::string
     */
    std::string get_cpu_info() noexcept(false);

    /**
     * @brief Returns the total amount of RAM.
     * 
     * @return std::string
     */
    std::string get_ram_info() noexcept(false);
    
}

#endif // HARDWARE_INFO_UTILS_H
