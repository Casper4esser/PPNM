#include <vector>
#include <cmath>
#include "funs.h"

namespace funs
{
    double erf(double x)
    {
        if (x < 0)
            return -erf(-x);

        std::vector<double> a{0.254829592, -0.284496736, 1.421413741, -1.453152027, 1.061405429};
        double t = 1 / (1 + 0.3275911 * x);
        double sum = t * (a[0] + t * (a[1] + t * (a[2] + t * (a[3] + t * a[4]))));
        return 1 - sum * std::exp(-x * x);
    }

    // Fra math exercise
    // Konstanter lagt i namespace for at undgå potentielle linker errors, hvis PI eller NaN bruges i andre biblioteker.
    // Det er nok lige meget for nu, men god praksis.
    namespace
    {
        constexpr double PI = std::numbers::pi;
        constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
    }

    double fgamma(double x)
    {
        if (x < 0)
            return PI / std::sin(PI * x) / fgamma(1 - x);
        if (x < 9)
            return fgamma(x + 1) / x;

        double lnfgamma = x * std::log(x + 1 / (12 * x - 1 / x / 10)) - x + std::log(2 * PI / x) / 2;
        return std::exp(lnfgamma);
    }

    double lngamma(double x)
    {
        if (x <= 0)
            return NaN;
        if (x < 9)
            return lngamma(x + 1) - std::log(x);

        return x * std::log(x + 1 / (12 * x - 1 / x / 10)) - x + std::log(2 * PI / x) / 2;
    }

    // kompleks udvidelse af gamma-funktion
    std::complex<double> cgamma(std::complex<double> z)
    {
        if (z.real() < 0.0)
            return PI / std::sin(PI * z) / cgamma(1.0 - z);

        if (z.real() < 9.0)
            return cgamma(z + 1.0) / z;

        std::complex<double> lncgamma = z * std::log(z) - z + std::log(2.0 * PI / z) / 2.0 + 1.0 / (12.0 * z) - 1.0 / (360.0 * z * z * z) + 1.0 / (1260.0 * z * z * z * z * z);

        return std::exp(lncgamma);
    }
}