#ifndef RUNTIME_UTILS_H
#define RUNTIME_UTILS_H

#include <chrono>
#include <string>

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
    std::string get_current_datetime_str(bool use_gmt = false);

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
    std::string create_banner(const std::string& app_name, bool use_gmt = false);

    /**
     * @brief Returns a message regarding the build.
     * It includes the build date-time and compiler name/version.
     * 
     * @return std::string
     */
    std::string get_build_info();

    /**
     * @brief Returns details regarding the machine the program
     * is running on.
     * It includes OS name/version, CPU model and total RAM.
     * 
     * @return std::string
     */
    std::string get_machine_info();

}

#endif // RUNTIME_UTILS_H