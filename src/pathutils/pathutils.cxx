#include <string>
#include <stdexcept>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
    #include <shlobj.h>
    #include <userenv.h>
    #include <memory>
#else
    #include <pwd.h>
    #include <unistd.h>
#endif

namespace pathutils
{
   //============================================
   std::string get_home_directory() 
   {
#ifdef _WIN32
      // Windows implementation
      HANDLE token = nullptr;
      if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) 
      {
         throw std::runtime_error("Failed to open process token");
      }

      // Use smart pointer for automatic cleanup
      std::unique_ptr<void, decltype(&CloseHandle)> tokenPtr(token, CloseHandle);

      DWORD size = 0;
      // First call to get required buffer size
      GetUserProfileDirectoryW(token, nullptr, &size);
      if (size == 0) 
      {
         throw std::runtime_error("Failed to get user profile directory size");
      }

      // Allocate buffer
      std::wstring path(size, 0);
      if (!GetUserProfileDirectoryW(token, &path[0], &size)) 
      {
         throw std::runtime_error("Failed to get user profile directory");
      }

      // Convert wide string to regular string
      int requiredSize = WideCharToMultiByte(CP_UTF8, 0, path.c_str(), -1, 
                                          nullptr, 0, nullptr, nullptr);
      if (requiredSize == 0) 
      {
         throw std::runtime_error("Failed to convert path to UTF-8");
      }

      std::string result(requiredSize, 0);
      if (WideCharToMultiByte(CP_UTF8, 0, path.c_str(), -1, 
                              &result[0], requiredSize, nullptr, nullptr) == 0) 
                              {
         throw std::runtime_error("Failed to convert path to UTF-8");
      }

      // Remove null terminator if present
      if (!result.empty() && result.back() == '\0') 
      {
         result.pop_back();
      }

      return result;

#else
      // Unix-like systems implementation
      const char* homeEnv = std::getenv("HOME");
      if (homeEnv != nullptr) 
      {
         return std::string(homeEnv);
      }

      // Fallback to password database if HOME is not set
      struct passwd* pw = getpwuid(getuid());
      if (pw == nullptr) 
      {
         throw std::runtime_error("Failed to get home directory");
      }

      return std::string(pw->pw_dir);
#endif
   }
}
