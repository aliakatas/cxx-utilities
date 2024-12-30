cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

# Include the compiler selection module
include(CompilerSelection)

# Call the function to find the preferred compiler
find_preferred_cxx_compiler()

project(app-logger-test VERSION 1.0.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Get the source code files
file(GLOB SOURCE_FILES
  "${CMAKE_SOURCE_DIR}/*.cxx"
)

# Add the shared library
#add_subdirectory("${CMAKE_SOURCE_DIR}/../../AppLogger")
# this does not work as it is out-of-tree...

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link the standard libraries in a platform-independent way
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CXX_STANDARD_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE app-logger)

# Add the include directory to the application's target
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${CMAKE_SOURCE_DIR}/../../include/" 
)

# Add the library directory
target_link_directories(${PROJECT_NAME} PUBLIC 
   "${CMAKE_SOURCE_DIR}/../../AppLogger/build" 
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