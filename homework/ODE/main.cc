#include "vector.h"
#include "ODE.h"
#include <iostream>
#include <fstream>
#include <cmath>

pp::vector harmonic_oscillator(double, pp::vector y) {
    pp::vector dydx(2);
    dydx[0] = y[1];
    dydx[1] = -y[0];
    return dydx;
}

pp::vector damped_oscillator(double, pp::vector y) {
    double b = 0.25;
    double c = 5.0;
    pp::vector dydx(2);
    dydx[0] = y[1];
    dydx[1] = -b * y[1] - c * std::sin(y[0]);
    return dydx;
}

pp::vector lotka_volterra(double, pp::vector y) {
    double a = 1.5, b = 1.0, c = 1.0, d = 3.0;
    pp::vector dydx(2);
    dydx[0] = a * y[0] - b * y[0] * y[1];
    dydx[1] = c * y[0] * y[1] - d * y[1];
    return dydx;
}

int main() {
    pp::vector y0_harm(2);
    y0_harm[0] = 1.0;
    y0_harm[1] = 0.0;
    auto [x1, y1] = pp::driver(harmonic_oscillator, 0.0, 10.0, y0_harm);

    std::ofstream out1("harmonic.txt");
    for (int i = 0; i < x1.size(); ++i)
        out1 << x1[i] << " " << y1[i][0] << " " << y1[i][1] << "\n";
    out1.close();

    pp::vector y0_damped(2);
    y0_damped[0] = 3.14159 - 0.1;
    y0_damped[1] = 0.0;
    auto [x2, y2] = pp::driver(damped_oscillator, 0.0, 10.0, y0_damped);

    std::ofstream out2("damped.txt");
    for (int i = 0; i < x2.size(); ++i)
        out2 << x2[i] << " " << y2[i][0] << " " << y2[i][1] << "\n";
    out2.close();

    pp::vector y0_lv(2);
    y0_lv[0] = 10.0;
    y0_lv[1] = 5.0;
    auto [x3, y3] = pp::driver(lotka_volterra, 0.0, 15.0, y0_lv);

    std::ofstream out3("lotka_volterra.txt");
    for (int i = 0; i < x3.size(); ++i)
        out3 << x3[i] << " " << y3[i][0] << " " << y3[i][1] << "\n";
    out3.close();

    return 0;
}