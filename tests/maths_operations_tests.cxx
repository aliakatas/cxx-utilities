#include "maths_geometry/maths_operations.hpp"

#include <iostream>

int main()
{
   // --- get_row_major_linear_index ---
   std::cout << "\nTesting 'get_row_major_linear_index' \n";
   {
      int ncols = 16;
      int irow = 5;
      int icol = 7;
      int idx = maths_ops::get_row_major_linear_index(irow, icol, ncols);
      std::cout << " NCOLS: " << ncols;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")";
      std::cout << "  index = " << idx << std::endl;
   }

   {
      long ncols = 16;
      long irow = 5;
      long icol = 7;
      long idx = maths_ops::get_row_major_linear_index(irow, icol, ncols);
      std::cout << " NCOLS: " << ncols;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")";
      std::cout << "  index = " << idx << std::endl;
   }

   {
      long long ncols = 16;
      long long irow = 5;
      long long icol = 7;
      long long idx = maths_ops::get_row_major_linear_index(irow, icol, ncols);
      std::cout << " NCOLS: " << ncols;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")";
      std::cout << "  index = " << idx << std::endl;
   }
   
   {
      size_t ncols = 16;
      size_t irow = 5;
      size_t icol = 7;
      size_t idx = maths_ops::get_row_major_linear_index(irow, icol, ncols);
      std::cout << " NCOLS: " << ncols;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")";
      std::cout << "  index = " << idx << std::endl;
   }

   // --- get_column_major_linear_index ---
   std::cout << "\nTesting 'get_column_major_linear_index' \n";
   {
      int nrows = 16;
      int irow = 5;
      int icol = 7;
      int idx = maths_ops::get_column_major_linear_index(irow, icol, nrows);
      std::cout << " NROWS: " << nrows;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")";
      std::cout << "  index = " << idx << std::endl;
   }

   {
      long nrows = 16;
      long irow = 5;
      long icol = 7;
      long idx = maths_ops::get_column_major_linear_index(irow, icol, nrows);
      std::cout << " NROWS: " << nrows;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")";
      std::cout << "  index = " << idx << std::endl;
   }

   {
      long long nrows = 16;
      long long irow = 5;
      long long icol = 7;
      long long idx = maths_ops::get_column_major_linear_index(irow, icol, nrows);
      std::cout << " NROWS: " << nrows;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")";
      std::cout << "  index = " << idx << std::endl;
   }

   {
      size_t nrows = 16;
      size_t irow = 5;
      size_t icol = 7;
      size_t idx = maths_ops::get_column_major_linear_index(irow, icol, nrows);
      std::cout << " NROWS: " << nrows;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")";
      std::cout << "  index = " << idx << std::endl;
   }

   // --- get_2D_indices_from_row_major_linear_index ---
   std::cout << "\nTesting 'get_2D_indices_from_row_major_linear_index' \n";
   {
      int ncols = 12;
      int irow = 0;
      int icol = 0;
      int idx = 18;
      maths_ops::get_2D_indices_from_row_major_linear_index(&irow, &icol, ncols, idx);
      std::cout << " NCOLS: " << ncols;
      std::cout << ", index = " << idx;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")" << std::endl;
   }

   {
      long ncols = 12;
      long irow = 0;
      long icol = 0;
      long idx = 18;
      maths_ops::get_2D_indices_from_row_major_linear_index(&irow, &icol, ncols, idx);
      std::cout << " NCOLS: " << ncols;
      std::cout << ", index = " << idx;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")" << std::endl;
   }

   {
      long long ncols = 12;
      long long irow = 0;
      long long icol = 0;
      long long idx = 18;
      maths_ops::get_2D_indices_from_row_major_linear_index(&irow, &icol, ncols, idx);
      std::cout << " NCOLS: " << ncols;
      std::cout << ", index = " << idx;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")" << std::endl;
   }

   {
      size_t ncols = 12;
      size_t irow = 0;
      size_t icol = 0;
      size_t idx = 18;
      maths_ops::get_2D_indices_from_row_major_linear_index(&irow, &icol, ncols, idx);
      std::cout << " NCOLS: " << ncols;
      std::cout << ", index = " << idx;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")" << std::endl;
   }

   // --- get_2D_indices_from_column_major_linear_index ---
   std::cout << "\nTesting 'get_2D_indices_from_column_major_linear_index' \n";
   {
      int nrows = 19;
      int irow = 0;
      int icol = 0;
      int idx = 47;
      maths_ops::get_2D_indices_from_column_major_linear_index(&irow, &icol, nrows, idx);
      std::cout << " NROWS: " << nrows;
      std::cout << ", index = " << idx;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")" << std::endl;
   }

   {
      long nrows = 19;
      long irow = 0;
      long icol = 0;
      long idx = 47;
      maths_ops::get_2D_indices_from_column_major_linear_index(&irow, &icol, nrows, idx);
      std::cout << " NROWS: " << nrows;
      std::cout << ", index = " << idx;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")" << std::endl;
   }

   {
      long long nrows = 19;
      long long irow = 0;
      long long icol = 0;
      long long idx = 47;
      maths_ops::get_2D_indices_from_column_major_linear_index(&irow, &icol, nrows, idx);
      std::cout << " NROWS: " << nrows;
      std::cout << ", index = " << idx;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")" << std::endl;
   }

   {
      size_t nrows = 19;
      size_t irow = 0;
      size_t icol = 0;
      size_t idx = 47;
      maths_ops::get_2D_indices_from_column_major_linear_index(&irow, &icol, nrows, idx);
      std::cout << " NROWS: " << nrows;
      std::cout << ", index = " << idx;
      std::cout << ", (irow, icol) = (";
      std::cout << irow << ", " << icol << ")" << std::endl;
   }

   // --- are_equal ---
   std::cout << "\nTesting 'are_equal' \n";
   {
      float a = 3.2f;
      float b = 3.200000001f;
      std::cout << " " << a << " == " << b << " ? " << maths_ops::are_equal(a, b);
      std::cout << " with tolerance = " << std::numeric_limits<float>::epsilon() << std::endl;
   }
   
   {
      double a = 3.2;
      double b = 3.200000001;
      std::cout << " " << a << " == " << b << " ? " << maths_ops::are_equal(a, b);
      std::cout << " with tolerance = " << std::numeric_limits<double>::epsilon() << std::endl;
   }

   {
      long double a = 3.2L;
      long double b = 3.200000001L;
      std::cout << " " << a << " == " << b << " ? " << maths_ops::are_equal(a, b);
      std::cout << " with tolerance = " << std::numeric_limits<long double>::epsilon() << std::endl;
   }

   // --- deg_to_rad ---
   std::cout << "\nTesting 'deg_to_rad' \n";
   {
      float deg = 180.f;
      std::cout << " " << deg << " deg = " << maths_ops::deg_to_rad(deg) << " rad" << std::endl;
   }
   {
      double deg = 90.;
      std::cout << " " << deg << " deg = " << maths_ops::deg_to_rad(deg) << " rad" << std::endl;
   }
   {
      long double deg = 270.L;
      std::cout << " " << deg << " deg = " << maths_ops::deg_to_rad(deg) << " rad" << std::endl;
   }

   // --- rad_to_deg ---
   std::cout << "\nTesting 'rad_to_deg' \n";
   {
      float rad = M_PI;
      std::cout << " " << rad << " rad = " << maths_ops::rad_to_deg(rad) << " deg" << std::endl;
   }
   {
      double rad = 2 * M_PI;
      std::cout << " " << rad << " rad = " << maths_ops::rad_to_deg(rad) << " deg" << std::endl;
   }
   {
      long double rad = M_PI / 4;
      std::cout << " " << rad << " rad = " << maths_ops::rad_to_deg(rad) << " deg" << std::endl;
   }

   // --- get_0_360_deg ---
   std::cout << "\nTesting 'get_0_360_deg' \n";
   {
      float deg = 540.f;
      std::cout << " " << deg << " deg = " << maths_ops::get_0_360_deg(deg) << " deg" << std::endl;
   }
   {
      double deg = 363.;
      std::cout << " " << deg << " deg = " << maths_ops::get_0_360_deg(deg) << " deg" << std::endl;
   }
   {
      long double deg = 801.L;
      std::cout << " " << deg << " deg = " << maths_ops::get_0_360_deg(deg) << " deg" << std::endl;
   }

   // --- get_0_2pi_rad ---
   std::cout << "\nTesting 'get_0_2pi_rad' \n";
   {
      float rad = 5 * M_PI;
      std::cout << " " << rad << " rad = " << maths_ops::get_0_2pi_rad(rad) << " rad" << std::endl;
   }
   {
      double rad = 13.41;
      std::cout << " " << rad << " rad = " << maths_ops::get_0_2pi_rad(rad) << " rad" << std::endl;
   }
   {
      long double rad = 2.25 * M_PI;
      std::cout << " " << rad << " rad = " << maths_ops::get_0_2pi_rad(rad) << " rad" << std::endl;
   }

   // --- to_compass_angle_deg ---
   std::cout << "\nTesting 'to_compass_angle_deg' \n";
   {
      float deg = 270.f;
      std::cout << " angle = " << deg << "(deg), compass = " << maths_ops::to_compass_angle_deg(deg) << " (deg)" <<std::endl;
   }
   {
      double deg = 90.;
      std::cout << " angle = " << deg << "(deg), compass = " << maths_ops::to_compass_angle_deg(deg) << " (deg)" <<std::endl;
   }
   {
      long double deg = 180.L;
      std::cout << " angle = " << deg << "(deg), compass = " << maths_ops::to_compass_angle_deg(deg) << " (deg)" <<std::endl;
   }

   // --- to_compass_angle_rad ---
   std::cout << "\nTesting 'to_compass_angle_rad' \n";
   {
      float rad = (3./2.) * M_PI;
      std::cout << " angle = " << rad << "(rad), compass = " << maths_ops::to_compass_angle_rad(rad) << " (rad)" <<std::endl;
   }
   {
      double rad = 0.;
      std::cout << " angle = " << rad << "(rad), compass = " << maths_ops::to_compass_angle_rad(rad) << " (rad)" <<std::endl;
   }
   {
      long double rad = (5./6.) * M_PI;
      std::cout << " angle = " << rad << "(rad), compass = " << maths_ops::to_compass_angle_rad(rad) << " (rad)" <<std::endl;
   }

   // --- convert_to_meteorological_dir_deg ---
   std::cout << "\nTesting 'convert_to_meteorological_dir_deg' \n";
   {
      long double deg = 45.L;
      std::cout << " " << deg << " (geometric angle - deg) => " << maths_ops::convert_to_meteorological_dir_deg(deg) << " (meteo angle - deg)" << std::endl;
   }
   {
      float deg = -270.f;
      std::cout << " " << deg << " (geometric angle - deg) => " << maths_ops::convert_to_meteorological_dir_deg(deg) << " (meteo angle - deg)" << std::endl;
   }

   // --- convert_to_meteorological_dir_rad ---
   std::cout << "\nTesting 'convert_to_meteorological_dir_rad' \n";
   {
      long double rad = 0.L;
      std::cout << " " << rad << " (geometric angle - rad) => " << maths_ops::convert_to_meteorological_dir_rad(rad) << " (meteo angle - rad)" << std::endl;
   }
   {
      float rad = -M_PI;
      std::cout << " " << rad << " (geometric angle - rad) => " << maths_ops::convert_to_meteorological_dir_rad(rad) << " (meteo angle - rad)" << std::endl;
   }

   // --- vector_magnitude ---
   std::cout << "\nTesting 'vector_magnitude' \n";
   {
      float x = 1.f;
      float y = 1.f;
      std::cout << " (" << x << ", " << y << ") = " << maths_ops::vector_magnitude(x, y) << std::endl; 
   }
   {
      double x = 12.;
      double y = 0.;
      std::cout << " (" << x << ", " << y << ") = " << maths_ops::vector_magnitude(x, y) << std::endl; 
   }
   {
      long double x = -3.L;
      long double y = -4.L;
      std::cout << " (" << x << ", " << y << ") = " << maths_ops::vector_magnitude(x, y) << std::endl; 
   }

   // --- vector_direction ---
   std::cout << "\nTesting 'vector_direction' \n";
   {
      float x = 0.f;
      float y = 0.f;
      std::cout << " (" << x << ", " << y << ") = " << maths_ops::vector_direction(x, y);
      std::cout << " (" << maths_ops::rad_to_deg(maths_ops::vector_direction(x, y)) << "deg)" << std::endl;
   }
   {
      double x = -5.;
      double y = 5.;
      std::cout << " (" << x << ", " << y << ") = " << maths_ops::vector_direction(x, y);
      std::cout << " (" << maths_ops::rad_to_deg(maths_ops::vector_direction(x, y)) << "deg)" << std::endl;
   }
   {
      long double x = -1.L;
      long double y = -3.L;
      std::cout << " (" << x << ", " << y << ") = " << maths_ops::vector_direction(x, y);
      std::cout << " (" << maths_ops::rad_to_deg(maths_ops::vector_direction(x, y)) << "deg)" << std::endl;
   }







   // --- interp_linear ---
   std::cout << "\nTesting 'interp_linear' \n";
   {
      float x = 1.2f;
      float x0 = 1.f;
      float x1 = 2.f;
      float y0 = 4.f;
      float y1 = 6.f;
      float y = maths_ops::interp_linear(x, x0, y0, x1, y1);
      std::cout << "(" << x0 << ", " << y0 << ") --> (" << x1 << ", " << y1 << ") = (" << x << ", " << y << ")" << std::endl;
   }

   std::cout << "\nDone\n";
   return EXIT_SUCCESS;
}