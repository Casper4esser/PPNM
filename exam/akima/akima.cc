#include "akima.h"
#include <cmath>
#include <stdexcept>
#include <cassert>

namespace pp
{
    Akima::Akima(const pp::vector &x_in, const pp::vector &y_in) : x(x_in), y(y_in)
    {
        int n = x_in.size();
        assert(n > 2 && "Der skal være mindst 3 punkter");
        assert(x_in.size() == y_in.size() && "x og y skal have samme længde");

        b.resize(n);
        c.resize(n - 1);
        d.resize(n - 1);

        pp::vector p(n - 1);
        pp::vector h(n - 1);

        for (int i = 0; i < n - 1; i++)
        {
            h[i] = x[i + 1] - x[i];
            assert(h[i] > 0 && "x-værdierne skal være strengt voksende");
            p[i] = (y[i + 1] - y[i]) / h[i];
        }

        b[0] = p[0];
        b[1] = (p[0] + p[1]) / 2.0;
        b[n - 1] = p[n - 2];
        b[n - 2] = (p[n - 3] + p[n - 2]) / 2.0;

        for (int i = 2; i < n - 2; i++)
        {
            double w1 = std::abs(p[i + 1] - p[i]);
            double w2 = std::abs(p[i - 1] - p[i - 2]);

            if (w1 + w2 < 1e-8)  // if(w1 + w2 == 0), men med en lille tolerance til afrundingsfejl
            {
                b[i] = (p[i - 1] + p[i]) / 2.0;
            }
            else
            {
                b[i] = (w1 * p[i - 1] + w2 * p[i]) / (w1 + w2);
            }
        }

        // b = S' så jeg kan bruge b til at regne c og d
        for (int i = 0; i < n - 1; i++)
        {
            c[i] = (3.0 * p[i] - 2.0 * b[i] - b[i + 1]) / h[i];
            d[i] = (b[i + 1] + b[i] - 2.0 * p[i]) / (h[i] * h[i]);
        }
    }

    int Akima::binsearch(double z) const
    {
        assert(z >= x[0] && z <= x[x.size() - 1]);
        int i = 0;
        int j = x.size() - 1;
        while (j - i > 1)
        {
            int mid = (i + j) / 2;
            if (z > x[mid])
            {
                i = mid;
            }
            else
            {
                j = mid;
            }
        }
        return i;
    }

    double Akima::eval(double z) const
    {
        int n = x.size();
        assert(z >= x[0] && z <= x[n - 1] && "z er uden for interpolationsintervallet");

        int i = binsearch(z);

        double h_val = z - x[i];
        return y[i] + h_val * (b[i] + h_val * (c[i] + h_val * d[i])); // polynomiet er omskrevet for at minimere antallet af gange-operationer.
                                                                      // Dette blev foreslået af Google Gemini, men er også gjort i eksemplerne i bogen
    }
} // namespace pp