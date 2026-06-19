#include "vector.h"
#include <string>
#include <iostream>
#include <cmath>
#include <functional>
#include <cassert>
#include <cstdlib>
#define SELF (*this)
#define FOR(i, V) for (int i = 0; i < V.size(); i++)

namespace pp
{
    bool approx(double a, double b, double acc, double eps)
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
}