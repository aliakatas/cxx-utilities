#pragma once

#if defined (__WIN32__) || defined(_WIN32)
#include <windows.h>
#define Dlopen(name, flags) LoadLibraryA(name)
#define Dlclose FreeLibrary
#define Dlerror GetLastError
#elif defined(__linux__)
#include <dlfcn.h>
#define Dlopen(name, flags) dlopen(name, flags)
#define Dlclose dlclose
#define Dlerror dlerror
#endif

#include "get_os_error.hxx"

#include <stdexcept>
#include <string>

/**
 * @brief Cross-platform loader for dynamic libraries.
*/
template <typename dtype_t>
class LibLoader
{
private:
#if defined (__WIN32__) || defined(_WIN32)
    HMODULE p_lib_handle = nullptr;
#elif defined(__linux__)
    void* p_lib_handle = nullptr;
#endif
public:

    /**
     * @brief Loads the dynamic library in memory.
     *
     * @param libname [in] The name of the library to load. For linux, "lib" is prepended to the name.
     * @param load_options [in] Ignored for Windows. See https://man7.org/linux/man-pages/man3/dlopen.3.html for Linux.
     *
     * @throws Runtime error if the load fails.
    */
    explicit LibLoader(const char* libname, const int load_options) noexcept(false)
    {
      std::string local_libname{ libname };
#if defined(__linux__)
      local_libname = std::string("lib") + local_libname;
#endif
      p_lib_handle = Dlopen(local_libname.c_str(), load_options);
      if (p_lib_handle == nullptr)
      {   // Error handling for loading the library
         std::string message = std::string("Failed to open library: ") + local_libname + std::string(" (");

         std::string what_happened = get_os_error();

         message += what_happened + std::string(")");

         throw std::runtime_error(message.c_str());
      }
    }

    /**
     * @brief Loads the dynamic library in memory.
     *
     * @param libname [in] The name of the library to load. For linux, "lib" is prepended to the name.
     * @param load_options [in] Ignored for Windows. See https://man7.org/linux/man-pages/man3/dlopen.3.html for Linux.
     *
     * @throws Runtime error if the load fails.
    */
    explicit LibLoader(const std::string& libname, const int load_options) noexcept(false) :
        LibLoader(libname.c_str(), load_options)
    {}

    /**
     * @brief Releases the handle to the library.
    */
    ~DynLibLoader() noexcept
    {
        Dlclose(p_lib_handle);
    }

    /**
     * @brief Returns the handle to the dynamic library.
    */
#if defined (__WIN32__) || defined(_WIN32)
    HINSTANCE Handle() const
#elif defined(__linux__)
    void* Handle() const 
#endif
    {
        return p_lib_handle;
    }

};
