#include "LinearSpline.h"
#include <cmath>
#include <cassert>

namespace pp
{
    LinearSpline::LinearSpline(const vec &x_data, const vec &y_data) : x(x_data), y(y_data)
    {
        assert(x.size() == y.size() && x.size() > 1);
    }

    int LinearSpline::binsearch(double z) const
    {
        assert(z >= x[0] && z <= x[x.size() - 1]);
        int i = 0;
        int j = x.size() - 1;
        while (j - i > 1)
        {
            int mid = (i + j) / 2;
            if (z > x[mid])
            {
                i = mid;
            }
            else
            {
                j = mid;
            }
        }
        return i;
    }

    double LinearSpline::eval(double z) const
    {
        int i = binsearch(z);
        double dx = x[i + 1] - x[i];
        assert(dx > 0);

        double dy = y[i + 1] - y[i];
        return y[i] + (dy / dx) * (z - x[i]);
    }

    double LinearSpline::integ(double z) const
    {
        int idx = binsearch(z);
        double integral_sum = 0.0;

        for (int i = 0; i < idx; ++i)
        {
            double dx = x[i + 1] - x[i];
            integral_sum += 0.5 * dx * (y[i] + y[i + 1]);
        }

        double dx_partial = z - x[idx];
        double p_i = (y[idx + 1] - y[idx]) / (x[idx + 1] - x[idx]);

        integral_sum += y[idx] * dx_partial + 0.5 * p_i * dx_partial * dx_partial;

        return integral_sum;
    }

}