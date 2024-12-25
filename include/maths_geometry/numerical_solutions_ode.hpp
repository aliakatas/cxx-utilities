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
    * @brief Implements the Taylor series integration of a function.
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
    * @brief Implements the modified Euler method.
    * It uses a half-step before calculating the full step.
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
   modified_euler(T start, index_t i, T dt, T& t, T& y, T (*func)(T, T)) 
   {
      t = start + i * dt;
      y += dt * func(t + static_cast<T>(.5) * dt, y + static_cast<T>(.5) * dt * func(t, y));
   }

   /**
    * @brief Implements the Runge-Kutta (4th order) method.
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
   runge_kutta_o4(T start, index_t i, T dt, T& t, T& y, T (*func)(T, T)) 
   {
      t = start + i * dt;
      T k1 = func(t, y);
      T k2 = func(t + static_cast<T>(.5) * dt, y + static_cast<T>(.5) * dt * k1);
      T k3 = func(t + static_cast<T>(.5) * dt, y + static_cast<T>(.5) * dt * k2);
      T k4 = func(t + dt, y + dt * k3);
      y += (dt / static_cast<T>(6)) * (k1 + static_cast<T>(2) * k2 + static_cast<T>(2) * k3 + k4);
   }

   /**
    * @brief Implements the Adams-Bashforth method (two-step).
    * https://en.wikipedia.org/wiki/Linear_multistep_method
    * 
    * @tparam T Supports float, double and long double.
    * @tparam index_t Supports int, long, long long, and size_t.
    * @param t0 [in] The starting value of the independent coordinate.
    * @param i [in] The number of steps to take.
    * @param dt [in] The resolution of the independent coordinate.
    * @param t [out] The value of the independent coordinate.
    * @param y0 [in] The value of the function two steps back.
    * @param y1 [in] The value of the function one step back.
    * @param ynew [out] The new value.
    * @param f The function to calculate.
    */
   template <typename T, typename index_t>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value && 
      (std::is_same<index_t, int>::value || std::is_same<index_t, long>::value || 
      std::is_same<index_t, long long>::value || std::is_same<index_t, size_t>::value), void>::type
   adams_bashforth(T t0, index_t i, T dt, T& t, 
      T& y0, T& y1, T& ynew, T (*func)(T, T)) 
   {
      ynew = y1 + dt * (static_cast<T>(1.5) * func(t, y1) - static_cast<T>(.5) * func(t - dt, y0));
      t = t0 + i * dt;
   }

}