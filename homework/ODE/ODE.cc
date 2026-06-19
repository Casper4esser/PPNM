#include "ODE.h"
#include "vector.h"
#include "matrix.h"
#include <cmath>
#include <algorithm>

namespace pp
{
    std::tuple<pp::vector, pp::vector> rkstep12(
        std::function<pp::vector(double, pp::vector)> f,
        double x,
        pp::vector y,
        double h)
    {
        pp::vector k0 = f(x, y);
        pp::vector k1 = f(x + h / 2.0, y + k0 * (h / 2.0));
        pp::vector yh = y + k1 * h;
        pp::vector dy = (k1 - k0) * h;
        return {yh, dy};
    }

    std::tuple<pp::vector, pp::matrix> driver(
        std::function<pp::vector(double, pp::vector)> f,
        double a, double b,
        pp::vector yinit,
        double h, double acc, double eps)
    {
        double x = a;
        pp::vector y = yinit;

        int max_steps = 500;
        int count = 0;

        pp::vector xlist(max_steps);
        pp::matrix ylist(yinit.size(), max_steps);

        xlist[count] = x;
        ylist[count] = y;
        count++;

        while (true)
        {
            // Hvis vi er færdige returnerer vi og tilpasser størrelsen
            if (x >= b)
            {
                xlist.resize(count);
                ylist.resize(yinit.size(), count);
                return {xlist, ylist};
            }

            if (x + h > b)
            {
                h = b - x;
            }

            auto [yh, dy] = rkstep12(f, x, y, h);

            double tol = (acc + eps * pp::norm(yh)) * std::sqrt(h / (b - a));
            double err = pp::norm(dy);

            if (err <= tol)
            {
                x += h;
                y = yh;

                if (count >= max_steps)
                {
                    max_steps *= 2;
                    xlist.resize(max_steps);
                    ylist.resize(yinit.size(), max_steps);
                }

                xlist[count] = x;
                ylist[count] = y;
                count++;
            }
            
            if (err > 0)
            {
                h *= std::min(std::pow(tol / err, 0.25) * 0.95, 2.0);
            }
            else
            {
                h *= 2.0;
            }
        }
    }
}
