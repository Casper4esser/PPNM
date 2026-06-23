#pragma once
#include "vector.h"
#include <functional>

namespace pp
{
    struct ann
    {
        int n;
        std::function<double(double)> f;
        vector p;

        ann(int n, std::function<double(double)> activation_func);

        double response(double x) const;

        void train(const vector &x, const vector &y);
    };
}