#include "applogger/apploggerwithchannels.hxx"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include <string>
#include <map>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;


// Singleton instance getter
AppLoggerWithChannels& AppLoggerWithChannels::getInstance() 
{
    static AppLoggerWithChannels instance;
    return instance;
}

// Initialize the AppLoggerWithChannels with default settings
void AppLoggerWithChannels::init() 
{
    // Add common attributes
    logging::add_common_attributes();
    
    // Create default console sink
    initConsoleSink();
}

void AppLoggerWithChannels::addChannelSink_working_format(
    const std::string& channel,
    const std::string& filename,
    const AppLoggerWithChannels::Severity minSeverity,
    const std::string& format
) {
    typedef sinks::synchronous_sink<sinks::text_file_backend> sink_t;
    
    auto backend = boost::make_shared<sinks::text_file_backend>(
        keywords::file_name = filename,
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)
    );

    auto sink = boost::make_shared<sink_t>(backend);

    // Set filter for both channel and severity
    sink->set_filter(
        expr::attr<std::string>("Channel") == channel &&
        expr::attr<AppLoggerWithChannels::Severity>("Severity") >= minSeverity
    );

    // Parse the format string and create a formatter
    auto formatter = logging::parse_formatter(format);
    
    // Set the custom formatter
    sink->set_formatter(formatter);

    // Store the sink in our map
    channelSinks[channel] = sink;
    
    // Add the sink to the core
    logging::core::get()->add_sink(sink);
}

// Add a channel-specific sink with custom filter and format
void AppLoggerWithChannels::addChannelSink(
    const std::string& channel,
    const std::string& filename,
    const AppLoggerWithChannels::Severity minSeverity,
    const std::string& format
) {
    typedef sinks::synchronous_sink<sinks::text_file_backend> sink_t;
    
    auto backend = boost::make_shared<sinks::text_file_backend>(
        keywords::file_name = filename,
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)
    );

    auto sink = boost::make_shared<sink_t>(backend);

    // Set filter for both channel and severity
    sink->set_filter(
        expr::attr<std::string>("Channel") == channel &&
        expr::attr<AppLoggerWithChannels::Severity>("Severity") >= minSeverity
    );

    // Set the formatter
    sink->set_formatter(
        expr::stream
            << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
            << " [" << expr::attr<std::string>("Channel") << "]"
            << " [" << expr::attr<AppLoggerWithChannels::Severity>("Severity") << "] "
            << expr::smessage
    );

    // Store the sink in our map
    channelSinks[channel] = sink;
    
    // Add the sink to the core
    logging::core::get()->add_sink(sink);
}

// Initialize console sink with custom format
void AppLoggerWithChannels::initConsoleSink() 
{
    typedef sinks::synchronous_sink<sinks::text_ostream_backend> console_sink_t;
    
    auto backend = boost::make_shared<sinks::text_ostream_backend>();
    backend->add_stream(
        boost::shared_ptr<std::ostream>(&std::cout, boost::null_deleter())
    );

    auto sink = boost::make_shared<console_sink_t>(backend);

    // Set console formatter with channel information
    sink->set_formatter(
        expr::stream
            << "[" << expr::attr<std::string>("Channel") << "]"
            << "[" << expr::attr<AppLoggerWithChannels::Severity>("Severity") << "] "
            << expr::smessage
    );

    // Set minimum severity for console
    sink->set_filter(
        expr::attr<AppLoggerWithChannels::Severity>("Severity") >= AppLoggerWithChannels::Severity::Info
    );

    logging::core::get()->add_sink(sink);
}

// Get or create a channel-specific logger
logging::sources::severity_channel_logger<AppLoggerWithChannels::Severity, std::string>& AppLoggerWithChannels::getChannelLogger(
    const std::string& channel
) {
    auto it = channelLoggers.find(channel);
    if (it == channelLoggers.end()) {
        auto logger = boost::make_shared<logging::sources::severity_channel_logger<AppLoggerWithChannels::Severity, std::string>>(
            keywords::channel = channel
        );
        channelLoggers[channel] = logger;
        return *logger;
    }
    return *(it->second);
}

// // Example usage
// int main() {
//     try
//     {
//         auto& logger = AppLoggerWithChannels::getInstance();
//         logger.init();
        
//         // Add channel-specific sinks
//         logger.addChannelSink(
//             "Network",
//             "logs/network_%Y%m%d.log",
//             AppLoggerWithChannels::Severity::Debug,
//             "%TimeStamp% [%Channel%] [%Severity%] %Message%"
//         );
        
//         logger.addChannelSink(
//             "Database",
//             "logs/db_%Y%m%d.log",
//             AppLoggerWithChannels::Severity::Info,
//             "%TimeStamp% [%Channel%] [%Severity%] %Message%"
//         );
        
//         logger.addChannelSink(
//             "Security",
//             "logs/security_%Y%m%d.log",
//             AppLoggerWithChannels::Severity::Warning,
//             "%TimeStamp% [%Channel%] [%Severity%] %Message%"
//         );
        
//         // Log to specific channels
//         logger.info("Network", "Connection established");
//         logger.error("Network", "Connection lost");
        
//         logger.debug("Database", "Executing query: SELECT * FROM users");
//         logger.info("Database", "Query completed successfully");
        
//         logger.warning("Security", "Failed login attempt");
//         logger.error("Security", "Possible intrusion detected");
        
//     } 
//     catch (const std::exception& e) 
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return 1;
//     }
    
//     return 0;
// }