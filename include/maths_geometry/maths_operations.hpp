#ifndef MATHS_OPERATIONS_H
#define MATHS_OPERATIONS_H

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
#define DEFAULT_ZERO_THRESHOLD   0.00001

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
   typename std::enable_if<
      std::is_same<T, float>::value || 
      std::is_same<T, double>::value ||
      std::is_same<T, long double>::value, bool>::type
   are_equal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) {
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
   typename std::enable_if<
      std::is_same<T, float>::value || 
      std::is_same<T, double>::value ||
      std::is_same<T, long double>::value, T>::type
   deg_to_rad(const T d)
   {
      return M_PI * d / ONE_EIGHTY_DEG;
   }

   /**
    * @brief Translates and angle in radians to degrees.
    * 
    * Does not apply any limitations to the input or output values
    * 
    * @tparam T supports float, double and long double
    * @param r [in] Angle in radians.
    * @return Angle in degrees.
    */
   template <typename T>
   HOSTDEVDECOR
   typename std::enable_if<
      std::is_same<T, float>::value || 
      std::is_same<T, double>::value ||
      std::is_same<T, long double>::value, T>::type
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
   typename std::enable_if<
      std::is_same<T, float>::value || 
      std::is_same<T, double>::value ||
      std::is_same<T, long double>::value, T>::type
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
   typename std::enable_if<
      std::is_same<T, float>::value || 
      std::is_same<T, double>::value ||
      std::is_same<T, long double>::value, T>::type
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
   typename std::enable_if<
      std::is_same<T, float>::value || 
      std::is_same<T, double>::value ||
      std::is_same<T, long double>::value, T>::type
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
   typename std::enable_if<
      std::is_same<T, float>::value || 
      std::is_same<T, double>::value ||
      std::is_same<T, long double>::value, T>::type
   to_compass_angle_rad(T r)
   {
      r = (M_PI / 2) - r;
      return get_0_2pi_rad(r);
   }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T convert_to_meteorological_dir_deg(T d)
   // {
   //    d += 180;
   //    return get_0_360_deg(d);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T convert_to_meteorological_dir_rad(T r)
   // {
   //    r += M_PI;
   //    return get_0_2pi_rad(r);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T vector_magnitude(const T x, const T y)
   // {
   //    return sqrt(x * x + y * y);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T vector_direction(const T x, const T y)
   // {
   //    return atan2(y, x);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T points_squared_distance(const T x, const T y, const T x_origin, const T y_origin)
   // {
   //    return (x - x_origin) * (x - x_origin) + (y - y_origin) * (y - y_origin);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T points_distance(const T x, const T y, const T x_origin, const T y_origin)
   // {
   //    return vector_magnitude(x - x_origin, y - y_origin);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR void calculate_rotation_matrix(T angle_rad, T* rotation_matrix)
   // {
   //    rotation_matrix[0] = cos(angle_rad);
   //    rotation_matrix[1] = -sin(angle_rad);
   //    rotation_matrix[2] = sin(angle_rad);
   //    rotation_matrix[3] = cos(angle_rad);
   // }

   // //##################################################################
   // template <typename T, typename RM>
   // HOSTDEVDECOR void rotate_point(T* x, T* y, const RM* rotation_matrix)
   // {
   //    T xtemp = *x;
   //    T ytemp = *y;
   //    *x = rotation_matrix[0] * xtemp + rotation_matrix[1] * ytemp;
   //    *y = rotation_matrix[2] * xtemp + rotation_matrix[3] * ytemp;
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR void translate_point(T* x, T* y, const T x0, const T y0)
   // {
   //    *x += x0;
   //    *y += y0;
   // }

   // //##################################################################
   // template <typename T, typename RM, typename Tref>
   // HOSTDEVDECOR void rotate_point_about(T* x, T* y, const RM* rot_mat, const Tref xref, const Tref yref)
   // {
   //    *x -= xref;
   //    *y -= yref;
   //    T xnew = *x * rot_mat[0] + *y * rot_mat[1];
   //    T ynew = *x * rot_mat[2] + *y * rot_mat[3];
   //    *x = xnew + xref;
   //    *y = ynew + yref;
   // }

   // //##################################################################
   // template <typename T, typename idx_t, typename GT>
   // HOSTDEVDECOR void apply_affine_transformation(T* x, T* y, const idx_t irow, const idx_t icol, const GT* geotransform)
   // {
   //    *x = geotransform[0] + icol * geotransform[1] + irow * geotransform[2];
   //    *y = geotransform[3] + icol * geotransform[4] + irow * geotransform[5];
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T dot_product(const T a_x, const T a_y, const T b_x, const T b_y)
   // {
   //    return a_x * b_x + a_y * b_y;
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T cross_product(const T a_x, const T a_y, const T b_x, const T b_y)
   // {
   //    return a_x * b_y - a_y * b_x;
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR void unit_vector(T* unit_vec_x, T* unit_vec_y,
   //    const T original_vec_x, const T original_vec_y, const T zero_theshold = DEFAULT_ZERO_THRESHOLD)
   // {
   //    T mag = vector_magnitude(original_vec_x, original_vec_y);
   //    if (mag > zero_theshold) {
   //       *unit_vec_x = original_vec_x / mag;
   //       *unit_vec_y = original_vec_y / mag;
   //    }
   //    else {
   //       *unit_vec_x = original_vec_x;
   //       *unit_vec_y = original_vec_y;
   //    }
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T parallel_vector_component(
   //    const T vec_x, const T vec_y,
   //    const T ref_line_start_x, const T ref_line_start_y,
   //    const T ref_line_end_x, const T ref_line_end_y,
   //    const T zero_theshold = DEFAULT_ZERO_THRESHOLD)
   // {
   //    T line_vec_x = ref_line_end_x - ref_line_start_x;
   //    T line_vec_y = ref_line_end_y - ref_line_start_y;
   //    T unit_vec_x = 0., unit_vec_y = 0.;
   //    unit_vector(&unit_vec_x, &unit_vec_y, line_vec_x, line_vec_y, zero_theshold);

   //    return dot_product(vec_x, vec_y, unit_vec_x, unit_vec_y);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T perpendicular_vector_component(
   //    const T vec_x, const T vec_y,
   //    const T ref_line_start_x, const T ref_line_start_y,
   //    const T ref_line_end_x, const T ref_line_end_y,
   //    const T zero_theshold = DEFAULT_ZERO_THRESHOLD)
   // {
   //    T line_vec_x = ref_line_end_x - ref_line_start_x;
   //    T line_vec_y = ref_line_end_y - ref_line_start_y;
   //    T unit_vec_x = 0., unit_vec_y = 0.;
   //    unit_vector(&unit_vec_x, &unit_vec_y, line_vec_x, line_vec_y, zero_theshold);

   //    return cross_product(unit_vec_x, unit_vec_y, vec_x, vec_y);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR void set_affine_transformation(T* geotransform, T x_top_left, T y_top_left, T dx, T dy, T angle_deg)
   // {
   //    T angle_rad = deg_to_rad(angle_deg);
   //    geotransform[0] = x_top_left;
   //    geotransform[1] = dx * std::cos(angle_rad);
   //    geotransform[2] = dy * std::sin(angle_rad);
   //    geotransform[3] = y_top_left;
   //    geotransform[4] = dx * std::sin(angle_rad);
   //    geotransform[5] = -dy * std::cos(angle_rad);
   // }

   // //##################################################################
   // template <typename T, typename gT>
   // HOSTDEVDECOR void decrypt_affine_transformation_matrix(T* top_left_x, T* top_left_y,
   //    T* dx, T* dy, T* angle_rad, const gT* transform_matrix)
   // {
   //    // Get the origin
   //    *top_left_x = transform_matrix[0];
   //    *top_left_y = transform_matrix[3];

   //    // Get the angle as well as the resolution
   //    *angle_rad = std::atan(transform_matrix[4] / transform_matrix[1]);
   //    if (std::abs(*angle_rad) > 1.e-6) {
   //       *dx = transform_matrix[1] / std::cos(*angle_rad);
   //       *dy = -transform_matrix[5] / std::cos(*angle_rad);
   //    }
   //    else {
   //       *dx = transform_matrix[1];
   //       *dy = -transform_matrix[5];
   //    }
   // }

   // //##################################################################
   // template <typename T, typename gT>
   // HOSTDEVDECOR void apply_inverse_affine_transformation(int* irow, int* icol, const T x, const T y, const gT* transform_matrix)
   // {
   //    T Dx = x - transform_matrix[0];
   //    T Dy = y - transform_matrix[3];

   //    T det = transform_matrix[1] * transform_matrix[5] - transform_matrix[2] * transform_matrix[4];
   //    T det_icol = Dx * transform_matrix[5] - transform_matrix[2] * Dy;
   //    T det_irow = transform_matrix[1] * Dy - Dx * transform_matrix[4];

   //    *irow = static_cast<int>(round(det_irow / det));
   //    *icol = static_cast<int>(round(det_icol / det));
   //    //*irow = static_cast<int>(floor(det_irow / det));
   //    //*icol = static_cast<int>(floor(det_icol / det));
   //    //*irow = static_cast<int>(det_irow / det);
   //    //*icol = static_cast<int>(det_icol / det);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T shoelace_term(T x1, T y1, T x2, T y2)
   // {
   //    return cross_product(x1, y1, x2, y2);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR void get_line_coeff(T x1, T y1, T x2, T y2, T* a, T* b, T* c)
   // {
   //    *a = y1 - y2;
   //    *b = x2 - x1;
   //    *c = x1 * y2 - x2 * y1;
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR T distance_point_to_line(T x1, T y1, T x2, T y2, T xp, T yp)
   // {
   //    T a, b, c;
   //    get_line_coeff(x1, y1, x2, y2, &a, &b, &c);
   //    return fabs(a * xp + b * yp + c) / sqrt(a * a + b * b);
   // }

   // //##################################################################
   // template <typename T>
   // HOSTDEVDECOR int is_point_to_left_of_line_segment(T xstart, T ystart, T xend, T yend, T xp, T yp)
   // {
   //    return (xend - xstart) * (yp - ystart) - (yend - ystart) * (xp - xstart) > 0 ? 1 : 0;
   // }

   // //##################################################################
   // template<typename real_t>
   // HOSTDEVDECOR real_t chezy_to_manning(const real_t chezy_roughness, const real_t water_depth, const real_t minimum_depth)
   // {
   //    real_t d = water_depth > minimum_depth ? water_depth : minimum_depth; // std::max(water_depth, minimum_depth);
   //    return std::pow(d, 1.0 / 6.0) / chezy_roughness;
   // }

   // /**
   // * @brief Calculates the equation of the given line pq in the slope-intersept form: y = mx + b.
   // * 
   // * @param m [out] Slope of the line.
   // * @param b [out] y-intersept constant of the line.
   // * @param px [in] x coordinate of the line's start point.
   // * @param py [in] y coordinate of the line's start point.
   // * @param qx [in] x coordinate of the line's end point.
   // * @param qy [in] y coordinate of the line's end point.
   // */
   // template <typename T> 
   // HOSTDEVDECOR void get_line_equation_intercept(T* m, T* b, T px, T py, T qx, T qy)
   // {
   //    *m = (qy - py) / (qx - px);
   //    *b = py - (*m) * px;
   // };

   // /**
   // * @brief Calculates the equation of the given line pq in the standard form: Ax + By + C = 0.
   // *
   // * @param A [out] Coefficient of the x coordinate of the equation.
   // * @param B [out] Coefficient of the y coordinate of the equation.
   // * @param C [out] Constant coefficient  of the equation.
   // * @param px [in] x coordinate of the line's start point.
   // * @param py [in] y coordinate of the line's start point.
   // * @param qx [in] x coordinate of the line's end point.
   // * @param qy [in] y coordinate of the line's end point.
   // */
   // template <typename T> 
   // HOSTDEVDECOR void get_line_equation_standard(T* A, T* B, T* C, T px, T py, T qx, T qy) 
   // {
   //    *A = qy - py;
   //    *B = px - qx;
   //   //*C = py * (qx - px) - px * (qy - py);
   //    *C = py * (-1.0) * (*B) - px * (1.0) * (*A);
   // };

   // /**
   // * @brief Finds the coordinates of an offset point 'a' from an intersection point 'o' of a line 'pq'.
   // * 
   // * Lines 'ao' and 'pq' are perpendicular.
   // * The width of the segment 'ao' is given.
   // * 
   // * @param ax [out] The x coordinate of the offset point.
   // * @param ay [out] The y coordinate of the offset point.
   // * @param ox [in] The x coordinate of the intersection point 'o'.
   // * @param oy [in] The y coordinate of the intersection point 'o'.
   // * @param distance [in] The offset distance of point 'a' from point 'o'.
   // * @param px [in] x coordinate of the start point of line 'pq'.
   // * @param py [in] y coordinate of the start point of line 'pq'.
   // * @param qx [in] x coordinate of the end point of line 'pq'.
   // * @param qy [in] y coordinate of the end point of line 'pq'.
   // */
   // template <typename T> 
   // HOSTDEVDECOR void offset_point_from_segment(T* ax, T* ay, T ox, T oy, T distance, T px, T py, T qx, T qy)
   // {
   //    T A = 0.0, B = 0.0, C = 0.0;
   //    math_ops::get_line_equation_standard(&A, &B, &C, px, py, qx, qy);
   //    // normal
   //    double nx = -A;
   //    double ny = +B;
   //    // unit normal
   //    double nn = sqrt(nx * nx + ny * ny);
   //    nx = nx / nn;
   //    ny = ny / nn;
   //    // a = o + d n
   //    *ax = ox + nx * distance;
   //    *ay = oy + ny * distance;
   // };

   // /**
   // * @brief Calculates the acute angle between two linear segments pq and ab.
   // * 
   // * @param px [in] x coordinate of the start point of the segment pq.
   // * @param py [in] y coordinate of the start point of the segment pq.
   // * @param qx [in] x coordinate of the end point of the segment pq.
   // * @param qy [in] y coordinate of the end point of the segment pq.
   // * @param ax [in] x coordinate of the start point of the segment ab.
   // * @param ay [in] y coordinate of the start point of the segment ab.
   // * @param bx [in] x coordinate of the end point of the segment ab.
   // * @param by [in] y coordinate of the end point of the segment ab.
   // * @param inrad [in] When set as true angle is returned in rad (default), otherwise the angle is returned in degrees.
   // * @return The angle between two segments pq and ab in rad or degrees.
   // */
   // template <typename T> 
   // HOSTDEVDECOR T angle_between_segments(T px, T py, T qx, T qy, T ax, T ay, T bx, T by, bool inrad = true)
   // {
   //    T c_1 = 0.0;
   //    T m_1 = 0.0;
   //    math_ops::get_line_equation_intersept(&m_1, &c_1, px, py, qx, qy);
   //    T c_2 = 0.0;
   //    T m_2 = 0.0;
   //    math_ops::get_line_equation_intersept(&m_2, &c_2, ax, ay, bx, by);

   //    T tantheta = (m_1 - m_2) / (1 + m_1 * m_2);
   //    T theta_inrad = atan((double)tantheta);

   //    if (inrad)
   //       return theta_inrad;
   //    else
   //       return math_ops::rad_to_deg(theta_inrad);
   // }

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
   typename std::enable_if<
      std::is_same<T, float>::value || 
      std::is_same<T, double>::value ||
      std::is_same<T, long double>::value, T>::type
   interp_linear(const T x, const T x0, const T y0, const T x1, const T y1)
   {
      return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
   }
}

#endif // MATHS_OPERATIONS_H