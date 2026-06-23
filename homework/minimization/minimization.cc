#include "minimization.h"
#include "QR.h"
#include <cmath>
#include <stdexcept>

namespace pp
{
    vector gradient(const std::function<double(vector)> &phi, vector x)
    {
        double phi_x = phi(x);
        vector g(x.size());

        for (int i = 0; i < x.size(); i++)
        {
            double dx_i = (1.0 + std::abs(x[i])) * std::pow(2.0, -26);
            x[i] += dx_i;
            g[i] = (phi(x) - phi_x) / dx_i;
            x[i] -= dx_i;
        }
        return g;
    }

    matrix hessian(const std::function<double(vector)> &phi, vector x)
    {
        int n = x.size();
        matrix H(n, n);
        vector g_x = gradient(phi, x);

        for (int j = 0; j < n; j++)
        {
            double dx_j = (1.0 + std::abs(x[j])) * std::pow(2.0, -13);
            x[j] += dx_j;
            vector dg = gradient(phi, x) - g_x;
            for (int i = 0; i < n; i++)
            {
                H(i, j) = dg[i] / dx_j;
            }
            x[j] -= dx_j;
        }
        return H;
    }

    vector newton(const std::function<double(vector)> &phi, vector x, int &steps, double acc)
    {
        steps = 0;
        int max_steps = 1000;

        while (steps < max_steps)
        {
            vector g = gradient(phi, x);

            if (norm(g) < acc)
            {
                break;
            }

            matrix H = hessian(phi, x);

            for (int i = 0; i < H.rows(); i++)
            {
                H(i, i) += 1e-6;
            }

            qr solver(H);
            vector dx = solver.solve(-g);

            double lambda = 1.0;
            double phi_x = phi(x);

            while (lambda >= 1.0 / 1024.0)
            {
                if (phi(x + dx * lambda) < phi_x)
                {
                    break;
                }
                lambda /= 2.0;
            }

            x += dx * lambda;
            steps++;
        }
        return x;
    }
}