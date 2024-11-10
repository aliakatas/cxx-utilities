#pragma once

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
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
    enum class Severity {
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };

    // Singleton instance getter
    static AppLogger& getInstance();

    // Initialize the AppLogger with default settings
    void init();

    // Add a custom file sink with specific severity filter and format
    void addFileSink(
        const std::string& filename,
        const Severity minSeverity,
        const std::string& format
    );

    // Log a message with specified severity
    template<typename T>
    void log(const Severity severity, const T& message) {
        auto& slg = getLogger();
        BOOST_LOG_SEV(slg, severity) << message;
    }

    // Convenience methods for different severity levels
    template<typename T> void debug(const T& message)   { log(Severity::Debug, message); }
    template<typename T> void info(const T& message)    { log(Severity::Info, message); }
    template<typename T> void warning(const T& message) { log(Severity::Warning, message); }
    template<typename T> void error(const T& message)   { log(Severity::Error, message); }
    template<typename T> void critical(const T& message)   { log(Severity::Critical, message); }

private:
    AppLogger() = default;
    ~AppLogger() = default;
    AppLogger(const AppLogger&) = delete;
    AppLogger& operator=(const AppLogger&) = delete;

    // Initialize console sink with custom format
    void initConsoleSink();

    // Initialize default file sink
    void initDefaultFileSink();

    // Get the severity AppLogger instance
    logging::sources::severity_logger<Severity>& getLogger();
};

// Severity level to string conversion
template<typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(
    std::basic_ostream<CharT, TraitsT>& strm,
    AppLogger::Severity lvl)
{
    static const char* const str[] = {
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
