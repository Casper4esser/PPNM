#include "vector.h"
#include "matrix.h"
#include "QR.h"

namespace pp
{
    qr::qr(const matrix &A)
    {
        int n = A.rows();
        int m = A.cols();

        if (n < m)
        {
            throw std::invalid_argument("Matrix A skal have n >= m for QR-faktorisering");
        }

        Q = A;
        R = matrix(m, m);

        for (int i = 0; i < m; ++i)
        {
            R(i, i) = norm(Q[i]);

            Q[i] = Q[i] / R(i, i);

            for (int j = i + 1; j < m; ++j)
            {
                R(i, j) = dot(Q[i], Q[j]);
                Q[j] = Q[j] - Q[i] * R(i, j);
            }
        }
    }

    vector qr::solve(const pp::vector &b) const
    {
        int m = R.cols();
        vector x(m);

        for (int i = 0; i < m; ++i)
        {
            x[i] = dot(Q[i], b);
        }

        // back substitution fra dokumentet
        for (int i = m - 1; i >= 0; --i)
        {
            double sum = 0.0;

            for (int k = i + 1; k < m; ++k)
            {
                sum += R(i, k) * x[k];
            }
            // isoler x[i]
            x[i] = (x[i] - sum) / R(i, i);
        }
        return x;
    }

    double qr::det() const
    {
        double determinant = 1.0;

        for (int i = 0; i < R.cols(); ++i)
        {
            determinant *= R(i, i);
        }

        return determinant;
    }
}
