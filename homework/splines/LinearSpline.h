#include "vector.h"

using vec = pp::vector;

namespace pp
{
    struct LinearSpline
    {
        pp::vector x, y;

        LinearSpline(const vec &x_data, const vec &y_data);

        int binsearch(double z) const;
        double eval(double z) const;
        double integ(double z) const;
    };
}