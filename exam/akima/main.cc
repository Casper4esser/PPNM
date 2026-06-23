#include <iostream>
#include "vector.h"
#include "akima.h"
#include <fstream>

int main() {
    // eksempel-data
    pp::vector x = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    pp::vector y = {2.1, 2.8, 2.8, 4.5, 5.0, 1.2};

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

    return 0;
}