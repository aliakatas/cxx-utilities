cmake_minimum_required(VERSION 3.16)

# Define the preferred order of compilers
set(PREFERRED_CXX_COMPILERS icpx g++ clang++ cl)

# Function to find the first available compiler from the list
function(find_preferred_cxx_compiler)
    foreach(compiler ${PREFERRED_CXX_COMPILERS})
        find_program(CXX_COMPILER_PATH ${compiler})
        if(CXX_COMPILER_PATH)
            set(CMAKE_CXX_COMPILER "${CXX_COMPILER_PATH}" CACHE FILEPATH "C++ compiler" FORCE)
            message(STATUS "Using preferred C++ compiler (path): ${CXX_COMPILER_PATH}")
            message(STATUS "Using preferred C++ compiler: ${CMAKE_CXX_COMPILER}")
            return()
        endif()
    endforeach()
    message(WARNING "None of the preferred C++ compilers were found. Using CMake's default.")
endfunction()

# Call the function to find the preferred compiler
find_preferred_cxx_compiler()

project(cxx-utilities VERSION 1.0.0 LANGUAGES CXX)
set(MODULE_NAME ${PROJECT_NAME})
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# Get the current git hash
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Calculate days since 01-01-2020 using the Python script
execute_process(
    COMMAND python3 ${CMAKE_SOURCE_DIR}/../include/build_utilities/calculate_days.py
    OUTPUT_VARIABLE DAYS_SINCE_2020
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Configure the version header file
configure_file(
    ${CMAKE_SOURCE_DIR}/../include/build_utilities/version_info.hpp.in
    ${CMAKE_BINARY_DIR}/include/version_info.hpp
)
# Configure the module name header file
configure_file(
    ${CMAKE_SOURCE_DIR}/../include/build_utilities/module_name.hpp.in
    ${CMAKE_BINARY_DIR}/include/module_name.hpp
)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create the executable
add_executable(test-build-version-utils "${CMAKE_CURRENT_SOURCE_DIR}/build_version_utils_tests.cxx")
add_executable(test-system-info-utils "${CMAKE_CURRENT_SOURCE_DIR}/system_info_utils_tests.cxx")
add_executable(test-time-utils "${CMAKE_CURRENT_SOURCE_DIR}/time_utils_tests.cxx")
add_executable(test-maths-operations "${CMAKE_CURRENT_SOURCE_DIR}/maths_operations_tests.cxx")

# Link the standard libraries in a platform-independent way
target_link_libraries(test-build-version-utils PRIVATE ${CMAKE_CXX_STANDARD_LIBRARIES})
target_link_libraries(test-system-info-utils PRIVATE ${CMAKE_CXX_STANDARD_LIBRARIES})
target_link_libraries(test-time-utils PRIVATE ${CMAKE_CXX_STANDARD_LIBRARIES})
target_link_libraries(test-maths-operations PRIVATE ${CMAKE_CXX_STANDARD_LIBRARIES})

# Add the include directory to the application's target
target_include_directories(test-build-version-utils PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/../include" 
    "${CMAKE_BINARY_DIR}/include"
)
target_include_directories(test-system-info-utils PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/../include" 
)
target_include_directories(test-time-utils PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/../include" 
)
target_include_directories(test-maths-operations PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/../include" 
)

# Build options
option(BUILD_DEBUG "Build debug version" OFF)

# Set compiler flags based on the compiler and build type
if(MSVC)
    # MSVC compiler flags
    set(COMMON_FLAGS "/W4")
    set(DEBUG_FLAGS "/Od /Zi")
    set(RELEASE_FLAGS "/O2")
else()
    # GCC, Clang, and other compiler flags
    set(COMMON_FLAGS "-Wall -Wextra")
    set(DEBUG_FLAGS "-O0 -g")
    set(RELEASE_FLAGS "-O3")
endif()

if(BUILD_DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} ${DEBUG_FLAGS}")
    target_compile_definitions(test-build-version-utils PRIVATE "_DEBUG")
    target_compile_definitions(test-system-info-utils PRIVATE "_DEBUG")
    target_compile_definitions(test-time-utils PRIVATE "_DEBUG")
    target_compile_definitions(test-maths-operations PRIVATE "_DEBUG")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} ${RELEASE_FLAGS}")
endif()

# Check the compiler and set compiler-specific options
if(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    # Settings for Intel C++ compilers
    # add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # Settings for GNU compilers (e.g., GCC, G++)
    # add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Settings for Microsoft Visual C++ compiler
    # add_compile_options(/W4)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Settings for Clang and AppleClang compilers
    # add_compile_options(-Wall -Wextra -Wpedantic)
else()
    # Settings for other compilers
    message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()