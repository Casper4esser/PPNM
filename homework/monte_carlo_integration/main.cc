#include "mc.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstdint>

struct LCG {
    uint64_t seed, a, c, m;

    LCG(uint64_t initial_seed, uint64_t a_val = 1664525, uint64_t c_val = 1013904223, uint64_t m_val = 4294967296ULL) 
        : seed(initial_seed), a(a_val), c(c_val), m(m_val) {}

    double operator()() {
        seed = (a * seed + c) % m;
        return static_cast<double>(seed + 1) / static_cast<double>(m + 1);
    }
};

int main() {
    LCG my_lcg(42);
    auto rnd = [&my_lcg]() { return my_lcg(); };
    
    auto f_circle = [](const std::vector<double>& v) {
        double x = v[0], y = v[1];
        if (x*x + y*y <= 1.0) return 1.0;
        return 0.0;
    };

    std::vector<double> a_circ = {-1.0, -1.0};
    std::vector<double> b_circ = {1.0, 1.0};
    
    std::ofstream outfile("mc_error.txt");
    outfile << "# N\tActual_Error\tEstimated_Error\tO_1_sqrt_N\n";
    
    double exact_pi = M_PI;
    
    for (int N = 100; N <= 1000000; N *= 2) {
        auto [result, err_est] = pp::plain_mc(2, f_circle, a_circ, b_circ, N, rnd);
        double actual_error = std::abs(result - exact_pi);
        
        double ref_line = 2.0 / std::sqrt(N);
        
        outfile << N << "\t" << actual_error << "\t" << err_est << "\t" << ref_line << "\n";
    }

    // til at skrive cirkelvolumen i out.txt
    int N_circ = 1000000;
    auto [res_circ, err_circ] = pp::plain_mc(2, f_circle, a_circ, b_circ, N_circ, rnd);
    
    std::cout << "Cirkel (N = " << N_circ << "):" << std::endl;
    std::cout << "Beregnet areal   : " << res_circ << " +/- " << err_circ << "\n";
    std::cout << "Eksakt areal     : " << exact_pi << "\n";
    std::cout << "Faktisk fejl     : " << std::abs(res_circ - exact_pi) << "\n\n";
    
    std::cout << "Ellipsoide: " << std::endl;
    auto f_ellipsoid = [](const std::vector<double>& v) {
        double x = v[0], y = v[1], z = v[2];
        if (x*x/1.0 + y*y/4.0 + z*z/9.0 <= 1.0) return 1.0;
        return 0.0;
    };

    std::vector<double> a_ellip = {-1.0, -2.0, -3.0};
    std::vector<double> b_ellip = { 1.0,  2.0,  3.0};
    
    int N_3d = 1000000;
    auto [res_ellip, err_ellip] = pp::plain_mc(3, f_ellipsoid, a_ellip, b_ellip, N_3d, rnd);
    double exact_vol = (4.0/3.0) * M_PI * 1.0 * 2.0 * 3.0; 
    
    std::cout << "Beregnet volumen : " << res_ellip << " +/- " << err_ellip << "\n";
    std::cout << "Eksakt volumen   : " << exact_vol << "\n";
    std::cout << "Faktisk fejl     : " << std::abs(res_ellip - exact_vol) << "\n";

    return 0;
}