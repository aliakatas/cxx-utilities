#pragma once

#ifdef __NVCC__
#include <device_launch_parameters.h>
#define HOSTDEVDECOR    __host__ __device__
#else 
#define HOSTDEVDECOR
#endif

#include <cmath>
#include <type_traits>

namespace num_ode
{
   /**
    * @brief Implements the Taylor series-based term of a function.
    * 
    * @tparam T Supports float, double and long double.
    * @tparam index_t Supports int, long, long long, and size_t.
    * @param start [in] The starting value of the independent coordinate.
    * @param i [in] The number of steps to take.
    * @param dt [in] The resolution of the independent coordinate.
    * @param t [out] The value of the independent coordinate.
    * @param y [inout] The value of the function after applying the Taylor term.
    * @param func The function to calculate.
    */
   template <typename T, typename index_t>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value && 
      (std::is_same<index_t, int>::value || std::is_same<index_t, long>::value || 
      std::is_same<index_t, long long>::value || std::is_same<index_t, size_t>::value), void>::type
   taylor(const T start, const index_t i, const T dt, T& t, T& y, T (*func)(T, T)) 
   {
      t = start + i * dt;
      y += dt * func(t, y);
   }

   /**
    * @brief Implements the Euler method-based term of a function.
    * 
    * @tparam T Supports float, double and long double.
    * @tparam index_t Supports int, long, long long, and size_t.
    * @param i [in] The number of steps to take.
    * @param dt [in] The resolution of the independent coordinate.
    * @param t [out] The value of the independent coordinate.
    * @param y [inout] The value of the function after applying the Taylor term.
    * @param func The function to calculate.
    */
   template <typename T, typename index_t>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value && 
      (std::is_same<index_t, int>::value || std::is_same<index_t, long>::value || 
      std::is_same<index_t, long long>::value || std::is_same<index_t, size_t>::value), void>::type
   euler(T start, index_t i, T dt, T& t, T& y, T (*func)(T, T)) 
   {
      t = start + i * dt;
      y += dt * func(t + static_cast<T>(.5) * dt, y + static_cast<T>(.5) * dt * func(t, y));
   }

}