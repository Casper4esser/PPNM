#pragma once
#include <functional>
#include <vector>
#include <utility> 

namespace pp {
    std::pair<double, double> plain_mc(
        int dim,
        std::function<double(const std::vector<double>&)> f,
        const std::vector<double>& a,
        const std::vector<double>& b,
        int N,
        std::function<double()> random_double
    );
}