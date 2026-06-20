#include "integrate.h"
#include <iostream>

namespace pp
{
    double integrate(std::function<double(double)> f, double a, double b,
                     double acc, double eps, double f2, double f3)
    {

        double h = b - a;

        if (std::isnan(f2))
        {
            f2 = f(a + 2.0 * h / 6.0);
            f3 = f(a + 4.0 * h / 6.0);
        }

        double f1 = f(a + 1.0 * h / 6.0);
        double f4 = f(a + 5.0 * h / 6.0);

        double Q = (2.0 * f1 + f2 + f3 + 2.0 * f4) / 6.0 * h;
        double q = (f1 + f2 + f3 + f4) / 4.0 * h;

        double err = std::abs(Q - q);
        double tol = acc + eps * std::abs(Q);

        if (err < tol)
        {
            return Q;
        }
        else
        {
            double Q_left = integrate(f, a, a + h / 2.0, acc / std::sqrt(2.0), eps, f1, f2);
            double Q_right = integrate(f, a + h / 2.0, b, acc / std::sqrt(2.0), eps, f3, f4);
            return Q_left + Q_right;
        }
    }

    double erf(double z)
    {
        if (z < 0)
        {
            return -erf(-z);
        }
        else if (z >= 0 && z <= 1.0)
        {
            auto integrand = [](double x)
            { return std::exp(-x * x); };
            return (2.0 / std::sqrt(M_PI)) * integrate(integrand, 0.0, z);
        }
        else
        {
            auto integrand = [z](double t)
            {
                double term = z + (1.0 - t) / t;
                return std::exp(-term * term) / (t * t);
            };
            return 1.0 - (2.0 / std::sqrt(M_PI)) * integrate(integrand, 0.0, 1.0);
        }
    }
}