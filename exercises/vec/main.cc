#include "vec.h"
#include <iostream>

int main()
{
    vec v1 = vec(1, 2, 3);
    vec v2 = vec(2, 7, 1);
    vec v3 = vec(3, 0, 9);
    double s = 2.5;
    vec default_v = vec();

    vec sum = v1 + v2 + v3;
    vec diff = v1 - v2;
    vec prod1 = v1 * s;
    vec prod2 = s * v2;

    std::cout << "v1 = " << v1 << "\n";
    std::cout << "v2 = " << v2 << "\n";
    std::cout << "v3 = " << v3 << "\n";

    std::cout << "v1 + v2 + v3 = " << sum << "\n";
    std::cout << "v1 - v2 = " << diff << "\n";
    std::cout << "v1 * 2.5 = " << prod1 << "\n";
    std::cout << "2.5 * v2 = " << prod2 << "\n";

    std::cout << "default_vec = " << default_v << "\n";

    vec v4 = vec(0.1, 0.1, 0.1);
    vec v5 = v4 + v4 + v4 + v4;
    vec v6 = 4 * v4;

    std::cout << "v4 = " << v4 << "\n";
    std::cout << "approx(v4 + v4 + v4 + v4 == 4 * v4)  ? " << (approx(v5, v6) ? "true" : "false") << "\n"; 

    std::cout << "v1 cross v2 = " << cross(v1, v2) << "\n";
    std::cout << "v1 dot v2 = " << dot(v1, v2) << "\n";

    return 0;
}
