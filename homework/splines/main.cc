#include <iostream>
#include <cmath>
#include "LinearSpline.h"
#include "vector.h"

int main()
{
    pp::vector x_data = pp::linspace(0.0, 9.0, 0.5);

    pp::vector y_data = x_data.map([](double val)
                                   { return std::cos(val); });

    pp::LinearSpline myspline(x_data, y_data);

    std::cout << "# z \t f(z)_interp \t integral\n";
    for (double z = 0; z <= 9; z += 0.1)
    {
        double fz = myspline.eval(z);
        double Fz = myspline.integ(z);
        std::cout << z << " \t " << fz << " \t " << Fz << "\n";
    }

    return 0;
}