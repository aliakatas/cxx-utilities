cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

# Include the compiler selection module
include(CompilerSelection)

# Call the function to find the preferred compiler
find_preferred_cxx_compiler()

project(app-logger VERSION 1.0.0 LANGUAGES CXX)
set(MODULE_NAME ${PROJECT_NAME})
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# Get the current git hash
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Calculate days since 01-01-2020 using the Python script
execute_process(
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/../include/build_utilities/calculate_days.py
    OUTPUT_VARIABLE DAYS_SINCE_2020
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Configure the version header file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/build_utilities/version_info.hpp.in
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_inc/version_info.hpp
)
# Configure the module name header file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/build_utilities/module_name.hpp.in
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_inc/module_name.hpp
)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(BOOST_ROOT "~/Boost/boost_1_86_0-intel/")
set(Boost_NO_SYSTEM_PATHS ON)
find_package(Boost 1.85 REQUIRED COMPONENTS
             log log_setup)

if(NOT Boost_FOUND)
    message( FATAL_ERROR "Boost not found!" )
endif()

# Get the source code files
file(GLOB SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/applogger/*.cxx"
)

# Get the header files
file(GLOB HEADER_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/applogger/*.hxx"
)

# Create the executable
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

message(STATUS "BOOST Include DIRS " ${Boost_INCLUDE_DIRS})

message(STATUS "BOOST LIB DIRS " ${Boost_LIBRARY_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${Boost_LIBRARY_DIRS})

# Link the standard libraries in a platform-independent way
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_CXX_STANDARD_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC 
    boost_log boost_log_setup boost_filesystem 
    boost_thread boost_atomic boost_chrono
)

# Add the include directory to the application's target
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/../include" 
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/applogger"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
    ${Boost_INCLUDE_DIRS}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE "BOOST_LOG_DYN_LINK")

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
    target_compile_definitions(${PROJECT_NAME} PRIVATE "_DEBUG")
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