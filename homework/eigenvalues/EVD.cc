#include "vector.h"
#include "matrix.h"
#include "EVD.h"
#include <string>
#include <iostream>
#include <cmath>
#include <functional>
#include <cassert>
#include <cstdlib>

// kommenaterne er til min egen læring og ikke til nogen, som læser koden

namespace pp
{
    void EVD::timesJ(pp::matrix &A, int p, int q, double theta)
    {
        double c = std::cos(theta), s = std::sin(theta);
        for (int i = 0; i < A.rows(); i++)
        {
            double aip = A(i, p), aiq = A(i, q);
            A(i, p) = c * aip - s * aiq;
            A(i, q) = s * aip + c * aiq;
        }
    }

    void EVD::Jtimes(pp::matrix &A, int p, int q, double theta)
    {
        double c = std::cos(theta), s = std::sin(theta);
        for (int j = 0; j < A.cols(); j++)
        {
            double apj = A(p, j), aqj = A(q, j);
            A(p, j) = c * apj + s * aqj;
            A(q, j) = -s * apj + c * aqj;
        }
    }

    // det efter : er "member initializer list" og det giver V og w deres startværdier. 
    // Det er vigtigt at w står før v, fordi vi i struct først initializer w og så V. 
    EVD::EVD(pp::matrix A) : w(A.rows()), V(A.rows(), A.rows()) {
        int n = A.rows();
        V.setid();

        bool changed;
        do {
            changed = false;
            for (int p = 0; p < n - 1; p++) {
                for (int q = p + 1; q < n; q++) {
                    double apq = A(p, q), app = A(p, p), aqq = A(q, q);
                    
                    double theta = 0.5 * std::atan2(2 * apq, aqq - app);
                    double c = std::cos(theta), s = std::sin(theta);
                    
                    double new_app = c * c * app - 2 * s * c * apq + s * s * aqq;
                    double new_aqq = s * s * app + 2 * s * c * apq + c * c * aqq;
                    
                    if (!pp::approx(new_app, app) || !pp::approx(new_aqq, aqq)) {
                        changed = true;
                        timesJ(A, p, q, theta);  // A = A * J
                        Jtimes(A, p, q, -theta); // A = J^T * A
                        timesJ(V, p, q, theta);  // V = V * J 
                    }
                }
            }
        } while (changed); 

        for (int i = 0; i < n; i++) {
            w[i] = A(i, i);
        }
    }

} // namespace pp
