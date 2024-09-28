#include "system_info_utilities/system_info_utils.hpp"

#include <iostream>

int main()
{
   std::cout << sysinfoutils::get_os_version() << std::endl;
   std::cout << sysinfoutils::get_cpu_info() << std::endl;
   std::cout << sysinfoutils::get_ram_info() << std::endl;

   return EXIT_SUCCESS;
}