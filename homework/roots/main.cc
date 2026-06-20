#include "roots.h"
#include <iostream>

using namespace pp;

int main()
{
    std::cout << "f(x) = x^2 - 4 : \n";
    std::function<vector(const vector &)> simple_f = [](const vector &v)
    {
        vector res(1);
        res[0] = v[0] * v[0] - 4.0;
        return res;
    };

    vector x_start_1d(1);
    x_start_1d[0] = 5.0;
    vector root_1d = newton(simple_f, x_start_1d);
    std::cout << "Rod fundet ved x = " << root_1d[0] << "\n\n";

    std::cout << "Rosenbrock's Valley Function : \n";
    std::function<vector(const vector &)> rosenbrock_grad = [](const vector &v)
    {
        double x = v[0];
        double y = v[1];
        vector df(2);
        df[0] = -2.0 * (1.0 - x) - 400.0 * x * (y - x * x);
        df[1] = 200.0 * (y - x * x);
        return df;
    };

    vector x_start_ros(2);
    x_start_ros[0] = 0.0;
    x_start_ros[1] = 0.0;
    vector min_ros = newton(rosenbrock_grad, x_start_ros);
    std::cout << "Minimum for Rosenbrock fundet ved:\n";
    std::cout << "x = " << min_ros[0] << ", y = " << min_ros[1] << "\n\n";

    std::cout << "Himmelblau's Function : \n";
    std::function<vector(const vector &)> himmelblau_grad = [](const vector &v)
    {
        double x = v[0];
        double y = v[1];
        vector df(2);
        df[0] = 4.0 * x * (x * x + y - 11.0) + 2.0 * (x + y * y - 7.0);
        df[1] = 2.0 * (x * x + y - 11.0) + 4.0 * y * (x + y * y - 7.0);
        return df;
    };

    vector x_start_him1 = {0.0, 0.0};
    vector x_start_him2 = {-5.0, -5.0};

    vector min_him1 = newton(himmelblau_grad, x_start_him1);
    vector min_him2 = newton(himmelblau_grad, x_start_him2);

    std::cout << "Minimum 1 for Himmelblau fundet ved:\n";
    std::cout << "x = " << min_him1[0] << ", y = " << min_him1[1] << "\n";
    std::cout << "Minimum 2 for Himmelblau fundet ved:\n";
    std::cout << "x = " << min_him2[0] << ", y = " << min_him2[1] << "\n";

    return 0;
}