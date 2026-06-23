#include "vector.h"
#include "ann.h"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>

double target_function(double x) {
    return std::cos(5.0 * x - 1.0) * std::exp(-x * x);
}

double gaussian_wavelet(double x) {
    return x * std::exp(-x * x);
}

int main() {
    int N = 40;
    
    pp::vector x_train = pp::linspace(-1.0, 1.0, 2.0 / (N - 1));
    pp::vector y_train(x_train.size());
    for (int k = 0; k < x_train.size(); k++) {
        y_train[k] = target_function(x_train[k]);
    }

    int hidden_neurons = 6;
    pp::ann network(hidden_neurons, gaussian_wavelet);

    network.train(x_train, y_train);
    
    std::ofstream out("data.txt");
    
    for (double x = -1.0; x <= 1.0; x += 0.01) {
        double approx_y = network.response(x);
        double exact_y = target_function(x);
        
        out << x << " " << approx_y << " " << exact_y << "\n";
    }
    out.close();
    
    return 0;
}