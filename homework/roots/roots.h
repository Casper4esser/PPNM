#pragma once
#include "vector.h"
#include "matrix.h"
#include <functional>

namespace pp
{
    vector solve_linear_system(const matrix &J, const vector &fx_neg);

    matrix jacobian(const std::function<vector(const vector &)> &f, vector x, const vector &fx);

    vector newton(const std::function<vector(const vector &)> &f,
                  vector x,
                  double acc = 1e-4,
                  double alpha_min = 1e-3,
                  int max_iter = 1000);
}