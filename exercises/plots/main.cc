#include "funs.h"
#include <iostream>
#include <fstream>
#include <cmath>

int main()
{
    std::ofstream erf_out("erf_data.txt");
    std::ofstream gamma_out("gamma_data.txt");
    std::ofstream lngamma_out("lngamma_data.txt");
    std::ofstream cgamma_out("cgamma_data.txt");

    std::ofstream gamma_pts("gamma_points.txt");
    std::ofstream lngamma_pts("lngamma_points.txt");

    for (double x = -3; x <= 3; x += 0.1)
    {
        erf_out << x << " " << funs::erf(x) << "\n";
    }

    for (double x = 0.1; x <= 5; x += 0.1)
    {
        gamma_out << x << " " << funs::fgamma(x) << "\n";
        lngamma_out << x << " " << funs::lngamma(x) << "\n";
    }

    for (int n = 1; n <= 5; ++n)
    {
        double val = funs::factorial(n - 1); // gamma til et heltal er lig (n-1)!
        gamma_pts << n << " " << val << "\n";
        lngamma_pts << n << " " << std::log(val) << "\n";
    }

    for (double x = -4.0; x <= 4.0; x += 0.05)
    {
        for (double y = -4.0; y <= 4.0; y += 0.05)
        {
            std::complex<double> z(x, y);
            double abs_val = std::abs(funs::cgamma(z));

            cgamma_out << x << " " << y << " " << abs_val << "\n";
        }
        cgamma_out << "\n"; // VIGTIGT: Blank linje adskiller rækker for Gnuplot pm3d (?)
    }

    return 0;
}