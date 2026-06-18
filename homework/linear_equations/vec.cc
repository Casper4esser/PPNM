// Kommentarerne er for min egen læring og ikke til nogen, som læser koden.

#include "vec.h"
#include <string>
#include <iostream>
#include <cmath>
#include <functional>
#include <cassert>
#include <cstdlib>
#define SELF (*this)
#define FOR(i, V) for (int i = 0; i < V.size(); i++)
#define FOR1(i, A) for (int i = 0; i < A.size1(); i++)
#define FOR2(j, A) for (int j = 0; j < A.size2(); j++)

namespace pp
{
    bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9)
    {
        double diff = std::abs(a - b);
        if (diff <= acc)
            return true;
        double max_ab = std::max(std::abs(a), std::abs(b));
        return diff <= eps * max_ab;
    }

    vector &vector::operator+=(const vector &other)
    {
        FOR(i, SELF)
        {
            SELF[i] += other[i];
        }
        return SELF;
    }

    vector &vector::operator-=(const vector &other)
    {
        FOR(i, SELF)
        {
            SELF[i] -= other[i];
        }
        return SELF;
    }

    vector &vector::operator*=(double s)
    {
        FOR(i, SELF)
        {
            SELF[i] *= s;
        }
        return SELF;
    }

    vector &vector::operator/=(double s)
    {
        FOR(i, SELF)
        {
            SELF[i] /= s;
        }
        return SELF;
    }

    void vector::print(std::string s) const
    {
        std::cout << s;
        // for(auto &x : data) std::cout<<x<<" ";
        for (auto &x : data)
            printf("%10.3g ", x);
        std::cout << "\n";
    }

    vector vector::map(std::function<double(double)> f) const
    {
        vector r(size());
        FOR(i, SELF)
        {
            r.data[i] = f(data[i]);
        }
        return r;
    }

    vector operator+(vector a, const vector &b)
    {
        a += b;
        return a;
    }

    vector operator-(vector a, const vector &b)
    {
        a -= b;
        return a;
    }

    vector operator*(vector a, double s)
    {
        a *= s;
        return a;
    }

    vector operator*(double s, vector a)
    {
        a *= s;
        return a;
    }

    vector operator/(vector a, double s)
    {
        a /= s;
        return a;
    }

    vector operator-(vector a)
    {
        a *= -1;
        return a;
    }

    std::ostream &operator<<(std::ostream &os, const vector &v)
    {
        os << "[";
        FOR(i, v)
        {
            os << v[i];
            if (i < v.size() - 1)
            {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    bool approx(const vector &a, const vector &b, double acc, double eps)
    {
        if (a.size() != b.size())
        {
            return false;
        }

        FOR(i, a)
        {
            if (!approx(a[i], b[i], acc, eps))
            {
                return false;
            }
        }
        return true;
    }

    double dot(const vector &a, const vector &b)
    {
        double result = 0.0;
        FOR(i, a)
        {
            result += a[i] * b[i];
        }
        return result;

        // angiveligt havde en superoptimeret løsning være
        // return std::inner_product(a.data.begin(), a.data.end(), b.data.begin(), 0.0);
    }

    double norm(const vector &a)
    {
        return std::sqrt(dot(a, a)); // dot(v1, v1) virker måske ikke for komplekse tal
    }

    vector generate_random_vector(const int n)
    {
        pp::vector b(n);

        for (int i = 0; i < n; ++i)
        {
            b[i] = (double)rand() / RAND_MAX;
        }

        return b;
    }

    // her begynder matrix-ting

    // lav identitetsmatricen
    void matrix::setid()
    {
        assert(size1() == size2());
        for (int i = 0; i < size1(); i++)
        {
            SELF(i, i) = 1;
            for (int j = i + 1; j < size1(); j++)
            {
                SELF(i, j) = SELF(j, i) = 0;
            }
        }
    }

    matrix matrix::transpose() const
    {
        matrix R(size2(), size1());
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
        for (int i = 0; size2(); i++)
        {
            SELF[i] += B[i];
        }
        return SELF;
    }
    matrix &matrix::operator-=(const matrix &B)
    {
        for (int i = 0; i < size2(); i++)
            SELF[i] -= B[i];
        return *this;
    }
    matrix &matrix::operator*=(const double c)
    {
        for (int i = 0; i < size2(); i++)
            SELF[i] *= c;
        return *this;
    }
    matrix &matrix::operator/=(const double c)
    {
        for (int i = 0; i < size2(); i++)
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
        assert(size1() == size2());
        assert(c >= 0);

        matrix R(size1(), size2());
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
        for (int i = 0; i < size1(); i++)
        {
            for (int j = 0; j < size2(); j++)
            {
                printf("%10.3g ", SELF(i, j));
            }
            printf("\n");
        }
    }

    matrix operator+(matrix A, const matrix &B)
    {
        for (int i = 0; i < A.size2(); i++)
        {
            A[i] += B[i];
        }
        return A;
    }

    matrix operator-(matrix A, const matrix &B)
    {
        for (int i = 0; i < A.size2(); i++)
        {
            A[i] -= B[i];
        }
        return A;
    }

    matrix operator*(const matrix &A, const matrix &B)
    {
        if (A.size2() != B.size1())
        {
            throw std::invalid_argument("size mismatch");
        }
        matrix R(A.size1(), B.size2());
        for (int k = 0; k < A.size2(); k++)
        {
            for (int j = 0; j < B.size2(); j++)
            {
                double Bkj = B(k, j);
                for (int i = 0; i < A.size1(); i++)
                    R(i, j) += A(i, k) * Bkj;
            }
        }
        return R;
    }

    matrix operator*(matrix A, const double c)
    {
        for (auto &col : A.cols)
        {
            col *= c;
        }
        return A;
    }

    matrix operator*(const double c, matrix A)
    {
        for (auto &col : A.cols)
        {
            col *= c;
        }
        return A;
    }

    matrix operator/(matrix A, const double c)
    {
        for (auto &col : A.cols)
        {
            col /= c;
        }
        return A;
    }

    vector operator*(const matrix &A, const vector &v)
    {
        vector r(A.size1());
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
        if (A.size1() != B.size1() || A.size2() != B.size2())
        {
            return false;
        }

        for (int i = 0; i < A.size1(); ++i)
        {
            for (int j = 0; j < A.size2(); ++j)
            {
                if (!approx(A(i, j), B(i, j), acc, eps))
                {
                    return false;
                }
            }
        }
        return true;
    }

    // her starter qr
    qr::qr(const matrix &A)
    {
        int n = A.size1(); // rows
        int m = A.size2(); // cols

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
        int m = R.size2();
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

        for (int i = 0; i < R.size2(); ++i)
        {
            determinant *= R(i, i);
        }

        return determinant;
    }

} // pp