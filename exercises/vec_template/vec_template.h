#pragma once
#include <string>
#include <iostream>
#include <complex>

// når man bruger templates har man ikke en .cc-fil hørende til sin header-fil.
// Jeg kan ikke rigtig finde ud af hvorfor.

template <typename T>
struct vec
{
    T x, y, z;

    vec(T x, T y, T z) : x(x), y(y), z(z) {}
    vec() : vec(T(0), T(0), T(0)) {}
    vec(const vec &) = default;
    vec(vec &&) = default;
    ~vec() = default;
    vec &operator=(const vec &) = default;
    vec &operator=(vec &&) = default;

    vec &operator+=(const vec &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec &operator-=(const vec &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vec &operator*=(T s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    vec &operator/=(T s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    void set(T a, T b, T c)
    {
        x = a;
        y = b;
        z = c;
    }

    void print(const std::string &s = "") const
    {
        std::cout << s << x << " " << y << " " << z << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &os, const vec &v)
    {
        os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        return os;
    }
};

template <typename T>
vec<T> operator+(vec<T> a, const vec<T> &b)
{
    a += b;
    return a;
}

template <typename T>
vec<T> operator-(vec<T> a, const vec<T> &b)
{
    a -= b;
    return a;
}

// Jeg havde først skrevet vec <T> operator*(vec<T> a, T s), men fik en fejl ved 4 * v1, fordi v1 var type vec<double> men 4 var int.
// Derfor troede computeren at T skulle double men så så int. Derfor er der to typenames.
// Dog kan der stadig komme fejl, hvis vi har vektoren [1,2,3] og ganger med 2i, for så er resultatet [2i, 4i, 6i].
// Altså en kompleks vektor, men vec<T> var oprindeligt en double vektor og ikke en complex vektor, og vi lovede at funktionen skulle spytte samme type ud.
// Derfor ændrer vi output-typen til auto og bruger declared type (decltype).
template <typename T, typename U>
auto operator*(const vec<T> &a, U s)
{
    using ResultType = decltype(a.x * s);
    return vec<ResultType>(a.x * s, a.y * s, a.z * s);
}

template <typename T, typename U>
auto operator*(U s, const vec<T> &a)
{
    using ResultType = decltype(s * a.x);
    return vec<ResultType>(a.x * s, a.y * s, a.z * s);
}

template <typename T>
vec<T> operator/(vec<T> a, T s)
{
    a /= s;
    return a;
}

template <typename T>
vec<T> operator-(const vec<T> &a)
{
    return vec<T>(-a.x, -a.y, -a.z);
}

template <typename T>
T dot(const vec<T> &v1, const vec<T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// special-funktion til komplekse tal
// Der er forskellige konventioner om, om man konjugerer den første eller anden vektor.
// Jeg konjugerer den første. Det er vist fysik-konventionen.
template <typename T>
std::complex<T> dot(const vec<std::complex<T>> &v1, const vec<std::complex<T>> &v2)
{
    return std::conj(v1.x) * v2.x +
           std::conj(v1.y) * v2.y +
           std::conj(v1.z) * v2.z;
}

template <typename T>
vec<T> cross(const vec<T> &v1, const vec<T> &v2)
{
    T x_comp = v1.y * v2.z - v1.z * v2.y;
    T y_comp = v1.z * v2.x - v1.x * v2.z;
    T z_comp = v1.x * v2.y - v1.y * v2.x;
    return vec<T>(x_comp, y_comp, z_comp);
}

// Intet anonymt namespace her. Det laver man åbenbart aldrig i en headerfil. Kun i .cc-filer.
// Grunden er, at i en .cc-fil eksisterer funktionen kun i den fil, men en header-fil bruges til at bygge andre .cc-filer,
// så namespace-funktionen bliver kopieret ind i alle de filer, som inkluderer headeren.
template <typename T>
bool approx(const vec<T> &v1, const vec<T> &v2, T acc = 1e-6, T eps = 1e-6)
{
    // lambda-funktion. [] fortæller at det er en lambda-funktion.
    // Den fungerer basically bare som en funktion inde i en funktion. Jeg ved ikke, hvad en lambda-funktion egentlig bør bruges til.
    // I C++ er det åbenbart bare ulovligt at have funktioner i funktioner. Det skal være lambda-funktioner eller en funktion i en class eller struct.
    // En lambda-funktion opretter åbenbart en usynlig class og lægger funktionen ind i den.
    // Hvis man absolut vil have det i et namespace, så kunne man kalde namespacet detail og skrive inline før funktionen.
    auto approx_scalar = [](T a, T b, T acc_val, T eps_val)
    {
        T diff = std::abs(a - b);
        if (diff <= acc_val)
            return true;
        T max_ab = std::max(std::abs(a), std::abs(b));
        return diff <= eps_val * max_ab;
    };

    return approx_scalar(v1.x, v2.x, acc, eps) &&
           approx_scalar(v1.y, v2.y, acc, eps) &&
           approx_scalar(v1.z, v2.z, acc, eps);
}

// kaldenavne
using vecd = vec<double>;
using veci = vec<int>;
using vecc = vec<std::complex<double>>;
