#ifndef RUNTIME_UTILS_H
#define RUNTIME_UTILS_H

#include <ctime>
#include <sstream>
#include <string>
#include <chrono>

namespace rtu
{
    /**
     * @brief A structure to facilitate measuring performance of parts
     * of the application. 
     */
    template <typename unit_t = std::chrono::milliseconds>
    struct Stopwatch
    {
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        Stopwatch() {}

        ~Stopwatch() {}

        /**
         * Resets the stopwatch
         */
        void reset()
        {
            start = std::chrono::high_resolution_clock::now();
        }

        /**
         * Returns the time elapsed in units "unit_t".
         */
        double elapsed()
        {
            auto end = std::chrono::high_resolution_clock::now();

            auto s = std::chrono::time_point_cast<unit_t>(start).time_since_epoch().count();
            auto e = std::chrono::time_point_cast<unit_t>(end).time_since_epoch().count();

            return static_cast<double>(e - s);  // of unit => unit_t
        }
    };

    /**
     * @brief Returns the current date & time in a "%Y-%m-%d %H:%M:%S" format.
     * 
     * @param use_gmt [in] Flag to indicate use of GMT time instead of local time (default).
     * @return std::string
     */
    inline std::string get_current_datetime_str(bool use_gmt = false) 
    {
        auto now = std::time(nullptr);
        char mbstr[100];
        if (use_gmt)
            std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", std::gmtime(&now));
        else 
            std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return std::string(mbstr);
    }

    /**
     * @brief Returns a message common to most (CLI) applications 
     * including the name of the application and when the instance 
     * has started. 
     * 
     * If a debug build is detected, an appropriate message is added.
     * 
     * @param app_name [in] The name of the application.
     * @param use_gmt [in] Flag to indicate use of GMT time instead of local time (default).
     * @return std::string
     */
    inline std::string create_banner(const std::string& app_name, bool use_gmt = false)
    {
        std::stringstream ss;
        ss << "Starting " << app_name << " at " << get_current_datetime_str(use_gmt) << "...";
    #ifdef _DEBUG
        ss << "\n  *** DEBUG BUILD - no optimisations ***";
    #endif 
        return ss.str();
    }
}

#endif // RUNTIME_UTILS_H