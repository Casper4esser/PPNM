#include "vec_template.h"
#include <iostream>
#include <complex>

int main()
{
    vecd v1 = vecd(1, 2, 3);
    vecd v2 = vecd(2, 7, 1);
    vecd v3 = vecd(3, 0, 9);
    double s = 2.5;
    vecd default_v = vecd();

    vecd sum = v1 + v2 + v3;
    vecd diff = v1 - v2;
    vecd prod1 = v1 * s;
    vecd prod2 = s * v2;

    std::cout << "v1 = " << v1 << "\n";
    std::cout << "v2 = " << v2 << "\n";
    std::cout << "v3 = " << v3 << "\n";

    std::cout << "v1 + v2 + v3 = " << sum << "\n";
    std::cout << "v1 - v2 = " << diff << "\n";
    std::cout << "v1 * 2.5 = " << prod1 << "\n";
    std::cout << "2.5 * v2 = " << prod2 << "\n";

    std::cout << "default_vec = " << default_v << "\n";

    vecd v4 = vecd(0.1, 0.1, 0.1);
    vecd v5 = v4 + v4 + v4 + v4;
    vecd v6 = 4 * v4;

    std::cout << "v4 = " << v4 << "\n";
    std::cout << "approx(v4 + v4 + v4 + v4 == 4 * v4)  ? " << (approx(v5, v6) ? "true" : "false") << "\n";

    std::cout << "v1 cross v2 = " << cross(v1, v2) << "\n";
    std::cout << "v1 dot v2 = " << dot(v1, v2) << "\n";

    std::cout << "Komplekse tal: \n";

    std::complex<double> c1(1.0, 2.0);
    std::complex<double> c2(3.0, -1.0);
    std::complex<double> c3(0.0, 5.0);
    std::complex<double> c4(3, 3);

    vecc v_complex1(c1, c2, c3);
    vecc v_complex2(c4, c1, c2);

    auto result = dot(v_complex1, v_complex2);

    std::cout << "v_complex1 = " << v_complex1 << "\n";
    std::cout << "v_complex2 = " << v_complex2 << "\n";
    std::cout << "v_complex1 dot v_complex2 = " << result << "\n";

    return 0;
}
