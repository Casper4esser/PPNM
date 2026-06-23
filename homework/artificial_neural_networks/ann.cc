#include "ann.h"
#include "minimization.h"
#include <cmath>
#include <iostream>

namespace pp
{
    ann::ann(int n, std::function<double(double)> activation_func)
        : n(n), f(activation_func)
    {
        p.resize(3 * n);

        double distance = 2.0 / (n > 1 ? (n - 1) : 1);

        for (int i = 0; i < n; i++)
        {
            p[3 * i] = -1.0 + i * distance;
            p[3 * i + 1] = distance * 1.2;
            p[3 * i + 2] = 6;
        }
    }

    double ann::response(double x) const
    {
        double sum = 0.0;
        for (int i = 0; i < n; i++)
        {
            double a = p[3 * i];
            double b = p[3 * i + 1];
            double w = p[3 * i + 2];
            sum += f((x - a) / b) * w;
        }
        return sum;
    }

    void ann::train(const vector &x_data, const vector &y_data)
    {

        std::function<double(vector)> cost_function = [&](vector current_p)
        {
            double cost = 0.0;

            for (int k = 0; k < x_data.size(); k++)
            {
                double sum = 0.0;
                for (int i = 0; i < n; i++)
                {
                    double a = current_p[3 * i];
                    double b = current_p[3 * i + 1];
                    double w = current_p[3 * i + 2];
                    sum += f((x_data[k] - a) / b) * w;
                }
                double diff = sum - y_data[k];
                cost += diff * diff;
            }
            return cost;
        };

        int steps = 0;
        double acc = 1e-3;

        this->p = pp::newton(cost_function, this->p, steps, acc);

        std::cout << "Træning fuldført efter " << steps << " skridt.\n";
    }
}