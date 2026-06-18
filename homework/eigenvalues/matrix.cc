// Kommentarerne er for min egen læring og ikke til nogen, som læser koden.

#include "vector.h"
#include "matrix.h"
#include <string>
#include <iostream>
#include <cmath>
#include <functional>
#include <cassert>
#include <cstdlib>
#define SELF (*this)
#define FOR(i, V) for (int i = 0; i < V.size(); i++)
#define FOR1(i, A) for (int i = 0; i < A.rows(); i++)
#define FOR2(j, A) for (int j = 0; j < A.cols(); j++)

namespace pp{
    // lav identitetsmatricen
    void matrix::setid()
    {
        assert(rows() == cols());
        for (int i = 0; i < rows(); i++)
        {
            SELF(i, i) = 1;
            for (int j = i + 1; j < rows(); j++)
            {
                SELF(i, j) = SELF(j, i) = 0;
            }
        }
    }

    matrix matrix::transpose() const
    {
        matrix R(cols(), rows());
        FOR1(i, SELF)
        {
            FOR2(j, SELF)
            {
                R(j, i) = SELF(i, j);
            }
        }
        return R;
    }

    matrix &matrix::operator+=(const matrix &B)
    {
        for (int i = 0; cols(); i++)
        {
            SELF[i] += B[i];
        }
        return SELF;
    }
    matrix &matrix::operator-=(const matrix &B)
    {
        for (int i = 0; i < cols(); i++)
            SELF[i] -= B[i];
        return *this;
    }
    matrix &matrix::operator*=(const double c)
    {
        for (int i = 0; i < cols(); i++)
            SELF[i] *= c;
        return *this;
    }
    matrix &matrix::operator/=(const double c)
    {
        for (int i = 0; i < cols(); i++)
            SELF[i] /= c;
        return *this;
    }

    matrix &matrix::operator*=(const matrix &B)
    {
        *this = *this * B;
        return *this;
    }

    matrix matrix::operator^(int c)
    {
        assert(rows() == cols());
        assert(c >= 0);

        matrix R(rows(), cols());
        R.setid();

        for (int i = 0; i < c; i++)
        {
            R *= (*this);
        }
        return R;
    }

    void matrix::print(std::string s) const
    {
        printf("%s\n", s.c_str());
        for (int i = 0; i < rows(); i++)
        {
            for (int j = 0; j < cols(); j++)
            {
                printf("%10.3g ", SELF(i, j));
            }
            printf("\n");
        }
    }

    matrix operator+(matrix A, const matrix &B)
    {
        for (int i = 0; i < A.cols(); i++)
        {
            A[i] += B[i];
        }
        return A;
    }

    matrix operator-(matrix A, const matrix &B)
    {
        for (int i = 0; i < A.cols(); i++)
        {
            A[i] -= B[i];
        }
        return A;
    }

    matrix operator*(const matrix &A, const matrix &B)
    {
        if (A.cols() != B.rows())
        {
            throw std::invalid_argument("size mismatch");
        }
        matrix R(A.rows(), B.cols());
        for (int k = 0; k < A.cols(); k++)
        {
            for (int j = 0; j < B.cols(); j++)
            {
                double Bkj = B(k, j);
                for (int i = 0; i < A.rows(); i++)
                    R(i, j) += A(i, k) * Bkj;
            }
        }
        return R;
    }

    matrix operator*(matrix A, const double c)
    {
        for (auto &col : A.columns)
        {
            col *= c;
        }
        return A;
    }

    matrix operator*(const double c, matrix A)
    {
        for (auto &col : A.columns)
        {
            col *= c;
        }
        return A;
    }

    matrix operator/(matrix A, const double c)
    {
        for (auto &col : A.columns)
        {
            col /= c;
        }
        return A;
    }

    vector operator*(const matrix &A, const vector &v)
    {
        vector r(A.rows());
        FOR2(j, A)
        {
            double vj = v[j];
            FOR1(i, A)
            {
                r[i] += A(i, j) * vj;
            }
        }
        return r;
    }

    matrix generate_random_matrix(const int n, const int m)
    {
        pp::matrix A(n, m);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                A(i, j) = (double)rand() / RAND_MAX;
            }
        }
        return A;
    }

    matrix eye(int n)
    {
        matrix A(n, n);
        A.setid();
        return A;
    }

    bool approx(const matrix &A, const matrix &B, double acc, double eps)
    {
        if (A.rows() != B.rows() || A.cols() != B.cols())
        {
            return false;
        }

        for (int i = 0; i < A.rows(); ++i)
        {
            for (int j = 0; j < A.cols(); ++j)
            {
                if (!approx(A(i, j), B(i, j), acc, eps))
                {
                    return false;
                }
            }
        }
        return true;
    }
}