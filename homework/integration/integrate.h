#pragma once
#include <functional>
#include <cmath>

namespace pp
{
    double integrate(std::function<double(double)> f, double a, double b,
                     double acc = 0.001, double eps = 0.001,
                     double f2 = NAN, double f3 = NAN);

    double erf(double z);
}