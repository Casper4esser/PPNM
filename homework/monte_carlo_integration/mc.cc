#include "mc.h"
#include <cmath>
#include <algorithm>

namespace pp {
    std::pair<double, double> plain_mc(
        int dim,
        std::function<double(const std::vector<double>&)> f,
        const std::vector<double>& a,
        const std::vector<double>& b,
        int N,
        std::function<double()> random_double)
    {
        double V = 1.0;
        for (int i = 0; i < dim; i++) {
            V *= (b[i] - a[i]);
        }

        double sum = 0.0;
        double sum2 = 0.0;
        std::vector<double> x(dim);

        for (int i = 0; i < N; i++) {
            for (int k = 0; k < dim; k++) {
                x[k] = a[k] + random_double() * (b[k] - a[k]);
            }
            
            double fx = f(x);
            sum += fx;
            sum2 += fx * fx;
        }

        double mean = sum / N;
        double var = std::max(0.0, sum2 / N - mean * mean);
        
        double integral = mean * V;
        double error = V * std::sqrt(var / N);

        return {integral, error};
    }
}