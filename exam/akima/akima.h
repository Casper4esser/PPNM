#pragma once
#include "vector.h"
#include <cassert>

namespace pp
{
    struct Akima
    {
        pp::vector x;
        pp::vector y;
        pp::vector b;
        pp::vector c;
        pp::vector d;

        Akima(const pp::vector &x_in, const pp::vector &y_in);

        double eval(double z) const;

        int binsearch(double z) const;
    };
} // namespace pp

