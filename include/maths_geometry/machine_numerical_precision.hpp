#pragma once
#include <type_traits>

/**
 * @brief Returns the numerical precision of the 
 * machine given the data type.
 * 
 * @tparam T Supports float, double, long double.
 * @return Numerical precision of the machine for the particular data type.
 */
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
get_machine_precision() 
{
    T e = static_cast<T>(1.0L);
    while (e + static_cast<T>(1.0L) != static_cast<T>(1.0L))
        e *= static_cast<T>(0.5L);
    return e;
}

