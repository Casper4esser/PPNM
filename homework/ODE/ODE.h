#pragma once
#include "vector.h"
#include "matrix.h"
#include <functional>
#include <vector>
#include <tuple>

namespace pp
{
    std::tuple<pp::vector, pp::vector> rkstep12(
        std::function<pp::vector(double, pp::vector)> f,
        double x,
        pp::vector y,
        double h);

    std::tuple<pp::vector, pp::matrix> driver(
        std::function<pp::vector(double, pp::vector)> f,
        double a,
        double b,
        pp::vector yinit,
        double h = 0.125,
        double acc = 0.01,
        double eps = 0.01);
}
