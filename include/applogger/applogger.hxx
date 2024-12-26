#pragma once

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
#include <boost/log/support/date_time.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <iostream>
#include <map>
#include <string>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

class AppLogger 
{
public:
    // Define severity levels
    enum class Severity 
    {
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };

    static Severity severityFromString(const std::string& str) noexcept(false);

    // Singleton instance getter
    static AppLogger& getInstance();

    // Initialize the AppLogger with default settings
    void init();

    void addChannelSinkWithFormat(
        const std::string& channel,
        const std::string& filename,
        const Severity minSeverity,
        const std::string& format
    );

    // Add a channel-specific sink with custom filter and format
    void addChannelSink(
        const std::string& channel,
        const std::string& filename,
        const Severity minSeverity
    );

    // Log a message to a specific channel with specified severity
    template<typename T>
    void logToChannel(const std::string& channel, const Severity severity, const T& message) 
    {
        auto& slg = getChannelLogger(channel);
        BOOST_LOG_SEV(slg, severity) << message;
    }

    // Convenience methods for different severity levels with channel specification
    template<typename T> 
    void debug(const std::string& channel, const T& message) 
    { 
        logToChannel(channel, Severity::Debug, message); 
    }
    
    template<typename T> 
    void info(const std::string& channel, const T& message) 
    { 
        logToChannel(channel, Severity::Info, message); 
    }
    
    template<typename T> 
    void warning(const std::string& channel, const T& message) 
    { 
        logToChannel(channel, Severity::Warning, message); 
    }
    
    template<typename T> 
    void error(const std::string& channel, const T& message) 
    { 
        logToChannel(channel, Severity::Error, message); 
    }
    
    template<typename T> 
    void critical(const std::string& channel, const T& message) 
    { 
        logToChannel(channel, Severity::Critical, message); 
    }

    AppLogger() = default;
    ~AppLogger() = default;
private:
    
    AppLogger(const AppLogger&) = delete;
    AppLogger& operator=(const AppLogger&) = delete;

    // Store channel-specific sinks
    std::map<std::string, boost::shared_ptr<sinks::synchronous_sink<sinks::text_file_backend>>> channelSinks;
    
    // Store channel-specific loggers
    std::map<std::string, boost::shared_ptr<logging::sources::severity_channel_logger<Severity, std::string>>> channelLoggers;

    // Initialize console sink with custom format
    void initConsoleSink();

    // Get or create a channel-specific logger
    logging::sources::severity_channel_logger<Severity, std::string>& getChannelLogger(
        const std::string& channel
    );
};

// Severity level to string conversion
template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(
    std::basic_ostream<CharT, TraitsT>& strm,
    AppLogger::Severity lvl)
{
    static const char* const str[] = 
    {
        "Debug",
        "Info",
        "Warning",
        "Error",
        "Critical"
    };
    
    if (static_cast<std::size_t>(lvl) < sizeof(str) / sizeof(*str))
        strm << str[static_cast<std::size_t>(lvl)];
    else
        strm << static_cast<int>(lvl);
    
    return strm;
}
