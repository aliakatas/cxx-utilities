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
set(VERSION_PATCH 3)

# Get the current git hash
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Calculate days since 01-01-2020 using the Python script
execute_process(
    COMMAND python3 ${CMAKE_SOURCE_DIR}/utils/calculate_days.py
    OUTPUT_VARIABLE DAYS_SINCE_2020
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Configure the version header file
configure_file(
    ${CMAKE_SOURCE_DIR}/include/version_info.h.in
    ${CMAKE_BINARY_DIR}/include/version_info.h
)
# Configure the module name header file
configure_file(
    ${CMAKE_SOURCE_DIR}/include/module_name.h.in
    ${CMAKE_BINARY_DIR}/include/module_name.h
)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
message(STATUS "Include dir: ${INCLUDE_DIR}")
# set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
# message(STATUS "Source dir: ${SOURCE_DIR}")

# # Define the executable sources
# file(GLOB EXECUTABLE_SOURCES 
#     "${SOURCE_DIR}/*.cpp" 
#     "${SOURCE_DIR}/*.cxx"
#     "${CMAKE_CURRENT_SOURCE_DIR}/cxx-utilities/src/*.cpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/cxx-utilities/src/*.cxx"
#     )

# # Define the executable headers
# file(GLOB EXECUTABLE_HEADERS 
#     "${INCLUDE_DIR}/*.h" 
#     "${INCLUDE_DIR}/*.hpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/cxx-utilities/include/*.h"
#     "${CMAKE_CURRENT_SOURCE_DIR}/cxx-utilities/include/*.hpp"
#     )

# Create the executable
add_executable(test-build-version-utils tests/test_build_version_utils.cxx)
add_executable(test-hardware-info-utils tests/test_hardware_info_utils.cxx)

# Link the standard libraries in a platform-independent way
target_link_libraries(test-build-version-utils PRIVATE ${CMAKE_CXX_STANDARD_LIBRARIES})
target_link_libraries(test-hardware-info-utils PRIVATE ${CMAKE_CXX_STANDARD_LIBRARIES})

# Add the include directory to the application's target
target_include_directories(test-build-version-utils PUBLIC 
    "${INCLUDE_DIR}" 
    "${CMAKE_BINARY_DIR}/include"
)
target_include_directories(test-hardware-info-utils PUBLIC 
    "${INCLUDE_DIR}" 
    "${CMAKE_BINARY_DIR}/include"
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
    target_compile_definitions(test-hardware-info-utils PRIVATE "_DEBUG")
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