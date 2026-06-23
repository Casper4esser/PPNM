#include <iostream>
#include "vector.h"
#include "matrix.h"
#include "minimization.h"
#include <cmath>

using namespace pp;

double rosenbrock(vector x)
{
    return std::pow(1.0 - x[0], 2.0) + 100.0 * std::pow(x[1] - std::pow(x[0], 2.0), 2.0);
}

double himmelblau(vector x)
{
    return std::pow(std::pow(x[0], 2.0) + x[1] - 11.0, 2.0) + std::pow(x[0] + std::pow(x[1], 2.0) - 7.0, 2.0);
}

int main()
{
    int steps = 0;

    vector x_rosen = {0.0, 0.0};
    vector min_rosen = newton(rosenbrock, x_rosen, steps);
    std::cout << "Rosenbrock:" << std::endl;
    std::cout << "Minimum ved: " << min_rosen << std::endl;
    std::cout << "Antal skridt: " << steps << std::endl;
    std::cout << "f(x,y) = " << rosenbrock(min_rosen) << "\n\n";

    vector x_himmel = {3.0, 3.0};   // anderledes startgæt, fordi det ellers ikke konvergerer
    vector min_himmel = newton(himmelblau, x_himmel, steps);
    std::cout << "Himmelblau" << std::endl;
    std::cout << "Minimum ved: " << min_himmel << std::endl;
    std::cout << "Antal skridt: " << steps << std::endl;
    std::cout << "f(x,y) = " << himmelblau(min_himmel) << std::endl;

    return 0;
}