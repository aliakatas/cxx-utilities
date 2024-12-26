#include "applogger_c_interface.hxx"
#include "applogger.hxx"

#include "build_utilities/build_version_utils.hpp"

#include <string>
#include <vector>
// #include <iostream>

namespace applogger
{
   AppLogger* applogger = nullptr;
   std::vector<std::string> messages;
}

#if __cplusplus
extern "C" {
#endif

   //====================================================================
   DllExport void get_applogger_errors(char* buffer, int* nchars, int* err)
   {
      try
      {
         size_t msize = 0;
         for (const auto& m : applogger::messages)
            msize += (m.length() + 1);
         
         if (buffer)
         {
            char* local_buffer = new char[msize];
            if (local_buffer == nullptr)
            {
               *err = APPLOGGER_EXIT_ERROR;
               return;
            }
            memset(local_buffer, 0, msize * sizeof(char));

            std::string temp;
            for (const auto& m : applogger::messages)
               temp += m + std::string("\n");

            strcpy(local_buffer, temp.c_str());

            memset(buffer, 0, *nchars * sizeof(char));
            strncpy(buffer, local_buffer, *nchars - 1);
            delete[] local_buffer;
         }
         else 
         {  
            *nchars = static_cast<int>(msize);
         }
      }
      catch(const std::exception& e)
      {
         std::cerr << e.what() << '\n';
         *err = APPLOGGER_EXIT_ERROR;
         return;
      }
      
      *err = APPLOGGER_EXIT_SUCCESS;
   }

   //====================================================================
   DllExport void get_applogger_version(char* buffer, int* nchars, int* err)
   {
      try
      {
         std::string version = build_info::get_app_name() + std::string("\n");
         version += build_info::get_version() + std::string("\n");
         version += build_info::get_build_date_time();

         size_t msize = version.length();

         if (buffer)
         {
            char* local_buffer = new char[msize];
            if (local_buffer == nullptr)
            {
               *err = APPLOGGER_EXIT_ERROR;
               return;
            }
            memset(local_buffer, 0, msize * sizeof(char));

            strcpy(local_buffer, version.c_str());

            memset(buffer, 0, *nchars * sizeof(char));
            strncpy(buffer, local_buffer, *nchars - 1);
            delete[] local_buffer;
         }
         else 
         {
            *nchars = static_cast<int>(msize);
         }
      }
      catch(const std::exception& e)
      {
         std::cerr << e.what() << '\n';
         *err = APPLOGGER_EXIT_ERROR;
         return;
      }
      
      *err = APPLOGGER_EXIT_SUCCESS;
   }


#if __cplusplus
}
#endif
