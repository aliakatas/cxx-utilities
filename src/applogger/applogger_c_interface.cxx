#include "applogger_c_interface.hxx"
#include "applogger.hxx"

#include "build_utilities/build_version_utils.hpp"

#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <set>

namespace applogger
{
   std::unique_ptr<AppLogger> applogger;
   std::vector<std::string> messages;
   std::set<std::string> channels;
}

void log_message_to_channel(const AppLogger::Severity& severityVal, const std::string& channel, const std::string& message)
{
   switch (severityVal)
   {
   case AppLogger::Severity::Debug:
      applogger::applogger->debug(channel, message);
      break;
   case AppLogger::Severity::Info:
      applogger::applogger->info(channel, message);
      break;
   case AppLogger::Severity::Warning:
      applogger::applogger->warning(channel, message);
      break;
   case AppLogger::Severity::Error:
      applogger::applogger->error(channel, message);
      break;
   case AppLogger::Severity::Critical:
      applogger::applogger->critical(channel, message);
      break;
   default:
      // do nothing
      break;
   }
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
            applogger::messages.clear();
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
         version += build_info::get_build_date_time() + std::string(" with ");
         version += build_info::get_compiler_info();

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
            strncpy(buffer, local_buffer, *nchars);
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
   DllExport void initialise_applogger(int* err)
   {
      try
      {
         applogger::applogger = std::make_unique<AppLogger>();
         
         applogger::applogger->init();
      }
      catch(const std::exception& e)
      {
         applogger::messages.push_back(e.what());
         *err = APPLOGGER_EXIT_ERROR;
         return;
      }
      
      *err = APPLOGGER_EXIT_SUCCESS;
   }

   //====================================================================
   DllExport void add_sink_to_applogger(const char* sinkname, 
      const char* channel, const char* format, const char* minseverity, int* err)
   {
      try
      {
         *err = APPLOGGER_EXIT_SUCCESS;
         if (!applogger::applogger)
         {
            throw std::runtime_error(std::string(__FUNCTION__) + std::string(": logger is not initialised yet!"));
         }

         AppLogger::Severity severity = AppLogger::Severity::Info;
         try
         {
            if (minseverity)
               severity = AppLogger::severityFromString(std::string(minseverity));
         }
         catch(const std::exception& e)
         {
            applogger::messages.push_back(e.what());
            applogger::messages.push_back("Using default value of 'Info'");
            *err = APPLOGGER_EXIT_WITH_MESSAGES;
         }
         
         if (format)
            applogger::applogger->addChannelSinkWithFormat(std::string(channel), std::string(sinkname), severity, std::string(format));
         else 
            applogger::applogger->addChannelSink(std::string(channel), std::string(sinkname), severity);

         applogger::channels.emplace(channel);
      }
      catch(const std::exception& e)
      {
         applogger::messages.push_back(e.what());
         *err = APPLOGGER_EXIT_ERROR;
         return;
      }
   }

   //====================================================================
   DllExport void send_message_to_applogger(const char* channel, const char* severity, const char* message, int*err)
   {
      try
      {
         *err = APPLOGGER_EXIT_SUCCESS;
         if (!applogger::applogger)
         {
            throw std::runtime_error(std::string(__FUNCTION__) + std::string(": logger is not initialised yet!"));
         }

         AppLogger::Severity severityVal = AppLogger::Severity::Info;
         try
         {
            if (severity)
               severityVal = AppLogger::severityFromString(std::string(severity));
         }
         catch(const std::exception& e)
         {
            applogger::messages.push_back(e.what());
            applogger::messages.push_back("Using default value of 'Info'");
            *err = APPLOGGER_EXIT_WITH_MESSAGES;
         }

         if (channel)
         {
            if (applogger::channels.find(std::string(channel)) != applogger::channels.end())
               log_message_to_channel(severityVal, std::string(channel), std::string(message));
            else 
            {
               *err = APPLOGGER_EXIT_WITH_MESSAGES;
               applogger::messages.push_back("channel not regognised, logging to all available channels");
               for (auto& c : applogger::channels)
                  log_message_to_channel(severityVal, c, std::string(message));
            }
         }
         else
         {
            for (auto& c : applogger::channels)
               log_message_to_channel(severityVal, c, std::string(message));
         }
      }
      catch(const std::exception& e)
      {
         applogger::messages.push_back(e.what());
         *err = APPLOGGER_EXIT_ERROR;
         return;
      }
   }

   //====================================================================
   DllExport void destroy_applogger(int* err)
   {
      *err = APPLOGGER_EXIT_SUCCESS;
      applogger::messages.clear();
      applogger::channels.clear();
      // applogger::applogger should be destroyed since it's 
      // a unique_ptr...
   }

#if __cplusplus
}
#endif
