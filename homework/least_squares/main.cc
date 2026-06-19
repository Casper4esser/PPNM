#include "vector.h"
#include "matrix.h"
#include "QR.h"
#include "lsfit.h"
#include <cmath>
#include <iostream>
#include <fstream>

int main()
{
    std::vector<double> t_raw = {1, 2, 3, 4, 6, 9, 10, 13, 15};
    std::vector<double> y_raw = {117, 100, 88, 72, 53, 29.5, 25.2, 15.2, 11.1};
    std::vector<double> dy_raw = {6, 5, 4, 4, 4, 3, 3, 2, 2};

    int n = t_raw.size();

    pp::vector t(n);
    pp::vector ln_y(n);
    pp::vector d_ln_y(n);

    for (int i = 0; i < n; ++i)
    {
        t[i] = t_raw[i];
        ln_y[i] = std::log(y_raw[i]);
        d_ln_y[i] = dy_raw[i] / y_raw[i];
    }

    // definerer basisfunktionerne f_0(t) = 1 og f_1(t) = t
    // []() = {} er en lambdafunktion
    auto fs = std::vector<std::function<double(double)>>{
        [](double)
        { return 1.0; },
        [](double z)
        { return z; }};

    pp::vector c = lsfit(fs, t, ln_y, d_ln_y);

    double lambda = -c[1];
    double half_life = std::log(2.0) / lambda;

    std::cout << "half-life : " << half_life << std::endl;

    std::ofstream data_out("rutherford_data.txt");
    for (int i = 0; i < n; ++i)
    {
        data_out << t_raw[i] << " " << y_raw[i] << " " << dy_raw[i] << "\n";
    }

    std::ofstream fit_out("rutherford_fit.txt");
    double a = std::exp(c[0]); // c[0] var ln(a)

    for (double t_plot = 0.0; t_plot <= 16.0; t_plot += 0.1) {
        double y_plot = a * std::exp(-lambda * t_plot);
        fit_out << t_plot << " " << y_plot << "\n";
    }



    return 0;
}
