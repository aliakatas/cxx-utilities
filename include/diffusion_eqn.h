#ifndef DIFFUSION_EQN_H
#define DIFFUSION_EQN_H

#include <string>
#include <algorithm>
#include <stdexcept>

// Function to solve the 1D diffusion equation using finite difference method
// ∂u/∂t = α * ∂²u/∂x²
// Assumes that r <= 0.5 => alpha * dt / (dx * dx) <= 0.5
template <typename dtype_t>
void solve_1d_diffusion_eqn(dtype_t alpha, dtype_t dx, dtype_t dt, int nx, int nt, dtype_t* u) noexcept(false)
{
    // Stability condition
    dtype_t r = alpha * dt / (dx * dx);

    if (r > 0.5)
    {
        std::string t = std::string(__FUNCTION__) + std::string(": stability criterion exceeded (") + 
            std::to_string(r) + std::string("). Must be <= 0.5");
        throw std::runtime_error(t.c_str());
    }

    dtype_t* u_new = new dtype_t[nx];
    if (u_new == nullptr)
    {
        std::string t = std::string(__FUNCTION__) + std::string(": failed to allocate memory for u_new");
        throw std::runtime_error(t.c_str());
    }

    // Iterate over time steps
    for (int n = 0; n < nt; ++n) {
        // Apply boundary conditions
        u_new[0] = static_cast<dtype_t>(0.);
        u_new[nx - 1] = static_cast<dtype_t>(0.);

        // Update interior points
        for (int i = 1; i < nx - 1; ++i) 
        {
            u_new[i] = u[i] + r * (u[i + 1] - 2.0 * u[i] + u[i - 1]);
        }

        // Update the solution vector
        std::copy(u_new, u_new + nx, u);
    }

    delete[] u_new;
}

// Function to compute the spatial derivative using finite differences
template <typename dtype_t>
dtype_t spatial_derivative_1d(const dtype_t* u, int idx, int idx_max, dtype_t dx) 
{
    if (idx == 0) 
        return (u[1] - u[0]) / dx;
    else if (idx == idx_max)
        return (u[idx] - u[idx - 1]) / dx;
    else
        return (u[idx + 1] - u[idx - 1]) / (2.0 * dx);
}

// Function to solve the 1D diffusion equation using Runge-Kutta 4th order method
template <typename dtype_t>
void solve_1d_diffusion_eqn_rk4(dtype_t alpha, dtype_t dx, dtype_t dt, int nx, int nt, dtype_t* u) noexcept(false)
{
    dtype_t* k1 = new dtype_t[4 * nx];
    if (k1 == nullptr)
    {
        std::string t = std::string(__FUNCTION__) + std::string(": failed to allocate memory for k-factors");
        throw std::runtime_error(t.c_str());
    }
    dtype_t* k2 = &k1[nx];
    dtype_t* k3 = &k1[2 * nx];
    dtype_t* k4 = &k1[3 * nx];

    dtype_t* u_temp = new dtype_t[nx];
    if (u_temp == nullptr)
    {
        std::string t = std::string(__FUNCTION__) + std::string(": failed to allocate memory for temp array");
        throw std::runtime_error(t.c_str());
    }

    // Iterate over time steps
    for (int n = 0; n < nt; ++n) {
        // Compute k1
        for (int i = 0; i < nx; ++i) {
            k1[i] = alpha * spatialDerivative(u, i, dx);
        }

        // Compute k2
        for (int i = 0; i < nx; ++i) {
            u_temp[i] = u[i] + 0.5 * dt * k1[i];
        }
        for (int i = 0; i < nx; ++i) {
            k2[i] = alpha * spatialDerivative(u_temp, i, dx);
        }

        // Compute k3
        for (int i = 0; i < nx; ++i) {
            u_temp[i] = u[i] + 0.5 * dt * k2[i];
        }
        for (int i = 0; i < nx; ++i) {
            k3[i] = alpha * spatialDerivative(u_temp, i, dx);
        }

        // Compute k4
        for (int i = 0; i < nx; ++i) {
            u_temp[i] = u[i] + dt * k3[i];
        }
        for (int i = 0; i < nx; ++i) {
            k4[i] = alpha * spatialDerivative(u_temp, i, dx);
        }

        // Update the solution vector
        for (int i = 0; i < nx; ++i) {
            u[i] += (dt / 6.0) * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
        }
    }

    delete[] k1;
    delete[] u_temp;
}

#endif // DIFFUSION_EQN_H