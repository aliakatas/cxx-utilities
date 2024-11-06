#pragma once

#ifdef __NVCC__
#include <device_launch_parameters.h>
#define HOSTDEVDECOR    __host__ __device__
#else 
#define HOSTDEVDECOR
#endif

#include <cmath>
#include <type_traits>

namespace numanalysis
{
   /**
    * @brief Finds a root of a real-value function using 
    * the Newton-Raphson method (https://en.wikipedia.org/wiki/Newton%27s_method).
    * 
    * @tparam T Supports float, double and long double.
    * @param start [in] 
    * @param f [in]
    * @param df [in]
    * @param tol [in]
    * @param max_iter [in]
    * @return An approximation to a root of the funtion f.
    */
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   newton_raphson_1var(T start, T (*f)(T), T (*df)(T), T tol, int max_iter) 
   {
      int iter = 0;
      T last = start;
      while (iter < max_iter) {
         start = last - f(last) / df(last);
         if (std::abs(start - last) < tol)
            return start;
         last = start;
         ++iter;
      }
      return start;
   }

}


