#ifndef WAVEFORMS_H
#define WAVEFORMS_H

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif 
#include <cmath>
#include <string>
#include <stdexcept>

template <typename dtype_t>
void create_1d_waveform(dtype_t* d, int npoints, int npeaks, dtype_t amplitude) noexcept(false)
{
    if (d == nullptr)
    {
        std::string t = std::string(__FUCNTION__) + std::string(": output array is NULL");
        throw std::runtime_error(t.c_str());
    }

    dtype_t denominator = (npeaks + 1) * npoints;
    for (auto i = 0; i < npoints; ++i)
    {
        d[i] = amplitude * std::sin(M_PI * static_cast<dtype_t>(i) / denominator);
    }
}


#endif // WAVEFORMS_H