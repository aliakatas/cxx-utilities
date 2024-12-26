#include "applogger/applogger_c_interface.hxx"
#include <iostream>
#include <stdexcept>

void manage_applogger_error_messages(int return_code);

int main() 
{
    try
    {
      int buffer_size = 0;
      int err = 0;
      get_applogger_version(nullptr, &buffer_size, &err);
      if (err != APPLOGGER_EXIT_SUCCESS)
      {
        std::cerr << "Error: something went wrong while getting the number of chars in applogger's version string" << std::endl;
      }

      char* applogger_version = new char[buffer_size];
      get_applogger_version(applogger_version, &buffer_size, &err);
      if (err != APPLOGGER_EXIT_SUCCESS)
      {
        std::cerr << "Error: something went wrong while getting the applogger's version string" << std::endl;
      }
      else
        std::cout << applogger_version << std::endl;

      add_sink_to_applogger(nullptr, nullptr, nullptr, nullptr, &err);
      manage_applogger_error_messages(err);

      initialise_applogger(&err);
      manage_applogger_error_messages(err);

      add_sink_to_applogger("sink-log.log", "glob", nullptr, "info", &err);
      manage_applogger_error_messages(err);
      
      //   // Add channel-specific sinks
      //   logger.addChannelSink(
      //       "Network",
      //       "logs/network_%Y%m%d.log",
      //       AppLogger::Severity::Debug,
      //       "%TimeStamp% [%Channel%] [%Severity%] %Message%"
      //   );
        
      //   logger.addChannelSink(
      //       "Database",
      //       "logs/db_%Y%m%d.log",
      //       AppLogger::Severity::Info,
      //       "%TimeStamp% [%Channel%] [%Severity%] %Message%"
      //   );
        
      //   logger.addChannelSink(
      //       "Security",
      //       "logs/security_%Y%m%d.log",
      //       AppLogger::Severity::Warning,
      //       "%TimeStamp% [%Channel%] [%Severity%] %Message%"
      //   );
        
      //   // Log to specific channels
      //   logger.info("Network", "Connection established");
      //   logger.error("Network", "Connection lost");
        
      //   logger.debug("Database", "Executing query: SELECT * FROM users");
      //   logger.info("Database", "Query completed successfully");
        
      //   logger.warning("Security", "Failed login attempt");
      //   logger.error("Security", "Possible intrusion detected");
        
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

void manage_applogger_error_messages(int return_code)
{
  if (return_code == APPLOGGER_EXIT_SUCCESS)
    return;

  int err = 0;
  char* message_buffer = nullptr;
  int message_size = 0;
  get_applogger_errors(message_buffer, &message_size, &err);
  if (err != APPLOGGER_EXIT_SUCCESS)
  {
    std::cerr << "Error: something went wrong while getting the applogger's error messages" << std::endl;
  }
  else
  {
    message_buffer = new char[message_size];
    get_applogger_errors(message_buffer, &message_size, &err);
    if (err != APPLOGGER_EXIT_SUCCESS)
    {
      std::cerr << "Error: something went wrong while getting the applogger's error messages" << std::endl;
    }
    else
      std::cout << message_buffer << std::endl;
  }

  if (message_buffer)
    delete[] message_buffer;
}


