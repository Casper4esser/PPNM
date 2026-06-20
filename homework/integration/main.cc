#include "integrate.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

int ncalls = 0;

int main()
{
    ncalls = 0;
    auto f1 = [](double x)
    { ncalls++; return std::sqrt(x); };
    double I1 = pp::integrate(f1, 0, 1, 1e-4, 1e-4);
    std::cout << "int_0^1 sqrt(x) dx = " << I1 << "\nForventet: 0.6666... | Kald: " << ncalls << "\n\n";

    ncalls = 0;
    auto f2 = [](double x)
    { ncalls++; return 1.0 / std::sqrt(x); };
    double I2 = pp::integrate(f2, 0, 1, 1e-4, 1e-4);
    std::cout << "int_0^1 1/sqrt(x) dx = " << I2 << "\nForventet: 2.0 | Kald: " << ncalls << "\n\n";

    ncalls = 0;
    auto f3 = [](double x)
    { ncalls++; return std::sqrt(1.0 - x*x); };
    double I3 = pp::integrate(f3, 0, 1, 1e-4, 1e-4);
    std::cout << "int_0^1 sqrt(1-x^2) dx = " << I3 << "\nForventet: " << M_PI / 4.0 << " | Kald: " << ncalls << "\n\n";

    ncalls = 0;
    auto f4 = [](double x)
    { ncalls++; return std::log(x) / std::sqrt(x); };
    double I4 = pp::integrate(f4, 0, 1, 1e-4, 1e-4);
    std::cout << "int_0^1 ln(x)/sqrt(x) dx = " << I4 << "\nForventet: -4.0 | Kald: " << ncalls << "\n\n";

    std::cout << "Beregnet erf(1) = " << std::setprecision(15) << pp::erf(1.0) << "\n";
    std::cout << "Tabuleret erf(1)= 0.84270079294971486934\n\n";

    std::ofstream outfile("erf_convergence.txt");
    double exact_erf = 0.84270079294971486934;

    for (double acc = 0.1; acc >= 1e-8; acc /= 2.0)
    {
        double calc_manual = pp::integrate([](double x)
                                           { return std::exp(-x * x); }, 0, 1, acc, 0.0) *
                             2.0 / std::sqrt(M_PI);
        double err = std::abs(calc_manual - exact_erf);

        outfile << std::scientific << std::setprecision(8) << acc << " " << err << "\n";
    }

    return 0;
}