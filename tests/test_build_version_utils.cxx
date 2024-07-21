#include "build_version_utils.h"

#include <iostream>

int main()
{
    std::cout << build_info::get_build_date_time() << std::endl;
    std::cout << build_info::get_compiler_info() << std::endl;
    std::cout << build_info::get_nvidia_cuda_version() << std::endl;
    std::cout << build_info::get_version() << std::endl;

    return EXIT_SUCCESS;
}