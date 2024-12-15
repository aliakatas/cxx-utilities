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
    * @param start [in] The starting point for the method.
    * @param f The function to calculate the root for.
    * @param df The first derivative of the function.
    * @param tol [in] The tolerance within which to find the root.
    * @param max_iter [in]The max number of iterations.
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

   /**
    * @brief Calculates the root of a function using the 
    * bisection method (https://en.wikipedia.org/wiki/Bisection_method).
    * 
    * @tparam T Supports float, double and long double.
    * @param start [in] The starting point for the method.
    * @param finish [in] The last point for the method.
    * @param f The function to find the root for.
    * @param tol [in] The tolerance within which to find the root.
    * @param maxIter [in] The max number of iterations.
    * @param regularise [in] Flag to force regularisation when calculating the mid-point. Off by default/if omitted.
    * @return The root of the function within tolerance.
    */
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   bisection(T start, T finish, T (*f)(T), T tol, int maxIter, bool regularise = false) 
   {
      int iter = 0;
      T mid = static_cast<T>(0.);
      while (iter < maxIter) 
      {
         if (regularise)
            mid = (f(finish) * start - f(start) * finish) / (f(finish) - f(start));
         else 
            mid = (start + finish) / static_cast<T>(2.);

         if (f(start) * f(mid) < static_cast<T>(0.))
            finish = mid;
         else if (f(mid) * f(finish) < static_cast<T>(0.))
            start = mid;
         else
            return mid;

         if (std::fabs(f(mid)) < tol)
            return mid;
         ++iter;
      }
      return mid;
   }

   /**
    * @brief Calculates the root of a function using the 
    * secant method (https://en.wikipedia.org/wiki/Secant_method).
    * 
    * @tparam T Supports float, double and long double.
    * @param p0 [in] The starting point of the interval within which to find the root.
    * @param p1 [in] The last point of the interval within which to find the root.
    * @param f The function to find the root for.
    * @param tol [in] The tolerance within which to find the root.
    * @param maxIter [in] The max number of iterations.
    * @return The root of the function within tolerance.
    */
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   secant(T p0, T p1, T (*f)(T), T tol, int maxIter) 
   {
      int iter = 0;
      T temp = static_cast<T>(0.);
      while (iter < maxIter) {
         temp = p1;
         p1 = p1 - f(p1) * (p1 - p0) / (f(p1) - f(p0));
         if (std::fabs(p0 - p1) < tol)
            return p1;
         p0 = temp;
         ++iter;
      }
      return p0;
   }


}


