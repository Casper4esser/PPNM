#pragma once
#include <complex>

namespace funs
{
    double erf(double x);
    double fgamma(double x);
    double lngamma(double x);

    // Factorial returnerer double i stedet for int pga. integer overflow. Dvs. en int kan højst være 2.147.483.647
    // men 13! er allerede 6.2 mia.
    // constexpr behøver heller ikke være der. Idéen med constexpr er at beregne faste konstanter allerede under
    // kompileringen. Derfor er det hurtigere, men alt i funktionen skal være noget som compileren kan forstå.
    // Alt skal stå i header og ikke sourcefil, når man bruger constexpr, for compileren kigger kun i headerfilen.
    constexpr double factorial(int n)
    {
        double res = 1.0;
        for (int i = 1; i <= n; ++i)
            res *= i;
        return res;
    };

    std::complex<double> cgamma(std::complex<double> z);
}