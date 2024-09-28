#include "build_utilities/build_version_utils.hpp"

#include <iostream>

int main()
{
   std::cout << build_info::get_app_name() << std::endl;
   std::cout << build_info::get_build_date_time() << std::endl;
   std::cout << build_info::get_compiler_info() << std::endl;
   std::cout << build_info::get_nvidia_cuda_version() << std::endl;
   std::cout << build_info::get_version() << std::endl;

   return EXIT_SUCCESS;
}