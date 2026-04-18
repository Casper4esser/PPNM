#include <cmath>

namespace utils
{
    bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9)
    {
        double diff = std::abs(a - b);
        if (diff <= acc)
            return true;
        double max_ab = std::max(std::abs(a), std::abs(b));
        return diff <= eps * max_ab;
    }
}
