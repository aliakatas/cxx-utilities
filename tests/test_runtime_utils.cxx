#include "runtime_utils.h"

#include <iostream>
#include <thread>

int main()
{
    std::cout << "Local time: " << rtu::get_current_datetime_str() << std::endl;
    std::cout << "GM time: " << rtu::get_current_datetime_str(true) << std::endl;

    rtu::Stopwatch stopwatch;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Elapsed " << stopwatch.elapsed() << " ms" << std::endl;

    stopwatch.reset();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Elapsed " << stopwatch.elapsed() << " ms" << std::endl;

    stopwatch.reset();
    std::this_thread::sleep_for(std::chrono::seconds(11));
    rtu::Stopwatch<>::ElapsedTime elapsed_time = stopwatch.elapsed_adaptive();
    std::cout << "Elapsed " << elapsed_time.time << " " << elapsed_time.unit << std::endl;

    stopwatch.reset();
    std::this_thread::sleep_for(std::chrono::minutes(4));
    elapsed_time = stopwatch.elapsed_adaptive();
    std::cout << "Elapsed " << elapsed_time.time << " " << elapsed_time.unit << std::endl;

    return EXIT_SUCCESS;
}