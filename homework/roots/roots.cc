#include "roots.h"
#include "QR.h"
#include <cmath>

namespace pp
{
    vector solve_linear_system(const matrix &J, const vector &fx_neg)
    {
        qr qr_decomp(J);
        return qr_decomp.solve(fx_neg);
    }

    matrix jacobian(const std::function<vector(const vector &)> &f, vector x, const vector &fx)
    {
        int n = x.size();
        matrix J(n, n);

        for (int j = 0; j < n; j++)
        {
            double dx = std::max(std::abs(x[j]), 1.0) * std::pow(2.0, -26.0);

            x[j] += dx;
            vector df = f(x) - fx;
            x[j] -= dx;

            for (int i = 0; i < n; i++)
            {
                J(i, j) = df[i] / dx;
            }
        }
        return J;
    }

    vector newton(const std::function<vector(const vector &)> &f, vector x, double acc, double alpha_min, int max_iter)
    {
        vector fx = f(x);

        for (int iter = 0; iter < max_iter; iter++)
        {
            if (norm(fx) < acc)
            {
                break;
            }

            matrix J = jacobian(f, x, fx);
            vector Dx = solve_linear_system(J, -fx);

            double alpha = 1.0;
            vector z;
            vector fz;

            while (true)
            {
                z = x + Dx * alpha;
                fz = f(z);

                if (norm(fz) < (1.0 - alpha / 2.0) * norm(fx))
                {
                    break;
                }
                if (alpha < alpha_min)
                {
                    break;
                }
                alpha /= 2.0;
            }

            x = z;
            fx = fz;
        }
        return x;
    }
}