#pragma once

#if defined (__WIN32__) || defined(_WIN32)
#include <windows.h>
#define Dlsym(handle, symbol) GetProcAddress(handle, symbol)
#elif defined(__linux__)
#include <dlfcn.h>
#define Dlsym(handle, symbol) dlsym(handle, symbol)
#endif
#include "get_os_error.hxx"

#include <string>
#include <stdexcept>

template <typename func_t>
class FuncLoader
{
public:
   /**
    * @brief Loads a function from a shared library.
    * The shared library must be loaded before calling this.
    * 
    * @param func_name [in] The name of the function to load from the shared library.
    * @param libname [in] The name of the shared library (used for messages only).
    * @param lib_handle [in] The handle for the shared lirbary loaded using the LibLoader.
    * @return The handle for the function to be used later in the program.
    * 
    * @throws Runtime error if the load fails.
    */
#if defined (__WIN32__) || defined(_WIN32)
    static func_t load(const char* func_name, const char* libname, HINSTANCE lib_handle) noexcept(false)
#elif defined(__linux__)
    static func_t load(const char* func_name, const char* libname, void* lib_handle) noexcept(false)
#endif
    {
        func_t l_func = (func_t)Dlsym(lib_handle, func_name);
        if (l_func == nullptr)
        {   // Error handling for symbol resolution
            std::string message = std::string("Failed to load function: ") + std::string(func_name) + std::string(" from ") +
                std::string(libname) + std::string(" (");

            std::string what_happened = get_os_error();

            message += what_happened + std::string(")");

            throw std::runtime_error(message.c_str());
        }
        return l_func;
    }
};

