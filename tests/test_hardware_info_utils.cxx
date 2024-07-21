#include "hardware_info_utils.h"

#include <iostream>

int main()
{
    std::cout << hwinfoutils::get_os_version() << std::endl;
    std::cout << hwinfoutils::get_cpu_info() << std::endl;
    std::cout << hwinfoutils::get_ram_info() << std::endl;

    return EXIT_SUCCESS;
}