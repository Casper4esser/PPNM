#pragma once
#include "vector.h"
#include "matrix.h"
#include <functional>

namespace pp
{
    pp::vector lsfit(const std::vector<std::function<double(double)>> &fs,
                     const pp::vector &x,
                     const pp::vector &y,
                     const pp::vector &dy);
}
