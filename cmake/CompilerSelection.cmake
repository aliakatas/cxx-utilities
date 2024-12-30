# Guard against multiple inclusion
if(DEFINED COMPILER_SELECTION_INCLUDED)
    return()
endif()
set(COMPILER_SELECTION_INCLUDED TRUE)

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