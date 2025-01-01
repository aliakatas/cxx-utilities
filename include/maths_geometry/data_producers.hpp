#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

// #include <cmath>
// #include <algorithm>
#include <type_traits>
#include <cstdlib>

#ifdef __NVCC__
#include <device_launch_parameters.h>
#define HOSTDEVDECOR    __host__ __device__
#else 
#define HOSTDEVDECOR
#endif

namespace dataprod
{  
   /**
    * @brief 
    * 
    * @tparam T 
    * @tparam num_t 
    * 
    */
   template <typename T, typename num_t>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value && 
      std::is_integral<num_t>::value, void>::type
   gradient_1D(T* data, num_t n, T start, T finish)
   {
      T dd = (finish - start) / (n - 1);
      for (auto i = 0; i < n; ++i)
         data[i] = start + i * dd;
   }

   /**
    * @brief 
    * 
    * @tparam T 
    * @tparam num_t 
    * 
    */
   template <typename T, typename num_t>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value && 
      std::is_integral<num_t>::value, void>::type
   random_1D(T* data, num_t n, T minval, T maxval)
   {
      T dd = (finish - start) / (n - 1);
      for (auto i = 0; i < n; ++i)
         data[i] = minval + (static_cast<T>(std::rand()) / stati_cast<T>(RAND_MAX)) * (maxval - minval);
   }

   // TODO:
   //   - gradient 2D
   //   - random 2D
   //   - waves 1D
   //   - waves 2D
   //   - modify 1D domain with features (using set values)
   //   - modify 2D domain with features (using set values)


}
