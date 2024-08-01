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

        /**
         * Returns the time elapsed in a suitable unit with a string.
         */
        struct ElapsedTime
        {
            double time;
            std::string unit;
        };

        ElapsedTime elapsed_adaptive()
        {
            using namespace std::chrono;
            auto end = high_resolution_clock::now();
            auto duration = end - start;

            double milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
            
            if (milliseconds < 10000)   // 10 seconds
            {
                return { milliseconds, "milliseconds" };
            }
            else if (milliseconds < 3 * 60 * 1000) // 3 minutes
            {
                double seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
                return { seconds, "seconds" };
            }
            else if (milliseconds < 3600 * 1000) // 1 hour
            {
                double minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
                return { minutes, "minutes" };
            }
            
            // hours.. 
            double hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
            return { hours, "hours" };
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

}

#endif // RUNTIME_UTILS_H