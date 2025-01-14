#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <cmath>
#include <algorithm>
#include <type_traits>

#ifdef __NVCC__
#include <device_launch_parameters.h>
#define HOSTDEVDECOR    __host__ __device__
#else 
#define HOSTDEVDECOR
#endif

#define ONE_EIGHTY_DEG           180.0

namespace maths_ops 
{
   /**
    * @brief Returns the 1D array index given the 
    * 2D indexes and the number of columns.
    * 
    * Applies to storage of an array in row-major order (C-like).
    * 
    * @tparam T supports int, long, long long and size_t
    * @param irow [in] The row index.
    * @param icol [in] The column index.
    * @param ncols [in] The number of columns of the 2D array.
    * @return The linear index.
    */
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<
      std::is_same<T, int>::value || 
      std::is_same<T, long>::value ||
      std::is_same<T, long long>::value ||
      std::is_same<T, size_t>::value, T>::type        // Enabling function using SFINAE
   get_row_major_linear_index(const T irow, const T icol, const T ncols)
   {
      return irow * ncols + icol;
   }

   /**
    * @brief Returns the 1D array index given the 
    * 2D indexes and the number of rows.
    * 
    * Applies to storage of an array in column-major order (Fortran-like).
    * 
    * @tparam T supports int, long, long long and size_t
    * @param irow [in] The row index.
    * @param icol [in] The column index.
    * @param nrows [in] The number of rows of the 2D array.
    * @return The linear index.
    */
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<
      std::is_same<T, int>::value || 
      std::is_same<T, long>::value ||
      std::is_same<T, long long>::value ||
      std::is_same<T, size_t>::value, T>::type        // Enabling function using SFINAE
   get_column_major_linear_index(const T irow, const T icol, const T nrows)
   {
      return icol * nrows + irow;
   }

   /**
    * @brief Calculates the row and column indexes for an
    * element in a 2D array stored in a flat arrangement in
    * a row-major order (C-like).
    * 
    * @tparam T supports int, long, long long and size_t
    * @param irow [out] The row index.
    * @param icol [out] The column index.
    * @param ncols [in] The number of columns of the 2D array.
    * @param idx [in] The 1D (linear) index to translate.
    */ 
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<
      std::is_same<T, int>::value || 
      std::is_same<T, long>::value ||
      std::is_same<T, long long>::value ||
      std::is_same<T, size_t>::value, void>::type        // Enabling function using SFINAE
   get_2D_indices_from_row_major_linear_index(T* irow, T* icol, const T ncols, const T idx)
   {
      *irow = idx / ncols;
      *icol = idx % ncols;
   }

   /**
    * @brief Calculates the row and column indexes for an
    * element in a 2D array stored in a flat arrangement in
    * a column-major order (Fortran-like).
    * 
    * @tparam T supports int, long, long long and size_t
    * @param irow [out] The row index.
    * @param icol [out] The column index.
    * @param nrows [in] The number of rows of the 2D array.
    * @param idx [in] The 1D (linear) index to translate.
    */ 
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<
      std::is_same<T, int>::value || 
      std::is_same<T, long>::value ||
      std::is_same<T, long long>::value ||
      std::is_same<T, size_t>::value, void>::type        // Enabling function using SFINAE
   get_2D_indices_from_column_major_linear_index(T* irow, T* icol, const T nrows, const T idx)
   {
      *irow = idx % nrows;
      *icol = idx / nrows;
   }

   /** 
    * @brief Compares two floating point numbers for equality
    * within some tolerance.
    * 
    * @tparam T supports float, double and long double
    * @param a [in] The first number.
    * @param b [in] The second number.
    * @param epsilon [in] The tolerance parameter. Defaults to FLT_EPSILON, DBL_EPSILON or LDBL_EPSILON based on the data type in operation.
    */
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value, bool>::type
   are_equal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) 
   {
      return std::fabs(a - b) < epsilon;
   }

   /**
    * @brief Translates an angle in degrees to radians.
    * 
    * Does not apply any limitations to the input or output values
    * 
    * @tparam T supports float, double and long double
    * @param d [in] Angle in degrees.
    * @return Angle in radians.
    */
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   deg_to_rad(const T d)
   {
      return M_PI * d / ONE_EIGHTY_DEG;
   }

   /**
    * @brief Translates and angle in radians to degrees.
    * 
    * Does not apply any limitations to the input or output values
    * 
    * @tparam T Supports float, double and long double.
    * @param r [in] Angle in radians.
    * @return Angle in degrees.
    */
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   rad_to_deg(const T r)
   {
      return ONE_EIGHTY_DEG * r / M_PI;
   }

   /**
    * @brief Limits an angle in degrees between the values of 0 and 360.
    * 
    * @tparam T supports float, double and long double
    * @param d [in] Angle in degrees.
    * @return Angle adjusted in range [0, 360]
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   get_0_360_deg(T d)
   {
      while (d < 0) {
         d += 360;
      }
      while (d > 360) {
         d -= 360;
      }
      return d;
   }

   /**
    * @brief Limits an angle in radians between the values of 0 and 2*PI.
    * 
    * @tparam T supports float, double and long double
    * @param r [in] Angle in radians.
    * @return Angle adjusted in range [0, 2*PI]
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   get_0_2pi_rad(T r)
   {
      while (r < 0) {
         r += 2 * M_PI;
      }
      while (r >= 2 * M_PI) {
         r -= 2 * M_PI;
      }
      return r;
   }

   /**
    * @brief Converts an angle in degrees to follow the compass convention.
    * That is 0 deg = North - up. A positive angle rotates clockwise.
    * 
    * @tparam T Supports float, double and long double.
    * @param d [in] Angle in degrees.
    * @return Angle converted to the 0-up system.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   to_compass_angle_deg(T d)
   {
      d = 90 - d;
      return get_0_360_deg(d);
   }

   /**
    * @brief Converts an angle in radians to follow the compass convention.
    * That is 0 rad = North - up. A positive angle rotates clockwise.
    * 
    * @tparam T Supports float, double and long double.
    * @param r [in] Angle in radians.
    * @return Angle converted to the 0-up system.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   to_compass_angle_rad(T r)
   {
      r = (M_PI / 2) - r;
      return get_0_2pi_rad(r);
   }

   /**
    * @brief Converts an angle of a vector in degrees to follow the meteorological convention.
    * That is 0 deg = North - up. A positive angle rotates clockwise. 
    * Angle indicates the point of origin
    * 
    * @tparam T Supports float, double and long double.
    * @param r [in] Angle in degrees.
    * @return Angle converted to the meteorological convention.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   convert_to_meteorological_dir_deg(T d)
   {
      d += 180;
      return get_0_360_deg(d);
   }

   /**
    * @brief Converts an angle of a vector in radians to follow the meteorological convention.
    * That is 0 rad = North - up. A positive angle rotates clockwise. 
    * Angle indicates the point of origin
    * 
    * @tparam T Supports float, double and long double.
    * @param r [in] Angle in radians.
    * @return Angle converted to the meteorological convention.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   convert_to_meteorological_dir_rad(T r)
   {
      r += M_PI;
      return get_0_2pi_rad(r);
   }

   /**
    * @brief Calculates the magnitude of a (euclidean) vector.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam T Supports float, double and long double.
    * @param x [in] The x-component of the vector.
    * @param y [in] The y-component of the vector.
    * @return Vector magnitude.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   vector_magnitude(const T x, const T y)
   {
      return std::sqrt(x * x + y * y);
   }

   /**
    * @brief Calculates the direction of a (euclidean) vector.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam T Supports float, double and long double.
    * @param x [in] The x-component of the vector.
    * @param y [in] The y-component of the vector.
    * @return Vector direction in radians.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   vector_direction(const T x, const T y)
   {
      return std::atan2(y, x);
   }

   /**
    * @brief Calculates the squared value of the distance 
    * between two points in euclidean space.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam T Supports float, double and long double.
    * @param x1 [in] The x-coordinate of the first point.
    * @param y1 [in] The y-coordinate of the first point.
    * @param x2 [in] The x-coordinate of the second point.
    * @param y2 [in] The y-coordinate of the second point.
    * @return Distance squred.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   points_squared_distance(const T x1, const T y1, const T x2, const T y2)
   {
      return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
   }

   /**
    * @brief Calculates the euclidean distance 
    * between two points in euclidean space.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam T Supports float, double and long double.
    * @param x1 [in] The x-coordinate of the first point.
    * @param y1 [in] The y-coordinate of the first point.
    * @param x2 [in] The x-coordinate of the second point.
    * @param y2 [in] The y-coordinate of the second point.
    * @return Distance.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   points_distance(const T x1, const T y1, const T x2, const T y2)
   {
      return std::sqrt(points_squared_distance(x1, y1, x2, y2));
   }

   /**
    * @brief Calculates the 2D rotation matrix.
    * 
    * @tparam T Supports float, double and long double.
    * @param angle_rad [in] The angle in radians.
    * @param rotation_matrix [out] The rotation matrix. Must have at least 4 elements. Memory allocation must happen before calling this
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, void>::type
   calculate_rotation_matrix(T angle_rad, T* rotation_matrix)
   {
      rotation_matrix[0] = std::cos(angle_rad);
      rotation_matrix[1] = -std::sin(angle_rad);
      rotation_matrix[2] = std::sin(angle_rad);
      rotation_matrix[3] = std::cos(angle_rad);
   }

   /**
    * @brief Translates a 2D point in 2D.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam T Supports float, double and long double.
    * @param x [inout] The x-coordinate of the point.
    * @param y [inout] They y-coordinate of the point.
    * @param dx [in] The displacement in x-direction.
    * @param dy [in] The displacement in y-direction.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, void>::type
   translate_point(T* x, T* y, const T dx, const T dy)
   {
      *x += dx;
      *y += dy;
   }

   /**
    * @brief Rotates a 2D point given the rotation matrix.
    * The point is rotated about the axes origin.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam T Supports float, double and long double.
    * @tparam RM Supports float, double and long double.
    * @param x [inout] The x-coordinate of the point.
    * @param y [inout] The y-coordinate of the point.
    * @param rotation_matrix [in] The rotation matrix to be applied.
    */
   template <typename T, typename RM>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value && std::is_floating_point<RM>::value, void>::type
   rotate_point(T* x, T* y, const RM* rotation_matrix)
   {
      T xtemp = *x;
      T ytemp = *y;
      *x = static_cast<T>(rotation_matrix[0] * xtemp + rotation_matrix[1] * ytemp);
      *y = static_cast<T>(rotation_matrix[2] * xtemp + rotation_matrix[3] * ytemp);
   }

   /**
    * @brief Rotates a 2D point about another point in 2D space.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam T Supports float, double and long double.
    * @tparam RM Supports float, double and long double.
    * @tparam Tref Supports float, double and long double.
    * @param x [inout] The x-coordinate of the point.
    * @param y [inout] The y-coordinate of the point.
    * @param rot_mat [in] The rotation matrix to be applied.
    * @param xref [in] The x-coordinate of the point to rotate about.
    * @param yref [in] The y-coordinate of the point to rotate about.
    */
   template <typename T, typename RM, typename Tref>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value && 
      std::is_floating_point<RM>::value &&
      std::is_floating_point<Tref>::value, void>::type
   rotate_point_about(T* x, T* y, const RM* rot_mat, const Tref xref, const Tref yref)
   {
      translate_point(x, y, -xref, -yref);
      rotate_point(x, y, rot_mat);
      translate_point(x, y, xref, yref);
   }

   /**
    * @brief Calculates the dot product of two vectors in 2D.
    * 
    * @tparam T Supports float, double and long double.
    * @param a_x [in] The x-component of the first vector.
    * @param a_y [in] The y-component of the first vector.
    * @param b_x [in] The x-component of the second vector.
    * @param b_y [in] The y-component of the second vector.
    * @return Dot product.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   dot_product(const T a_x, const T a_y, const T b_x, const T b_y)
   {
      return a_x * b_x + a_y * b_y;
   }

   /**
    * @brief Calculates the z-component of the cross-product of 
    * two vectors in 2D space.
    * 
    * @tparam T Supports float, double and long double.
    * @param a_x [in] The x-component of the first vector.
    * @param a_y [in] The y-component of the first vector.
    * @param b_x [in] The x-component of the second vector.
    * @param b_y [in] The y-component of the second vector.
    * @return z-component of the cross product.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   cross_product(const T a_x, const T a_y, const T b_x, const T b_y)
   {
      return a_x * b_y - a_y * b_x;
   }

   /**
    * @brief Creates the geotransform array according to
    * https://gdal.org/en/latest/tutorials/geotransforms_tut.html.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam GT Supports float, double and long double.
    * @tparam T Supports float, double and long double.
    * @param geotransform [out] The geotransform array. Must be at least 6 elements long. Memory allocation must happen before calling this.
    * @param x_top_left [in] x-coordinate of the top left corner of the image.
    * @param y_top_left [in] y-coordinate of the top left corner of the image.
    * @param dx [in] x-coordinate of the image resolution. For rotated images, it corresponds to the "horizontal" analysis if the image was north-up. Must be positive.
    * @param dy [in] y-coordinate of the image resolution. For rotated images, it corresponds to the "vertical" analysis if the image was north-up. Must be positive.
    * @param angle_rad [in] Angle of rotation of the image in radians.
    */
   template <typename GT, typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<GT>::value && std::is_floating_point<T>::value, void>::type
   set_affine_geotransform(GT* geotransform, 
      const T x_top_left, const T y_top_left, const T dx, const T dy, const T angle_rad)
   {
      geotransform[0] = static_cast<GT>(x_top_left);
      geotransform[1] = static_cast<GT>(dx * std::cos(angle_rad));
      geotransform[2] = static_cast<GT>(dy * std::sin(angle_rad));
      geotransform[3] = static_cast<GT>(y_top_left);
      geotransform[4] = static_cast<GT>(dx * std::sin(angle_rad));
      geotransform[5] = static_cast<GT>(-dy * std::cos(angle_rad));
   }

   /**
    * @brief Retrieve the information used to build the geotransform
    * according to https://gdal.org/en/latest/tutorials/geotransforms_tut.html.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam T Supports float, double and long double.
    * @tparam GT Supports float, double and long double.
    * @param x_top_left [out] x-coordinate of the top left corner of the image.
    * @param y_top_left [out] y-coordinate of the top left corner of the image.
    * @param dx [out] x-coordinate of the image resolution. For rotated images, it corresponds to the "horizontal" analysis if the image was north-up.
    * @param dy [out] y-coordinate of the image resolution. For rotated images, it corresponds to the "vertical" analysis if the image was north-up.
    * @param angle_rad [out] Angle of rotation of the image in radians.
    * @param geotransform [in] The geotransform array.
    */
   template <typename T, typename GT>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value && std::is_floating_point<GT>::value, void>::type
   decrypt_affine_geotransform(T* x_top_left, T* y_top_left,
      T* dx, T* dy, T* angle_rad, const GT* geotransform)
   {
      // Get the origin
      *x_top_left = static_cast<T>(geotransform[0]);
      *y_top_left = static_cast<T>(geotransform[3]);

      // Get the angle as well as the resolution
      *angle_rad = std::atan(geotransform[4] / geotransform[1]);
      if (std::abs(*angle_rad) > 1.e-6) {
         *dx = geotransform[1] / std::cos(*angle_rad);
         *dy = -geotransform[5] / std::cos(*angle_rad);
      }
      else {
         *dx = geotransform[1];
         *dy = -geotransform[5];
      }
   }

   /**
    * @brief Applies the geotransform to calculate the x and y
    * coordinates of an image according to 
    * https://gdal.org/en/latest/tutorials/geotransforms_tut.html.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam T Supports float, double and long double.
    * @tparam index_t Supports any data type that is numerical or can be converted (implicitly or not) to a numerical value.
    * @tparam GT Supports float, double and long double.
    * @param x [out] x-coordinate of the point (pixel).
    * @param y [out] y-coordinate of the point (pixel).
    * @param irow [in] The row index to use for the pixel.
    * @param icol [in] The column index to use for the pixel.
    * @param geotransform [in] The geotransform array.
    */
   template <typename T, typename index_t, typename GT>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value && 
      std::is_arithmetic<index_t>::value &&
      std::is_floating_point<GT>::value, void>::type
   apply_geotransform(T* x, T* y, 
      const index_t irow, const index_t icol, const GT* geotransform)
   {
      *x = static_cast<T>(geotransform[0] + icol * geotransform[1] + irow * geotransform[2]);
      *y = static_cast<T>(geotransform[3] + icol * geotransform[4] + irow * geotransform[5]);
   }

   /**
    * @brief Applies the inverse geotransform to retrieve the 
    * row and column indexes for a pixel given the x and y 
    * coordinates according to https://gdal.org/en/latest/tutorials/geotransforms_tut.html.
    * 
    * The result is rounded to the nearest integer value. No bound or overflow checks.
    * 
    * It does not perform any sanity checks on the input values.
    * 
    * @tparam index_t Supports int, long, long long and size_t.
    * @tparam T Supports float, double and long double.
    * @tparam GT Supports float, double and long double.
    * @param irow [out] Row index.
    * @param icol [out] Column index.
    * @param x [in] x-coordinate of the pixel.
    * @param y [in] y-coordinate of the pixel.
    * @param geotransform [in] The geotransform array.
    */
   template <typename index_t, typename T, typename GT>
   HOSTDEVDECOR 
   typename std::enable_if<
      (std::is_same<index_t, int>::value || std::is_same<index_t, long>::value || std::is_same<index_t, long long>::value || std::is_same<index_t, size_t>::value) &&
      std::is_floating_point<T>::value && 
      std::is_floating_point<GT>::value, void>::type
   apply_inverse_geotransform(index_t* irow, index_t* icol, 
      const T x, const T y, const GT* geotransform)
   {
      T Dx = static_cast<T>(x - geotransform[0]);
      T Dy = static_cast<T>(y - geotransform[3]);

      T det = static_cast<T>(geotransform[1] * geotransform[5] - geotransform[2] * geotransform[4]);
      T det_icol = static_cast<T>(Dx * geotransform[5] - geotransform[2] * Dy);
      T det_irow = static_cast<T>(geotransform[1] * Dy - Dx * geotransform[4]);

      *irow = static_cast<index_t>(std::round(det_irow / det));
      *icol = static_cast<index_t>(std::round(det_icol / det));
   }

   /**
    * @brief Calculates the unit vector components of a 2D vector.
    * 
    * @tparam T Supports float, double, long double.
    * @param unit_vec_x [out] x-component of the unit vector.
    * @param unit_vec_y [out] y-component of the unit vector.
    * @param original_vec_x [in] x-component of the 2D vector.
    * @param original_vec_y [in] y-component of the 2D vector.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, void>::type
   unit_vector(T* unit_vec_x, T* unit_vec_y,
      const T original_vec_x, const T original_vec_y)
   {
      constexpr T zero_theshold = std::numeric_limits<T>::epsilon();
      constexpr T mag = vector_magnitude(original_vec_x, original_vec_y);
      if (mag > zero_theshold) {
         *unit_vec_x = original_vec_x / mag;
         *unit_vec_y = original_vec_y / mag;
      }
      else {
         *unit_vec_x = original_vec_x;
         *unit_vec_y = original_vec_y;
      }
   }

   /**
    * @brief Calculates the component of a vector that 
    * is parallel to a given line segment.
    * 
    * @tparam T Supports float, double, long double.
    * @param vec_x [in] x-component of the input vector.
    * @param vec_y [in] y-component of the input vector.
    * @param ref_line_start_x [in] x-coordinate of the starting point of the line segment.
    * @param ref_line_start_y [in] y-coordinate of the starting point of the line segment.
    * @param ref_line_end_x [in] x-coordinate of the ending point of the line segment.
    * @param ref_line_end_y [in] y-coordinate of the ending point of the line segment.
    * @return Vector component parallel to the line segment.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   parallel_vector_component(
      const T vec_x, const T vec_y,
      const T ref_line_start_x, const T ref_line_start_y,
      const T ref_line_end_x, const T ref_line_end_y)
   {
      T line_vec_x = ref_line_end_x - ref_line_start_x;
      T line_vec_y = ref_line_end_y - ref_line_start_y;
      T unit_vec_x = static_cast<T>(0), unit_vec_y = static_cast<T>(0);
      unit_vector(&unit_vec_x, &unit_vec_y, line_vec_x, line_vec_y);

      return dot_product(vec_x, vec_y, unit_vec_x, unit_vec_y);
   }

   /**
    * @brief Calculates the component of a vector that 
    * is perpendicular (normaL) to a given line segment.
    * 
    * @tparam T Supports float, double, long double.
    * @param vec_x [in] x-component of the input vector.
    * @param vec_y [in] y-component of the input vector.
    * @param ref_line_start_x [in] x-coordinate of the starting point of the line segment.
    * @param ref_line_start_y [in] y-coordinate of the starting point of the line segment.
    * @param ref_line_end_x [in] x-coordinate of the ending point of the line segment.
    * @param ref_line_end_y [in] y-coordinate of the ending point of the line segment.
    * @return Vector component perpendicular to the line segment.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   perpendicular_vector_component(
      const T vec_x, const T vec_y,
      const T ref_line_start_x, const T ref_line_start_y,
      const T ref_line_end_x, const T ref_line_end_y)
   {
      T line_vec_x = ref_line_end_x - ref_line_start_x;
      T line_vec_y = ref_line_end_y - ref_line_start_y;
      T unit_vec_x = static_cast<T>(0), unit_vec_y = static_cast<T>(0);
      unit_vector(&unit_vec_x, &unit_vec_y, line_vec_x, line_vec_y);

      return cross_product(unit_vec_x, unit_vec_y, vec_x, vec_y);
   }

   /**
    * @brief Calculates a term of the Shoelace formula.
    * https://en.wikipedia.org/wiki/Shoelace_formula
    * 
    * @tparam T Supports float, double, long double.
    * @param x1 [in] x-coordinate of first point.
    * @param y1 [in] y-coordinate of first point.
    * @param x2 [in] x-coordinate of second point.
    * @param y2 [in] y-coordinate of second point.
    * @return Value of the term.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   shoelace_term(T x1, T y1, T x2, T y2)
   {
      return cross_product(x1, y1, x2, y2);
   }

   /**
    * @brief Calculates the coefficients A, B, C of the generalised
    * line equation given two points in 2D.
    * Eqn: Ax + By + C = 0
    * 
    * @tparam T Supports float, double, long double.
    * @param x1 [in] x-coordinate of first point.
    * @param y1 [in] y-coordinate of first point.
    * @param x2 [in] x-coordinate of second point.
    * @param y2 [in] y-coordinate of second point.
    * @param a [out] Value of coefficient A.
    * @param b [out] Value of coefficient B.
    * @param c [out] Value of coefficient C.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, void>::type 
   get_generalised_line_eqn_coeff(T x1, T y1, T x2, T y2, T* a, T* b, T* c)
   {
      *a = y1 - y2;
      *b = x2 - x1;
      *c = x1 * y2 - x2 * y1;
   }

   /**
    * @brief Calculates the distance (normal) of a point 
    * to a line in 2D space.
    * 
    * @tparam T Supports float, double, long double.
    * @param x1 [in] x-coordinate of the first point on the line segment.
    * @param y1 [in] y-coordinate of the first point on the line segment.
    * @param x2 [in] x-coordinate of the second point on the line segment.
    * @param y2 [in] y-coordinate of the second point on the line segment.
    * @param xp [in] x-coordinate of the point.
    * @param yp [in] y-coordinate of the point.
    * @return The distance from the point to the line segment.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type 
   distance_point_to_line(T x1, T y1, T x2, T y2, T xp, T yp)
   {
      T a, b, c;
      get_line_coeff(x1, y1, x2, y2, &a, &b, &c);
      return std::abs(a * xp + b * yp + c) / std::sqrt(a * a + b * b);
   }

   /**
    * @brief Checks whether a point is on the left 
    * of a directed (signed) line segment using the 
    * outer product of the vectors defined by (1) the
    * line segment and (2) the starting point of the 
    * line segment and the test point.
    * 
    * @tparam T Supports float, double, long double.
    * @param xstart [in] x-coordinate of the starting point of the line segment.
    * @param ystart [in] y-coordinate of the starting point of the line segment.
    * @param xend [in] x-coordinate of the ending point of the line segment.
    * @param yend [in] y-coordinate of the ending point of the line segment.
    * @param xp [in] x-coordinate of the point to test.
    * @param yp [in] y-coordinate of the point to test.
    * @return 1 if point is on the left, 0 otherwise.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, int>::type 
   is_point_to_left_of_line_segment(T xstart, T ystart, T xend, T yend, T xp, T yp)
   {
      return (xend - xstart) * (yp - ystart) - (yend - ystart) * (xp - xstart) > 0 ? 1 : 0;
   }

   /**
   * @brief Calculates the coefficients of the equation 
   * of a line given points p and q in the slope-intercept 
   * form: y = m * x + b.
   * 
   * @tparam T Supports float, double, long double.
   * @param m [out] Slope of the line.
   * @param b [out] y-intersept constant of the line.
   * @param px [in] x coordinate of the line's starting point.
   * @param py [in] y coordinate of the line's starting point.
   * @param qx [in] x coordinate of the line's ending point.
   * @param qy [in] y coordinate of the line's ending point.
   */
   template <typename T> 
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, void>::type 
   get_line_equation_intercept(T* m, T* b, T px, T py, T qx, T qy)
   {
      *m = (qy - py) / (qx - px);
      *b = py - (*m) * px;
   };

   /**
   * @brief Calculates the coefficients of the equation 
   * of a line given points p and q in the standard form: 
   * Ax + By + C = 0.
   *
   * @tparam T Supports float, double, long double.
   * @param A [out] Coefficient of the x coordinate of the equation.
   * @param B [out] Coefficient of the y coordinate of the equation.
   * @param C [out] Constant coefficient  of the equation.
   * @param px [in] x coordinate of the line's starting point.
   * @param py [in] y coordinate of the line's starting point.
   * @param qx [in] x coordinate of the line's ending point.
   * @param qy [in] y coordinate of the line's ending point.
   */
   template <typename T> 
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, void>::type 
   get_line_equation_standard(T* A, T* B, T* C, T px, T py, T qx, T qy) 
   {
      *A = qy - py;
      *B = px - qx;
      *C = -((*A) * px + (*B) * py);
   };

   /**
    * @brief Implements a linear interpolation in 1D.
    *
    * Based on https://en.wikipedia.org/wiki/Linear_interpolation.
    * It does not perform any sanity check for the input values.
    *
    * @tparam T Supports float, double and long double.
    * @param x [in] The x-coordinate where the value is needed.
    * @param x0 [in] The min x-coordinate where the value of the function is known.
    * @param y0 [in] The value of the function at x0.
    * @param x1 [in] The max x-coordinate where the value of the function is known.
    * @param y1 [in] The value of the function at x1.
    * @return The interpolated value.
    */
   template <typename T>
   HOSTDEVDECOR 
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   interp_linear(const T x, const T x0, const T y0, const T x1, const T y1)
   {
      return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
   }

   /**
    * @brief Implements logarithm for any base.
    * 
    * @tparam T Supports float, double and long double.
    * @param x [in] The number of which to calculate the logarithm.
    * @param base [in] The base of the logarithm.
    * @return The logarithm value.
    */
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value, T>::type
   logarithm(const T x, const T base)
   {
      return std::log10(x) / std::log10(base);
   }

   /**
    * @brief Calculates the integral of a function using 
    * the Simpson's rule (https://en.wikipedia.org/wiki/Simpson%27s_rule).
    * 
    * @tparam T Supports float, double and long double.
    * @tparam num_t Supports int, long, long long, and size_t.
    * @param first [in] The starting value of the interval to calculate the integral for.
    * @param last [in] The last value of the interval to calculate the integral for.
    * @param npoints [in] The number of points to use for the integral.
    * @param f The function to integrate.
    * @return The value of the integral.
    */
   template <typename T, typename num_t>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value && 
      (std::is_same<num_t, int>::value || std::is_same<num_t, long>::value || 
      std::is_same<num_t, long long>::value || std::is_same<num_t, size_t>::value), T>::type
   simpson(const T first, const T last, const num_t npoints, T (*func)(T)) {
      T h = (last - first) / npoints;
      T integral = static_cast<T>(0.);

      for (auto i = 0; i < npoints - 1; i += 2)
         integral += func(first + h * i) + 4.f * f(first + h * (i + 1)) + f(first + h * (i + 2));

      return h * integral / static_cast<T>(3.);
   }

   /**
    * @brief Calculates the integral of a function using 
    * the Newton-Cotes formula for Trapezoidal (https://en.wikipedia.org/wiki/Newton%E2%80%93Cotes_formulas).
    * 
    * @tparam T Supports float, double and long double.
    * @tparam num_t Supports int, long, long long, and size_t.
    * @param first [in] The starting value of the interval to calculate the integral for.
    * @param last [in] The last value of the interval to calculate the integral for.
    * @param npoints [in] The number of points to use for the integral.
    * @param f The function to integrate.
    * @return The value of the integral.
    */
   template <typename T, typename num_t>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value && 
      (std::is_same<num_t, int>::value || std::is_same<num_t, long>::value || 
      std::is_same<num_t, long long>::value || std::is_same<num_t, size_t>::value), T>::type
   newton_cotes(T first, T last, num_t npoints, T (*f)(T)) 
   {
      T h = (last - first) / npoints;
      T integral = static_cast<T>(0.);

      for (auto i = 0; i < npoints; ++i)
         integral += f(first + i * h) + f(first + (i + 1) * h);

      return h * integral / static_cast<T>(2.);
   }

   /**
    * @brief Calculates the integral of a function using 
    * the Newton-Cotes formula for Simpson's 3/8 (https://en.wikipedia.org/wiki/Newton%E2%80%93Cotes_formulas).
    * 
    * @tparam T Supports float, double and long double.
    * @tparam num_t Supports int, long, long long, and size_t.
    * @param first [in] The starting value of the interval to calculate the integral for.
    * @param last [in] The last value of the interval to calculate the integral for.
    * @param npoints [in] The number of points to use for the integral.
    * @param f The function to integrate.
    * @return The value of the integral.
    */
   template <typename T, typename num_t>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value && 
      (std::is_same<num_t, int>::value || std::is_same<num_t, long>::value || 
      std::is_same<num_t, long long>::value || std::is_same<num_t, size_t>::value), T>::type
   newton_cotes38f(T first, T last, num_t npoints, T (*f)(T)) 
   {
      T h = (last - first) / npoints;
      T integral = static_cast<T>(0.);

      for (auto i = 0; i < npoints - 2; i += 3)
         integral += f(first + i * h) + 3.f * f(first + (i + 1) * h) + 3.f * f(first + (i + 2) * h) + f(first + (i + 3) * h);

      return static_cast<T>(3.) * h * integral / static_cast<T>(8.);
   }

   /**
    * @brief Calculates the integral of a function using 
    * the Gauss-Chebysev method (https://en.wikipedia.org/wiki/Chebyshev%E2%80%93Gauss_quadrature) 
    * 
    * @tparam T Supports float, double and long double.
    * @tparam num_t Supports int, long, long long, and size_t.
    * @param first [in] The starting value of the interval to calculate the integral for.
    * @param last [in] The last value of the interval to calculate the integral for.
    * @param npoints [in] The number of points to use for the integral.
    * @param f The function to integrate.
    * @return The value of the integral.
    */
   template <typename T, typename num_t>
   HOSTDEVDECOR
   typename std::enable_if<std::is_floating_point<T>::value && 
      (std::is_same<num_t, int>::value || std::is_same<num_t, long>::value || 
      std::is_same<num_t, long long>::value || std::is_same<num_t, size_t>::value), T>::type 
   gauss_chebyshev(T first, T last, num_t npoints, T (*f)(T)) 
   {
      T out{ 0 };
      T x_i{ 0 };
      T arg{ 0 };
      T diff{ last - first };
      T sum{ last + first };

      for (auto i = 0; i <= npoints; ++i) {
         arg = static_cast<T>(M_PI) * (2 * i + 1) / (2 * (npoints + 1));
         x_i = -std::cos(arg);
         out += std::sin(arg) * f(static_cast<T>(0.5) * diff * x_i + static_cast<T>(0.5) * sum);
      }
      return static_cast<T>(0.5) * diff * (static_cast<T>(M_PI) / (npoints + 1)) * out;
   }


}

