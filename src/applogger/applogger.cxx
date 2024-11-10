#include "applogger/applogger.hxx"

// #include <boost/log/core.hpp>
// #include <boost/log/trivial.hpp>
// #include <boost/log/expressions.hpp>
// #include <boost/log/sinks/text_file_backend.hpp>
// #include <boost/log/sinks/text_ostream_backend.hpp>
// #include <boost/log/sources/severity_logger.hpp>
// #include <boost/log/sources/record_ostream.hpp>
// #include <boost/log/utility/setup/file.hpp>
// #include <boost/log/utility/setup/console.hpp>
// #include <boost/log/utility/setup/common_attributes.hpp>
// #include <boost/log/support/date_time.hpp>
// #include <boost/core/null_deleter.hpp>
// #include <boost/shared_ptr.hpp>
// #include <boost/make_shared.hpp>
// #include <iostream>
// #include <string>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

//================================================
AppLogger& AppLogger::getInstance() 
{
   static AppLogger instance;
   return instance;
}

//================================================
void AppLogger::init() {
   // Add common attributes
   logging::add_common_attributes();
   
   // Create console sink
   initConsoleSink();
   
   // Create default file sink
   initDefaultFileSink();
}

//================================================
void AppLogger::addFileSink(
   const std::string& filename,
   const Severity minSeverity,
   const std::string& format
) 
{
   // Create a file sink
   typedef sinks::synchronous_sink<sinks::text_file_backend> file_sink_t;
   
   auto backend = boost::make_shared<sinks::text_file_backend>(
      keywords::file_name = filename,
      keywords::rotation_size = 10 * 1024 * 1024,  // 10 MB rotation
      keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)  // Rotate at midnight
   );

   auto sink = boost::make_shared<file_sink_t>(backend);

   // Set the filter
   sink->set_filter(
      expr::attr<Severity>("Severity") >= minSeverity
   );

   // Set the formatter
   sink->set_formatter(
      expr::stream
            << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
            << " [" << expr::attr<Severity>("Severity") << "] "
            << expr::smessage
   );

   // Add the sink to the core
   logging::core::get()->add_sink(sink);
}

//================================================
void AppLogger::initConsoleSink() 
{
   typedef sinks::synchronous_sink<sinks::text_ostream_backend> console_sink_t;
   
   auto backend = boost::make_shared<sinks::text_ostream_backend>();
   backend->add_stream(
      boost::shared_ptr<std::ostream>(&std::cout, boost::null_deleter())
   );

   auto sink = boost::make_shared<console_sink_t>(backend);

   // Set console formatter
   sink->set_formatter(
      expr::stream
            << "[" << expr::attr<Severity>("Severity") << "] "
            << expr::smessage
   );

   // Set minimum severity for console
   sink->set_filter(
      expr::attr<Severity>("Severity") >= Severity::Info
   );

   logging::core::get()->add_sink(sink);
}

//================================================
void AppLogger::initDefaultFileSink() 
{
   addFileSink(
      "logs/default_%Y%m%d.log",
      Severity::Info,
      "%TimeStamp% [%Severity%] %Message%"
   );
}

//================================================
logging::sources::severity_logger<AppLogger::Severity>& AppLogger::getLogger() {
   static logging::sources::severity_logger<AppLogger::Severity> slg;
   return slg;
}

// // Example usage
// int main() {
//     try {
//         auto& logger = Logger::getInstance();
        
//         // Initialize with default settings
//         logger.init();
        
//         // Add custom file sink for errors only
//         logger.addFileSink(
//             "logs/errors_%Y%m%d.log",
//             Logger::Severity::Error,
//             "%TimeStamp% [%Severity%] %Message%"
//         );
        
//         // Add custom file sink for debugging with different format
//         logger.addFileSink(
//             "logs/debug_%Y%m%d.log",
//             Logger::Severity::Debug,
//             "[%TimeStamp%] <%Severity%> %Message%"
//         );
        
//         // Log some messages
//         logger.debug("This is a debug message");
//         logger.info("This is an info message");
//         logger.warning("This is a warning message");
//         logger.error("This is an error message");
//         logger.critical("This is a critical message");
        
//         // Or use the generic log method
//         logger.log(Logger::Severity::Info, "This is another info message");
        
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return 1;
//     }
    
//     return 0;
// }
