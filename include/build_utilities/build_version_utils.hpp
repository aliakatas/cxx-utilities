#pragma once

#if __has_include("version_info.hpp")
#include "version_info.hpp"
#else
// Define custom macros if the header file doesn't exist
#define VERSION_MAJOR   0
#define VERSION_MINOR   1
#define VERSION_PATCH   0
#define BUILD_INDEX     0
#define REPO_INDEX      "aaaaaaaa"
#endif

#if __has_include("module_name.hpp")
#include "module_name.hpp"
#else
#define MODULE_NAME     "module-template"
#endif

#include <string>

/**
 * @brief Implements functions that help with general information
 * about the build of the application.
 * 
 */
namespace build_info 
{
   /**
    * @brief Returns the name of 
    * the app/module/library.
    * 
    * @return std::string
    */
   inline std::string get_app_name()
   {
        return std::string(MODULE_NAME);
   }

   /**
    * @brief Get the compiler information used to
    * build the module where the function is called
    * from.
    * 
    * @return std::string 
    */
   inline std::string get_compiler_info()
   {
      // Compiler name
#ifdef __clang__
      std::string compilerName = "Clang";
#elif defined(__INTEL_LLVM_COMPILER)
      std::string compilerName = "Intel DPC++";
#elif defined(__INTEL_COMPILER)
      std::string compilerName = "Intel C++ Classic";
#elif defined(__GNUC__)
      std::string compilerName = "GCC (GNU Compiler Collection)";
#elif defined(_MSC_VER)
      std::string compilerName = "Microsoft Visual C++";
#else
      std::string compilerName = "Unknown Compiler";
#endif

      // Compiler version
#ifdef __clang__
      std::string compilerVersion = __clang_version__;
#elif defined(__INTEL_LLVM_COMPILER)
      long long v = __INTEL_LLVM_COMPILER;

      long long vmajor = v / 1'000'000;
      long long va = v % 1'000'000;

      long long vminor = va / 1000;
      long long vv = va % 1000;

      std::string compilerVersion = std::to_string(vmajor) + std::string(".") + std::to_string(vminor) + std::string(".") + std::to_string(vv);
#elif defined(__INTEL_COMPILER)
      long long v = __INTEL_COMPILER;

      long long vmajor = v / 100;
      long long vminor = v % 100;

      std::string compilerVersion = std::to_string(vmajor) + std::string(".") + std::to_string(vminor);
#elif defined(__GNUC__)
      std::string compilerVersion = std::to_string(__GNUC__) + "." +
                                    std::to_string(__GNUC_MINOR__) + "." +
                                    std::to_string(__GNUC_PATCHLEVEL__);
#elif defined(_MSC_VER)
      // https://devblogs.microsoft.com/oldnewthing/20221219-00/?p=107601
      long long v = _MSC_FULL_VER; 

      long long vmajor = v / 10000000;
      long long va = v % 10000000;
      
      long long vminor = va / 100000;
      long long vv = va % 100000;

      //std::string compilerVersion = std::to_string(_MSC_FULL_VER);
      std::string compilerVersion = std::to_string(vmajor) + std::string(".") + std::to_string(vminor) + std::string(".") + std::to_string(vv);
#else
      std::string compilerVersion = "Unknown Version";
#endif

      return compilerName + std::string(" :: ") + compilerVersion;
   }

   /**
    * @brief Get the build date & time of the module
    * where the function is called from.
    * 
    * @return std::string 
    */
   inline std::string get_build_date_time()
   {

      std::string compileDate = __DATE__;
      std::string compileTime = __TIME__;

      // Creating the formatted date and time string
      std::string compileDateTime = compileDate + ", " + compileTime;

      return compileDateTime;
   }
    
   /**
    * @brief Get the Nvidia CUDA version used to build 
    * the module where the function is called from.
    * 
    * @return CUDA version as a string. 
    */
   inline std::string get_nvidia_cuda_version()
   {
#ifdef __NVCC__
      return std::string("CUDA") + " :: " +
         std::to_string(__CUDACC_VER_MAJOR__) + "." +
         std::to_string(__CUDACC_VER_MINOR__) + "." +
         std::to_string(__CUDACC_VER_BUILD__);
#else
      return std::string("CUDA not used");
#endif 
   }

   /**
    * @brief Get the version number for  
    * the module/app/library being built.
    * 
    * Follows Semantic versioning https://semver.org/
    * 
    * @return Version as string, formatted as MAJOR.MINOR.PATCH+INDEX.REPO_INDEX
    */
   inline std::string get_version()
   {
      std::string version = std::to_string(VERSION_MAJOR) + "." +
         std::to_string(VERSION_MINOR) + "." +
         std::to_string(VERSION_PATCH) + "+" +
         std::to_string(BUILD_INDEX) + "." +
         std::string(REPO_INDEX);
#ifdef _DEBUG
      version += std::string("-DEBUG");
#endif // _DEBUG
      return version;
   }
}
