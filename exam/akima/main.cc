#include <iostream>
#include "vector.h"
#include "akima.h"
#include <fstream>

int main() {
    // eksempel-data
    pp::vector x = {-4.5, -2.0, -1.0, 1.0, 2.0, 4.5};
    pp::vector y = {-1, -1, -1, 1, 1, 1};

    pp::Akima spline(x, y);

    std::ofstream data_file("data.txt");
    for (int i = 0; i < x.size(); i++) {
        data_file << x[i] << " " << y[i] << std::endl;
    }
    data_file.close();

    std::ofstream spline_file("spline.txt");
    double z_step = 0.05;
    for (double z = x[0]; z <= x[x.size() - 1]; z += z_step) {
        spline_file << z << " " << spline.eval(z) << "\n";
    }
    spline_file.close();

    std::ofstream README("README.txt");
    README << "Jeg hørte, at man måske skulle skrive, hvor mange point, man forventer. Jeg har løst opgaven, men heller ikke mere end det, så det må blive 6 point.";
    README.close();

    return 0;
}