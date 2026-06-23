#pragma once
#include "vector.h"
#include "matrix.h"
#include <functional>

namespace pp {
    vector gradient(const std::function<double(vector)>& phi, vector x);

    matrix hessian(const std::function<double(vector)>& phi, vector x);

    vector newton(const std::function<double(vector)>& phi, vector x, int& steps, double acc = 1e-3);
}