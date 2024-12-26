#include "applogger/applogger_c_interface.hxx"
#include <iostream>
#include <stdexcept>

int main() 
{
    try
    {
      int buffer_size = 0;
      int err = 0;
      get_applogger_version(nullptr, &buffer_size, &err);

      char* applogger_version = new char[buffer_size];
      get_applogger_version(applogger_version, &buffer_size, &err);

      std::cout << applogger_version << std::endl;

      //   auto& logger = AppLogger::getInstance();
      //   logger.init();
        
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